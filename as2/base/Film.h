#ifndef FILM_H_
#define FILM_H_

class Film {
  public:
    void setPixel(int x, int y, GLfloat r, GLfloat g, GLfloat b) {
      glColor3f(r, g, b);
      glVertex2f(x + 0.5, y + 0.5);   // The 0.5 is to target pixel
      // centers 
      // Note: Need to check for gap
      // bug on inst machines.
    }

    // Write the color to (sample.x, sample.y) on the image
    void commit(Sample& sample, Color& color) {
      setPixel(sample.x, sample.y, color.r, color.g, color.b);
    }
    
    // Output image to a file
    void writeImage() {
    }
};

#endif
