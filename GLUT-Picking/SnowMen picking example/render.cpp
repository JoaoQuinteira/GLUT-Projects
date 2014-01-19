#include <stdlib.h>
#include <GL/glut.h>

#include <math.h>
#include <gl\glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdio.h>


#include "render.h"

static GLint snowman_display_list;


void quit() {}


void processKeyboard(unsigned char key, int x, int y) {
	printf("key: %d\n",key);
}


void picked(GLuint name, int sw) {
	printf("my name = %d in %d\n",name,sw);
}


void init(camera *cam) {


	cam->pos[0] = 1.5;
	cam->pos[1] = 3.75;
	cam->pos[2] = 3;

	cam->lookAt[0] = 1.5;
	cam->lookAt[1] = 1.75;
	cam->lookAt[2] = 0;

	cam->lookUp[0] = 0;
	cam->lookUp[1] = 1;
	cam->lookUp[2] = 0;

}


void drawSnowMan() {


	glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body	
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);


// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f,0.5f,10,2);
}



GLuint createDL() {
	GLuint snowManDL;

	// Create the id for the list
	snowManDL = glGenLists(1);

	glNewList(snowManDL,GL_COMPILE);
		drawSnowMan();
	glEndList();

	return(snowManDL);
}


void initScene(int argc, char **argv) {

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	snowman_display_list = createDL();
}



void draw() {

// Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

// Draw 4 SnowMen

	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++) {
			glPushMatrix();
			glPushName(i*2+j);
			glTranslatef(i*3.0,0,-j * 3.0);
			glCallList(snowman_display_list);
			glPopName();
			glPopMatrix();
		}

}




