#ifndef ARGS_H_
#define ARGS_H_

#include <iostream>

using namespace std;

char* filename;

//
// Parses the arguments from the command line
//
void parseArgs(int argc, char *argv[]) {
  for(int i = 1; i < argc;) {
    char *option = argv[i];
   
    // Load scene from file
    // -f filename
    if (strcmp(option, "-f") == 0) {
      filename = argv[i + 1];
      i += 2;
    } else {
      cerr << "Invalid argument: " << option << endl;
      exit(1);
    }
  }
}

#endif
