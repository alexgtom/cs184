CC = g++
CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -I./lib -DOSX
LDFLAGS = -framework GLUT -framework OpenGL \
	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
	lib/libfreeimage.a \
	-lGL -lGLU -lm -lstdc++

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
