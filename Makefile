SRC = wordFreak.c bst.c textMod.c
OBJ = wordFreak.o bst.o textMod.o 
PROG = wordfreak

$(PROG): $(OBJ)
	gcc -std=c99 $(OBJ) -o $(PROG)

$(OBJ): $(SRC)
