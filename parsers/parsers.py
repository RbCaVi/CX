def getuop(s):
    s=s.lstrip()
    for uop in uops:
        if s.startswith(uop):
            return [s[len(uop):],uop]
    return [s,None]

def getbop(s):
    s=s.lstrip()
    for bop in bops:
        if s.startswith(bop[0]):
            return s[len(bop[0]):],bop
    return s,None

letters='qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_'
numbers='0123456789'

def getint(s):
    s=s.lstrip()
    i=0
    while i<len(s) and s[i] in numbers:
        i=i+1
    if i==0:
        return s,None
    return s[i:],int(s[:i])

def getword(s):
    s=s.lstrip()
    i=0
    if i<len(s) and s[i] in letters:
        i=i+1
    else:
        return s,None
    while i<len(s) and s[i] in letters+numbers:
        i=i+1
    if i==0:
        return s,None
    return s[i:],s[:i]

def alternate(*fs):
    def getalternated(s):
        starts=s
        for i,f in enumerate(fs):
            s,v=f(s)
            if v is not None:
                return s,[i,v]
        return starts,None
    return getalternated

def concat(*fs):
    def getconcated(s):
        starts=s
        out=[]
        for f in fs:
            s,v=f(s)
            if v is None:
                return starts,None
            out.append(v)
        return s,out
    return getconcated

def repeat(f):
    def getrepeated(s):
        out=[]
        while True:
            s,v=f(s)
            if v is None:
                break
            out.append(v)
        return s,out
    return getrepeated

def transform(f,transformer):
    def gettransformed(s):
        s,v=f(s)
        if v is None:
            return s,v
        return s,transformer(v)
    return gettransformed

def transformvalue(v):
    if v[0]==2:
        return v[1][1]
    return v

getvalue=transform(getalternate(getint,getword,concat(getstr('('),sep(',',getexpr),getstr(')'))),transformvalue)

def getstr(pattern):
    def gets(s):
        s=s.lstrip()
        if s.startswith(pattern):
            return s[len(pattern):],pattern
        return s,None
    return gets

def sep(sep,f):
    def getsepd(s):
        starts=s
        out=[]
        while True:
            s,v=f(s)
            if v is None:
                return s,out
            out.append(v)
            s=s.lstrip()
            if not s.startswith(sep):
                return s,out
            s=s[len(sep):]
    return getsepd

#while true
#   try to parse unary operators (/casts?)
#   if value
#       push to out with uops
#   else
#       error
#   if binary operator
#       while top.prec>op.prec||(top.prec==op.prec and op.assoc==LEFT)
#           out.push(opstack.pop())
#       push to opstack
#       cycle
#   if func args
#       funccall
#       cycle
#   if index
#       index
#       cycle
#   if end of expr
#       end
#out.push(opstack.pop())

def getexpr(s):
    starts=s
    out=[]
    ops=[]
    while True:
        s,uops=getrepeat(getuop)(s)
        s,value=getvalue(s)
        if value is None:
            return [starts,None]
        for uop in uops:
            value=[uop,value]
        s,things=repeat(alternate(concat(getstr('.'),getword),concat(getstr('('),sep(',',getexpr),getstr(')')),concat(getstr('['),sep(',',getexpr),getstr(']'))))(s)
        for thing in things:
            tid,thing=thing
            if tid==0:
                # attribute access
                _,attr=thing
                value=['.',value,attr]
            if tid==1:
                # function call
                _,args,_=thing
                value=['()',value,*args]
            if tid==2:
                # array index
                _,idxs,_=thing
                value=['[]',value,*idxs]
        out.append(value)
        s,bop=getbop(s)
        if bop is not None:
            while len(ops)>0 and (ops[-1][1]>bop[1] or (ops[-1][1]==bop[1] and bop[2]==LEFT)):
                v2=out.pop()
                v1=out.pop()
                out.append([ops.pop(),v1,v2])
            ops.append(bop)
            continue
        break
    while len(ops)>0:
        v2=out.pop()
        v1=out.pop()
        out.append([ops.pop(),v1,v2])
    return [s,out[0]]

uops=['-','+','*']
LEFT=0
RIGHT=1
bops=[['**',1,RIGHT],['+',0,LEFT],['*',1,LEFT]]
getexpr('(a**b)**c')