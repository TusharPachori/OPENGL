#include "GL/glut.h"
#include"math.h"

int n=0;
int scale =1;

void drawsquare(float x, float y, float r, int iter){
  glPushMatrix(); // save the current matrix
  glScalef(scale, scale, 0); // scale the matrix
  glBegin(GL_LINE_LOOP);
  glColor3f(1,0,0);
  glVertex2f(x-r, y-r);
  glColor3f(1,1,0);
  glVertex2f(x+r, y-r);
  glColor3f(0,1,1);
  glVertex2f(x+r, y+r);
  glColor3f(1,0,1);

  glVertex2f(x-r, y+r);
  glEnd();
  glBegin(GL_LINES);
  glColor3f(1,0,0);
  glVertex2f(x-r, y-r);
  glColor3f(0,1,1);
  glVertex2f(x+r, y+r);
  glColor3f(1,1,0);
  glVertex2f(x+r, y-r);
  glColor3f(1,0,1);
  glVertex2f(x-r, y+r);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glColor3f(1,0,0);
  glVertex2f(x-r, y);
  glColor3f(0,0,1);
  glVertex2f(x, y-r);
  glColor3f(0,1,1);
  glVertex2f(x+r, y);
  glColor3f(1,1,0);
  glVertex2f(x, y+r);
  glEnd();
  glBegin(GL_LINES);
  glColor3f(1,0,0);
  glVertex2f(x-r, y);
  glColor3f(0,1,1);
  glVertex2f(x+r, y);
  glColor3f(1,0,1);
  glVertex2f(x, y-r);
  glColor3f(1,1,0);
  glVertex2f(x, y+r);
  glEnd();
  glPopMatrix();
  if(iter>0){
    iter--;
    drawsquare(x-r/2, y-r/2, r/2, iter);
    drawsquare(x+r/2, y-r/2, r/2, iter);
    drawsquare(x+r/2, y+r/2, r/2, iter);
    drawsquare(x-r/2, y+r/2, r/2, iter);
    drawsquare(x-(3*r/2), y-(3*r/2), r/2, iter);
    drawsquare(x+(3*r/2), y-(3*r/2), r/2, iter);
    drawsquare(x-(3*r/2), y+(3*r/2), r/2, iter);
    drawsquare(x+(3*r/2), y+(3*r/2), r/2, iter);


  }
}

void display(void){
  glColor3f(0,0,1);
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

void MouseButton(int button,int state,int x, int y){
  if (button==GLUT_LEFT_BUTTON){
    if (state==GLUT_DOWN){
      n++;
      glutPostRedisplay();    }
  }
}

void processNormalKeys(unsigned char key, int x, int y){
	if (key == 43){
    scale = scale+1;
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();
    glFlush();
  }
  if (key == 45){
    if(scale>1){
    scale = scale-0.5;
  }
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();
    glFlush();
  }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(500, 500);
    glutCreateWindow("3D Gasket");
    glutDisplayFunc(display);
    glutMouseFunc(MouseButton);
	  myinit();
    glutKeyboardFunc(processNormalKeys);

    glutMainLoop();
}

