# include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

float x=0, y=0;

static int window;
static int menu_id;
static int submenu_id;
static int value = 0;

typedef float point2[2];
int n=0;

point2 v[]={{-1.0*4.999, -0.58*4.999}, {1.0*4.999, -0.58*4.999}, {0.0*4.999, 1.15*4.999}};
/*point2 v[]={{-1.0*4.999, -0.58*4.999}, {1.0*4.999, -0.58*4.999}, {0.0*4.999, 1.15*4.999}};
point2 v[]={{-1.0*4.999, -0.58*4.999}, {1.0*4.999, -0.58*4.999}, {0.0*4.999, 1.15*4.999}};
point2 v[]={{-1.0*4.999, -0.58*4.999}, {1.0*4.999, -0.58*4.999}, {0.0*4.999, 1.15*4.999}};*/



void triangle( point2 a, point2 b, point2 c){
  glColor3f(1,1,1);
  glBegin(GL_LINE_LOOP);
   glVertex2fv(a);
   glVertex2fv(b);
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

        divide_triangle(a, v0, v1, m-1);
        divide_triangle(c, v1, v2, m-1);
        divide_triangle(b, v2, v0, m-1);
    }
    else
	triangle(a,b,c);
}


void display ( ){
    divide_triangle(v[0], v[1], v[2], n);
    divide_triangle(v[0], v[1], v[2], n);
    divide_triangle(v[0], v[1], v[2], n);
    divide_triangle(v[0], v[1], v[2], n);

}

void myinit ( ){
  glClearColor ( 0, 0, 0, 0 );
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f ( 0, 0, 0 );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-9.9983, 9.9983, -9.9983, 9.9983);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void MouseButton(int button,int state,int x, int y){
  if (button==GLUT_LEFT_BUTTON){
    if (state==GLUT_DOWN){
      n++;
      glutPostRedisplay();    }
  }
}

void processNormalKeys(unsigned char key, int x, int y){
	if (key == 27){
    value=0;
    n=0;
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
  }
}

int main ( int argc, char *argv[] ){
  glutInit ( &argc, argv );
  glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize(glutGet (GLUT_SCREEN_WIDTH), glutGet (GLUT_SCREEN_HEIGHT));
  glutInitWindowPosition ( 0, 0 );
  window = glutCreateWindow ( "Barnsley Fractal Fern" );
  glutDisplayFunc ( display );
  glutMouseFunc(MouseButton);

  myinit ( );
  	glutKeyboardFunc(processNormalKeys);
  glutMainLoop ( );
  return 0;
}

