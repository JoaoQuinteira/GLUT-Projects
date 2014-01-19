//#include "soap\soapBasicHttpBinding_USCOREIServiceProxy.h"
//#include "soap\BasicHttpBinding_USCOREIService.nsmap"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include <string>
#include <GL/glui.h>
#include <sstream>
#include <algorithm>
#include <iterator>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define RAD(x)          (M_PI*(x)/180)
#define GRAUS(x)        (180*(x)/M_PI) //Degrees

#define DEBUG               1

#define HEIGHT                550
#define WIDHT                 750
#define RAIO_CIRCUNFERENCIA   3		//radius
#define COMPRIMENTO_TORSO     8		//body size
#define COMPRIMENTO_MEMBROS   4.5	//size of arms and legs 

#define CHOSEN_CHARS_SIZE     26

using namespace std;

/*----*/

typedef struct {
	GLfloat    x,y,z;
}Pos;

typedef struct {
	Pos      eye,center,up;
	GLfloat  fov;
}Camera;

typedef struct {
	GLboolean   doubleBuffer;
	Camera      camera;
	GLboolean   ortho;
}State;

State state;


string chosenCharsLabel="Chosen Characters:";

string word;
string cat;
GLUI *glui;		//main menu
GLUI *glui1;	//add word menu
GLUI *glui2;	//winwindow
GLUI *glui3;	//losswindow

GLUI_EditText *edittext;
GLUI_EditText *edittext1;
int main_window;

char chosenKeys[CHOSEN_CHARS_SIZE];
int* checkWord; //vai ter o mesmo tamanho da palavra e vai conter 0 ou 1 nas diferentes posiçoes caso o user ja tenha acertado na letra nessa mesma posição

bool gameover=false; 
bool win=false;
bool loss=false;
int attempts=0; 

/*-----*/

void Draw(void);
void drawObjects();
void drawHangman();
void drawHead();
void drawTorso();
void drawArmLeg(); 
void drawLines();
void checkChar(unsigned char key);
void Init(void);
void Key(unsigned char key, int x, int y);
void Reshape(int widht,int height);
void addNewWord(int a);
void myGlutIdle(void);
void closeWindow(int a);
void closeWindow1(int a);
void display_help(void);
void handleAddNewWord(int a);
void playAgain2(int a);
void playAgain3(int a);
int main();

/*METHODS*/

void Init(void){
	srand( (unsigned)time(NULL));

	state.camera.eye.x=40;
	state.camera.eye.y=40;
	state.camera.eye.z=40;
	state.camera.center.x=0;
	state.camera.center.y=0;
	state.camera.center.z=0;
	state.camera.up.x=0;
	state.camera.up.y=0;
	state.camera.up.z=1;
	state.ortho=GL_TRUE;
	state.camera.fov=60;

	/*Resets the variables*/
	attempts=0;
	gameover=false; 
	win=false;
	loss=false;

	for (int i = 0; i < CHOSEN_CHARS_SIZE; i++){
		chosenKeys[i]=NULL;
	}

	//initializes checkWord's array with 0's
	const int length=word.length();
	checkWord=new int[length];

	for (int i = 0; i < length; i++){
		checkWord[i]=0;
	}

	glClearColor(0.5, 0.5, 0.5, 0.5);

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_DEPTH_TEST);
}

void Reshape(int width, int height){
	// glViewport(botom, left, width, height)
	// define parte da janela a ser utilizada pelo OpenGL

	glViewport(0, 0, (GLint) width, (GLint) height);

	// Matriz Projeccao
	// Matriz onde se define como o mundo e apresentado na janela
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// gluOrtho2D(left,right,bottom,top); 
	// projeccao ortogonal 2D, com profundidade (Z) entre -1 e 1

	if(state.ortho)
	{
		if (width < height)
			glOrtho(-20, 20, -20*(GLdouble)height/width, 20*(GLdouble)height/width,-100,100);
		else
			glOrtho(-20*(GLdouble)width/height, 20*(GLdouble)width/height,-20, 20, -100,100);
	}
	else
		gluPerspective(state.camera.fov,(GLfloat)width/height,1,100);

	// Matriz Modelview
	// Matriz onde são realizadas as tranformacoes dos modelos desenhados
	glMatrixMode(GL_MODELVIEW);
}

