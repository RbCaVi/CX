#from pyparser.parser import parse
#from pyparser.basicparsers import parse
#from pyparser.uop import unaryop

#result,state=parse(unaryop,'*')
#result,state=parse(unaryop,'8')

from pyparser.iterparser import StrSetParser,ParserState,ConcatParser,AlternateParser

def test(p,ss):
	for s in ss:
		print(f'parsing {repr(s)} with {repr(p)}')
		it=p.parse(ParserState(s))
		for x in it:
			print('value',repr(p.getvalue(x)))
			print('state',repr(x))
		print()


p=StrSetParser(['6','5','65'])

#test(p,['6','65','5'])

p1=StrSetParser(['7'])
p2=StrSetParser(['5'])
p=ConcatParser(p1,p2)

test(p,['75','7','5','77','55'])

p=p1+p2

test(p,['75','7','5','77','55'])

p=AlternateParser(p1,p2)

test(p,['75','7','5'])

p=p1|p2

test(p,['75','7','5'])