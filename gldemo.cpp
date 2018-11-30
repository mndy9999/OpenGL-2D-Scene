#include "stdafx.h"
#include <random>

using namespace std;
using namespace CoreStructures;

// Global variables
float crabX = 0;			// crab postion on the X axis (left and right)
float octopusY = -0.7f;		// octopus position on the Y axis (up and down)
bool mFish = false;			// click on fish
bool mOctopus = false;		// click on octopus
bool mBush = false;			// click on bush
bool keyLeftPressed = false;
bool keyRightPressed = false;
const int NUM_BUBBLES = 50;		// number of bubbles generated
float scale_prob[10] = { 0.075f, 0.075f, 0.1f, 0.1f, 0.15f, 0.15f, 0.15f, 0.15f, 0.1f, 0.4f };	//size of bubbles

// Bubbles instance information
struct bubble_instance{
	// matrices to model position and scale of bubble object
	GUMatrix4		pos;
	GUMatrix4		scale;
}bubbles[NUM_BUBBLES];


// Textures
GLuint myGroundTexture = 0;
GLuint myFishTexture = 0;
GLuint myCrabTexture = 0;
GLuint myBubblesTexture = 0;
GLuint myPatrickTexture = 0;
GLuint myBushTexture = 0;
GLuint myOctopusTexture = 0;
GLuint myTreasureTexture = 0;
GLuint locT; // location of "T" uniform variable in myShaderProgram

// Shader program object for applying textures to our shapes
GLuint myShaderProgram;


// Vertex Buffer Object IDs
GLuint quadPosVBO, quadColourVBO, quadTexCoordVBO, quadIndicesVBO;
GLuint fishPosVBO, fishColourVBO, fishTexCoordVBO, fishIndicesVBO;
GLuint crabPosVBO, crabColourVBO, crabTexCoordVBO, crabIndicesVBO;
GLuint patrickPosVBO, patrickColourVBO, patrickTexCoordVBO, patrickIndicesVBO;
GLuint bushPosVBO, bushColourVBO, bushTexCoordVBO, bushIndicesVBO;
GLuint octopusPosVBO, octopusColourVBO, octopusTexCoordVBO, octopusIndicesVBO;
GLuint treasurePosVBO, treasureColourVBO, treasureTexCoordVBO, treasureIndicesVBO;
GLuint bubblesPosVBO, bubblesColourVBO, bubblesTexCoordVBO, bubblesIndicesVBO;

// Packed vertex arrays
#pragma region Packet Vertex Arrays

// Background (QUAD_STRIP)
static GLfloat quadVertices[] = {

	1.0f, -1.0f,
	1.0f, 1.0f,
	-1.0f, -1.0f,
	-1.0, 1.0f,
};
static GLubyte quadColors[] = {

	255, 0, 0, 255,
	255, 255, 0, 255,
	0, 255, 0, 255,
	0, 255, 255, 255

};
static float quadTextureCoords[] = {

	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 0.0f

};
static GLubyte quadVertexIndices[] = { 0, 1, 2, 3 };

// Fish (TRIANGLE_STRIP)
static GLfloat fishVertices[] = {

	-0.3f, -0.4f,
	-0.3f, 0.4f,
	0.4f, -0.4f,
	0.4f, 0.4f
};
static GLubyte fishColors[] = {

	255, 0, 0, 255,
	255, 255, 0, 255,
	0, 255, 0, 255,
	0, 255, 255, 255
};
static float fishTextureCoords[] = {

	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 0.0f
};
static GLubyte fishVertexIndices[] = { 0, 1, 2, 3};

// Crab (TRIANGLE_STRIP)
static GLfloat crabVertices[] = {

	-0.1f, -0.1f,
	-0.1f, 0.1f,
	0.1f, -0.1f,
	0.1f, 0.1f
};
static GLubyte crabColors[] = {

	255, 0, 0, 255,
	255, 255, 0, 255,
	0, 255, 0, 255,
	0, 255, 255, 255
};
static float crabTextureCoords[] = {

	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 0.0f
};
static GLubyte crabVertexIndices[] = { 0, 1, 2, 3 };

