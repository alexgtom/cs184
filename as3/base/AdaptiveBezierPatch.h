#ifndef ADAPTIVE_BEZIER_PATCH_H_
#define ADAPTIVE_BEZIER_PATCH_H_

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <iostream>
#include <cmath>


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

#include "BezierPatch.h"
#include "PointDeriv.h"
#include "PointNormal.h"

class Triangle {
  public:
    static long count;
    /*
     *      p3        /  \
     *     /  \     e1   e3
     *   p1 -- p2   /- e2 -\
     */
    vec2 p1;
    vec2 p2;
    vec2 p3;
    
    long id;

    
    /*
     * p1, p2, p3 are the parametric coordinates of the triangle (u, v)
     */
    Triangle(vec2 p1, vec2 p2, vec2 p3) {
      this->p1 = p1;
      this->p2 = p2;
      this->p3 = p3;
      id = count;
      count++;
    }

    friend std::ostream& operator<< (std::ostream& stream, const Triangle& t) {
      stream << "Triangle(ID: " << t.id << " | " << to_string(t.p1) << ", " << to_string(t.p2) << ", " << to_string(t.p3) << ")";
      return stream;
    }
};

long Triangle::count = 0;

class AdaptiveBezierPatch : public BezierPatch {
  public:
    float error;

    // triangles to render
    vector<Triangle> triangles;

    AdaptiveBezierPatch() : BezierPatch() {}
    AdaptiveBezierPatch(vector<vec3> points, float error) {
      this->points = points;
      this->error = error;
      subdividepatch();
    }

    void subdividepatch() {
      vector<Triangle> triangle_stack;
      triangle_stack.push_back(Triangle(vec2(0.0, 0.0), vec2(1.0, 0.0), vec2(1.0, 1.0)));
      triangle_stack.push_back(Triangle(vec2(1.0, 1.0), vec2(0.0, 1.0), vec2(0.0, 0.0)));

      while(triangle_stack.size() > 0) {
        Triangle top = triangle_stack.back();
        triangle_stack.pop_back();

        if (triangle_split_type(top) == 0)
          triangles.push_back(top);
        else {
          vector<Triangle> triangle_splits = split_triangle(top);
          for(int i = 0; i < triangle_splits.size(); i++) {
            triangle_stack.push_back(triangle_splits[i]);
          }
        }
      }
    }
    
    /*
     * Returns an integer from 0-7 which indicates how to split the triangle
     * according the the table in the Surfaces slides
     */
    int triangle_split_type(Triangle tri) {
      int split_type = 0;

      if (split_edge(tri.p1, tri.p3))  {
        split_type += 1;
      }
      if (split_edge(tri.p1, tri.p2)) {
        split_type += 2;
      }
      if (split_edge(tri.p3, tri.p2)) {
        split_type += 4;
      }
      
      return split_type;
    }
    
    /* Returns true if we should split the edge, false otherwise
     */
    bool split_edge(vec2 p1, vec2 p2) {
      vec2 para_midpoint = (p1 + p2) / 2.0f;
      PointNormal mid_point_normal = bezpatchinterp(para_midpoint.x, para_midpoint.y);
      PointNormal bottom_point_normal = bezpatchinterp(p1.x, p1.y);
      PointNormal upper_point_normal = bezpatchinterp(p2.x, p2.y);
      vec3 flat_midpoint = (bottom_point_normal.point + upper_point_normal.point) / 2.0f;
      vec3 dist_vector = mid_point_normal.point - flat_midpoint;
        return length(dist_vector) >= error;
        // return abs(dot(dist_vector, dist_vector)) >= error;
    }

