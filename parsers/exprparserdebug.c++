#include <iostream>

#include "exprparser.h++"

std::ostream &operator<<(std::ostream &os, ExprType t) {
	switch(t){
		case ExprType::VALUE:
			os << "VALUE";
			break;
		case ExprType::EXPR:
			os << "EXPR";
			break;
		default:
			os << "<Unknown ExprType>";
			break;
	}

  return os;
}