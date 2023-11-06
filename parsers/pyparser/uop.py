from pyparser.basicparsers import stripped,alternate,strp

uops=['+','-']

unaryop=stripped(alternate(*[strp(uop) for uop in uops]))