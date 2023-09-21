lexer grammar CxLexer;

PLUS : '+';
MINUS : '-';
STAR : '*';
DIV : '/';
POW : '**';
AND : '&&';
OR : '||';
BITAND: '&';
BITOR : '|';
XOR : '^';
AT : '@';
ATAT : '@@';
ATSTAR : '@*';
ATDIV : '@/';
ATPLUS: '@+';
ATMINUS : '@-';
ATOR : '@|';
ATAND : '@&';
LSHIFT : '>>';
RSHIFT : '<<';

CMPNE : '><' | '<>'  | '!='	;

CMPGT : '>'  | '!<=' | '!=<';

CMPLT : '<'  | '!>=' | '!=>';

CMPGE : '>=' | '=>'  | '!<'	;

CMPLE : '<=' | '=<'  | '!>'	;

CMPEQ : '==' | '!<>' | '!><';

QMARK : '?';
COLON : ':';

SEMICOLON : ';';

LITERALBOOL : 'true'|'false';
LITERALNUM : [0-9]+;