#ifndef SCENE_H_
#define SCENE_H_

#include "Sampler.h"
#include "Sample.h"
#include "Film.h"
#include "Camera.h"
#include "Ray.h"
#include "RayTracer.h"

class Scene {
  public:
    int width, height;
    Scene(int width, int height) {
      this->width = width;
      this->height = height;
    }

    void render() {
      Sampler sampler(width, height);
      Sample sample;
      Film film;
      Color color;
      Camera camera;
      Ray ray;
      RayTracer raytracer;

      while(!sampler.generateSample(&sample)) {
        camera.generateRay(sample, &ray);
        raytracer.trace(ray, &color);
        film.commit(sample, color);
      }
      film.writeImage();
    }
};

#endif
