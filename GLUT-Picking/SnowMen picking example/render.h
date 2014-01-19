

typedef struct cameras {
	float pos[3];
	float lookAt[3];
	float lookUp[3];
} camera;



// callback to initialize the scenes for each subwindow
void initScene(int argc, char **argv);

void init(camera *cam);

// callback to draw the window
void draw();


// callback when picking occurs
void picked(GLuint name,int sw);


// keyboard callback
void processKeyboard(unsigned char key, int x, int y);


// callback for quiting
void quit();

