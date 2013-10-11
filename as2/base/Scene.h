#ifndef SCENE_H_
#define SCENE_H_

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include "Sampler.h"
#include "Sample.h"
#include "Film.h"
#include "Camera.h"
#include "Ray.h"
#include "RayTracer.h"
#include "GeometricPrimitive.h"
#include "AggregatePrimitive.h"
#include "Shape.h"

using namespace std;

class Scene {
  public:
    // dimensions of output image
    int width, height;

    // max depth of ray tracer 
    int maxdepth;

    // Output filename
    string output_file;

    // Keep track of GeometricPrimitives
    vector<Primitive*> geo_prim_list;
    vector<Point*> vertex_list;

    void loadScene(string file) {
      // default output file if none specified
      output_file = "output.png"; 

      ifstream inpfile(file.c_str());
      if(!inpfile.is_open()) {
        cout << "Unable to open file" << endl;
      } else {
        string line;
        //MatrixStack mst;

        while(inpfile.good()) {
          vector<string> splitline;
          string buf;

          getline(inpfile,line);
          stringstream ss(line);

          while (ss >> buf) {
            splitline.push_back(buf);
          }
          //Ignore blank lines
          if(splitline.size() == 0) {
            continue;
          }

          //Ignore comments
          if(splitline[0][0] == '#') {
            continue;
          }

          //Valid commands:
          //size width height
          //  must be first command of file, controls image size
          else if(!splitline[0].compare("size")) {
            width = atoi(splitline[1].c_str());
            height = atoi(splitline[2].c_str());
          }
          //maxdepth depth
          //  max # of bounces for ray (default 5)
          else if(!splitline[0].compare("maxdepth")) {
             maxdepth = atoi(splitline[1].c_str());
          }
          //output filename
          //  output file to write image to 
          else if(!splitline[0].compare("output")) {
            output_file = splitline[1];
          }

          //camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov
          //  specifies the camera in the standard way, as in homework 2.
          else if(!splitline[0].compare("camera")) {
            // lookfrom:
            //    atof(splitline[1].c_str())
            //    atof(splitline[2].c_str())
            //    atof(splitline[3].c_str())
            // lookat:
            //    atof(splitline[4].c_str())
            //    atof(splitline[5].c_str())
            //    atof(splitline[6].c_str())
            // up:
            //    atof(splitline[7].c_str())
            //    atof(splitline[8].c_str())
            //    atof(splitline[9].c_str())
            // fov: atof(splitline[10].c_str());
          }

          //sphere x y z radius
          //  Defines a sphere with a given position and radius.
          else if(!splitline[0].compare("sphere")) {
            // Create new sphere:
            //   Store 4 numbers
            //   Store current property values
            //   Store current top of matrix stack
            float x = atof(splitline[1].c_str());
            float y = atof(splitline[2].c_str());
            float z = atof(splitline[3].c_str());
            float r = atof(splitline[4].c_str());
            Transformation objToWorld;
            Transformation worldToObj;
            
            geo_prim_list.push_back(
              new GeometricPrimitive(
                new Sphere(r),
                objToWorld,
                worldToObj,
                NULL // TODO: put a real material here
              )
            );
          }
          //maxverts number
          //  Defines a maximum number of vertices for later triangle specifications. 
          //  It must be set before vertices are deï¬ned.
          else if(!splitline[0].compare("maxverts")) {
            // Care if you want
            // Here, either declare array size
            // Or you can just use a STL vector, in which case you can ignore this
            
            // NOTE: we don't need this since we are using a STL vector, so
            // we throw away this token
          }
          //maxvertnorms number
          //  Defines a maximum number of vertices with normals for later specifications.
          //  It must be set before vertices with normals are deï¬ned.
          else if(!splitline[0].compare("maxvertnorms")) {
            // NOTE: we don't need this since we are using a STL vector, so
            // we throw away this token
          }
          //vertex x y z
          //  Defines a vertex at the given location.
          //  The vertex is put into a pile, starting to be numbered at 0.
          else if(!splitline[0].compare("vertex")) {
            // Create a new vertex with these 3 values, store in some array
            float x = atof(splitline[1].c_str());
            float y = atof(splitline[2].c_str());
            float z = atof(splitline[3].c_str());
            
            vertex_list.push_back(new Point(x, y, z));
          }
          //vertexnormal x y z nx ny nz
          //  Similar to the above, but define a surface normal with each vertex.
          //  The vertex and vertexnormal set of vertices are completely independent
          //  (as are maxverts and maxvertnorms).
          else if(!splitline[0].compare("vertexnormal")) {
            // x: atof(splitline[1].c_str()),
            // y: atof(splitline[2].c_str()),
            // z: atof(splitline[3].c_str()));
            // nx: atof(splitline[4].c_str()),
            // ny: atof(splitline[5].c_str()),
            // nz: atof(splitline[6].c_str()));
            // Create a new vertex+normal with these 6 values, store in some array
          }
          //tri v1 v2 v3
          //  Create a triangle out of the vertices involved (which have previously been specified with
          //  the vertex command). The vertices are assumed to be specified in counter-clockwise order. Your code
          //  should internally compute a face normal for this triangle.
          else if(!splitline[0].compare("tri")) {
            // v1: atof(splitline[1].c_str())
            // v2: atof(splitline[2].c_str())
            // v3: atof(splitline[3].c_str())
            // Create new triangle:
            //   Store pointer to array of vertices
            //   Store 3 integers to index into array
            //   Store current property values
            //   Store current top of matrix stack
            
            Transformation objToWorld;
            Transformation worldToObj;
            Point* p0 = vertex_list[atoi(splitline[1].c_str())];
            Point* p1 = vertex_list[atoi(splitline[2].c_str())];
            Point* p2 = vertex_list[atoi(splitline[3].c_str())];

            geo_prim_list.push_back(
              new GeometricPrimitive(
                new Triangle(*p0, *p1, *p2),
                objToWorld,
                worldToObj,
                NULL // TODO: put a real material here
              )
            );
          }
          //trinormal v1 v2 v3
          //  Same as above but for vertices specified with normals.
          //  In this case, each vertex has an associated normal, 
          //  and when doing shading, you should interpolate the normals 
          //  for intermediate points on the triangle.
          else if(!splitline[0].compare("trinormal")) {
            // v1: atof(splitline[1].c_str())
            // v2: atof(splitline[2].c_str())
            // v3: atof(splitline[3].c_str())
            // Create new triangle:
            //   Store pointer to array of vertices (Different array than above)
            //   Store 3 integers to index into array
            //   Store current property values
            //   Store current top of matrix stack
          }

          //translate x y z
          //  A translation 3-vector
          else if(!splitline[0].compare("translate")) {
            // x: atof(splitline[1].c_str())
            // y: atof(splitline[2].c_str())
            // z: atof(splitline[3].c_str())
            // Update top of matrix stack
          }
          //rotate x y z angle
          //  Rotate by angle (in degrees) about the given axis as in OpenGL.
          else if(!splitline[0].compare("rotate")) {
            // x: atof(splitline[1].c_str())
            // y: atof(splitline[2].c_str())
            // z: atof(splitline[3].c_str())
            // angle: atof(splitline[4].c_str())
            // Update top of matrix stack
          }
          //scale x y z
          //  Scale by the corresponding amount in each axis (a non-uniform scaling).
          else if(!splitline[0].compare("scale")) {
            // x: atof(splitline[1].c_str())
            // y: atof(splitline[2].c_str())
            // z: atof(splitline[3].c_str())
            // Update top of matrix stack
          }
          //pushTransform
          //  Push the current modeling transform on the stack as in OpenGL. 
          //  You might want to do pushTransform immediately after setting 
          //   the camera to preserve the â€œidentityâ€ transformation.
          else if(!splitline[0].compare("pushTransform")) {
            //mst.push();
          }
          //popTransform
          //  Pop the current transform from the stack as in OpenGL. 
          //  The sequence of popTransform and pushTransform can be used if 
          //  desired before every primitive to reset the transformation 
          //  (assuming the initial camera transformation is on the stack as 
          //  discussed above).
          else if(!splitline[0].compare("popTransform")) {
            //mst.pop();
          }

          //directional x y z r g b
          //  The direction to the light source, and the color, as in OpenGL.
          else if(!splitline[0].compare("directional")) {
            // x: atof(splitline[1].c_str()),
            // y: atof(splitline[2].c_str()),
            // z: atof(splitline[3].c_str()));
            // r: atof(splitline[4].c_str()),
            // g: atof(splitline[5].c_str()),
            // b: atof(splitline[6].c_str()));
            // add light to scene...
          }
          //point x y z r g b
          //  The location of a point source and the color, as in OpenGL.
          else if(!splitline[0].compare("point")) {
            // x: atof(splitline[1].c_str()),
            // y: atof(splitline[2].c_str()),
            // z: atof(splitline[3].c_str()));
            // r: atof(splitline[4].c_str()),
            // g: atof(splitline[5].c_str()),
            // b: atof(splitline[6].c_str()));
            // add light to scene...
          }
          //attenuation const linear quadratic
          //  Sets the constant, linear and quadratic attenuations 
          //  (default 1,0,0) as in OpenGL.
          else if(!splitline[0].compare("attenuation")) {
            // const: atof(splitline[1].c_str())
            // linear: atof(splitline[2].c_str())
            // quadratic: atof(splitline[3].c_str())
          }
          //ambient r g b
          //  The global ambient color to be added for each object 
          //  (default is .2,.2,.2)
          else if(!splitline[0].compare("ambient")) {
            // r: atof(splitline[1].c_str())
            // g: atof(splitline[2].c_str())
            // b: atof(splitline[3].c_str())
          }

          //diffuse r g b
          //  specifies the diï¬€use color of the surface.
          else if(!splitline[0].compare("diffuse")) {
            // r: atof(splitline[1].c_str())
            // g: atof(splitline[2].c_str())
            // b: atof(splitline[3].c_str())
            // Update current properties
          }
          //specular r g b 
          //  specifies the specular color of the surface.
          else if(!splitline[0].compare("specular")) {
            // r: atof(splitline[1].c_str())
            // g: atof(splitline[2].c_str())
            // b: atof(splitline[3].c_str())
            // Update current properties
          }
          //shininess s
          //  specifies the shininess of the surface.
          else if(!splitline[0].compare("shininess")) {
            // shininess: atof(splitline[1].c_str())
            // Update current properties
          }
          //emission r g b
          //  gives the emissive color of the surface.
          else if(!splitline[0].compare("emission")) {
            // r: atof(splitline[1].c_str())
            // g: atof(splitline[2].c_str())
            // b: atof(splitline[3].c_str())
            // Update current properties
          } else {
            cerr << "Unknown command: " << splitline[0] << endl;
          }

        } // end while loop
        inpfile.close();
      }
    }

    void render() {
      Sampler sampler(width, height);
      Sample sample;
      Film film(width, height, output_file);
      Color color;
      Camera camera;
      AggregatePrimitive aggregate_primitive(geo_prim_list);
      Ray ray;
      RayTracer raytracer(&aggregate_primitive);

      while(sampler.generateSample(&sample)) {
        camera.generateRay(sample, &ray);
        raytracer.trace(ray, &color);
        film.commit(sample, color);
      }
      film.writeImage();
    }
};

#endif
