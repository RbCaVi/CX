from pyparser.parser import Parser,parse,called
from pyparser.basicparsers import stripped,transform

uops=['+','-']

@stripped
def unaryop():
class UnaryOpParser():
	def parse(self,state):
		for i,uop in enumerate(uops):
			if state.s.startswith(uop):
				state.value=uop
				state.i=i
				state.length=len(uop)
				return True
		return False
	def backtrack(self,state):
		i=state.i
		while i<uops.length:
			uop=uops[i]
			if state.s.startswith(uop):
				state.value=uop
				state.i=i
				state.length=len(uop)
				return True
			i+=1
		return False
	return Parser(parseuop,backtrackuop)