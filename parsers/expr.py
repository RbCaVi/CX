value=ComposedParser()

class ExprParser(TransformParser):
	def __init__(self):
		valuep=('('+self+')')|value
		value2=uop[:]+valuep+(('('+self+')') or ('['+self+']') or ('.'+ident))
		self.parser=value2+(bop+value2)[:]

	def f(value):
		return value

expr=ExprParser()

genericword=lambda startchars,chars:transform(charset(startchars)+charset(chars)[:],lambda x:[x[0]]+x[1])

letters=[chr(ord('a')+x) for x in range(26)]+[chr(ord('A')+x) for x in range(26)]
numbers=[chr(ord('0')+x) for x in range(10)]
spaces=' \t\n\r\f\v'

word=atomic(genericword(letters,letters+numbers))

def strip(parser):
	return transform(charset(spaces)[:]+parser,operator.itemgetter(1))

intp=atomic(charset(numbers)[:])

value.parser=strip(intp)|strip(word)