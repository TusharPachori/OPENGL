//# include <cstdlib>
# include <iostream>
# include <GL/glut.h>

using namespace std;

int main ( int argc, char *argv[] );
void display ( );
void myinit ( );

typedef GLfloat point2[2];

int main ( int argc, char *argv[] ){
  glutInit ( &argc, argv );
  glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize ( 400, 600 );
  glutInitWindowPosition ( 0, 0 );
  glutCreateWindow ( "Barnsley Fractal Fern" );
  glutDisplayFunc ( display );
  myinit ( );
  glutMainLoop ( );
  return 0;
}


void display ( ){
  int i;
  point2 p;
  int point_num = 500000;
  double prob[4] = { 0.85, 0.92, 0.99, 1.00 };
  double r;
  double x;
  double y;


  glClear ( GL_COLOR_BUFFER_BIT );

  p[0] = 0.4;//drand48 ( );
  p[1] = 0.4;//drand48 ( );

  for ( i = 0; i < point_num; i++ )
  {
    r = drand48 ( );

    if ( r < prob[0] )
    {
      x =   0.85 * p[0] + 0.04 * p[1] + 0.0;
      y = - 0.04 * p[0] + 0.85 * p[1] + 1.6;
    }
    else if ( r < prob[1] )
    {
      x =   0.20 * p[0] - 0.26 * p[1] + 0.0;
      y =   0.23 * p[0] + 0.22 * p[1] + 1.6;
    }
    else if ( r < prob[2] )
    {
      x = - 0.15 * p[0] + 0.28 * p[1] + 0.0;
      y =   0.26 * p[0] + 0.24 * p[1] + 0.44;
    }
    else
    {
      x =   0.00 * p[0] + 0.00 * p[1] + 0.0;
      y =   0.00 * p[0] + 0.16 * p[1] + 0.0;
    }

    p[0] = x;
    p[1] = y;

    glBegin ( GL_POINTS );
      glVertex2fv ( p );
    glEnd ( );
  }

  glFlush ( );

  return;
}

void myinit ( ){

  glClearColor ( 1.0, 1.0, 1.0, 1.0 );
  glColor3f ( 0.133, 0.545, 0.133 );
  glMatrixMode ( GL_PROJECTION );
  glLoadIdentity ( );
  gluOrtho2D ( -4.0, 4.0, -1.0, 11.0 );
  glMatrixMode ( GL_MODELVIEW );

  return;
}

