from pyparser.parser import Parser,parse,ParserState
import operator

class CharsetParser(Parser):
	def __init__(chars):
		self.chars=chars
	def parse(self,state):
		char=state.s[0]
		if char not in startchars:
			return False
		state.value=char
		state.length=1
		return True

genericword=lambda startchars,chars:transform(concat(charset(startchars),repeat(charset(chars))),lambda x:[x[0]]+x[1])

letters=[chr(ord('a')+x) for x in range(26)]+[chr(ord('A')+x) for x in range(26)]
numbers=[chr(ord('0')+x) for x in range(10)]
spaces=' \t\n\r\f\v'

word=genericword(letters,letters+numbers)

class ConcatParser(Parser):
	def __init__(self,*parsers):
		self.parsers=parsers
	def parse(self,state):
		state.states=[ParserState(state)]+([None]*(len(self.parsers)-1))
		i=0
		forwards=True
		while True:
			parsestate=state.states[i]
			parser=self.parsers[i]
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
	def backtrack(self,state):
		i=len(state.states)-1
		forwards=False
		while True:
			parsestate=state.states[i]
			parser=self.parsers[i]
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
	def getvalue(self,state):
		out=[]
		for parser,state in zip(self.parsers,state.states):
			out.append(parser.getvalue(state))
		return out
	return Parser(parseconcated,backtrackconcated,getvalueconcated)

class AlternatedParser(Parser):
	def __init__(self,*parsers):
		self.parsers=parsers
	def parse(self,state):
		parsestate=state
		for i,parser in enumerate(self.parsers):
			parsed,parsestate=parse(parser,state)
			if parsed:
				state.state=parsestate
				state.i=i
				return True
		return False
	def backtrack(self,state):
		i=state.i
		backed=self.parsers[i].backtrack(state.state)
		if backed:
			return True
		while True:
			parsestate=state.states[i]
			parser=self.parsers[i]
			parsed,parsestate=parse(parser,state)
			if parsed:
				state.state=parsestate
				state.i=i
				return True
			i+=1
			if i>=len(self.parsers):
				return False
	def getvalue(self,state):
		return state.i,self.parsers[state.i].getvalue(state.state)

def transform(parser,f):
	class TransformedParser(parser):
		def getvalue(self,state):
			return f(super().getvalue(state))
	return TransformedParser

def stripped(parser):
	return transform(concat(repeat(charset(spaces)),parser),operator.itemgetter(1))

class ConcatParser(Parser):
	def parse(self,state):
		return self.p.parse(state)
	def backtrack(self,state):
		return self.p.backtrack(state)
	def getvalue(self,state):
		return self.p.getvalue(state)