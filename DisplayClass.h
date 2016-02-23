#include <GLUT/glut.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "AnimalsClass.h"
#include "SceneryClass.h"
#include "CameraClass.h"

class Display
{
	public:
		Display();
		void display();
		void reshape(int w, int h);
		void keyboard(unsigned char key, int x, int y);
		void idle();
		void init();
		void setCoords(float v[], bool a, int id);
		void setChoice(int choice);
		GLubyte* loadTexture(char * file, int width, int height, int depth);
	private:
		Camera camera;
		Animals Fish[8];
		Scenery Floor;
		Scenery Rocks[4];
		int numberOfFish;
		float vec[3];
		GLfloat ambient[4];
		GLfloat specular[4];
		GLfloat diffuse[4];
		GLfloat position[4];
		GLubyte* texture1;
		GLubyte* texture2;
		GLuint textnames[2];
};

Display::Display()
{
	numberOfFish = 8;

}

void Display::init()
{
	//numberOfFish = 1;
	
	ambient[0] = 0.8; ambient[1] = 0.8; ambient[2] = 0.8; ambient[3] = 1.0;
	diffuse[0] = 10.0; diffuse[1] = 10.0; diffuse[2] = 10.0; diffuse[3] = 1.0;
	specular[0] = 1.0; specular[1] = 1.0; specular[2] = 10.0; specular[3] = 1.0;
	position[0] = 0.0; position[1] = -10.0; position[2] = 0.0; position[3] = 1.0;

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	//glBindTexture(GL_TEXTURE_2D, 0);
	glGenTextures(2, textnames);
	glBindTexture(GL_TEXTURE_2D, textnames[0]);
	texture1 = loadTexture("./assets/fish.bmp", 256, 256, 3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1);

	Fish[0].init(-1, 1.0, 2.0);
	Fish[1].init(-1, 1.0, 3.0);
	Fish[2].init(-1, 1.0, 1.0);
	Fish[3].init(-1, 1.0, 4.0);
	Fish[4].init(-1, 1.0, 1.5);
	Fish[5].init(-1, 1.0, 2.0);
	//Fish[6].init(-1, 1.0, 2.5);
	//Fish[7].init(-1, 1.0, 2.1);
	
	//Fish[2].setType(1);
	//Fish[4].setType(1);

	glBindTexture(GL_TEXTURE_2D, textnames[1]);
	texture2 = loadTexture("./assets/sand_texture.raw", 2048, 2048, 3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2048, 2048, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2);
	

	Floor.init(0.0, -10.0, 0.0);
	Rocks[0].init(3.0, -9.0, 5.0);
	Rocks[1].init(10.0, -8.0, 1.0);
	Rocks[2].init(-7.5, -8.0, -4.0);
	Rocks[3].init(-12.0, -7.5, 2.0);

	glEnable(GL_TEXTURE_2D);

	std::cout << "Texture " <<  textnames[0] << std::endl;
	std::cout << "Texture " << textnames[1] << std::endl;

}

void Display::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//display the camera
	camera.camera();

	glBindTexture(GL_TEXTURE_2D, textnames[0]);
	//draw fish coordinates are y/z offsets
	Fish[0].draw(1, 1);
	Fish[1].draw(-3, -3);
	Fish[2].draw(0, 3);
	Fish[3].draw(3, 4);
	Fish[4].draw(-1, -4.2);
	Fish[5].draw(-4, -4);
	//Fish[6].draw(2, 2);
	//Fish[7].draw(0, -4);

	glBindTexture(GL_TEXTURE_2D, textnames[1]);
	//base for frame of reference
	Floor.drawRock(0, 0, 0, 0);

	//scenery
	Rocks[0].drawRock(2.0, 1.0, 1.5, 1);
	Rocks[1].drawRock(1.5, 2.0, 2.0, 1);
	Rocks[2].drawRock(2.0, 2.0, 2.0, 1);
	Rocks[3].drawRock(1.0, 3.0, 1.5, 1);

	glutSwapBuffers();

}

void Display::reshape(int w, int h)
{
	if(h == 0)
		h = 1;
	float ratio = w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(65.0, ratio, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void Display::keyboard(unsigned char key, int x, int y)
{
	if(key == 27)
		exit(0);
	else
		camera.keyboard(key, x, y);
}

void Display::idle()
{
	for(int i = 0; i < numberOfFish; i++)
		Fish[i].idle();
	camera.idle();
}

void Display::setCoords(float v[], bool a, int id)
{
	camera.setOrientation(id);
	camera.setOnOff(a);
	camera.setCoordinates(v);
}

void Display::setChoice(int choice)
{
	camera.setChoice(choice);
}

GLubyte* Display::loadTexture(char * file, int width, int height, int depth)
{
  	GLubyte *raw_bitmap;
    FILE *texFile;

    int byteSize, textureSize;
    byteSize = sizeof(GLubyte);
    textureSize = width * height * depth * byteSize;

    texFile = fopen(file, "rb");

    if (texFile == NULL)
      {
        printf ("Texture %s not found\n", file);
        exit(1);
      }

    raw_bitmap = (GLubyte *) malloc (textureSize);

    if (raw_bitmap == NULL)
      {
        printf("Cannot allocate memory for texture %s\n", file);
        fclose(texFile);
        exit(1);
      }

    fread (raw_bitmap , width * height * depth, 1 , texFile );
    fclose (texFile);
    /*
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    /*  glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
        glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND );
    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
    */

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
  	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    return (raw_bitmap);

}