scanner: scanner.l
	lex -t scanner.l > scanner.c
	cc -o scanner scanner.c -ll

clean: 
	rm scanner scanner.c
