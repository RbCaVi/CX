def getexpect:
  "expect"+
  if
    (.equal//true)
  then
    ""
  else
    "not"
  end+
  "("+.check+","+(.value|tostring)+")";

def escape:sub("\"";"\\\"");

def maketest:
  "std::cout << \"testing "+(getexpect|escape)+"\" << std::endl;",
	"testresult="+getexpect+";",
  "std::cout << (testresult?\"passed\":\"failed\") << std::endl;",
  "if(!testresult){",
  "\tstd::cout << \"expected "+if
    (.equal//true)
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
  end;

($i|tonumber) as $inum|.[$inum].tests[]|"\t"+maketest