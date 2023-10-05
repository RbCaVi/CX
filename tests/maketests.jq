def getexpect:
  "expect"+
  if
    if .equal==false then false else true end
  then
    ""
  else
    "not"
  end+
  "("+.check+","+(.value|tostring)+")";

def escape:sub("\"";"\\\"");

def processtest:
  if type=="object" then
    [][]
  else
    .
  end;


def maketest:
  processtest|
  "{",
  "\t"+(
    "std::cout << \"testing "+(getexpect|escape)+"\" << std::endl;",
  	"testresult="+getexpect+";",
    "std::cout << (testresult?\"passed\":\"failed\") << std::endl;",
    "if(!testresult){",
    "\tstd::cout << \"expected "+if
      if .equal==false then false else true end
    then
      ""
    else
      "not"
    end+"\" << "+(.value|tostring)+" << \", got \" << "+.check+" << std::endl;",
    "}",
    "finalresult=finalresult&&testresult;",
    if
      .tests
    then
      "if(testresult){",
      "\t"+(.tests[]|maketest),
      "}"
    else
      [][]
    end
  ),
  "}";

($i|tonumber) as $inum|.[$inum].tests[]|"\t"+maketest