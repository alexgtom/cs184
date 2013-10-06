CC = g++

.PHONY: test
	
RM = /bin/rm -f 
all: main 
main: main.o 
	$(CC) $(CFLAGS) -o main main.o $(LDFLAGS) 
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o
clean: 
	$(RM) *.o main

test:
	cd test; make 
