#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define WIDTH 400
#define HEIGHT 400
#define BMP_Header_Length 54
void setLight(void)
{
	static const GLfloat light_position[] = { 1.0f, 1.0f, -1.0f, 1.0f };
	static const GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	static const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void setMaterial(const GLfloat mat_diffuse[4], GLfloat mat_shininess)
{
	static const GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_emission);

}

void grab(void)
{
	FILE* pDummyFile;
	FILE* pWritingFile;
	GLubyte* pPixelData;
	GLubyte BMP_Header[BMP_Header_Length];
	GLint i, j;
	GLint PixelDataLength;
	i = WIDTH * 3;
	while (i % 4 != 0)
		++i;
	PixelDataLength = i*HEIGHT;

	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if (pPixelData == 0)
	{
		exit(0);
	}
	pDummyFile = fopen("dummy.bmp", "rb");
	if (pDummyFile == 0)
	{
		exit(0);
	}
	pWritingFile = fopen("grab.bmp", "wb");
	if (pWritingFile == 0)
		exit(0);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, WIDTH, HEIGHT, GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET);

	i = WIDTH;
	j = HEIGHT;

	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	fclose(pDummyFile);
	fclose(pWritingFile);
	free(pPixelData);

}

void myDisplay(void)
{
	const static GLfloat red_color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	const static GLfloat green_color[] = { 0.0f, 1.0f, 0.0f, 0.3333f };
	const static GLfloat blue_color[] = { 0.0f, 0.0f, 1.0f, 0.5f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	setLight();

	setMaterial(red_color, 30.0);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.5f);
	glutSolidSphere(0.2, 30, 30);
	glPopMatrix();

	glDepthMask(GL_FALSE);


	setMaterial(blue_color, 30.0);
	glPushMatrix();
	glTranslatef(0.2f, 0.0f, -0.5f);
	glutSolidSphere(0.2, 30, 30);
	glPopMatrix();

	setMaterial(green_color, 20);
	glPushMatrix();
	glTranslatef(0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.15, 30, 30);
	glPopMatrix();

	glDepthMask(GL_TRUE);

	glutSwapBuffers();
	grab();
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