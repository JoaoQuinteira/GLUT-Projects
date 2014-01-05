#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <GL/glut.h>

#define SW              400
#define SH              400
#define DEBUG           1

int color[9]={0,0,0,0,0,0,0,0,0}; 
/*
0-white
1-red
2-blue
*/
bool player=true; //red starts 1st
bool pc=false;
 
 void Draw();
 void DrawBoard();
 void Init(int w, int h);
 void gl_select(int x, int y);
 void gl_selall(GLint hits, GLuint *buff);
 void mouseClick(/*int button, int state, int x, int y*/);
 void mousedw(int x, int y, int but);
 void draw_block(float x, float y, float z);
 void list_hits(GLint hits, GLuint *names);
 int handleHits(GLint hits, GLuint *names);
 void help();
 void Key(unsigned char key, int x, int y);
 void SpecialKey(int key, int x, int y);
  
 void Draw()
 {
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();
	
	glPushMatrix();
		DrawBoard(); //Draw the panel
	glPopMatrix();

    glutSwapBuffers();
 }
 
 void DrawBoard(){
	glTranslatef(0.0, 0.0, -4.0);
	
	if (color[0]==0) //white
 	glColor3f(1.0, 1.0, 1.0); 
	else if(color[0]==1) //red
	glColor3f(1.0, 0, 0.0);
	else if(color[0]==2) //blue
	glColor3f(0.0, 0, 1.0);

	glLoadName(1); /* Overwrite the first name in the buffer */
 	draw_block(-1, 1, 0);
 
	if (color[1]==0)
 	glColor3f(1.0, 1.0, 1.0); //Cor branca para todos os quadrados
	else if(color[1]==1)
	glColor3f(1.0, 0, 0.0);
	else if(color[1]==2) //blue
	glColor3f(0.0, 0, 1.0);

 	glLoadName(2); /* Overwrite the first name in the buffer */
 	draw_block(0, 1, 0);
 
	if (color[2]==0)
 	glColor3f(1.0, 1.0, 1.0); //Cor branca para todos os quadrados
	else if(color[2]==1)
	glColor3f(1.0, 0, 0.0);
	else if(color[2]==2) //blue
	glColor3f(0.0, 0, 1.0);

 	glLoadName(3); /* Overwrite the first name in the buffer */
 	draw_block(1, 1, 0);

	if (color[3]==0)
 	glColor3f(1.0, 1.0, 1.0); //Cor branca para todos os quadrados
	else if(color[3]==1)
	glColor3f(1.0, 0, 0.0);
	else if(color[3]==2) //blue
	glColor3f(0.0, 0, 1.0);

	glLoadName(4); /* Overwrite the first name in the buffer */
 	draw_block(-1, 0, 0);
 
	if (color[4]==0)
 	glColor3f(1.0, 1.0, 1.0); //Cor branca para todos os quadrados
	else if(color[4]==1)
	glColor3f(1.0, 0, 0.0);
	else if(color[4]==2) //blue
	glColor3f(0.0, 0, 1.0);

 	glLoadName(5); /* Overwrite the first name in the buffer */
 	draw_block(0, 0, 0);
 
	if (color[5]==0)
 	glColor3f(1.0, 1.0, 1.0); //Cor branca para todos os quadrados
	else if(color[5]==1)
	glColor3f(1.0, 0, 0.0);
	else if(color[5]==2) //blue
	glColor3f(0.0, 0, 1.0);

 	glLoadName(6); /* Overwrite the first name in the buffer */
 	draw_block(1, 0, 0);

	if (color[6]==0)
 	glColor3f(1.0, 1.0, 1.0); //Cor branca para todos os quadrados
	else if(color[6]==1)
	glColor3f(1.0, 0, 0.0);
	else if(color[6]==2) //blue
	glColor3f(0.0, 0, 1.0);

	glLoadName(7); /* Overwrite the first name in the buffer */
 	draw_block(-1, -1, 0);
 
	if (color[7]==0)
 	glColor3f(1.0, 1.0, 1.0); //Cor branca para todos os quadrados
	else if(color[7]==1)
	glColor3f(1.0, 0, 0.0);
	else if(color[7]==2) //blue
	glColor3f(0.0, 0, 1.0);

 	glLoadName(8); /* Overwrite the first name in the buffer */
 	draw_block(0, -1, 0);
 
	if (color[8]==0)
 	glColor3f(1.0, 1.0, 1.0); //Cor branca para todos os quadrados
	else if(color[8]==1)
	glColor3f(1.0, 0, 0.0);
	else if(color[8]==2) //blue
	glColor3f(0.0, 0, 1.0);

 	glLoadName(9); /* Overwrite the first name in the buffer */
 	draw_block(1, -1, 0);

 }

 void Init(int w, int h)
 {
 	glClearColor(0.5, 0.5, 0.5, 1.0);
 	glViewport(0, 0, w, h);
 
 	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
 
 	gluPerspective(60.0, 1.0, 0.0001, 1000.0);
 
 	glMatrixMode(GL_MODELVIEW);
 }
 
 //void mouseClick(int button, int state, int x, int y)
 //{
 //   if 	((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	//{
	//	gl_select(x,SH-y);
	//}
 //}


 void mouseClick(int button, int state, int x, int y){
   /*button => GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
     state  => GLUT_UP, GLUT_DOWN
     x,y    => mouse pointer coordinates
   */
	 switch(button){
    case GLUT_LEFT_BUTTON :      
      if(state == GLUT_DOWN){
		  printf("Mouse pointer at %d , %d \n",x,y);
		  gl_select(x,SH-y); //Due to Windows coordinates system and GLUT's
	  	  }
     break;

    case GLUT_RIGHT_BUTTON :
      if(state == GLUT_DOWN){}
      break;
}
 }

 void gl_selall(GLint hits, GLuint *buff)
 {
 	GLuint *p;
 	int i;
 
 	Draw();
 
 	p = buff;
 	for (i = 0; i < 6 * 4; i++)
 	{
 		printf("Slot %d: - Value: %d\n", i, p[i]);
 	}
 
 	printf("Buff size: %x\n", (GLbyte)buff[0]);
 }
 
 void gl_select(int x, int y)
 {
 	GLuint buff[64] = {0};
 	GLint hits, view[4];
 	int pos;
 
 	glSelectBuffer(64, buff); //This choose the buffer where store the values for the selection data
 
 	glGetIntegerv(GL_VIEWPORT, view); //This retrieve info about the viewport
 
 	glRenderMode(GL_SELECT); //Switching in selecton mode
 
 	/* Clearing the name's stack
 		This stack contains all the info about the objects */
 	glInitNames();
 
 	glPushName(0); //fill the stack with one element (or glLoadName will generate an error)
 
 	/* Now modify the vieving volume, restricting selection area around the cursor */
 	glMatrixMode(GL_PROJECTION);
 	glPushMatrix();
 		glLoadIdentity();
 
 		/* restrict the draw to an area around the cursor */
 		gluPickMatrix(x, y, 1.0, 1.0, view);
 		gluPerspective(60, 1.0, 0.0001, 1000.0);
 
 		glMatrixMode(GL_MODELVIEW); //Draw the objects onto the screen
 
 		glutSwapBuffers(); //draw only the names in the stack, and fill the array
 		Draw();
 
 		glMatrixMode(GL_PROJECTION);
 	glPopMatrix();
 
 	/* get number of objects drawed in that area
 		and return to render mode */
 	hits = glRenderMode(GL_RENDER);
 
	if (hits>0){ //If a cube was clicked (could be == 1).

		pos=handleHits(hits,buff); // gets the position of that cube (1-9)
	
 	list_hits(hits, buff); //Print a list of the objects

 	//gl_selall(hits, buff); show the whole buffer
	
	if(color[pos-1]==0){ // if the cube is white
		if(player){ //player 1 coloring 
			color[pos-1]=1; //colors the cube red 
			player=false;
			pc=true;
		}
		else{ //player 2/pc turns
			color[pos-1]=2; //color it blue
			player=true;
			pc=false;
	   }
	
		glMatrixMode(GL_MODELVIEW);
		glutPostRedisplay();	
	}
	else
		glMatrixMode(GL_MODELVIEW);
	}else 
		glMatrixMode(GL_MODELVIEW);
 }
  
 void draw_block(float x, float y, float z)
 {
 	glPushMatrix();
 		glTranslatef(x, y, z);
 		glutSolidCube(0.8);
 	glPopMatrix();
 }
 
