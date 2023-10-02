tests=$1

if test -z "$tests"; then
	echo "need tests"
	exit 1
fi

length=$(cat "$tests"|jq 'length')

rm -rf temp
mkdir temp

for ((i=0;i<length;i++)); do
	echo $i
	parserfile=$(cat "$tests"|jq --arg i "${i}" -r '($i|tonumber) as $inum|.[$inum]|.parserfile//(.parser|ascii_downcase)')

	parser=$(cat "$tests"|jq --arg i "${i}" -r '($i|tonumber) as $inum|.[$inum].parser')
	start=$(cat "$tests"|jq --arg i "${i}" -r '($i|tonumber) as $inum|.[$inum].start//0')
	input=$(cat "$tests"|jq --arg i "${i}" -r '($i|tonumber) as $inum|.[$inum].input')
	name=$(cat "$tests"|jq --arg i "${i}" -r '($i|tonumber) as $inum|.[$inum].name')

	echo "Doing $name"

	cat > temp/test"${name}".c++ << EOF
#include <iostream>
#include <list>

#include "../../buffer.h++"
#include "../../parsers/${parserfile}.h++"

template<class T>
std::ostream &operator<<(std::ostream &os, std::list<T> l) {
	os << "[";
	if(l.size()==0){
		os << "]";
	}
	auto it=l.begin();
	auto end=l.end();

	for(T value:l){
		os << std::endl << "  " << value;
	}

  return os;
}

std::ostream &operator<<(std::ostream &os, bool b) {
	os << (b?"true":"false");

  return os;
}

template<class T,class T2> requires std::equality_comparable_with<T2,T>
bool expect(T a,T2 b){
	return a==b;
}

template<class T,class T2> requires std::equality_comparable_with<T2,T>
bool expectnot(T a,T2 b){
	return a!=b;
}

int main(int,char**){
	Buffer *s=new Buffer("${input}");
	${parser} *p=new ${parser}(s);
	bool r=p->run(${start});
	bool testresult,finalresult=true;
$(cat "$tests"|jq --arg i "${i}" -rf maketests.jq)
	if(finalresult){
		return 0;
	}else{
		return 1;
	}
}
EOF

	g++ -std=c++20 -o temp/test"${name}" temp/test"${name}".c++ ../buffer.o ../whitespace.o ../parsers/parser.o ../parsers/${parserfile}.o
	if temp/test"${name}">temp/test${name}-out; then
   	echo "succeeded"
		rm temp/test"${name}".c++ temp/test"${name}" temp/test${name}-out
	fi
done

if [ -z "$(ls -A temp)" ]; then
	echo "all tests succeeded"
	rm -r temp
else
	echo "some tests failed"
fi
