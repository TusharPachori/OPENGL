#include "GL/glut.h"

int n=3;

void drawsquare(float x, float y, float r, int iter){
  glBegin(GL_LINE_LOOP);
  glVertex2f(x-r, y-r);
  glVertex2f(x+r, y-r);
  glVertex2f(x+r, y+r);
  glVertex2f(x-r, y+r);
  glEnd();
  if(iter>0){
    iter--;
    drawsquare(x-r, y-r, r/2, iter);
    drawsquare(x+r, y-r, r/2, iter);
    drawsquare(x+r, y+r, r/2, iter);
    drawsquare(x-r, y+r, r/2, iter);
  }
}

void display(void){

    drawsquare(0,0,5, n);
    glFlush();
}

void myinit()
{
  glClearColor(0,0,0, 1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-20, 20, -20, 20);
  glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(500, 500);
    glutCreateWindow("FRACTAL");
    glutDisplayFunc(display);

	myinit();
    glutMainLoop();
}

