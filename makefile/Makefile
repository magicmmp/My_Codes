abc: main.o abc.o
	g++ -o abc main.o abc.o
main.o : main.cc abc.h
	g++ -c main.cc
abc.o :abc.cc abc.h
	g++ -c abc.cc
clean :
	rm abc main.o abc.o

 
