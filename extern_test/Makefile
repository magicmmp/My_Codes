main : ex.o main.o
	gcc -o main ex.o main.o
ex.o : ex.c ex.h
	gcc -c  ex.c 
main.o : main.c ex.h
	gcc -c  main.c
clean :
	rm main ex.o main.o
