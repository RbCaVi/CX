def defaultbacktrack(state):
	return False

def defaultgetvalue(state):
	try:
		return state.value
	except AttributeException:
		return None

class Parser:
	def __init__(self,parse,backtrack=defaultbacktrack,getvalue=defaultgetvalue):
		self.parse=parse
		self.backtrack=backtrack
		self.getvalue=getvalue

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
