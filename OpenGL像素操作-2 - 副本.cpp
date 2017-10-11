#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define WIDTH 400
#define HEIGHT 400
#define BMP_Header_Length 54

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
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.5f, 1.0f);
	glEnd();
	glPixelZoom(-0.5f, -0.5f);
	glRasterPos2i(1, 1);
	glCopyPixels(WIDTH / 2, HEIGHT / 2, WIDTH / 2, HEIGHT / 2, GL_COLOR);
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