#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <stdexcept>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <time.h>
#include <math.h>

#include "base/Vector.h"
#include "base/Color.h"
#include "base/Args.h"
#include "base/Point.h"
#include "base/Ray.h"
#include "base/Scene.h"

using namespace std;

extern char* filename;

int main(int argc, char *argv[]) {
  // Parse Arguments
  parseArgs(argc, argv);

  Scene scene(filename);
  scene.render();

  return 0;
}
