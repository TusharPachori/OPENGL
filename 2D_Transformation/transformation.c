#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
static int window;
static int menu_id;
static int submenu_1;
static int submenu_2;
static int submenu_3;
static int value = 0;

float transx=0, transy=0;
int rotate=0;
float scalem=1;

#define MAX_CPTS  25

GLfloat cpts[MAX_CPTS][3];
int ncpts = 0;
static int width = 500, height = 500;
int n=0;
int scale=1;


void drawAlpha()
{
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(0,0);
    glVertex2f(0,1);
    glEnd();
    int i;
    for(i=0; i<ncpts-3; i +=3){
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, cpts[i]);
        glMapGrid1f(n, 0.0, 1.0);
        glEvalMesh1(GL_LINE, 0, n);
    }
    glBegin(GL_LINES);
    glVertex2f(0,0.5);
    glVertex2f(0.5,0);
    glEnd();
    glFlush();
}



void display(){
    cpts[0][0]=-0;
    cpts[0][1]=0.5;
    cpts[1][0]=0.7;
    cpts[1][1]=0.6;
    cpts[2][0]=0.7;
    cpts[2][1]=0.9;
    cpts[3][0]=0;
    cpts[3][1]=1;
    ncpts=4;
    n=500;
    glPushMatrix();
    glTranslated(transx, transy, 0);
    glRotatef(rotate,0,0,1);
    glScalef(scalem,scalem,0);
    drawAlpha();
    glPopMatrix();
    glFlush();
}

void menu(int num){
  glClear(GL_COLOR_BUFFER_BIT);
  if(num == 1){
    transx=transx+0.1;
    transy=transy+0.1;
  }else if(num == 2){
    transx=transx-0.1;
    transy=transy-0.1;
  }else if(num == 3){
    rotate=rotate+10;
  }else if(num == 4){
    rotate=rotate-10;
  }else if(num==5){
    scalem=scalem*1.1;
  }else if(num==6){
    scalem=scalem/1.1;
  }
  glutPostRedisplay();
}

void createMenu(void){
    submenu_1 = glutCreateMenu(menu);
    glutAddMenuEntry("+", 1);
    glutAddMenuEntry("-", 2);
    submenu_2 = glutCreateMenu(menu);
    glutAddMenuEntry("+", 3);
    glutAddMenuEntry("-", 4);
    submenu_3 = glutCreateMenu(menu);
    glutAddMenuEntry("+", 5);
    glutAddMenuEntry("-", 6);
    menu_id = glutCreateMenu(menu);
      glutAddSubMenu("Translate", submenu_1);
      glutAddSubMenu("Rotate", submenu_2);
      glutAddSubMenu("Scale", submenu_3);
      glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void reshape(int w, int h){
    width = w;
    height = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(width, height);
    window = glutCreateWindow("curves");
    glutDisplayFunc(display);
    createMenu();
    glutReshapeFunc(reshape);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glEnable(GL_MAP1_VERTEX_3);
    glutMainLoop();
}

