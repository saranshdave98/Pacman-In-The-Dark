#include <GL/glut.h>
#include "game.h"

int gridX, gridY;

int arr[10][10] = {};
int arr2[21][21] = {};
int arr3[21][21] = {};
int coll[21][21] = {};
int stack[100000] = {};
int xarr[1000] = {};
int yarr[1000] = {};
int top = 0;
int front = 0;
int p1var = -500;
int p2var = -500;
int max = -1;
int maxx = 0;
int maxy = 0;
int flag = 0;
extern float health;
extern int score;
extern float light;
extern int xr;
extern int yr;
extern int xe;
extern int ye;
extern int tim;
extern int dir;
extern int dir1;
extern int zoom;
extern int over;

const float DEG2RAD = 3.14159 / 180;

void unit(int, int, float, float, float, int);
void square(int, int, float, float, float, int);
void pacman(int, int, float, float, float, float, int, int);
void circle(int, int, float, float, float, float);
void endecide();
void move();

bool collision(unsigned char key, int x, int y)
{
	int xn, yn;
	xn = (x + 10 - 40)/20;
	yn = (y + 10 - 60)/20;

	if (key == GLUT_KEY_RIGHT)
	{
		if (arr2[xn + 1][yn])
		{
			if (!arr2[xn + 1][yn + 1])
				if (((xn * 20 + 60) - (x + 10))*((xn * 20 + 60) - (x + 10)) + ((yn * 20 + 80) - (y + 10))*((yn * 20 + 80) - (y + 10)) < 25)
					return 1;
			if (!arr2[xn + 1][yn - 1])
				if (((xn * 20 + 60) - (x + 10))*((xn * 20 + 60) - (x + 10)) + ((yn * 20 + 60) - (y + 10))*((yn * 20 + 60) - (y + 10)) < 25)
					return 1;
			return 0;
		}
		else
		{
			if ((xn * 20 + 60) - (x + 15) >= 0)
				return 0;
			else
				return 1;
		}
	}
	if (key == GLUT_KEY_LEFT)
	{
		if (arr2[xn - 1][yn])
		{
			if (!arr2[xn - 1][yn + 1])
				if (((xn * 20 + 40) - (x + 10))*((xn * 20 + 40) - (x + 10)) + ((yn * 20 + 80) - (y + 10))*((yn * 20 + 80) - (y + 10)) < 25)
					return 1;
			if (!arr2[xn - 1][yn - 1])
				if (((xn * 20 + 40) - (x + 10))*((xn * 20 + 40) - (x + 10)) + ((yn * 20 + 60) - (y + 10))*((yn * 20 + 60) - (y + 10)) < 25)
					return 1;
			return 0;
		}
		else
		{
			if ((x + 5) - (xn * 20 + 40) >= 0)
				return 0;
			else
				return 1;
		}
	}
	if (key == GLUT_KEY_UP)
	{
		if (arr2[xn][yn + 1])
		{
			if (!arr2[xn + 1][yn + 1])
				if (((xn * 20 + 60) - (x + 10))*((xn * 20 + 60) - (x + 10)) + ((yn * 20 + 80) - (y + 10))*((yn * 20 + 80) - (y + 10)) < 25)
					return 1;
			if (!arr2[xn - 1][yn + 1])
				if (((xn * 20 + 40) - (x + 10))*((xn * 20 + 40) - (x + 10)) + ((yn * 20 + 80) - (y + 10))*((yn * 20 + 80) - (y + 10)) < 25)
					return 1;
			return 0;
		}
		else
		{
			if ((yn * 20 + 80) - (y + 15) >= 0)
				return 0;
			else
				return 1;
		}
	}
	if (key == GLUT_KEY_DOWN)
	{
		if (arr2[xn][yn - 1])
		{
			if (!arr2[xn + 1][yn - 1])
				if (((xn * 20 + 60) - (x + 10))*((xn * 20 + 60) - (x + 10)) + ((yn * 20 + 60) - (y + 10))*((yn * 20 + 60) - (y + 10)) < 25)
					return 1;
			if (!arr2[xn - 1][yn - 1])
				if (((xn * 20 + 40) - (x + 10))*((xn * 20 + 40) - (x + 10)) + ((yn * 20 + 60) - (y + 10))*((yn * 20 + 60) - (y + 10)) < 25)
					return 1;
			return 0;
		}
		else
		{
			if ((y + 5) - (yn * 20 + 60) >= 0)
				return 0;
			else
				return 1;
		}
	}
}


