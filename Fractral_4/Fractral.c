#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include"math.h"
#include <stdio.h>

int n=0;
typedef float point2[2];

point2 v[]={{-3, -3}, {3, -3}, {0, 7.4}};
point2 x[]={{-3, -3}, {0, 7.4}, {-3, 4}};
point2 y[]={{3, -3}, {0, 7.4}, {3, 4}};
point2 z[]={{-3, -3}, {3, -3}, {0, -6.4}};



void triangle( point2 a, point2 b, point2 c){
  glColor3f(1,1,1);
  glBegin(GL_LINE_LOOP);
  glColor3f(1,0,0);
   glVertex2fv(a);
   glColor3f(0,1,0);
   glVertex2fv(b);
   glColor3f(1,0,1);
   glVertex2fv(c);
 glEnd();
 glFlush();
}

void divide_triangle(point2 a, point2 b, point2 c, int m){
    point2 v0, v1, v2;
    int j;
    if(m>0){
        for(j=0; j<2; j++)
		v0[j]=(a[j]+b[j])/2;
        for(j=0; j<2; j++)
		v1[j]=(a[j]+c[j])/2;
        for(j=0; j<2; j++)
		v2[j]=(b[j]+c[j])/2;
        divide_triangle(v0, v1, v2, m-1);
        divide_triangle(a, v0, v1, m-1);
        divide_triangle(c, v1, v2, m-1);
        divide_triangle(b, v2, v0, m-1);
    }
    else
	triangle(a,b,c);
}

void display(void){
  glColor3f(0,0,1);
  divide_triangle(v[0], v[1], v[2], n);
  divide_triangle(x[0], x[1], x[2], n);
  divide_triangle(y[0], y[1], y[2], n);
  divide_triangle(z[0], z[1], z[2], n);
    glFlush();
}

void myinit()
{
  glClearColor(0,0,0, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-5, 5, -10, 10);
  glClear(GL_COLOR_BUFFER_BIT);
}

void MouseButton(int button,int state,int x, int y){
  if (button==GLUT_LEFT_BUTTON){
    if (state==GLUT_DOWN){
      n++;
      glutPostRedisplay();    }
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
    glutMainLoop();
}

