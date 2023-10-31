import pyparser.parser

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

strip=charset(' \t\n\r\f\v')

def concat(*parsers):
	def parseconcated(state):
		state.states=[]
		parsestate=state
		for parser in parsers:
			parsed,parsestate=parse(parser,parsestate)
			if not parsed:
				return False
			state.states.append(parsestate)
		return True
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
			else:
				i-=1
			if i<0:
				return False
			if i==len(state.states):
				return True
	def getvalueconcated(state):
		out=[]
		for parser,state in zip(parsers,state.states):
			out.append(parser.getvalue(state))
		return out
	return Parser(parseconcated,backtrackconcated,getvalueconcated)

def stripped(parser):
	return transform(concat(strip,parser),operator.itemgetter(1))