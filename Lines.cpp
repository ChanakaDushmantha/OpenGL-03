#include <iostream>
#include <GL/glut.h>
#include <math.h>

float x1,x2,y11=0,y2;
int ww = 600, wh = 400;

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q')
        exit(0);
	else if (key == 'e' || key == 'E'){
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void myinit()
{            
     glViewport(0,0,ww,wh);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);
     glMatrixMode(GL_MODELVIEW);	 
}

void setPixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	glFlush();
}

void horizontal()
{
	if(x1>x2)
	{
		float temp;
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	for(float x=x1; x<=x2; x++)
	{
		setPixel(x,y11);
	}
}

void vertical()
{
	if(y11>y2)
	{
		float temp;
		temp = y11;
		y11 = y2;
		y2 = temp;
	}
	for(float y=y11; y<=y2; y++)
	{
		setPixel(x1,y);
	}
}

void bresenham1()
{
	if(x1>x2)
	{
		float temp;
		temp = x1;
		x1 = x2;
		x2 = temp;
		temp = y11;
		y11 = y2;
		y2 = temp;
	}
	int x = x1, y = y11;
	int dx = x2-x1;
	//std::cout<<dx<<", ";
	int dy = y2-y11;
	//std::cout<<dy<<" ";
	int dT = 2*(dy-dx);
	int dS = 2*dy;
	int d = 2*dy-dx;

	setPixel(x,y);
	while(x<x2)
	{
		x++;
		if(d<0)
		{
			d = d+dS;
		}
		else
		{
			d = d+dT;
			y++;
		}
		setPixel(x,y);
	}
	setPixel(x2,y2);
}

void bresenham2()
{
	if(x1>x2)
	{
		float temp;
		temp = x1;
		x1 = x2;
		x2 = temp;
		temp = y11;
		y11 = y2;
		y2 = temp;
	}
	int x = x1, y = y11;
	int dx = x2-x1;
	int dy = y2-y11;
	int dT = 2*(dy+dx);
	int dS = 2*dy;
	int d = -(2*dx+dy);

	setPixel(x,y);
	while(x<x2)
	{
		x++;
		if(d<0)
		{
			d = d-dS;
		}
		else
		{
			y--;
			d = d-dT;
		}
		setPixel(x,y);
	}
	setPixel(x2,y2);
}

void bresenham3()
{
if(y11>y2)
{
float temp;
temp = x1;
x1 = x2;
x2 = temp;
temp = y11;
y11 = y2;
y2 = temp;
}
int x = x1, y = y11;
int dx = x2-x1;
int dy = y2-y11;
int dT = 2*(dx-dy);
int dS = 2*dx;
int d = 2*dx-dy;

setPixel(x,y);
while(y<y2)
{
y++;
if(d<0)
{
d = d+dS;
}
else
{
x++;
d = d+dT;
}
setPixel(x,y);
}
setPixel(x2,y2);
}

void bresenham4()
{
if(y11>y2)
{
float temp;
temp = x1;
x1 = x2;
x2 = temp;
temp = y11;
y11 = y2;
y2 = temp;
}
int x = x1, y = y11;
int dx = x2-x1;
int dy = y2-y11;
int dT = 2*(dy+dx);
int dS = 2*dx;
int d = -(2*dy+dx);

setPixel(x,y);
while(y<y2)
{
y++;
if(d<0)
{
d = d-dS;
}
else
{
x--;
d = d-dT;
}
setPixel(x,y);
}
setPixel(x2,y2);
}

void myMouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			x1 = x;
			y11 = wh-y;
		}
		else if(state == GLUT_UP)
		{
			x2 = x;
			y2 = wh-y;

			if(y11==y2) horizontal();
			else if(x1==x2) vertical();

			float m = (y2-y11)/(x2-x1);

			if(0<m && m<1) bresenham1();
			else if(0>m && m>-1) bresenham2();
			else if(1<m) bresenham3();
			else if(-1>m) bresenham4();
		}
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww,wh);
	glutCreateWindow("Bresenham's Lines");
	myinit();
	glutDisplayFunc(display);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(keyboard); 
	glutMainLoop();
    
	return 0;
}