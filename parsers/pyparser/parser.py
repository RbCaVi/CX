def called(f):
	return f()

class Parser:
	def parse(self,state):
		return False

	def backtrack(self,state):
		return False

	def getvalue(self,state):
		try:
			return state.value
		except AttributeException:
			return None

class ParserState:
	def __init__(self,s):
		if type(s)==str:
			self.s=s
		else:
			self.s=s.s[s.length:]
		self.length=0

def parse(parser,s):
	state=ParserState(s)
	result=parser.parse(state)
	return result,state

def parseback(parser,state,back):
	state=ParserState(s)
	result=parser.parse(state)
	return result,state
