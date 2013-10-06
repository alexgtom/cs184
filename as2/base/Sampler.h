#ifndef SAMPLER_H_
#define SAMPLER_H_

#include "Sample.h"

class Sampler {
  public:
    int width, height;
    int cur_x, cur_y;

    Sampler(int width, int height) {
      this->width = width;
      this->height = height;
      cur_x = 0;
      cur_y = 0;
    }
    
    // Generates a sample and sets the sample pointer to 
    // the new sample. 
    //
    // Returns true if it could make a sample false otherwise
    bool generateSample(Sample* sample) {
      if (cur_x == width) {
        cur_x = 0;
        cur_y++;
      }
      if (cur_y == height) {
        return false;
      }

      *sample = Sample(cur_x, cur_y);

      cur_x++;
      return true;
    }
};

#endif
