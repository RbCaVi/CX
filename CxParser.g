grammar CxParser;
options { tokenVocab=CxLexer; }

program : expr EOF;
//program : globalstmts EOF;

//globalstmts : globalstmt*;

//globalstmt : funcdef;

//funcdef : 'fn' type name '(' args ')' (codeblock|expr);

//args : arg (',' arg)* ','?;

//arg : type? name?;

//codeblock : '{' stmt* '}';

/*stmt : vardeclstmt ';'
		 | expr ';'
		 | expr ASSIGNOP expr ';'
		 ;*/

expr : value '+' value;

value : '(' expr ')' | '1';

//vardeclstmt : 'def' type? vardecls;

//vardecls : vardecl (',' vardecl)* ','?;

//vardecl : name ('=' expr);