void keyboard(int key, int x, int y)
{
	int inc = 1;
	if (tim < p1var+300)
		inc = 3;
	switch (key)
	{
		case GLUT_KEY_UP:
			dir = 1;
			if (!collision(key, xr, yr + inc))
				yr = yr + inc;
			break;
		case GLUT_KEY_DOWN:
			dir = 3;
			if (!collision(key, xr, yr - inc))
				yr = yr - inc;
			break;
		case GLUT_KEY_LEFT:
			dir = 2;
			if (!collision(key, xr - inc, yr))
				xr = xr - inc;
			break;
		case GLUT_KEY_RIGHT:
			dir = 0;
			if (!collision(key, xr + inc, yr))
				xr = xr + inc;
			break;
		case GLUT_KEY_PAGE_UP:
			if (zoom < 20)
				zoom++;
			break;
		case GLUT_KEY_PAGE_DOWN:
			if (zoom > 0)
				zoom--;
			break;

	}
}

int ijToLoc(int i, int j)
{
	return i + 10 * j;
}

void mazeGen(int x, int y, int xp, int yp)
{
	if (x < 10 && x >= 0 && y <10 && y >= 0 && arr[x][y] == 0)
	{
		int cnt = 0, f1 = 0, f2 = 0, f3 = 0, f4 = 0;
		arr[x][y] = 1;
		stack[front] = ijToLoc(x, y);
		front++;

		xarr[top] = x * 40 + 60;
		yarr[top] = y * 40 + 80;
		arr2[1 + 2 * x][1 + 2 * y] = 1;
		arr3[1 + 2 * x][1 + 2 * y] = rand()%6;
		top++;
		xarr[top] = xp * 40 + 60;
		yarr[top] = yp * 40 + 80;
		arr2[1 + 2 * xp][1 + 2 * yp] = 1;
		arr3[1 + 2 * xp][1 + 2 * yp] = rand() % 6;
		top++;
		xarr[top] = (x + xp) * 20 + 60;
		yarr[top] = (y + yp) * 20 + 80;
		arr2[1 + x +xp][1 + y + yp] = 1;
		arr3[1 + x + xp][1 + y + yp] = rand() % 6;
		top++;

		while (cnt < 4)
		{
			int random = rand()%4;
			if (random == 0 && f1 == 0)
			{
				mazeGen(x, y-1,x,y);
				cnt++;
				f1 = 1;
			}
			if (random == 1 && f2 == 0)
			{
				mazeGen(x, y+1,x,y);
				cnt++;
				f2 = 1;
			}
			if (random == 2 && f3 == 0)
			{
				mazeGen(x+1, y,x,y);
				cnt++;
				f3 = 1;
			}
			if (random == 3 && f4 == 0)
			{
				mazeGen(x-1, y,x,y);
				cnt++;
				f4 = 1;
			}
		}
		--front;
		stack[front] = 0;
	}
}