// Patrick (TRIANGLE_STRIP)
static GLfloat patrickVertices[] = {

	-0.2f, -0.25f,
	-0.2f, 0.5f,
	0.2f, -0.25f,
	0.2f, 0.5f
};
static GLubyte patrickColors[] = {

	255, 0, 0, 255,
	255, 255, 0, 255,
	0, 255, 0, 255,
	0, 255, 255, 255
};
static float patrickTextureCoords[] = {

	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 0.0f
};
static GLubyte patrickVertexIndices[] = { 0, 1, 2, 3 };

// Bush (TRIANGLE_STRIP)
static GLfloat bushVertices[] = {

	-0.4f, -0.4f,
	-0.4f, 0.4f,
	0.4f, -0.4f,
	0.4f, 0.4f
};
static GLubyte bushColors[] = {

	255, 0, 0, 255,
	255, 255, 0, 255,
	0, 255, 0, 255,
	0, 255, 255, 255
};
static float bushTextureCoords[] = {

	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 0.0f
};
static GLubyte bushVertexIndices[] = { 0, 1, 2, 3 };

// Octopus (QUAD_STRIP)
static GLfloat octopusVertices[] = {

	-0.25f, 0.5f,
	-0.25f, -0.25f,
	0.25f, 0.5f,
	0.25f, -0.25f
};
static GLubyte octopusColors[] = {

	255, 0, 0, 255,
	255, 255, 0, 255,
	0, 255, 0, 255,
	0, 255, 255, 255,
};
static float octopusTextureCoords[] = {

	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 0.0f
};
static GLubyte octopusVertexIndices[] = { 0, 1, 2, 3 };

// Treasure (TRIANGLE_STRIP)
static GLfloat treasureVertices[] = {

	-0.2f, -0.2f,
	-0.2f, 0.2f,
	0.2f, -0.2f,
	0.2f, 0.2f
};
static GLubyte treasureColors[] = {

	255, 0, 0, 255,
	255, 255, 0, 255,
	0, 255, 0, 255,
	0, 255, 255, 255
};
static float treasureTextureCoords[] = {

	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 0.0f

};
static GLubyte treasureVertexIndices[] = { 0, 1, 2, 3 };


// Bubbles (TRIANGLE_STRIP)
static GLfloat bubblesVertices[] = {

	-0.2f, -0.2f,
	-0.2f, 0.2f,
	0.2f, -0.2f,
	0.2f, 0.2f
};
static GLubyte bubblesColors[] = {

	255, 0, 0, 255,
	255, 255, 0, 255,
	0, 255, 0, 255,
	0, 255, 255, 255

};
static float bubblesTextureCoords[] = {

	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 0.0f

};
static GLubyte bubblesVertexIndices[] = { 0, 1, 2, 3 };

#pragma endregion

// Function Prototypes
void init(int argc, char* argv[]);
void setupGroundTextureVBO(void);
void setupFishTextureVBO(void);
void setupCrabTextureVBO(void);
void setupPatrickTextureVBO(void);
void setupBushTextureVBO(void);
void setupOctopusTextureVBO(void);
void setupTreasureTextureVBO(void);
void setupBubblesTextureVBO(void);
void setupBubblesInstances(void);
void display(void);
void update(void);
void drawTexturedGroundVBO(void);
void drawTexturedFishVBO(void);
void drawTexturedCrabVBO(void);
void drawTexturedPatrickVBO(void);
void drawTexturedBushVBO(void);
void drawTexturedOctopusVBO(void);
void drawTexturedTreasureVBO(void);
void drawTexturedBubblesVBO(void);
void mouseButtonDown(int, int, int, int);
void keyDown(int, int, int);
void keyUp(int, int, int);


int _tmain(int argc, char* argv[]) 
{
	init(argc, argv);
	glutMainLoop();
	shutdownCOM();
	return 0;
}


