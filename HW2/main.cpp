#define GLM_ENABLE_EXPERIMENTAL

#include "Object.h"
#include "FreeImage.h"
#include "glew.h"
#include "freeglut.h"
#include "shader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/glm.hpp"
#include <iostream>
#include <string>
#include <math.h>
#include <stb_image.h>

using namespace std;



void shaderInit();
void bindbufferInit();
void textureInit();
void display();
void idle();
void reshape(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void DrawBasis();
void DrawUmbreon();
void LoadTexture(unsigned int&, const char*);

GLuint program;
GLuint VAO, VBO[3];
bool changed = false;
unsigned int basistexture, modeltexture,sky,forest,firework,current;


int windowSize[2] = { 600, 600 };
float angle = 0.0f;

Object* model = new Object("UmbreonHighPoly.obj");

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(windowSize[0], windowSize[1]);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("hw2");

	glewInit();
	shaderInit();
	bindbufferInit();
	textureInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

void shaderInit() {
	//// TODO: ////
	//
	// Hint:
	// 1. createShader
	// 2. createProgram
	GLuint vert = createShader("Shaders/vertexShader.vert","vertex");
	GLuint frag = createShader("Shaders/fragmentShader.frag","fragment");
	program = createProgram(vert,frag);
}

void bindbufferInit() {
	//// TODO: ////
	//
	//	 Hint:
	// 1. Setup VAO
	// 2. Setup VBO of vertex positions, normals, and texcoords
	
	//glGenVertexArrays n-># of vertex array object name to be generated arrays->specified an array in which the generated vertex array object names are stored
	glGenVertexArrays(1 , &VAO);
	glBindVertexArray(VAO);
	//vbo position
	//generate 1 buffer
	glGenBuffers(1,&VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//glBufferData buffer->name of the buffer object for glNameBufferData function size->specify size in byte
	//data-> specify a pointer to data usage->pattern of the data store
	//.data() will return the pointer to the first element of the array 
	glBufferData(GL_ARRAY_BUFFER,model->positions.size()*sizeof(float),model->positions.data() ,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)(0));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//vbo normal
	glGenBuffers(1, &VBO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, model->normals.size() * sizeof(float),model->normals.data(),GL_STATIC_DRAW );
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)(0));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//vbo texture coordinate
	glGenBuffers(1, &VBO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, model->texcoords.size() * sizeof(float),model->texcoords.data(),GL_STATIC_DRAW );
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (GLvoid*)(0));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
	


}

void textureInit() {
	LoadTexture(basistexture, "basis.jpg");
	LoadTexture(modeltexture, "Umbreon.jpg");
	LoadTexture(sky, "sky.jpg");
	LoadTexture(forest, "forest.jpg");
	LoadTexture(firework, "firework.jpg");
}

glm::mat4 getV()
{
	// set camera position and configuration
	return glm::lookAt(glm::vec3(7.5, 5.0, 7.5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}
glm::mat4 getP()
{
	// set perspective view
	float fov = 60.0f;
	float aspect = windowSize[0] / windowSize[1];
	float nearDistance = 1.0f;
	float farDistance = 1000.0f;
	return glm::perspective(glm::radians(fov), aspect, nearDistance, farDistance);
}

void display() {
	//Clear the buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawUmbreon();

	DrawBasis();

	angle += 0.01;
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
	windowSize[0] = w;
	windowSize[1] = h;
}

void LoadTexture(unsigned int& texture, const char* tFileName) {
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(tFileName, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{

   
	case 67:
	case 99:
		
		break;
	//f->firework
	case 70:
	case 102:
		changed = true;
		current = firework;
		break;
	//s->sky
	case 83:
	case 115:
		changed = true;
		current = sky;
		break;
	//o->original
	case 79:
	case 111:
		changed = false;
		current = modeltexture;
		break;
	//t->tree(forest)
	case 84:
	case 116:
		changed = true;
		current = forest;
		break;
	}



}

void idle() {
	glutPostRedisplay();
}

void DrawBasis() {
	// viewport transformation
	glViewport(0, 0, windowSize[0], windowSize[1]);

	// projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)windowSize[0] / (GLfloat)windowSize[1], 1.0, 1000.0);

	// viewing and modeling transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(7.5, 5.0, 7.5,// eye
		0.0, 0.0, 0.0,     // center
		0.0, 1.0, 0.0);    // up

	glPushMatrix();
	glRotatef(angle, 0, 1, 0);

	//// if you don't need this, you can just deleting
	float edge = 20;
	float R = 4;
	float pi = 3.1415926;

	//// TODO: ////
	//
	// draw the basis and make the side of basis with texture
	glBegin(GL_POLYGON);
	glColor3f(0.85f, 0.65f, 0.4f);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	for (int i = 0; i < edge; i++)
	{
		glVertex3f(R * cos(2 * pi / edge * i), 0.0f, R * sin(2 * pi / edge * i));
	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.85f, 0.65f, 0.4f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	for (int i = 0; i < edge; i++)
	{
		glVertex3f(R * cos(2 * pi / edge * i), -3.5f, R * sin(2 * pi / edge * i));
	}
	glEnd();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, basistexture);
	glBegin(GL_QUADS);
	for (int i = 0; i < edge; i++)
	{
		glNormal3f(cos(2 * pi / edge * (i + 0.5)), 0.0f, sin(2 * pi / edge * (i + 0.5)));

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(R * cos(2 * pi / edge * i), 0.0f, R * sin(2 * pi / edge * i));
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(R * cos(2 * pi / edge * (i + 1)), 0.0f, R * sin(2 * pi / edge * (i + 1)));
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(R * cos(2 * pi / edge * (i + 1)), -3.5f, R * sin(2 * pi / edge * (i + 1)));
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(R * cos(2 * pi / edge * i), -3.5f, R * sin(2 * pi / edge * i));	
		
	}glActiveTexture(0);
	
	
	
	glEnd();

	glPopMatrix();
}

void DrawUmbreon()
{

	glUseProgram(program);
	glm::mat4 M(1.0f);
	M = glm::rotate(M, glm::radians(angle), glm::vec3(0, 1, 0));
	M = glm::translate(M, glm::vec3(0, 1.3, 0));

	GLuint ModelMatrixID = glGetUniformLocation(program, "M");
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &M[0][0]);

	//// TODO: ////
	// pass projection matrix, and view matrix and trigger by Uniform (use getP() amd getV())
	// also pass modeltexture to shader and trigger by Uniform

	glm::mat4 Projection = getP();
	GLuint ProjectionID = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &Projection[0][0]);

	glm::mat4 View = getV();
	GLuint ViewID = glGetUniformLocation(program, "modelview");
	glUniformMatrix4fv(ViewID, 1, GL_FALSE, &View[0][0]);

	if(changed==false)current = modeltexture;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,current);
	//glBindTexture(GL_TEXTURE_2D, skytexture);
	GLint texLoc = glGetUniformLocation(program, "Texture");
	glUniform1i(texLoc, 0);
	
	glBindVertexArray(VAO);
	glDrawArrays(GL_QUADS, 0, 4 * model->fNum);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(0);
	
	glUseProgram(0);
}