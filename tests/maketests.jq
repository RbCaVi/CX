def getexpect:
  "expect"+
  if
    if .equal==false then false else true end
  then
    ""
  else
    "not"
  end+
  "(("+.check+"),("+(.value|tostring)+"))";

def escape:sub("\"";"\\\"");

def processtest:
  if .check|type=="object" then
    ("("+(.check.base//"base")+")") as $base|
    (.check.parts[0]|sub("@";$base)) as $newbase|
    if .check.parts|length<=1 then
      {
        check:$newbase,
        value:"(void*)NULL",
        equal:false,
        tests:.tests,
        setbase:.setbase
      }
    else
      {
        check:$newbase,
        value:"(void*)NULL",
        equal:false,
        tests:[.check.base=$newbase|.check.parts|=.[1:]|processtest],
      }
    end
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
    end+"\" << ("+(.value|tostring)+") << \", got \" << ("+.check+") << std::endl;",
    "}",
    "finalresult=finalresult&&testresult;",
    if .setbase then
      if .setbase==true then
        "auto tempbase=("+.check+");"
      else
        "auto tempbase=("+.setbase+");"
      end,
      "auto base=tempbase;"
    else
      [][]
    end,
    if .tests then
      "if(testresult){",
      "\t"+(.tests[]|maketest),
      "}"
    else
      [][]
    end
  ),
  "}";

($i|tonumber) as $inum|.[$inum].tests[]|"\t"+maketest
#($i|tonumber) as $inum|.[$inum].tests[]|processtest