void init(int argc, char* argv[]) {

	// Initialise COM so we can use Windows Imaging Component
	initCOM();

	// Initialise FreeGLUT
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	// Set window size, position and name
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(64, 64);
	glutCreateWindow("Funky Fish");

	// Register callback functions
	glutDisplayFunc(display);
	glutIdleFunc(update);
	glutMouseFunc(mouseButtonDown);
	glutSpecialFunc(keyDown);
	glutSpecialUpFunc(keyUp);

	// Initialise GLEW library
	GLenum err = glewInit();

	// Ensure GLEW was initialised successfully before proceeding
	if (err == GLEW_OK)
	{
		cout << "GLEW initialised okay\n";
	}
	else
	{
		cout << "GLEW could not be initialised\n";
		throw;
	}

	// Setup colour to clear the window
	glClearColor(0.2f, 0.2f, 0.8f, 0.0f);
	glLineWidth(9.0f);

	//Load textures
	myGroundTexture = fiLoadTexture("background.png");
	myFishTexture = fiLoadTextureA("fish.png");
	myCrabTexture = fiLoadTextureA("crab.png");
	myPatrickTexture = fiLoadTextureA("patrick.png");
	myBushTexture = fiLoadTextureA("seaweed.png");
	myOctopusTexture = fiLoadTextureA("octopus.png");
	myTreasureTexture = fiLoadTextureA("treasure.png");
	myBubblesTexture = fiLoadTextureA("bubbles.png");

	//Shader setup 
	myShaderProgram = setupShaders(string("Shaders\\basic_vertex_shader.txt"), string("Shaders\\basic_fragment_shader.txt"));
	// Get uniform location of "T" variable in shader program
	locT = glGetUniformLocation(myShaderProgram, "T");

	//Setup the scene using VBO
	setupGroundTextureVBO();
	setupFishTextureVBO();
	setupCrabTextureVBO();
	setupPatrickTextureVBO();
	setupBushTextureVBO();
	setupOctopusTextureVBO();
	setupTreasureTextureVBO();
	setupBubblesTextureVBO();
	setupBubblesInstances();
}

// our background
void setupGroundTextureVBO(void) {

	// setup VBO for the background object position data
	glGenBuffers(1, &quadPosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadPosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	// setup VBO for the background object colour data
	glGenBuffers(1, &quadColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadColors), quadColors, GL_STATIC_DRAW);

	// setup VBO for the background object texture coord data
	glGenBuffers(1, &quadTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadTextureCoords), quadTextureCoords, GL_STATIC_DRAW);

	// setup background vertex index array
	glGenBuffers(1, &quadIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadVertexIndices), quadVertexIndices, GL_STATIC_DRAW);
}

// our fish
void setupFishTextureVBO(void) {

	// setup VBO for the fish object position data
	glGenBuffers(1, &fishPosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, fishPosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fishVertices), fishVertices, GL_STATIC_DRAW);

	// setup VBO for the fish object colour data
	glGenBuffers(1, &fishColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, fishColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fishColors), fishColors, GL_STATIC_DRAW);

	// setup VBO for the fish object texture coord data
	glGenBuffers(1, &fishTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, fishTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fishTextureCoords), fishTextureCoords, GL_STATIC_DRAW);

	// setup fish vertex index array
	glGenBuffers(1, &fishIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fishIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(fishVertexIndices), fishVertexIndices, GL_STATIC_DRAW);
}

// our crab
void setupCrabTextureVBO(void) {

	// setup VBO for the crab object position data
	glGenBuffers(1, &crabPosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, crabPosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(crabVertices), crabVertices, GL_STATIC_DRAW);

	// setup VBO for the crab object colour data
	glGenBuffers(1, &crabColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, crabColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(crabColors), crabColors, GL_STATIC_DRAW);

	// setup VBO for the crab object texture coord data
	glGenBuffers(1, &crabTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, crabTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(crabTextureCoords), crabTextureCoords, GL_STATIC_DRAW);

	// setup crab vertex index array
	glGenBuffers(1, &crabIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, crabIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(crabVertexIndices), crabVertexIndices, GL_STATIC_DRAW);
}

