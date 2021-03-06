#include "gl1.hpp"

#include <GL/gl.h>

GlPreviewer::GlPreviewer() {
}

void GlPreviewer::DrawCube(unsigned short x, unsigned short y, unsigned short z,
                           Material mat) {
  glBegin(GL_TRIANGLES);

  glColor3f(mat.r, mat.g, mat.b);

  /* First face */
  glVertex3f(0.0 + x, 0.0 + y, 0.0 + z);
  glVertex3f(0.0 + x, 1.0 + y, 0.0 + z);
  glVertex3f(0.0 + x, 1.0 + y, 1.0 + z);

  glVertex3f(0.0 + x, 0.0 + y, 0.0 + z);
  glVertex3f(0.0 + x, 1.0 + y, 1.0 + z);
  glVertex3f(0.0 + x, 0.0 + y, 1.0 + z);

  glColor3f(mat.r * 0.6, mat.g * 0.6, mat.b * 0.6);

  /* Third face */
  glVertex3f(1.0 + x, 0.0 + y, 1.0 + z);
  glVertex3f(1.0 + x, 0.0 + y, 0.0 + z);
  glVertex3f(1.0 + x, 1.0 + y, 0.0 + z);

  glVertex3f(1.0 + x, 0.0 + y, 1.0 + z);
  glVertex3f(1.0 + x, 1.0 + y, 1.0 + z);
  glVertex3f(1.0 + x, 1.0 + y, 0.0 + z);

  glColor3f(mat.r, mat.g, mat.b);

  /* Forth face */
  glVertex3f(0.0 + x, 0.0 + y, 0.0 + z);
  glVertex3f(0.0 + x, 1.0 + y, 0.0 + z);
  glVertex3f(1.0 + x, 1.0 + y, 0.0 + z);

  glVertex3f(0.0 + x, 0.0 + y, 0.0 + z);
  glVertex3f(1.0 + x, 0.0 + y, 0.0 + z);
  glVertex3f(1.0 + x, 1.0 + y, 0.0 + z);

  glColor3f(mat.r * 0.9, mat.g * 0.9, mat.b * 0.9);

  /* Fifth face - Top */
  glVertex3f(0.0 + x, 1.0 + y, 0.0 + z);
  glVertex3f(0.0 + x, 1.0 + y, 1.0 + z);
  glVertex3f(1.0 + x, 1.0 + y, 1.0 + z);

  glVertex3f(0.0 + x, 1.0 + y, 0.0 + z);
  glVertex3f(1.0 + x, 1.0 + y, 0.0 + z);
  glVertex3f(1.0 + x, 1.0 + y, 1.0 + z);

  glColor3f(mat.r, mat.g, mat.b);

  /* Sixth face - Bottom*/
  glVertex3f(0.0 + x, 0.0 + y, 0.0 + z);
  glVertex3f(0.0 + x, 0.0 + y, 1.0 + z);
  glVertex3f(1.0 + x, 0.0 + y, 1.0 + z);

  glVertex3f(0.0 + x, 0.0 + y, 0.0 + z);
  glVertex3f(1.0 + x, 0.0 + y, 0.0 + z);
  glVertex3f(1.0 + x, 0.0 + y, 1.0 + z);

  glColor3f(mat.r * 0.6, mat.g * 0.6, mat.b * 0.6);

  /* Second face */
  glVertex3f(0.0 + x, 0.0 + y, 1.0 + z);
  glVertex3f(1.0 + x, 0.0 + y, 1.0 + z);
  glVertex3f(1.0 + x, 1.0 + y, 1.0 + z);

  glVertex3f(0.0 + x, 0.0 + y, 1.0 + z);
  glVertex3f(0.0 + x, 1.0 + y, 1.0 + z);
  glVertex3f(1.0 + x, 1.0 + y, 1.0 + z);
  glEnd();
}

void GlPreviewer::Render(int width, int height, Geometry* geo, Material3D mat,
                         float zoom, float rotation) {
// USE OLD OPENGL 1 code
#ifndef __HAIKU__
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glViewport(0, 0, width, height);

  // Isometric
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10.0f + zoom, 10.0f - zoom, -10.0f + zoom, 10.0f - zoom, -10.0f,
          10.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(35.264f, 1.0f, 0.0f, 0.0f);
  glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);

  glRotatef(rotation, 0.0f, 1.0f, 0.0f);

// Draw AXIS
#ifdef __HAIKU__
  glClearColor(0.0, 0.0, 0.0, 1.0);
#endif
  //

  glColor3f(1.0, 0.0, 0.0);

  glBegin(GL_LINES);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(100.0, 0.0, 0.0);
  glEnd();

  glColor3f(0.0, 1.0, 0.0);

  glBegin(GL_LINES);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 100.0, 0.0);
  glEnd();

  glColor3f(0.0, 0.0, 1.0);

  glBegin(GL_LINES);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 100.0);
  glEnd();

  for (short i = 0; i < geo->g; i++) {
	for (short j = 0; j < geo->g; j++) {
	  for (short k = 0; k < geo->g; k++) {
		if (geo->GetGrid(i, j, k) == 1) {
		  DrawCube(i, j, k, mat[i][j][k]);
		}
	  }
	}
  }
}
