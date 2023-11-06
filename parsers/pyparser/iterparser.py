class Parser:
	def parse(self,state):
		yield from ()
	def getvalue(self,state):
		try:
			return state.value
		except AttributeException:
			return None

class AlternateParser(Parser):
	def __init__(self,*parsers):
		self.parsers=parsers
	def parse(self,state):
		for i,p in enumerate(parsers):
			for state in p.parse(state):
				yield i,state

import itertools

class ConcatParser(Parser):
	def __init__(self,*parsers):
		self.parsers=parsers
	def parse(self,state):
		states=[[state]]
		for p in parsers:
			def f(ss):
				for s in p.parse(ss[-1]):
					yield ss+[s]
			states=itertools.chain.from_iterable(map(f,states))
		def f2(ss):

			ParserState(ss[-1])
		return map(f2,states)
	def getvalue(self,state):
		return map(f,parser.getvalue(state))

class TransformParser(Parser):
	def __init__(self,parser,f):
		self.parser=parser
		self.f=f
	def parse(self,state):
		return parser.parse(state)
	def getvalue(self,state):
		return map(f,parser.getvalue(state))