// Patrick
void setupPatrickTextureVBO(void) {

	// setup VBO for Patrick's position
	glGenBuffers(1, &patrickPosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, patrickPosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(patrickVertices), patrickVertices, GL_STATIC_DRAW);

	// setup VBO for Patrick's object colour data
	glGenBuffers(1, &patrickColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, patrickColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(patrickColors), patrickColors, GL_STATIC_DRAW);

	// setup VBO for Patrick's object texture coord data
	glGenBuffers(1, &patrickTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, patrickTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(patrickTextureCoords), patrickTextureCoords, GL_STATIC_DRAW);

	// setup Patrick's vertex index array
	glGenBuffers(1, &patrickIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, patrickIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(patrickVertexIndices), patrickVertexIndices, GL_STATIC_DRAW);
}

//our bush
void setupBushTextureVBO(void) {

	// setup VBO for the bush object position data
	glGenBuffers(1, &bushPosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, bushPosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bushVertices), bushVertices, GL_STATIC_DRAW);

	// setup VBO for the bush object colour data
	glGenBuffers(1, &bushColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, bushColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bushColors), bushColors, GL_STATIC_DRAW);

	// setup VBO for the bush object texture coord data
	glGenBuffers(1, &bushTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, bushTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bushTextureCoords), bushTextureCoords, GL_STATIC_DRAW);

	// setup bush vertex index array
	glGenBuffers(1, &bushIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bushIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bushVertexIndices), bushVertexIndices, GL_STATIC_DRAW);
}

// our octopus
void setupOctopusTextureVBO(void) {

	// setup VBO for the octopusobject position data
	glGenBuffers(1, &octopusPosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, octopusPosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(octopusVertices), octopusVertices, GL_STATIC_DRAW);

	// setup VBO for the octopus object colour data
	glGenBuffers(1, &octopusColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, octopusColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(octopusColors), octopusColors, GL_STATIC_DRAW);

	// setup VBO for the octopus object texture coord data
	glGenBuffers(1, &octopusTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, octopusTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(octopusTextureCoords), octopusTextureCoords, GL_STATIC_DRAW);

	// setup octopus vertex index array
	glGenBuffers(1, &octopusIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, octopusIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(octopusVertexIndices), octopusVertexIndices, GL_STATIC_DRAW);
}

// our treasure
void setupTreasureTextureVBO(void) {

	// setup VBO for the treasure object position data
	glGenBuffers(1, &treasurePosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, treasurePosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(treasureVertices), treasureVertices, GL_STATIC_DRAW);

	// setup VBO for the treasure object colour data
	glGenBuffers(1, &treasureColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, treasureColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(treasureColors), treasureColors, GL_STATIC_DRAW);

	// setup VBO for the treasure object texture coord data
	glGenBuffers(1, &treasureTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, treasureTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(treasureTextureCoords), treasureTextureCoords, GL_STATIC_DRAW);

	// setup treasure vertex index array
	glGenBuffers(1, &treasureIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, treasureIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(treasureVertexIndices), treasureVertexIndices, GL_STATIC_DRAW);
}

// our bubbles
void setupBubblesTextureVBO(void) {

	// setup VBO for the bubbles object position data
	glGenBuffers(1, &bubblesPosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, bubblesPosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bubblesVertices), bubblesVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	// setup VBO for the bubbles object colour data
	glGenBuffers(1, &bubblesColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, bubblesColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bubblesColors), bubblesColors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(1);

	// setup VBO for the bubbles object texture coord data
	glGenBuffers(1, &bubblesTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, bubblesTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bubblesTextureCoords), bubblesTextureCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);

	// setup bubbles vertex index array
	glGenBuffers(1, &bubblesIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bubblesIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bubblesVertexIndices), bubblesVertexIndices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void setupBubblesInstances(void)
{
	random_device rd;
	mt19937 mt(rd());

	auto positionRangeX = uniform_real_distribution<float>(-0.85f, -0.45f);
	auto positionRangeY = uniform_real_distribution<float>(0.1f, 1.0f);
	auto scaleProbRange = uniform_int_distribution<int>(0, 9);
	int count = 0;
	for (int i = 0; i<NUM_BUBBLES; ++i) {

		// Setup random position in [-1, +1] range
		float x = positionRangeX(mt);
		float y = positionRangeY(mt);

		// Get scale from scale_prob array
		float scale = scale_prob[scaleProbRange(mt)];

		// Setup the translation and scale matrices based on the randomly generated position and scale values.  Store these in the bubbles[] array
		bubbles[i].pos = GUMatrix4::translationMatrix(x, y, 0.0f);
		bubbles[i].scale = GUMatrix4::scaleMatrix(scale, scale, 1.0f);

	}
}


