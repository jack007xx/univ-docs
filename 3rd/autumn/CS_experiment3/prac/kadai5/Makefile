parser: parser.y scanner.l symtab.c symtab.h llvmcommands.c llvmcommands.h
	yacc -d parser.y
	lex scanner.l > lex.yy.c
	cc y.tab.c lex.yy.c symtab.c llvmcommands.c -ll -o parser

clean: 
	rm parser y.tab.c y.tab.h lex.yy.c
