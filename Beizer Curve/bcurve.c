#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

int n=1;
int automate=0;
int counter=0;
float scale=1;

GLfloat cpts[50][3];
int ncpts = 0;
static int width = 1100, height = 800;

static int window;
static int menu_id;
static int submenu_id;
static int value = 0;


void drawCurves(){
    int i;
    for(i=0; i<ncpts-3; i +=3){
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, cpts[i]);
        glMapGrid1f(n, 0.0, 1.0);
        glEvalMesh1(GL_LINE, 0, n);
    }
    glFlush();
}

void drawPoints(){
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_STRIP);
    for (i = 0; i < ncpts; i++)
        glVertex3fv(cpts[i]);
    glEnd();
    glFlush();
}

void display(){
    //drawPoints();
    if(value==3){
      cpts[0][0]=0;
      cpts[0][1]=0;
      cpts[1][0]=-0.5;
      cpts[1][1]=0.25;
      cpts[2][0]=0.02;
      cpts[2][1]=0.8;
      cpts[3][0]=0;
      cpts[3][1]=1;
      cpts[4][0]=-0.02;
      cpts[4][1]=0.8;
      cpts[5][0]=0.5;
      cpts[5][1]=0.25;
      cpts[6][0]=0;
      cpts[6][1]=0;
      ncpts=7;
      n=500;
      glColor3f(scale, 1-scale, 0);
      glPushMatrix();
      glScalef(scale,scale,0);
      drawCurves();
      glPopMatrix();
      glPushMatrix();
      glTranslated(0, 0.5,0);
      glRotatef(90,0,0,1);
      glTranslated(-0.5,0,0);
      glScalef(scale,scale,0);
      drawCurves();
      glPopMatrix();
      glPushMatrix();
      glTranslated(0, 0.5,0);
      glRotatef(180,0,0,1);
      glTranslated(0, 0.5,0);
      glScalef(scale,scale,0);
      drawCurves();
      glPopMatrix();
      glPushMatrix();
      glTranslated(0, 0.5,0);
      glRotatef(270,0,0,1);
      glTranslated(0.5, 0.0,0);
      glScalef(scale,scale,0);
      drawCurves();
      glPopMatrix();
      scale=scale/1.01;
      glutPostRedisplay();
    }else if(value==2){
      cpts[0][0]=0;
      cpts[0][1]=0;
      cpts[1][0]=-0.5;
      cpts[1][1]=0.25;
      cpts[2][0]=0.02;
      cpts[2][1]=0.8;
      cpts[3][0]=0;
      cpts[3][1]=1;
      cpts[4][0]=-0.02;
      cpts[4][1]=0.8;
      cpts[5][0]=0.5;
      cpts[5][1]=0.25;
      cpts[6][0]=0;
      cpts[6][1]=0;
      ncpts=7;
      n=500;
      glColor3f(1-scale, 1-scale, 1-scale);
      glPushMatrix();
      glScalef(scale,scale,0);
      drawCurves();
      glPopMatrix();
      scale=scale/1.01;
      glutPostRedisplay();
    }
    else if(value==3){

    }
}

void mouse(int button, int state, int x, int y){
    float wx, wy;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
       wx = (2.0 * x) / (float)(width - 1) - 1.0;
       wy = (2.0 * (height - 1 - y)) / (float)(height - 1) - 1.0;
       cpts[ncpts][0] = wx;
       cpts[ncpts][1] = wy;
       cpts[ncpts][2] = 0.0;
       ncpts++;

       glColor3f(1.0, 1.0, 1.0);
       glPointSize(3.0);
       glBegin(GL_POINTS);
          glVertex3f(wx, wy, 0.0);
       glEnd();
       glFlush();
       glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y){
    switch (key){
        case 'q': case 'Q':
            exit(0);
            break;
        case 'c': case 'C':
            ncpts = 0;
            automate=0;
            scale=1;
            glutPostRedisplay();
            break;
        case 'e': case 'E':
        automate=0;
            glutPostRedisplay();
            break;
        case 'b': case 'B':
            automate=1;
            drawCurves();
            break;
        case '+': case'=':
            n++;
            glClear(GL_COLOR_BUFFER_BIT);
            drawPoints();
            drawCurves();
            break;
        case '-': case'_':
            n++;
            glClear(GL_COLOR_BUFFER_BIT);
            drawPoints();
            drawCurves();
            break;
    }
}

void reshape(int w, int h){
    width = w;
    height = h;
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

void idle(){
  if(automate==1){
    counter+=1;
    if(counter==30000 && n<500){
      counter=0;
      n+=1;
      if (n<25){
        glColor3f(0.1, 0.1, 0.1);
      }else if (n<50){
        glColor3f(0.25, 0.25, 0.25);
      } else if (n<75){
        glColor3f(0.5, 0.5, 0.5);
      }else if (n<100){
        glColor3f(0.75, 0.75, 0.75);
      }else if (n<125){
        glColor3f(1.0, 0.0, 0.0);
      }else if (n<150){
        glColor3f(0.5, 0.5, 0.0);
      }else if (n<175){
        glColor3f(0, 1, 0);
      }else if (n<200){
        glColor3f(0.0, 0.5 ,0.5);
      }else if (n<225){
        glColor3f(0, 0, 1);
      }else if (n<250){
        glColor3f(1.0, 1.0, 1.0);
      }
      glClear(GL_COLOR_BUFFER_BIT);
      drawCurves();
    }
  }
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
      glutAddMenuEntry("PETAL", 2);
      glutAddMenuEntry(" FLOWER", 3);
      glutAddMenuEntry(" FREE_DRAW", 4);
    menu_id = glutCreateMenu(menu);
      glutAddMenuEntry("Clear", 1);
      glutAddSubMenu("CURVE", submenu_id);
      glutAddMenuEntry("Quit", 0);
      glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(width, height);
    window = glutCreateWindow("Beizer Curves");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(3.0);
    glEnable(GL_MAP1_VERTEX_3);
    glutIdleFunc(idle);
    createMenu();
    glutMainLoop();
}

