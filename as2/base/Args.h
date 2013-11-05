#ifndef ARGS_H_
#define ARGS_H_

#include <iostream>

#include "Scene.h"
#include "Film.h"

using namespace std;

//
// Parses the arguments from the command line
//
void parseArgs(int argc, char *argv[]) {
  for(int i = 1; i < argc;) {
    char *option = argv[i];
   
    if (strcmp(option, "-f") == 0) {
      // Load scene from file
      // -f filename
      char* filename = argv[i + 1];
      
      // create scene and render it
      Scene scene;
      scene.loadScene(filename);
      scene.render();

      i += 2;
    } else if (strcmp(option, "-t") == 0) {
      // A test to make sure Film outputs something to file
      // -t
      Film film(400, 400, "film_test.png");
      film.test();

      i += 1;
    } else {
      cerr << "Invalid argument: " << option << endl;
      exit(1);
    }
  }
}

#endif
