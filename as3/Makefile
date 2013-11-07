CXX = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -I./lib -DOSX
	LDFLAGS = -framework GLUT -framework OpenGL \
    	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
    	-lGL -lGLU -lm -lstdc++
else
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -Iglut-3.7.6-bin -I./lib
	LDFLAGS = -lglut -lGLU
endif
	
RM = /bin/rm -f 
all: clean main 
headers:
	$(CXX) $(CFLAGS) -fsyntax-only base/*.h
main: main.o 
	$(CXX) $(CFLAGS) -o main main.o $(LDFLAGS) 
main.o: headers main.cpp 
	$(CXX) $(CFLAGS) -c main.cpp -o main.o
clean: 
	$(RM) *.o main

testbez: main
	 ./main input/test.bez 0.1

teapotbez: main
	 ./main input/teapot.bez 0.1
