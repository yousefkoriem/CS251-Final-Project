#include <GL/freeglut.h>
#include <cstdio>
#include <valarray>

#define PI acos(-1.0)

void Table() {
  glLineWidth(10.0f);


  glBegin(GL_QUADS);
  {
    glColor3f(0.5f, 0.3f, 0.0f);
    // Bottom
    glVertex3f(-320.0f,-10.0f,-320.0f);
    glVertex3f(320.0f,-10.0f,-320.0f);
    glVertex3f(320.0f,-10.0f,320.0f);
    glVertex3f(-320.0f,-10.0f,320.0f);
    // Front
    glVertex3f(-320.0f,-10.0f,-320.0f);
    glVertex3f(320.0f,-10.0f,-320.0f);
    glVertex3f(-320.0f,0,-320.0f);
    glVertex3f(320.0f,0,-320.0f);
    // Back
    glVertex3f(320.0f,-10.0f,320.0f);
    glVertex3f(-320.0f,-10.0f,320.0f);
    glVertex3f(320.0f,0,320.0f);
    glVertex3f(-320.0f,0,320.0f);
  }
  glEnd();

  glBegin(GL_QUADS);
  {
    glColor3f(0.0f, 0.1f, 0.4f);
    glVertex3f(-320.0f,0,-320.0f);
    glVertex3f(320.0f,0,-320.0f);
    glVertex3f(320.0f,0,320.0f);
    glVertex3f(-320.0f,0,320.0f);
  }
  glEnd();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(1.0f, 1.0f, 1.0f);
  glLineWidth(3.0f);
  glBegin(GL_QUAD_STRIP);
  {
    glVertex3f(320.0f,0,-320.0f);
    glVertex3f(-320.0f,0,-320.0f);
    glVertex3f(320.0f,0,0);
    glVertex3f(-320.0f,0,0);
    glVertex3f(320.0f,0,320.0f);
    glVertex3f(-320.0f,0,320.0f);
  }
  glEnd();
  glLineWidth(5.0f);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_QUADS);
  {
    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex3f(0.0f,0,-320.0f);
    glVertex3f(0.0f,50,-320.0f);
    glVertex3f(0.0f,50,320.0f);
    glVertex3f(0.0f,0,320.0f);

    glVertex3f(0.0f,0,-320.0f);
    glVertex3f(0.0f,50,-320.0f);
    glVertex3f(0.0f,0,0.0f);
    glVertex3f(0.0f,50,0.0f);

    glVertex3f(0.0f,0,320.0f);
    glVertex3f(0.0f,50,320.0f);
    glVertex3f(0.0f,0,0.0f);
    glVertex3f(0.0f,50,0.0f);
  }
  glEnd();
  glPointSize(5.0f);
  glBegin(GL_POINTS);
  {
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f,50,-320.0f);
    glVertex3f(0.0f,50,320.0f);
  }
  glEnd();
}
int state = 1,statey = 1;
float dxz = 0.0f;
float dy = 0.0f;
int deg = 0.0f;
void Ball() {
  float r = 15.0f;
  float xc = 160.0f;
  float zc = 160.0f;
  glBegin(GL_POLYGON);
  {
    for(int k = 0; k < 180; ++k) {
      for (int i = 0; i < 360; ++i) {
        glColor3f(0.8f-0.1f*(k%10 == 0), 0.8f-0.1f*(k%10 == 0), 0.8f-0.1f*(k%10 == 0));
        float x = r * sin(k * PI / 180.0f) *  cos(i * PI / 180.0f);
        float y = r * sin(k * PI / 180.0f) * sin(i * PI / 180.0f);
        float z = r * cos(k * PI / 180.0f);
        glVertex3f(x+xc, y, z+zc);
      }
    }
  }
  glEnd();
}

void display() {
    glClearColor(0.1f, 0.5f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set up projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-640.0, 640.0, -360.0, 360.0, -640.0, 640.0);

    // Switch to modelview matrix for object transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Apply viewing transformations
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(deg, 0.0f, 1.0f, 0.0f);
    //glRotatef(45.0f, 0.0f, 1.0f, 0.0f);

    Table();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glTranslatef(-dxz, dy+10, -dxz);
    Ball();

    glutSwapBuffers();
}

void time(int) {
    deg = (deg + 1) % 360;
    switch(state) {
      case 1:
        dxz += 20.0f;
        if (dxz > 320.0f)
          state = -1;
        break;
      case -1:
        dxz -= 20.0f;
        if (dxz < 0.0f)
          state = 1;
    }
    switch(statey) {
      case 1:
        dy += 10.0f;
        if (dy > 80.0f)
          statey = -1;
        break;
      case -1:
        dy -= 10.0f;
        if (dy < 0.0f)
          statey = 1;
    }

    glutPostRedisplay();
    glutTimerFunc(1000/60, time, 0);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(1280, 720);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Task");
    glutDisplayFunc(display);
    glutTimerFunc(0, time, 0);
    glutMainLoop();
}