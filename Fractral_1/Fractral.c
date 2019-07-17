#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>

void init()
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-320,320,-240,240);
}

void drawTree(int currentDepth, int maxDepth, int angle)
{
    if (currentDepth > maxDepth)
        return;
   if (currentDepth <= maxDepth - 2)
    {
        glColor3d(0.5, 0.4, 0.0);                     //set branch color   0.55,0.3,0.08
         glLineWidth(10 * (pow(0.7, currentDepth)));      //set branch line  width
    }
    else
    {
        glColor3d(0.3, 0.5, 0);            //set leaf color
        glLineWidth(30 * (pow(0.7, currentDepth)));        // set leaf line width
    }

    double lineLen = 100 * pow(0.7,currentDepth);
    glBegin(GL_LINES);
    glVertex2d(0, 0);
    glVertex2d(0, lineLen);
    glEnd();

    int angle1 = angle;
    int angle2 = angle;

    glTranslated(0, lineLen, 0);
    glRotated(-angle1, 0, 0, 1);
    drawTree(currentDepth + 1, maxDepth, angle);
    glRotated(angle1 + angle2, 0, 0, 1);
    drawTree(currentDepth + 1, maxDepth, angle);
    glRotated(-angle2, 0, 0, 1);
    glTranslated(0, -lineLen, 0);
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.03,0.03,0.0);
    glPushMatrix();
    glScalef(0.8,0.8,0);
glTranslated(400,-300,0);
    glRotatef(45,0,0,1);
    drawTree(1,13, 35);
glPopMatrix();
glPushMatrix();
glScalef(0.8,0.8,0);
glTranslated(400,300,0);
    glRotatef(135,0,0,1);
    drawTree(1,13, 35);
glPopMatrix();
glPushMatrix();
glScalef(0.8,0.8,0);
glTranslated(-400,300,0);
    glRotatef(225,0,0,1);
    drawTree(1,13, 35);
glPopMatrix();
glPushMatrix();
glScalef(0.8,0.8,0);
glTranslated(-400,-300,0);
    glRotatef(315,0,0,1);
    drawTree(1,13, 35);
glPopMatrix();
//glTranslated(0, 0,0);
    //glRotatef(315,0,0,1);
   glScalef(1.2,1.2,0);
    drawTree(1,10, 80);
glPopMatrix();
//glTranslated(0, 0,0);
//glScalef(0.7,0.7,0);
    glRotatef(90,0,0,1);
    drawTree(1,10, 80);
glPopMatrix();
//glScalef(0.7,0.7,0);
    glRotatef(180,0,0,1);
    drawTree(1,10, 80);
glPopMatrix();
//glScalef(0.7,0.7,0);
    glRotatef(270,0,0,1);
    drawTree(1,10, 80);
glPopMatrix();
    glEnd();
    glFlush();
}
int main(int argc,char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Ujjawal");
    glutDisplayFunc(display);

    init();

    glutMainLoop();
    return 0;
}

