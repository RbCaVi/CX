from basicparsers import ComposedParser,alternate,concat,empty

def RepeatParser(ComposedParser):
	def __init__(self,p):
		self.p=alternate(concat(p,self),empty)