void drawMaze()
{

	square(40, 60, 0, 0, 0, 420);

	srand(time(0));

	mazeGen(rand()%10, rand()%10, 0, 0);

	for (int x = 0; x < top; x++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				square(xarr[x]+5*i, yarr[x]+5*j, 1, 1, 1, 5);
			}
		}
	}
	arr3[1][1] = 0;

	for (int x = 0; x < 21; x++)
	{
		for (int y = 0; y < 21; y++)
		{
			if (x + y > max)
			{
				maxx = x;
				maxy = y;
			}
			if (arr3[x][y])
			{
				if (arr3[x][y] == 1)
				{
					circle(x * 20 + 40, y * 20 + 60, 0, 1, 0, 1);
					if ((xr - (x * 20 + 40))*(xr - (x * 20 + 40)) + (yr - (y * 20 + 60))*(yr - (y * 20 + 60)) <= 36)
					{
						arr3[x][y] = 0;
						score++;
					}
				}
				if (arr3[x][y] == 2)
				{
					circle(x * 20 + 40, y * 20 + 60, 1, 1, 0, 1);
					if ((xr - (x * 20 + 40))*(xr - (x * 20 + 40)) + (yr - (y * 20 + 60))*(yr - (y * 20 + 60)) <= 36)
					{
						arr3[x][y] = 0;
						if (light <= 90)
							light += 10;
						else if (light <= 100)
							light = 100;
					}
				}
				if (arr3[x][y] == 3)
				{
					circle(x * 20 + 40, y * 20 + 60, 1, 0, 0, 1);
					if ((xr - (x * 20 + 40))*(xr - (x * 20 + 40)) + (yr - (y * 20 + 60))*(yr - (y * 20 + 60)) <= 36)
					{
						arr3[x][y] = 0;
						if (tim >= p2var + 300)
							health-=10;
						if (health <= 0)
							over = 1;
					}
				}
				if (arr3[x][y] == 4)
				{
					square(x * 20 + 40+9, y * 20 + 60+9, 0, 0.5, 0.5, 2);
					if ((xr - (x * 20 + 40))*(xr - (x * 20 + 40)) + (yr - (y * 20 + 60))*(yr - (y * 20 + 60)) <= 49)
					{
						arr3[x][y] = 0;
						p1var = tim;
					}
				}
				if (arr3[x][y] == 5)
				{
					square(x * 20 + 40 + 9, y * 20 + 60 + 9, 0.5, 0, 0.5, 2);
					if ((xr - (x * 20 + 40))*(xr - (x * 20 + 40)) + (yr - (y * 20 + 60))*(yr - (y * 20 + 60)) <= 49)
					{
						arr3[x][y] = 0;
						p2var = tim;
					}
				}
				if (arr3[x][y] == 6)
				{
					square(x * 20 + 20, y * 20 + 40, 1, 0, 0, 20);
					if ((xr - (x * 20 + 30))*(xr - (x * 20 + 30)) + (yr - (y * 20 + 50))*(yr - (y * 20 + 50)) <= 225)
					{
						over = 2;
					}
				}
			}
		}
	}

	arr3[maxx][maxy] = 6;

	if (!flag)
	{
		xe = maxx * 20 + 20;
		ye = maxy * 20 + 40;
		flag = 1;
	}

	pacman(xe, ye, 1.0, 0.0, 0.0, 5, tim%30, dir1);
	endecide();
	move();

	pacman(xr, yr, 0.8, 0.8, 0, 5,tim%30,dir);

	if ((xe - xr)*(xe - xr) + (ye - yr)*(ye - yr) <= 100)
		over = 1;

	tim++;
	if(tim%30==0)
		if (light>0)
			light--;
}

void move()
{
	if (dir1 == 0)
		xe++;
	if (dir1 == 1)
		ye++;
	if (dir1 == 2)
		xe--;
	if (dir1 == 3)
		ye--;
}

