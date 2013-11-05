# as0 stuff
CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -DOSX
	LDFLAGS = -framework GLUT -framework OpenGL \
    	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
    	-lGL -lGLU -lm -lstdc++
else
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -Iglut-3.7.6-bin
	LDFLAGS = -lglut -lGLU
endif
	
RM = /bin/rm -rf 

default: test

example: example_01.o 
	$(CC) $(CFLAGS) -o as1 example_01.o $(LDFLAGS) 
example_01.o: ../example_01.cpp
	$(CC) $(CFLAGS) -c ../example_01.cpp -o example_01.o


# gtest stuff
GTEST_DIR=../../gtest
AS_DIR=../..
TEST=as1_test

gtest:
	$(CC) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) \
		-pthread -c $(GTEST_DIR)/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

compile: example gtest
	$(CC) $(CFLAGS) -isystem $(GTEST_DIR)/include -pthread $(TEST).cc libgtest.a \
		 -I$(AS_DIR) -o $(TEST) $(LDFLAGS)

test: compile
	./$(TEST)

clean:
	$(RM) libgtest.a gtest-all.o $(TEST) *.o as1 *.dSYM
