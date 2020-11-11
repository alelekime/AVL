all: AVL
all: clean

AVL: AVL.o A.o
	gcc AVL.o A.o -o myavl -Wall

AVL.o: AVL.c A.h
	gcc -c AVL.c -Wall

A.o: A.c A.h
	gcc -c A.c -Wall


clean:
	-rm -f *.o

purge: clean
	-rm -f myavl