int handleHits(GLint hits, GLuint *names){
	 	/* For each hit in the buffer are allocated 4 bytes:
 		1. Number of hits selected 
 		2. Min Z
 		3. Max Z
 		4. Name of the hit (glLoadName) */
	int a=names[3];
	
	return a;	
}

 void list_hits(GLint hits, GLuint *names)
 {
 	int i;
 
 	/*
 		For each hit in the buffer are allocated 4 bytes:
 		1. Number of hits selected (always one,
 									beacuse when we draw each object
 									we use glLoadName, so we replace the
 									prevous name in the stack)
 		2. Min Z
 		3. Max Z
 		4. Name of the hit (glLoadName)
 	*/
 
 	printf("%d hits:\n", hits);
 
 	for (i = 0; i < hits; i++)
 		printf(	"Number: %d\n"
 				"Min Z: %d\n"
 				"Max Z: %d\n"
 				"Name on stack: %d\n",
 				(GLubyte)names[i * 4],
 				(GLubyte)names[i * 4 + 1],
 				(GLubyte)names[i * 4 + 2],
 				(GLubyte)names[i * 4 + 3]
 				);
 
 	printf("\n");
 }
 

void help(void){
  printf("\n\n Light Panel \n");
  printf("h,H - Display this again \n");
  printf("by João Quinteira \n");
  printf("any doubts or bug reporting -> j.quinteira93@hotmail.com");
  printf("ESC - Quit\n");

}



void Key(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      exit(1);

    case 'h' :
    case 'H' :
                help();
  }

  if(DEBUG)
    printf("Key Held:  %c\n",key);

}


 int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowSize(SW, SH);
    glutInitWindowPosition(200, 100);
    if (glutCreateWindow("Light Panel") == GL_FALSE)
    exit(1);

	glutDisplayFunc(Draw);
	/*Mouse Callback*/
    glutMouseFunc(mouseClick);
 
    Init(SW, SH);
 
	 help();

  /* Keyboard Callback  */
  glutKeyboardFunc(Key);

  glutMainLoop();
 
 	return EXIT_SUCCESS;
 }