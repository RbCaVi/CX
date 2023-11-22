class Parser:
	def parse(self,state):
		yield from ()
	def getvalue(self,state):
		try:
			return state.value
		except AttributeError:
			return None
	def __repr__(self):
		return f'{self.__class__.__name__}()'
	def __add__(self,other):
		if type(other) in [str,list,tuple]:
			other=StrParser(other)
		return concat(self,other)
	def __radd__(self,other):
		if type(other) in [str,list,tuple]:
			other=StrParser(other)
		return concat(other,self)
	def __or__(self,other):
		if type(other) in [str,list,tuple]:
			other=StrParser(other)
		return alternate(self,other)
	def __ror__(self,other):
		if type(other) in [str,list,tuple]:
			other=StrParser(other)
		return alternate(other,self)
	def __pos__(self):
		return atomic(self)

class ParserState:
	def __init__(self,s,value=None):
		if type(s)==str:
			self.s=s
		else:
			self.s=s.s
		if value is not None:
			self.value=value

	def advance(self,length):
		try:
			return ParserState(self.s[length:],self.value)
		except AttributeError:
			return ParserState(self.s[length:])
	def __repr__(self):
		try:
			return f'ParserState({repr(self.s)},{repr(self.value)})'
		except AttributeError:
			return f'ParserState({repr(self.s)})'

class AlternateParser(Parser):
	def __init__(self,*parsers):
		self.parsers=parsers
	def parse(self,state):
		for i,p in enumerate(self.parsers):
			for pstate in p.parse(state):
				print(pstate)
				out=ParserState(pstate.s)
				out.state=pstate
				out.i=i
				yield out
	def getvalue(self,state):
		return state.i,self.parsers[state.i].getvalue(state.state)
	def __repr__(self):
		return f'{self.__class__.__name__}({",".join(map(repr,self.parsers))})'


import itertools
import functools

class ConcatParser(Parser):
	def __init__(self,*parsers):
		self.parsers=parsers
	def parse(self,state):
		states=[[state]] # list of lists of states
		f=lambda p,ss:[ss+[s] for s in p.parse(ss[-1])]
		for p in self.parsers:
			states=itertools.chain.from_iterable(map(functools.partial(f,p),states))
		def f2(ss):
			s=ParserState(ss[-1].s)
			s.states=ss
			return s
		return map(f2,states)
	def getvalue(self,state):
		return [p.getvalue(s) for p,s in zip(self.parsers,state.states[1:])]
	def __repr__(self):
		return f'{self.__class__.__name__}({",".join(map(repr,self.parsers))})'

class TransformParser(Parser):
	def __init__(self,parser,f):
		self.parser=parser
		self.f=f
	def parse(self,state):
		return self.parser.parse(state)
	def getvalue(self,state):
		return map(f,self.parser.getvalue(state))
	def __repr__(self):
		return f'{self.__class__.__name__}({repr(self.parser)},{repr(self.f)})'

def flatten(s):
	if type(s)==str:
		return s
	try:
		return sum([flatten(x) for x in s],[])
	except TypeError:
		return s

class StrParser(Parser):
	def __init__(self,*ss):
		self.ss=flatten(ss)
	def parse(self,state):
		yield from map(lambda s:ParserState(state,s).advance(len(s)),filter(state.s.startswith,self.ss))
	def __repr__(self):
		return f'{self.__class__.__name__}({repr(self.ss)})'

def flatten2(s):
	if type(s)==str and len(s)==1:
		return s
	try:
		return [flatten2(x) for x in s]
	except TypeError:
		return s

class CharsetParser(Parser):
	def __init__(self,*ss):
		self.ss=flatten2(ss)
	def parse(self,state):
		yield from map(lambda s:ParserState(state,s).advance(len(s)),filter(state.s.startswith,self.ss))
	def __repr__(self):
		return f'{self.__class__.__name__}({repr(self.ss)})'

class ComposedParser(Parser):
	def parse(self,state):
		return self.parser.parse(state)
	def getvalue(self,state):
		return self.parser.getvalue(state)
	def __repr__(self):
		return f'{self.__class__.__name__}({repr(self.parser)})'

class RepeatParser(ComposedParser):
	def __init__(self,parser):
		self.p=parser
		self.parser=optional(parser+self)
	def getvalue(self,state):
		t,v=self.parser.getvalue(state)
		if t==0:
			return []
		else:
			v,vs=v
			return [v]+vs
	def __repr__(self):
		return f'{self.__class__.__name__}({repr(self.p)})'

class EmptyParser(Parser):
	def parse(self,state):
		yield state.advance(0)
	def getvalue(self,state):
		return None
	def __repr__(self):
		return f'{self.__class__.__name__}()'

class OptionalParser(ComposedParser):
	def __init__(self,parser):
		self.p=parser
		self.parser=alternate(parser,empty)
	def __repr__(self):
		return f'{self.__class__.__name__}({repr(self.p)})'

class AtomicParser(Parser):
	def __init__(self,parser):
		self.parser=parser
	def parse(self,state):
		return self.parser.parse(state)
	def __repr__(self):
		return f'{self.__class__.__name__}({repr(self.parser)})'

StrsParser=StrParser
StrSetParser=StrParser

empty=EmptyParser()
concat=ConcatParser
alternate=AlternateParser
repeat=RepeatParser
optional=OptionalParser
transform=TransformParser
atomic=AtomicParser
posessive=AtomicParser

class ExprParser(ComposedParser):
	def __init__(self):
		pass
		#valuep=
		#self.parser=