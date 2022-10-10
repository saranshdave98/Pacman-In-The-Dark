#include <GL/glut.h>
#include "game.h"

#define COL 500
#define ROW 500

int xr=60;
int yr=80;
int xe = 0;
int ye = 0;

int tim = 0;
int dir = 0;
int dir1 = 3;
int zoom = 0;
float health = 100;
float light = 100;
int over = 0;
int score = 0;

void display();
void reshape(int,int);
void timer(int);
void drawHUD();

void HUD()
{
	glColor3f(1.0,1.0,0.0);
	float temp = (0.1 + 0.3*(light / 100));
	glBegin(GL_QUADS);
	glVertex2f(0.1, 0.1);
	glVertex2f(temp, 0.1);
	glVertex2f(temp, 0.14);
	glVertex2f(0.1, 0.14);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	float temp2 = (0.1 + 0.3*(health / 100));
	cout << over <<"\n";
	glBegin(GL_QUADS);
	glVertex2f(0.1, 0.1+0.06);
	glVertex2f(temp2, 0.1+0.06);
	glVertex2f(temp2, 0.14+0.06);
	glVertex2f(0.1, 0.14+0.06);
	glEnd();
}

void drawHUD()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	HUD();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambi[] = { 0,0,0,1.0 };
	GLfloat diff[] = { 0,0,0,1.0 };
	GLfloat spec[] = { 1,1,1,1.0 };
	GLfloat pos[] =  { 0,0,1,1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambi);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowSize(500,500);

	glutCreateWindow("Pack-Man Light");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
	glutSpecialFunc(keyboard);
	glutMainLoop();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(xr+10, yr+10, 70-zoom,
		xr+10, yr+10, 0,
		0.0f, 1.0f, 0.0f);
	drawMaze();
	drawHUD();
	if (over == 1)
	{
		MessageBox(NULL,"You Lose!!!","GAME OVER", 0);
		exit(0);
	}
	char _score[10];
	itoa(score, _score, 10);
	char text[50] = "Congratulations!!!\nYour Score: ";
	strcat(text, _score);
	if (over == 2)
	{
		MessageBox(NULL, text , "You Win!!!", 0);
		exit(0);
	}
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, -10, 10);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
}