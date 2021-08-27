gcc_comp: flex_comp
	gcc -o parse ast.o symtab.o quad.o parser.tab.o lex.yy.o
flex_comp: bison_comp
	flex lex.l
	gcc -c parser.tab.h extdef.h lex.yy.c
bison_comp: sym_comp quad_comp
	bison -vd parser.y
	gcc -c ast.h quad.h symtab.h parser.tab.c
quad_comp:
	gcc -c ast.h quad.h quad.c
sym_comp: ast_comp
	gcc -c symtab.h symtab.c
ast_comp: 
	gcc -c extdef.h ast.h ast.c
clean: 
	rm -rf parse *.o *.gch *.output
