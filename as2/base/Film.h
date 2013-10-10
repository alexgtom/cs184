#ifndef FILM_H_
#define FILM_H_

#include <FreeImage/FreeImage.h>

#include <iostream>

using namespace std;

class Film {
  public:
    int width, height;
    FIBITMAP *image;
    string output_file;

    Film() {
    }

    Film(int width, int height, string output_file) {
      this->width = width;
      this->height = height;
      this->output_file = output_file;
      image = FreeImage_Allocate(width, height, 24);
    }

    Film(int width, int height) {
      this->width = width;
      this->height = height;
      this->output_file = "output.png";
      image = FreeImage_Allocate(width, height, 24);
    }

    // Write the color to (sample.x, sample.y) on the image
    void commit(Sample& sample, Color& color) { 
      // set pixel on image file
      
      RGBQUAD image_pixel_color;
      image_pixel_color.rgbRed = (int) (color.r * 255);
      image_pixel_color.rgbGreen = (int) (color.g * 255);
      image_pixel_color.rgbBlue = (int) (color.b * 255);

      FreeImage_SetPixelColor(image, sample.x, sample.y, &image_pixel_color);
    }
    
    // Output image to a file
    void writeImage() {
      if(FreeImage_Save(FIF_PNG, image, output_file.c_str(), 0)) {
        cerr << "Scene was saved to '" << output_file << "'" << endl;
      } else {
        cerr << "ERROR: Scene could not be saved to '" << output_file << "'" << endl;
      }

      FreeImage_Unload(image);
    }
    
    // Generate and image and output to file for testing
    void test() {
      Sampler sampler(width, height);
      Sample sample;

      while(sampler.generateSample(&sample)) {
        Color color(
          (float) sample.x / width, 
          (float) sample.y / height, 
          (float) ((sample.x + sample.y) % height) / height
        );
        commit(sample, color);
      }

      writeImage();
    }
};

#endif
