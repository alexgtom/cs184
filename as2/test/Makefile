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
	
# gtest stuff
GTEST_DIR=../../gtest
AS_DIR=../..

default: test

gtest:
	$(CC) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) \
		-pthread -c $(GTEST_DIR)/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

compile: gtest
	$(CC) $(CFLAGS) -isystem $(GTEST_DIR)/include -pthread main.cc libgtest.a \
		 -I$(AS_DIR) -o main $(LDFLAGS)

test: compile
	./main

clean:
	rm -rf libgtest.a gtest-all.o main *.o *.dSYM
