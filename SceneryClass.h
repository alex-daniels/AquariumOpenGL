#include <GLUT/glut.h>

#include "Cube.h"


#define FLOOR 10
#define ROCK  11

class Scenery
{
public:
	void init(float offx, float offy, float offz);
	void drawRock(float scalex, float scaley, float scalez, int id);
	GLubyte* loadTexture(char * file, int width, int height, int depth);
private:
	float offsetx;
	float offsety;
	float offsetz;
	float colorV[3];
	Cube cube;
	GLubyte *base;
	GLuint text[1];

};

void Scenery::init(float offx, float offy, float offz)
{
	cube.init();
	offsetx = offx;
	offsety = offy;
	offsetz = offz;

	//texture.init();

	//glBindTexture(GL_TEXTURE_2D, 1);
	//base = loadTexture("./assets/sand_texture.raw", 2048, 2048, 3);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2048, 2048, 0, GL_RGB, GL_UNSIGNED_BYTE, base);


	glNewList(FLOOR, GL_COMPILE);
	cube.drawCubes();
	//glutSolidCube(1);
	glEndList();

	glNewList(ROCK, GL_COMPILE);
	//glScalef(2.0, 2.0, 2.0);
	cube.drawCubes();
	//glutSolidCube(2.0);
	glEndList();

}

void Scenery::drawRock(float scalex, float scaley, float scalez, int id)
{
	//floor
	if(id == 0)
	{
		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);

		glColor3f(0.4, 0.4, 0.4);
		glTranslatef(offsetx, offsety, offsetz);
		glScalef(20.0, 1.5, 10.0);
		glCallList(FLOOR);

		glPopAttrib();
		glPopMatrix();
	}
	//rocks
	if(id == 1)
	{
		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);

		glColor3fv(colorV);
		glTranslatef(offsetx, offsety, offsetz);
		glScalef(scalex, scaley, scalez);
		glCallList(ROCK);

		glPopAttrib();
		glPopMatrix();
	}

}

GLubyte* Scenery::loadTexture(char * file, int width, int height, int depth)
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