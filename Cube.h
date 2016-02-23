#include <GLUT/glut.h>

class Cube
{
public:
	void polygon(int a, int b, int c, int d);
	void drawCubes();
	void init();
private:
	GLfloat vertices[8][3];
};


void Cube::init()
{
	vertices[0][0] = -1.0; vertices[0][1] = -1.0; vertices[0][2] = -1.0;
	vertices[1][0] = 1.0; vertices[1][1] = -1.0; vertices[1][2] = -1.0;
	vertices[2][0] = 1.0; vertices[2][1] = 1.0; vertices[2][2] = -1.0;
	vertices[3][0] = -1.0; vertices[3][1] = 1.0; vertices[3][2] = -1.0;
	vertices[4][0] = -1.0; vertices[4][1] = -1.0; vertices[4][2] = 1.0; 
 	vertices[5][0] = 1.0; vertices[5][1] = -1.0; vertices[5][2] = 1.0;
 	vertices[6][0] = 1.0; vertices[6][1] = 1.0; vertices[6][2] = 1.0;
 	vertices[7][0] = -1.0; vertices[7][1] = 1.0; vertices[7][2] = 1.0;
}

void Cube::polygon(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);
    glVertex3fv(vertices[a]);
    glTexCoord2f(0.0,1.0);
    glVertex3fv(vertices[b]);
    glTexCoord2f(1.0,1.0);
    glVertex3fv(vertices[c]);
    glTexCoord2f(1.0,0.0);
    glVertex3fv(vertices[d]);
    glEnd();
}

void Cube::drawCubes()
{
    polygon(0,3,2,1);
    polygon(2,3,7,6);
    polygon(0,4,7,3);
    polygon(1,2,6,5);
    polygon(4,5,6,7);
    polygon(0,1,5,4);
}
