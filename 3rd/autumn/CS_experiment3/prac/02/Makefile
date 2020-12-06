parser: parser.y scanner.l
	yacc -d parser.y
	lex scanner.l > lex.yy.c
	cc y.tab.c lex.yy.c -ll -o parser