void endecide()
{
	int xn, yn;
	xn = (xe + 10 - 40) / 20;
	yn = (ye + 10 - 60) / 20;
	if (xe % 20 == 0 && ye % 20 == 0)
	{
		if ((dir1 == 0 && arr2[xn][yn + 1]) || (dir1 == 0 && arr2[xn][yn - 1]))
		{
			int br = 0;
			while (!br)
			{
				int ron = rand() % 3;
				if (ron == 0 && arr2[xn+1][yn])
				{
					dir1 = 0;
					br = 1;
				}
				if (ron == 1 && arr2[xn][yn+1])
				{
					dir1 = 1;
					br = 1;
				}
				if (ron == 2 && arr2[xn][yn - 1])
				{
					dir1 = 3;
					br = 1;
				}
			}
		}
		else if (dir1 == 0 && !arr2[xn + 1][yn])
			dir1 = 2;
		if (dir1 == 1 && (arr2[xn+1][yn] || arr2[xn-1][yn]))
		{
			int br = 0;
			while (!br)
			{
				int ron = rand() % 3;
				if (ron == 0 && arr2[xn][yn+1])
				{
					dir1 = 1;
					br = 1;
				}
				if (ron == 1 && arr2[xn+1][yn])
				{
					dir1 = 0;
					br = 1;
				}
				if (ron == 2 && arr2[xn-1][yn])
				{
					dir1 = 2;
					br = 1;
				}
			}
		}
		else if (dir1 == 1 && !arr2[xn][yn + 1])
			dir1 = 3;
		if (dir1 == 2 && (arr2[xn][yn + 1] || arr2[xn][yn - 1]))
		{
			int br = 0;
			while (!br)
			{
				int ron = rand() % 3;
				if (ron == 0 && arr2[xn - 1][yn])
				{
					dir1 = 2;
					br = 1;
				}
				if (ron == 1 && arr2[xn][yn + 1])
				{
					dir1 = 1;
					br = 1;
				}
				if (ron == 2 && arr2[xn][yn - 1])
				{
					dir1 = 3;
					br = 1;
				}
			}
		}
		else if (dir1 == 2 && !arr2[xn - 1][yn])
			dir1 = 0;
		if (dir1 == 3 && (arr2[xn+1][yn] || arr2[xn-1][yn]))
		{
			int br = 0;
			while (!br)
			{
				int ron = rand() % 3;
				if (ron == 0 && arr2[xn][yn-1])
				{
					dir1 = 3;
					br = 1;
				}
				if (ron == 1 && arr2[xn+1][yn])
				{
					dir1 = 0;
					br = 1;
				}
				if (ron == 2 && arr2[xn-1][yn])
				{
					dir1 = 2;
					br = 1;
				}
			}
		}
		else if (dir1 == 3 && !arr2[xn][yn - 1])
			dir1 = 1;
	}
}

void unit(int x, int y, float r, float g, float b, int l)
{
	glLineWidth(2.0);
	glColor3f(r,g,b);
	glBegin(GL_LINE_LOOP);
	glVertex3f(x, y, 0);
	glVertex3f(x+l, y, 0);
	glVertex3f(x+l, y+l, 0);
	glVertex3f(x, y+l, 0);
	glEnd();
}

void square(int x, int y, float r, float g, float b, int l)
{
	GLfloat color[] = { r*((light / 100)*0.95 + 0.05),g*((light / 100)*0.95 + 0.05),b*((light / 100)*0.95 + 0.05),1.0 };
	GLfloat black[] = { 0,0,0,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, black);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color);
	glMaterialf(GL_FRONT, GL_SHININESS, 70.0);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(x, y, 0);
	glVertex3f(x + l, y, 0);
	glVertex3f(x + l, y + l, 0);
	glVertex3f(x, y + l, 0);
	glEnd();
}

void circle(int xc, int yc, float r, float g, float b, float radius)
{
	GLfloat color[] = { r*((light / 100)*0.95 + 0.05),g*((light / 100)*0.95 + 0.05),b*((light / 100)*0.95 + 0.05),1.0 };
	GLfloat black[] = { 0,0,0,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, black);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color);
	glMaterialf(GL_FRONT, GL_SHININESS, 70.0);
	glBegin(GL_POLYGON);

	for (int i = 0; i < 360; i++)
	{
		float degInRad = i*DEG2RAD;
		glVertex3f(xc + 10 + cos(degInRad)*radius, yc + 10 + sin(degInRad)*radius,0);
	}

	glEnd();
}

void pacman(int xc, int yc, float r, float g, float b, float radius, int t, int dir)
{
	GLfloat color[] = { r*((light / 100)*0.95 + 0.05),g*((light / 100)*0.95 + 0.05),b*((light / 100)*0.95 + 0.05),1.0 };
	GLfloat black[] = { 0,0,0,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, black);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color);
	glMaterialf(GL_FRONT, GL_SHININESS, 70.0);
	glBegin(GL_POLYGON);

	int tn = abs(t*2-30);

	glVertex3f(xc + 10, yc + 10, 0);

	for (int i = tn; i < 360-tn; i++)
	{
		float degInRad = (i+dir*90)*DEG2RAD;
		glVertex3f(xc + 10 + cos(degInRad)*radius, yc + 10 + sin(degInRad)*radius, 0);
	}

	glEnd();
}