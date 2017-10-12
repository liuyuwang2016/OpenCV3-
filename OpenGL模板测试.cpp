#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define WIDTH 400
#define HEIGHT 400
#define BMP_Header_Length 54

void draw_sphere()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	{
		GLfloat
			pos[] = { 5.0f, 5.0f, 0.0f, 1.0f },
			ambient[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	}
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(0, 0, 2);
	glutSolidSphere(0.5, 20, 20);
	glPopMatrix();
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 5, 25);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 0, 6.5, 0, 0, 0, 0, 1, 0);
	glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
	draw_sphere();

	glClearStencil(0);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 1, 0XFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glEnable(GL_STENCIL_TEST);

	glDisable(GL_LIGHTING);
	glColor3f(0.5f, 0.5f, 0.5f);
	glDepthMask(GL_FALSE);
	glRectf(-1.5f, -1.5f, 1.5f, 1.5f);

	glDepthMask(GL_TRUE);

	glStencilFunc(GL_EQUAL, 1, 0XFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glScalef(1.0f, 1.0f, -1.0f);
	draw_sphere();

	glutSwapBuffers();
	//grab();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("OpenGL");
	glutDisplayFunc(&myDisplay);

	glutMainLoop();
	return 0;
}