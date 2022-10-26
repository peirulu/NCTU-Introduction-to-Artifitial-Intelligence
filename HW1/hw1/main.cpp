#include "Object.h"
#include "glut.h"
#include <math.h>
#include<iostream>
int windowSize[2],rotate_1=0,rotate_3=0,rotate_all=0,clockwise=1,n=20;

void light();
void display();
void reshape(GLsizei, GLsizei);
void LoadModel(Object*);
void DrawBasis();
void keyboard(unsigned char key, int x, int y);

Object* elephant = new Object("elephant.obj");
Object* cube = new Object("cube.obj");
Object* teapot = new Object("teapot.obj");


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	light();
	glutCreateWindow("HW1");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

void light()
{
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_position[] = { 50.0, 75.0, 80.0, 1.0 };
	glShadeModel(GL_SMOOTH);
	// z buffer enable
	glEnable(GL_DEPTH_TEST);
	// enable lighting
	glEnable(GL_LIGHTING);
	// set light property
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	///TO DO Enable DepthTest
	///
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);


	///TO DO: add lighting, Viewport Matrix, Projection Matrix, ModelView Matrix
	
	//add lighting
	light();

	/***********Viewport matrix***********!!*/
	glViewport(0, 0,500,500 );
	
	/*******Projection matrix*********/
	//
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(fovy->angle in y direction,aspect->ratio of width and height,near->nearz,far->farz)
	gluPerspective(60, 1, 1.0, 1000.0);

	/***********Modelview matrix***************/
	glMatrixMode(GL_MODELVIEW);
	//¬°¦ó­nidentity?clear?
	glLoadIdentity();
	//gluLookAt(cameraxyz,centerxyz,upxyz)
	gluLookAt(20.0f, 20.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	///TO DO: add model, translate, rotate, scale
	
	glPushMatrix();
	glRotated(rotate_all, 0, 1, 0);
	//rotate_all += 1;
	if (clockwise)rotate_all += 1;
	else rotate_all -= 1;
	DrawBasis();
	glTranslatef(-3, 0, 3);
	LoadModel(teapot);
	glPopMatrix();

	glPushMatrix();
	glRotated(rotate_1, 0, 1, 0);
	if (clockwise)rotate_1 += 1;
	else rotate_1 -= 1;
	glTranslated(3,0,-3);
	glRotated(rotate_3,0,1,0);
	rotate_3 += 3;
	LoadModel(elephant);
	glTranslated(-2, 0, -2);
	glTranslated(0, 0.5, 0);
	glScaled(0.5,0.5,0.5);
	LoadModel(cube);
	glPopMatrix();
	


	glutPostRedisplay();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	windowSize[0] = w;
	windowSize[1] = h;
}

void LoadModel(Object* Model)
{
	for (size_t i = 0; i < Model->fNum; ++i)
	{
		glBegin(GL_TRIANGLES);
		for (size_t j = 0; j < 3; ++j)
		{
			glNormal3fv(Model->nList[Model->faceList[i][j].nIndex].ptr);
			glVertex3fv(Model->vList[Model->faceList[i][j].vIndex].ptr);
		}
		glEnd();
	}
}

void DrawBasis()
{
	///TO DO: draw basis
	///
	/************ Draw two 20-edge polygons**************/
	glBegin(GL_POLYGON);
	const GLfloat R = 10.0f;
	const GLfloat pi = acos(-1);

	//draw top
	//glColor3f(0.0f, 1.0f, 0.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	for (int i = 0; i < n; i++)
	{
		glVertex3f(R * cos(2 * pi / n * i), 0.0f, R * sin(2 * pi / n * i));
	}
	glEnd();
	//draw bottom
	glBegin(GL_POLYGON);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	for (int i = 0; i < n; i++)
	{
		glVertex3f(R * cos(2 * pi / n * i), -5.0f, R * sin(2 * pi / n * i));
	}
	glEnd();

	//draw side-rectangles 
	glBegin(GL_QUADS);
	for (int i = 0; i < n; i++)
	{
		glNormal3f(cos(2*pi/n*(i+0.5)), 0.0f,sin(2 * pi / n * (i + 0.5)) );
		glVertex3f(R * cos(2 * pi / n * i), 0.0f, R * sin(2 * pi / n * i));
		glVertex3f(R * cos(2 * pi / n * (i+1)), 0.0f, R * sin(2 * pi / n * (i+1)));
		glVertex3f(R * cos(2 * pi / n * (i + 1)), -5.0f, R * sin(2 * pi / n * (i + 1)));
		glVertex3f(R * cos(2 * pi / n * i), -5.0f, R * sin(2 * pi / n * i));	
	}
	glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
	/// TO DO: Set the keyboard control
	///
	
	switch (key)
	{
	
	//c
	case 67:
	case 99:
		clockwise += 1;
		clockwise %= 2;
		break;
	//add
	case 65:
	case 97:
		n += 1;
		if (n > 100)n = 100;
		cout << "edge:" << n << endl;
		break;
	//decrease
	case 68:
	case 100:
		n -= 1;
		if (n < 4)n = 4;
		cout << "edge:" << n << endl;
		break;
	}

}