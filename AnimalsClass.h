#include <GLUT/glut.h>
#include <cmath>
#include <iostream>

#define BODY 	1
#define FINS	2
#define TAIL	3
#define BODY2 	4

class Animals
{
	public:
		Animals();
		void init(float d, float x, float s);
		void draw(float offsety, float offsetz);
		void idle();
		void setType(int t) { type = t; }
		void setColorV(float v[]);
		float* getColorV() { return colorV; }
		void polygon(int a, int b, int c, int d);
		void drawCubes();
	private:
		int type;
		float colorV[3];
		float rotate;
		float translX;
		float translY;
		float translZ;
		float angle1;
		float angle2;
		float angle3;
		float angle4;
		float angle5;
		float angleX; 
		float angleY;
		float angle;
		float angleChange;
		float change1;
		float change2;
		float change3;
		float change4;
		float change5;
		float direction;
		float speed;
		float x;
		GLubyte *base;
		float vertices[8][3];
		GLuint textures;
};

Animals::Animals()
{
	translY = 0.0;
	translZ = 0.0;
	angle1 = 0.0;
	angle2 = 0.0;
	angleX = 0.0;
	angleY = 0.0;
	angle3 = 15.0;
	angle4 = 0.0;
	change1 = 0.05;
	change2 = 0.1;
	change3 = 0.05;
	change4 = 0.01;
	change5 = 0.5;
	angle = 0;
	angleChange = 0.1;
	x = 0.1;
}

void Animals::init(float d, float x, float s)
{
	direction = d;
	translX = x;
	speed = s;

	vertices[0][0] = -1.0; vertices[0][1] = -1.0; vertices[0][2] = -1.0;
	vertices[1][0] = 1.0; vertices[1][1] = -1.0; vertices[1][2] = -1.0;
	vertices[2][0] = 1.0; vertices[2][1] = 1.0; vertices[2][2] = -1.0;
	vertices[3][0] = -1.0; vertices[3][1] = 1.0; vertices[3][2] = -1.0;
	vertices[4][0] = -1.0; vertices[4][1] = -1.0; vertices[4][2] = 1.0; 
 	vertices[5][0] = 1.0; vertices[5][1] = -1.0; vertices[5][2] = 1.0;
 	vertices[6][0] = 1.0; vertices[6][1] = 1.0; vertices[6][2] = 1.0;
 	vertices[7][0] = -1.0; vertices[7][1] = 1.0; vertices[7][2] = 1.0;

	change1 = 0.05 * speed;
	change2 = 0.05 * speed;

	
	//base = texture.loadTexture("./assets/fish.bmp", 256, 256, 3);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, base);
	//glBindTexture(GL_TEXTURE_2D, 2);

	glNewList(BODY, GL_COMPILE);
	glScalef(1.5, 0.75, 0.5);
	//glutSolidCube(1.0);
	drawCubes();
	glEndList();

	glNewList(TAIL, GL_COMPILE);
	glScalef(1.5, 0.5, 0.2);
	drawCubes();
	//glutSolidCube(1.0);
	glEndList();

	//glNewList(FINS, GL_COMPILE);

	glNewList(BODY2, GL_COMPILE);
	glScalef(.75, .75, .75);
	drawCubes();
	//glutSolidSphere(1, 24, 12);
	glEndList();


}

void Animals::draw(float offsety, float offsetz)
{
	//regular fish
	if(type == 0)
	{
		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);

			glColor3fv(colorV);
			glTranslatef(translX, offsety, offsetz);
			glRotatef(angle, 0.0, 1.0, 0.0);
			glRotatef(angle2, 0.0, 0.0, 1.0);
			glCallList(BODY);

			glColor3fv(colorV);
			glRotatef(angle1, 0.0, 1.0, 0.0);
			glTranslatef(direction * 0.75, 0.0, 0.0);
			glCallList(TAIL);
			glPopMatrix();

		glPopAttrib();
		glPopMatrix();
	}
	//octopus
	if(type == 1)
	{
		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);

			glColor3fv(colorV);
			glTranslatef(angleX, angleY, offsetz);
			glTranslatef(0.0, offsety, offsetz);
			//glRotatef(angle3, 1.0, 0.0, 0.0);
			glRotatef(angle3 * direction, 0.0, 0.0, 1.0);
			glCallList(BODY2);

			glPushMatrix();
			glTranslatef(-.50, -1.5, 0.50);
			glRotatef(angle4, 0.0, 0.0, 1.0);
			glScalef(0.50, 5.0, 1.0);
			glCallList(TAIL);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(.50, -1.5, 0.50);
			glRotatef(angle4, 0.0, 0.0, 1.0);
			glScalef(0.50, 5.0, 1.0);
			glCallList(TAIL);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(.50, -1.5, -0.50);
			glRotatef(angle4, 0.0, 0.0, 1.0);
			glScalef(0.50, 5.0, 1.0);
			glCallList(TAIL);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-.50, -1.5, -0.50);
			glRotatef(angle4, 0.0, 0.0, 1.0);
			glScalef(0.50, 5.0, 1.0);
			glCallList(TAIL);
			glPopMatrix();
		glPopAttrib();
		glPopMatrix();
	}

}

void Animals::idle()
{
	translX += change1;

	angleX += change3 * speed;
	angleY += sin(change4) * 1.1;

	//std::cout << angleX << ", " << angleY <<std::endl;
	if(angleX > 15.0)
	{
		change3 = -change3;
		angle3 = -angle3;
	}
	if(angleY > 2.0)
		change4 = -change4;
	if(angleY < -2.0)
		change4 = -change4;
	if(angleX < -12.0)
	{
		change3 = -change3;
		angle3 = -angle3;
	}

	angle4 += change5;

	if(angle4 > 5)
		change5 = -change5;
	if(angle4 < -5)
		change5 = -change5;

	if(change3 == -change3)
		angle3 = -angle3;
	
	angle += angleChange * speed;

	angle1 += change2;

	if(angle > 3)
		angleChange = -angleChange;
	if(angle < -3)
		angleChange = -angleChange;

	if(translX > 20)
	{
		change1 = -0.05 * speed;
		if(direction == 1)
			angle2 = 0;
		else
			angle2 = 180;
	}
	if(translX < -20.0)
	{
		change1 = 0.05 * speed;
		if(direction == 1)
			angle2 = 180;
		else
			angle2 = 0;
	}

	if(angle1 > 30)
		change2 = -0.5 * speed * 2;
	else if(angle1 < -30)
		change2 = 0.5 * speed * 2;

	//std::cout << angle <<std::endl;
	glutPostRedisplay();
}

void Animals::setColorV(float v[])
{
	colorV[0] = v[0];
	colorV[1] = v[1];
	colorV[2] = v[2];
}

void Animals::polygon(int a, int b, int c, int d)
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

void Animals::drawCubes()
{
    polygon(0,3,2,1);
    polygon(2,3,7,6);
    polygon(0,4,7,3);
    polygon(1,2,6,5);
    polygon(4,5,6,7);
    polygon(0,1,5,4);
}

