from pyparser.parser import Parser,parse,ParserState
import operator

def charset(chars):
	def parsecharset(state):
		s=''
		for char in state.s:
			if char not in chars:
				break
			s+=char
		state.value=s
		state.length=len(s)
		return True
	def backtrackcharset(state):
		if len(state.value)==0:
			return False
		state.value=state.value[:-1]
		state.length=len(s)
		return True
	return Parser(parsecharset,backtrackcharset)

def genericword(startchars,chars):
	def parsecharset(state):
		s=''
		it=iter(state.s)
		char=next(it)
		if char not in startchars:
			return False
		s+=char
		for char in state.s:
			if char not in chars:
				break
			s+=char
		state.value=s
		state.length=len(s)
		return True
	def backtrackcharset(state):
		if len(state.value)==0:
			return False
		state.value=state.value[:-1]
		state.length=len(s)
		return True
	return Parser(parsecharset,backtrackcharset)

letters=[chr(ord('a')+x) for x in range(26)]+[chr(ord('A')+x) for x in range(26)]
numbers=[chr(ord('0')+x) for x in range(10)]
spaces=' \t\n\r\f\v'

word=genericword(letters,letters+numbers)

strip=charset(spaces)

def concat(*parsers):
	def parseconcated(state):
		state.states=[ParserState(state)]+([None]*(len(parsers)-1))
		i=0
		forwards=True
		while True:
			parsestate=state.states[i]
			parser=parsers[i]
			state.length-=parsestate.length
			if forwards:
				parsed=parser.parse(parsestate)
			else:
				parsed=parser.backtrack(parsestate)
			forwards=parsed
			if forwards:
				state.length+=parsestate.length
				i+=1
				if i==len(state.states):
					return True
				state.states[i]=ParserState(parsestate)
			else:
				i-=1
				if i<0:
					return False
	def backtrackconcated(state):
		i=len(state.states)-1
		forwards=False
		while True:
			parsestate=state.states[i]
			parser=parsers[i]
			state.length-=parsestate.length
			if forwards:
				parsed=parser.parse(parsestate)
			else:
				parsed=parser.backtrack(parsestate)
			forwards=parsed
			if forwards:
				state.length+=parsestate.length
				i+=1
				if i==len(state.states):
					return True
				state.states[i]=ParserState(parsestate)
			else:
				i-=1
				if i<0:
					return False
	def getvalueconcated(state):
		out=[]
		for parser,state in zip(parsers,state.states):
			out.append(parser.getvalue(state))
		return out
	return Parser(parseconcated,backtrackconcated,getvalueconcated)

def alternate(*parsers):
	def parsealternated(state):
		parsestate=state
		for i,parser in enumerate(parsers):
			parsed,parsestate=parse(parser,state)
			if parsed:
				state.state=parsestate
				state.i=i
				return True
		return False
	def backtrackalternated(state):
		i=state.i
		backed=parsers[i].backtrack(state.state)
		if backed:
			return True
		while True:
			parsestate=state.states[i]
			parser=parsers[i]
			parsed,parsestate=parse(parser,state)
			if parsed:
				state.state=parsestate
				state.i=i
				return True
			i+=1
			if i>=len(parsers):
				return False
	def getvaluealternated(state):
		return parsers[state.i].getvalue(state.state)
	return Parser(parsealternated,backtrackalternated,getvaluealternated)

def transform(parser,f):
	def getvaluetransformed(state):
		return f(parser.getvalue(state))
	return Parser(parser.parse,parser.backtrack,getvaluetransformed)

def stripped(parser):
	return transform(concat(strip,parser),operator.itemgetter(1))