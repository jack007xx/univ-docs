parser: parser.y scanner.l symtab/* llvm_code/* optimize/*
	yacc -d parser.y
	lex scanner.l > lex.yy.c
	cc -std=c99 y.tab.c lex.yy.c symtab/symtab.c llvm_code/llvm.c llvm_code/factor.c optimize/optimize.c -ll -o parser

clean: 
	rm parser y.tab.c y.tab.h lex.yy.c result.ll