void update(void) {
	// get keyboard imput and update the crab's position
	if (keyLeftPressed)
	{
		if (crabX > -0.29f)
		{
			crabX -= 0.01f;
		}
	}

	if (keyRightPressed)
	{
		if (crabX <= 0.46f)
		{
			crabX += 0.01f;
		}
	}
	//get mouse imput and update the octopus' position
	if (mBush)
	{
		if (octopusY < 0.29f)
		{
			octopusY += 0.01f;
		}
		else
			mBush = false;
	}

	if (mOctopus)
	{
		if (octopusY >= -0.7f)
		{
			octopusY -= 0.01f;
		}
		else
			mOctopus = false;
	}
	// Redraw the screen
	glutPostRedisplay();
}


void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// "Plug in" our shader into the GPU pipeline
	glUseProgram(myShaderProgram);

	// draw our objects
	drawTexturedGroundVBO();
	drawTexturedFishVBO();
	drawTexturedOctopusVBO();
	drawTexturedBushVBO();
	drawTexturedPatrickVBO();
	drawTexturedCrabVBO();
	drawTexturedTreasureVBO();

	// Draw multiple bubbles instances...
	if (mFish)
	{
		for (int i = 0; i < NUM_BUBBLES; i++) {

			// Combine matrices to do scale first then translate
			GUMatrix4 R = bubbles[i].pos * bubbles[i].scale;

			// Pass new transform (R) to uniform variable "T" in the shader 'myShaderProgram'
			glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&R);

			// Draw a (single) bubble
			drawTexturedBubblesVBO();
		}
	}
	
	glutSwapBuffers();
}

// draw our functions
void drawTexturedGroundVBO(void) {

	glUseProgram(myShaderProgram);

	// Move our background to the centre of the screen
	GUMatrix4 T = GUMatrix4::translationMatrix(0.0f, 0.0f, 0.0f);
	glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&T);

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, myGroundTexture);
	glUniform1i(glGetUniformLocation(myShaderProgram, "texture"), 0);
	glEnable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, quadPosVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, quadColourVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, quadTexCoordVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);


	// Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIndicesVBO);

	// Draw the object
	glDrawElements(GL_QUAD_STRIP, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glDisable(GL_TEXTURE_2D);


}

void drawTexturedFishVBO(void) {

	glUseProgram(myShaderProgram);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Move our fish
	GUMatrix4 T = GUMatrix4::translationMatrix(-0.7f, 0.0f, 0.0f);
	glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&T);

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, myFishTexture);
	glUniform1i(glGetUniformLocation(myShaderProgram, "texture"), 0);
	glEnable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, fishTexCoordVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);


	// Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fishIndicesVBO);

	// Draw the object
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glDisable(GL_TEXTURE_2D);


}

void drawTexturedCrabVBO(void) {

	glUseProgram(myShaderProgram);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Move our crab to the bottom of the screen
	GUMatrix4 T = GUMatrix4::translationMatrix(crabX, -0.8f, 0.0f);
	glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&T);

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, myCrabTexture);
	glUniform1i(glGetUniformLocation(myShaderProgram, "texture"), 0);
	glEnable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, crabPosVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, crabColourVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, crabTexCoordVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);


	// Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, crabIndicesVBO);

	// Draw the object
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glDisable(GL_TEXTURE_2D);


}

