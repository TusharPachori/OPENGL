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

const float DEG2RAD = 3.14159/180;

int n;

void nextPoint(){
  float nextX, nextY;

  float r = rand();

  if (r/RAND_MAX<0.01){
    glColor3f ( 1, 1, 1 );
    nextX = 0;
    nextY = 0.16*y;
  }else if(r/RAND_MAX<0.86){
    glColor3f (0, 1,0 );
    nextX = 0.85*x + 0.04*y + 0;
    nextY = -0.04*x + 0.85*y + 1.6;
  }else if(r/RAND_MAX<0.93){
    glColor3f ( 0, 0, 1 );
    nextX = 0.20*x - 0.26*y + 0;
    nextY = 0.23*x + 0.22*y + 1.6;
  }else{
    glColor3f ( 1, 0, 0 );
    nextX = -0.15*x + 0.28*y + 0;
    nextY = 0.26*x + 0.24*y + 0.44;
  }
  x=nextX;
  y=nextY;
}

void drawPoint(){
  glPointSize(2);
  glBegin(GL_POINTS);
    glVertex2f(x, y);
    glVertex2f(-x, -y);
    glVertex2f(y, -x);
    glVertex2f(-y, x);
  glEnd();
}

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

        divide_triangle(a, v0, v1, m-1);
        divide_triangle(c, v1, v2, m-1);
        divide_triangle(b, v2, v0, m-1);
    }
    else
	triangle(a,b,c);
}

void draw_pixel(int x, int y) {
  glColor3f(1.0,0.0,0.0);

	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
}

void drawCircle(float x, float y, float r, int iter){
   glBegin(GL_LINE_LOOP);
   for (int i=0; i < 360; i++){
      float degInRad = i*DEG2RAD;
      glVertex2f(x+cos(degInRad)*r,y+sin(degInRad)*r);
   }
   glEnd();
   glFlush();
   if(iter>0){
     iter--;
     glColor3f(1,0,0);
     drawCircle(x+r,y, r/2, iter);
     glColor3f(0,1,0);
     drawCircle(x-r,y, r/2, iter);
     glColor3f(0,0,1);
     drawCircle(x,y+r, r/2, iter);
     glColor3f(1,1,1);
     drawCircle(x,y-r, r/2, iter);
   }
}

void drawsquare(float x, float y, float r, int iter){
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
  glFlush();
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
  glFlush();

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
  glFlush();
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
  glFlush();

  if(iter>0){
    iter--;
    drawsquare(x-r/2, y-r/2, r/2, iter);
    drawsquare(x+r/2, y-r/2, r/2, iter);
    drawsquare(x+r/2, y+r/2, r/2, iter);
    drawsquare(x-r/2, y+r/2, r/2, iter);

  }
}

void display ( ){
  if (value==2){
    for (int i=0; i<25;i++){
      drawPoint();
      nextPoint();
    }
    glFlush();
  }else if (value==3){
    divide_triangle(v[0], v[1], v[2], n);
  }
  else if (value==4){
    drawCircle(0,0, 4.99915, n);
  }else if (value==5){
    drawsquare(0,0,4, n);
  }
  glutPostRedisplay();
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

void menu(int num){
  glClear(GL_COLOR_BUFFER_BIT);
  if(num == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
    n=0;
        value = num;
  }
  glutPostRedisplay();
}

void createMenu(void){
    submenu_id = glutCreateMenu(menu);
      glutAddMenuEntry("FERN", 2);
      glutAddMenuEntry(" USING TRIANGLE", 3);
      glutAddMenuEntry(" USING CIRCLE", 4);
      glutAddMenuEntry(" USING SQUARE", 5);
    menu_id = glutCreateMenu(menu);
      glutAddMenuEntry("Clear", 1);
      glutAddSubMenu("Fractals", submenu_id);
      glutAddMenuEntry("Quit", 0);
      glutAttachMenu(GLUT_RIGHT_BUTTON);
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
  glutInitWindowSize(1200, 800);
  glutInitWindowPosition ( 0, 0 );
  window = glutCreateWindow ( "Barnsley Fractal Fern" );
  glutDisplayFunc ( display );
  glutMouseFunc(MouseButton);

  myinit ( );
  createMenu();
  	glutKeyboardFunc(processNormalKeys);
  glutMainLoop ( );
  return 0;
}