    vector<Triangle> split_triangle(Triangle tri) {
      vector<Triangle> triangle_list;
      int split_type = triangle_split_type(tri);
      vec2 e1_midpoint = (tri.p1 + tri.p3) / 2.0f;
      vec2 e2_midpoint = (tri.p1 + tri.p2) / 2.0f;
      vec2 e3_midpoint = (tri.p3 + tri.p2) / 2.0f;

      switch(split_type) {
        // 0 splits
        case 0:
          break;

        // 1 splits
        case 1:
          triangle_list.push_back(Triangle(tri.p1, tri.p2, e1_midpoint));
          triangle_list.push_back(Triangle(e1_midpoint, tri.p2, tri.p3));
          break;
        case 2:
          triangle_list.push_back(Triangle(tri.p1, e2_midpoint, tri.p3));
          triangle_list.push_back(Triangle(e2_midpoint, tri.p2, tri.p3));
          break;
        case 4:
          triangle_list.push_back(Triangle(tri.p1, tri.p2, e3_midpoint));
          triangle_list.push_back(Triangle(e3_midpoint, tri.p3, tri.p1));
          break;

        // 2 split_list
        case 3:
          triangle_list.push_back(Triangle(tri.p1, e2_midpoint, e1_midpoint));
          triangle_list.push_back(Triangle(e1_midpoint, e2_midpoint, tri.p3));
          triangle_list.push_back(Triangle(tri.p3, e2_midpoint, tri.p2));
          break;
        case 5:
          triangle_list.push_back(Triangle(tri.p1, tri.p2, e1_midpoint));
          triangle_list.push_back(Triangle(e1_midpoint, tri.p2, e3_midpoint));
          triangle_list.push_back(Triangle(e1_midpoint, e3_midpoint, tri.p3));
          break;
        case 6:
          triangle_list.push_back(Triangle(tri.p1, e3_midpoint, tri.p3));
          triangle_list.push_back(Triangle(tri.p1, e2_midpoint, e3_midpoint));
          triangle_list.push_back(Triangle(e2_midpoint, tri.p2, e3_midpoint));
          break;

        // 3 split_list
        case 7:
          triangle_list.push_back(Triangle(tri.p1, e2_midpoint, e1_midpoint));
          triangle_list.push_back(Triangle(e1_midpoint, e2_midpoint, e3_midpoint));
          triangle_list.push_back(Triangle(e2_midpoint, tri.p2, e3_midpoint));
          triangle_list.push_back(Triangle(e1_midpoint, e3_midpoint, tri.p3));
          break;
      }

      return triangle_list;
    }

    void render_wireframe(void) {
      for(int i = 0; i < triangles.size(); i++) {
        Triangle tri = triangles[i];
        PointNormal p1 = bezpatchinterp(tri.p1.x, tri.p1.y);
        PointNormal p2 = bezpatchinterp(tri.p2.x, tri.p2.y);
        PointNormal p3 = bezpatchinterp(tri.p3.x, tri.p3.y);

        glBegin(GL_LINES);
        glVertex3f(p1.point.x, p1.point.y, p1.point.z);
        glVertex3f(p2.point.x, p2.point.y, p2.point.z);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(p2.point.x, p2.point.y, p2.point.z);
        glVertex3f(p3.point.x, p3.point.y, p3.point.z);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(p3.point.x, p3.point.y, p3.point.z);
        glVertex3f(p1.point.x, p1.point.y, p1.point.z);
        glEnd();
      }
    }

    void render_filled(void) {
      for(int i = 0; i < triangles.size(); i++) {
        Triangle tri = triangles[i];
        PointNormal p1 = bezpatchinterp(tri.p1.x, tri.p1.y);
        PointNormal p2 = bezpatchinterp(tri.p2.x, tri.p2.y);
        PointNormal p3 = bezpatchinterp(tri.p3.x, tri.p3.y);

        glBegin(GL_POLYGON);
        glNormal3f(p1.normal.x, p1.normal.y, p1.normal.z);
        glVertex3f(p1.point.x, p1.point.y, p1.point.z);
        glNormal3f(p2.normal.x, p2.normal.y, p2.normal.z);
        glVertex3f(p2.point.x, p2.point.y, p2.point.z);
        glNormal3f(p3.normal.x, p3.normal.y, p3.normal.z);
        glVertex3f(p3.point.x, p3.point.y, p3.point.z);
/**
        glNormal3f(p1.normal.x, p1.normal.y, p1.normal.z);
        glNormal3f(p2.normal.x, p2.normal.y, p2.normal.z);
        glNormal3f(p3.normal.x, p3.normal.y, p3.normal.z);
 **/
        glEnd(); 
      }
    }
    
   
    
    
};

#endif
