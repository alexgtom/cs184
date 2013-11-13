#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include <glm/glm.hpp>

#include "BezierPatch.h"
#include "AdaptiveBezierPatch.h"
#include "Subdivision.h"

using namespace glm;
using namespace std;

class Parser {
  public:
    vector<BezierPatch*> readFile(string file, float subdivisionParameter, int subdivisionType) {
      ifstream inpfile(file.c_str());
      int num_patches;
      vector<BezierPatch*> patch_list;

      if (!inpfile.is_open()) {
        cerr << "Unable to open file" << endl;
        exit(1);
      }


      string line;
      int row = 0;
      vector<vec3> points;

      while (inpfile.good()) {
        vector<string> splitline;
        string buf;

        getline(inpfile, line);
        stringstream ss(line);

        while (ss >> buf) {
          splitline.push_back(buf);
        }

        // Ignore blank lines
        if (splitline.size() == 0) {
          continue;
        }

        if (splitline.size() == 1) {
          num_patches = atoi(splitline[0].c_str());
          continue;
        }

        if (splitline.size() == 12) {
          for (int col = 0; col < 12; col += 3) {
            float x = atof(splitline[col + 0].c_str());
            float y = atof(splitline[col + 1].c_str());
            float z = atof(splitline[col + 2].c_str());
            points.push_back(vec3(x, y, z));
          }
        }

        row++;

        if (row % 4 == 0) {
          row = row % 4;
          if (subdivisionType == SUBDIVISION_UNIFORM)
            patch_list.push_back(new BezierPatch(points, subdivisionParameter));
          else if (subdivisionType == SUBDIVISION_ADAPTIVE)
            patch_list.push_back(new AdaptiveBezierPatch(points, subdivisionParameter));
          else {
            cerr << "Invalid subdivision type: " << subdivisionParameter << endl;
            exit(1);
          }
          points = vector<vec3>();
        }

      }

      return patch_list;
    }
};

#endif