void drawTexturedPatrickVBO(void) {

	glUseProgram(myShaderProgram);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Move Patrick
	GUMatrix4 T = GUMatrix4::translationMatrix(0.85f, -0.8f, 0.0f);
	glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&T);

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, myPatrickTexture);
	glUniform1i(glGetUniformLocation(myShaderProgram, "texture"), 0);
	glEnable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, patrickPosVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, patrickColourVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, patrickTexCoordVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);


	// Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, patrickIndicesVBO);

	// Draw the object
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glDisable(GL_TEXTURE_2D);


}

void drawTexturedBushVBO(void) {

	glUseProgram(myShaderProgram);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Move our bush
	GUMatrix4 T = GUMatrix4::translationMatrix(0.55f, -0.5f, 0.0f);
	glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&T);

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, myBushTexture);
	glUniform1i(glGetUniformLocation(myShaderProgram, "texture"), 0);
	glEnable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, bushPosVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, bushColourVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, bushTexCoordVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);


	// Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bushIndicesVBO);

	// Draw the object
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glDisable(GL_TEXTURE_2D);


}

void drawTexturedOctopusVBO(void) {

	glUseProgram(myShaderProgram);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Move our octopus
	GUMatrix4 T = GUMatrix4::translationMatrix(0.55f, octopusY, 0.0f);
	glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&T);

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, myOctopusTexture);
	glUniform1i(glGetUniformLocation(myShaderProgram, "texture"), 0);
	glEnable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, octopusPosVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, octopusColourVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, octopusTexCoordVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);


	// Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, octopusIndicesVBO);

	// Draw the object
	glDrawElements(GL_QUAD_STRIP, 12, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glDisable(GL_TEXTURE_2D);

}

void drawTexturedTreasureVBO(void) {

	glUseProgram(myShaderProgram);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Move our crab to the bottom of the screen
	GUMatrix4 T = GUMatrix4::translationMatrix(-0.6f, -0.8f, 0.0f);
	glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&T);


	// Bind each vertex buffer and enable
	// The data is still stored in the GPU but we need to set it up (which also includes validation of the VBOs behind-the-scenes)

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, myTreasureTexture);
	glUniform1i(glGetUniformLocation(myShaderProgram, "texture"), 0);
	glEnable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, treasurePosVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, treasureColourVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, treasureTexCoordVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);


	// Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, treasureIndicesVBO);

	// Draw the object - same function call as used for vertex arrays but the last parameter is interpreted as an offset into the currently bound index buffer (set to 0 so we start drawing from the beginning of the buffer).
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE_2D);

}

void drawTexturedBubblesVBO(void) {

	glUseProgram(myShaderProgram);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, myBubblesTexture);

	glBindBuffer(GL_ARRAY_BUFFER, bubblesPosVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, bubblesColourVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, bubblesTexCoordVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);


	// Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bubblesIndicesVBO);

	// Draw the object - same function call as used for vertex arrays but the last parameter is interpreted as an offset into the currently bound index buffer (set to 0 so we start drawing from the beginning of the buffer).
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}


#pragma region Event handling functions

 void mouseButtonDown(int button, int state, int x, int y) {

	 switch (button){
	 case GLUT_LEFT_BUTTON:
		 if ((x > 88 &&  x < 330) && (y > 258 && y < 455))
		 {
			 mFish = true;
			 break;
		 }
		 if ((x > 843 && x < 970) && (y > 86 && y < 257))
		 {
			 mOctopus = true;
			 break;
		 }
		 if ((x > 827 && x < 992) && (y > 489 && y < 656))
		 {
			 mBush = true;
			 break;
		 }
		 case GLUT_RIGHT_BUTTON:
		 if ((x > 88 && x < 330) && (y < 455 && y > 258))
		 {
			 mFish = false;
			 break;
		 }
	 }
}


void keyDown(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_LEFT:
		keyLeftPressed = true;
		break;
	case GLUT_KEY_RIGHT:
		keyRightPressed = true;
		break;
	}
}
void keyUp(int key, int x, int y) {

	switch (key) {

	case GLUT_KEY_LEFT:
		keyLeftPressed = false;
		break;

	case GLUT_KEY_RIGHT:
		keyRightPressed = false;
		break;
	}
}
#pragma endregion
