main:   main.o  funcao.o
	gcc  main.o   funcao.o -o main

main.o: main.c
	gcc -c  main.c

funcao.o:      funcao.c   funcao.h
	gcc -c  funcao.c

clean:
	rm *.o