void playAgain2(int a){	
	glui2->unlink();
	glui2->disable();
	glui2->close();
	glui2->hide();
	
	closeWindow(a);
	glutDestroyWindow(main_window);
	main();
}

void playAgain3(int a){
	glui3->unlink();
	glui3->disable();
	glui3->close();
	glui3->hide();
	
	closeWindow(a);
	glutDestroyWindow(main_window);
	main();
}

void myGlutIdle( void ){
  /* According to the GLUT specification, the current window is 
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != main_window) 
    glutSetWindow(main_window);  

  //glutPostRedisplay(); 

  glui->sync_live();
}

void drawHangman(){
	if(attempts>=1)
		drawHead();

	if(attempts>=2)
		drawTorso();

	if(attempts>=3){
		glPushMatrix();
		glTranslatef(0,-COMPRIMENTO_TORSO/3,0);

		glRotatef(-225,0,0,1);
		drawArmLeg();
		glPopMatrix();
	}
	if(attempts>=4){
		glPushMatrix();
		glTranslatef(0,-COMPRIMENTO_TORSO/3,0);
		glRotatef(225,0,0,1);
		drawArmLeg();
		glPopMatrix();
	}
	if(attempts>=5){
		glPushMatrix();
		glTranslatef(0,-COMPRIMENTO_TORSO,0);
		glRotatef(-225,0,0,1);
		drawArmLeg(); 
		glPopMatrix();
	}
	if(attempts>=6){
		glPushMatrix();
		glTranslatef(0,-COMPRIMENTO_TORSO,0);
		glRotatef(225,0,0,1);
		drawArmLeg();
		glPopMatrix();
	}
}

void drawHead(){
	glBegin(GL_LINE_LOOP);
	for (int i=0; i < 360; i++){
		float degInRad = RAD(i);
		glVertex2f(cos(degInRad)*RAIO_CIRCUNFERENCIA,sin(degInRad)*RAIO_CIRCUNFERENCIA);
	}
	glEnd();

}

void drawTorso(){
	glTranslatef(0,RAIO_CIRCUNFERENCIA/2 - COMPRIMENTO_TORSO/2,0);
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(0,-COMPRIMENTO_TORSO);
	glEnd();
}

void drawArmLeg(){
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(0,COMPRIMENTO_MEMBROS);
	glEnd();
}	

void drawObjects(){

	glPushMatrix();
	glTranslatef(0,RAIO_CIRCUNFERENCIA,0);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(0,COMPRIMENTO_MEMBROS/2);
	glEnd();
	glPopMatrix();

	glTranslatef(0,COMPRIMENTO_MEMBROS/2,0);
	glPushMatrix();
	glRotatef(-90,0,0,1);
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(0,COMPRIMENTO_MEMBROS+2);
	glEnd();
	glPopMatrix();

	glTranslatef(COMPRIMENTO_MEMBROS+2,0,0);
	glPushMatrix();
	glRotatef(180,0,0,1);
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(0,COMPRIMENTO_TORSO*3);
	glEnd();
	glPopMatrix();

	glTranslatef(0,-(COMPRIMENTO_TORSO*3),0);
	glPushMatrix();
	glRotatef(90,0,0,1);
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(0,COMPRIMENTO_TORSO);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90,0,0,1);
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(0,COMPRIMENTO_TORSO);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void drawLines(){
	int n=word.length();
	glPushMatrix();
	glBegin(GL_LINES); 

	for (int i = 0; i < n; i++){ 
		//draws lines according to the number of characters in the word
		glVertex2f(i*2,-2);
		glVertex2f((i+1)*2-1,-2);
	}
	glEnd();
	glPopMatrix();
}


void Draw(void){
	if(!gameover){
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		glPushMatrix();
			glTranslatef(-17,0,0);
			drawLines();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(13,11,0);
			glPushMatrix();
				drawObjects();
			glPopMatrix();

			if (attempts>0){
				drawHangman();
			}
		glPopMatrix();
	
		glPushMatrix();	
			int length=word.length();
			for (int i = 0; i < length; i++){
				if(checkWord[i]==1){
					glPushMatrix();
						glTranslatef(-17+i*2,-1,0);
						glRasterPos2f(0,0);
						glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,(int)word.at(i));
					glPopMatrix();
				}
			}
		glPopMatrix();

		//Writes category label
		glPushMatrix();	
		for (int i = 0; i < cat.length(); i++)
		{
			glPushMatrix();
				glTranslatef(-18+i*1.5,13,0);
				glRasterPos2f(0,0);
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,(int)cat.at(i));
			glPopMatrix();
		}
		glPopMatrix();

		//Conditions to end the game (either you found out the word or reached the maximum of attempts)
		if(attempts>=6){
			gameover=true;
			loss=true;
		}

		int count=0;
		for (int i = 0; i < length; i++){
			if(checkWord[i]==1)
				count++;
		}
		if (count==length){
			gameover=true;
			win=true;
		}
		if(!gameover){
		//adicionar as letras ja escolhidas no ecra(na parte de baixo)
		glPushMatrix();	
		for (int i = 0; i < chosenCharsLabel.length(); i++)
		{
			glPushMatrix();
				glTranslatef(-18+i*1.5,-13,0);
				glRasterPos2f(0,0);
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,(int)chosenCharsLabel.at(i));
			glPopMatrix();
		}	
			for (int i = 0; i < CHOSEN_CHARS_SIZE; i++){
				if(chosenKeys[i]!=NULL){
					glPushMatrix();
						glTranslatef(-18+i*2,-15,0);
						glRasterPos2f(0,0);
						glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,(int)chosenKeys[i]);
					glPopMatrix();
				}
			}
		glPopMatrix();
	}else{
		glui2 = GLUI_Master.create_glui( "HangMan", 0, 400, 250 );
		
		if(win){
		glui2->add_statictext("\n\n                     You won, Congratulations                 \n\n");
		glui2->add_button("OK",0,(GLUI_Update_CB)exit);
		glui2->add_button("Play Again",0,playAgain2);
		
		}else if(loss){
			glui2->add_statictext("\n\n                     You lost, better luck next time                 \n\n");
			glui2->add_button("OK",0,(GLUI_Update_CB)exit);
			glui2->add_button("Play Again",0, playAgain2);
		}
	}
		glFlush();
		if (state.doubleBuffer)
			glutSwapBuffers();

	}else{
		glui3 = GLUI_Master.create_glui( "HangMan", 0, 400, 250 );
		
		if(win){
		glui3->add_statictext("\n\n                     You won, Congratulations                 \n\n");
		glui3->add_button("OK",0,(GLUI_Update_CB)exit);
		glui3->add_button("Play Again",0, playAgain3);

		}else if(loss){
			glui3->add_statictext("\n\n                     You lost, better luck next time                 \n\n");
			glui3->add_button("OK",0,(GLUI_Update_CB)exit);
			glui3->add_button("Play Again",0, playAgain3);

		}
	}
}

void display_help(void){
	printf("Hangman\n");
	printf("ESC - Sair\n");
}


void checkChar(unsigned char key){
	//checks if the key/char was already chosen before
	key=toupper(key); //uppercase
	bool exit=false;
	for (int i = 0; i < CHOSEN_CHARS_SIZE; i++){
		if(key==chosenKeys[i]){
			exit=true;
			i=CHOSEN_CHARS_SIZE;
		}
	}
	
	if(!exit){
		//adds the char to the array
		for (int i = 0; i < CHOSEN_CHARS_SIZE; i++){
			if (chosenKeys[i]==NULL){
				chosenKeys[i]=key;
				i=CHOSEN_CHARS_SIZE;
			}
		}

	bool write=false;
	int n=word.length();

	for (int i = 0; i < n; i++){
		
		if(word.at(i)==key){ // If the char belongs to the word
			checkWord[i]=1;		
			write=true;
		}		
	}
	if (write==false)
		attempts=attempts+1;
	}

	glutPostRedisplay();

}

void Key(unsigned char key, int x, int y)
{
	checkChar(key);
	 
	switch (key) {
	   case 27:
	     exit(1);
	}
}
void handleAddNewWord(int a){
	ofstream myfile ("words.txt",ios::app); //write to a file
	string catToBeAdded=edittext->get_text();
	string wordToBeAdded=edittext1->get_text();

	string toBeAdded=catToBeAdded+";"+wordToBeAdded; 
	
	if(myfile.is_open())		
		myfile <<"\n"<<toBeAdded;

	myfile.close();
	closeWindow1(a);
}

void closeWindow1(int a){
	glui1->unlink();
	glui1->disable();
	glui1->close();
	glui1->hide();	
}

void closeWindow(int a){
	glui->unlink();
	glui->disable();
	glui->close();
	glui->hide();
}

void addNewWord(int a){ //called form GLUI button
	
	glui1 = GLUI_Master.create_glui( "GLUI", 0, 800, 150 );
	glui1->add_statictext( "Add New Word" );
	glui1->add_separator();
	
	edittext = glui1->add_edittext( "Category:", GLUI_EDITTEXT_TEXT);
	edittext->set_w(200);
	edittext1 = glui1->add_edittext( "Word:", GLUI_EDITTEXT_TEXT);
	edittext1->set_w(200);

	glui1->add_button( "OK", 303,handleAddNewWord );
	glui1->add_button( "Close",0,closeWindow1);

	
}

int main(/*int argc, char **argv*/){
	 int count=0;
	 ifstream myReadFile,myReadFile1;
	 myReadFile.open("words.txt");
	 myReadFile1.open("words.txt");
	 string output;

	 /*Counts the number of lines*/
	if (myReadFile.is_open()) {
		 while (!myReadFile.eof()) {
			 getline(myReadFile,output);
			 count++;
		}
	}
	myReadFile.close();
	
	/*Reads the file to an array*/
	 string* buffer;
	 buffer=new string[count];
	 int i=0;

	if (myReadFile1.is_open()) {
		while (!myReadFile1.eof()) {
			getline(myReadFile1,output);
			buffer[i]=output;
			i++;
		}
	}
	myReadFile1.close();

	/*Generates a random number to display a category + word on the screen*/
	srand(time(NULL));
	int randomnumber;
    randomnumber = rand() % count;
    
	string catword= buffer[randomnumber]; //category;word
	
	int pos=catword.find(";"); //index of ';'
	
	word=catword.substr(pos+1); //word
	
	cat=catword.substr(0,pos); //category

	/*Just in case, better safe than sorry*/
	transform(cat.begin(), cat.end(),cat.begin(), ::toupper);
	transform(word.begin(), word.end(),word.begin(), ::toupper);


	/*----------------GLUT & GLUI--------------------*/

	char str[]=" makefile MAKEFILE Makefile ";
	state.doubleBuffer=1;


	//glutInit(&argc, argv);
	glutInitWindowPosition(250, 80);
	glutInitWindowSize(WIDHT, HEIGHT);
	glutInitDisplayMode(((state.doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE) | GLUT_RGB | GLUT_DEPTH);
	main_window=glutCreateWindow("Hangman");
		
	Init();
	
	display_help();

	glutDisplayFunc(Draw);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);
	
	glui = GLUI_Master.create_glui( "GLUI", 0, 1050, 150 );
	glui->add_statictext( "           Menu             " );
	glui->add_separator();
	glui->add_button("Add New Word",0,addNewWord);
	glui->add_button( "Close",0,closeWindow);
	
	//glui->set_main_gfx_window( main_window );

    /* We register the idle callback with GLUI, *not* with GLUT */
	GLUI_Master.set_glutIdleFunc( myGlutIdle );
	
	glutMainLoop();
	return 0;
}


