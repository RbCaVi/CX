from pyparser.parser import parse
from pyparser.basicparsers import parse
from pyparser.uop import unaryop

result,state=parse(unaryop,'*')
result,state=parse(unaryop,'8')