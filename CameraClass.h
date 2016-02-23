#include <GLUT/glut.h>
#include <cmath>
#include <iostream>

class Camera
{
public:
	Camera();
	void camera();
	void keyboard(unsigned char key, int x, int y);
	void setCoordinates(float v[]);
	void setOnOff(bool a) { onOff = a; }
	void setOrientation(int a) { orientation = a; }
	void idle();
	void setChoice(int c){ choice = c; }
private:
	float camx;
	float camy; 
	float camz;
	float lx;
	float ly;
	float lz;
	float changex;
	float changey;
	float changez;
	bool onOff;
	int orientation;
	int choice;
};

Camera::Camera()
{
	camx = 0.0;
	camy = 0.0;
	camz = 35.0;
	lx = 0.0;
	ly = 0.0;
	lz = -1.0;
	changex = 0.5;
	changey = 0.5;
	changez = 0.5;
	onOff = false;
	orientation = 0;
	choice = 0;
}

void Camera::camera()
{
	glLoadIdentity();
	gluLookAt(camx, camy, camz, lx + camx, ly + camy, lz + camz, 0.0, 1.0, 0.0);
}

void Camera::keyboard(unsigned char key, int x, int y)
{
	if(!onOff)
	{
		switch(key)
		{
			case 'X':
				camx -= (lx + changex);
				//std::cout << "x" << camx << std::endl;
				//std::cout << "lx" << lx << std::endl;
				break;

			case 'x':
				camx += (lx + changex);

				if(camx == 8)
				{
					camx = -30.0;
					lx = 1.0;
					changex = -changex;
				}

				if(camx == -8 && lx == 1.0)
				{
					camx = 30.0;
					lx = -1.0;
					changex = -changex;
				}
				//std::cout << "x" << camx << std::endl;
				//std::cout << "lx" << lx << std::endl;
				break;

			case 'Y':
				camy -= (ly + changey);
				//std::cout << "y" << camy << std::endl;
				//std::cout << "ly" << ly << std::endl;
				break;

			case 'y':
				camy += (ly + changey);

				if(camy == 8)
				{
					camy = -10;
					ly = 1.0;
					changey = -changey;
				}

				if(camy == 0 && ly == 1)
				{
					camy = 30;
					ly = -1.0;
					changey = -changey;
				}
				//std::cout << "y" << camy << std::endl;
				//std::cout << "ly" << ly << std::endl;
				break;


			case 'Z':

				camz += (lz + changez);
				if(camz == 17.5)
				{
					camz = -30.0;
					lz = 1.0;
					changez = -changez;
				}

				if(camz == -17.5 && lz == 1.0)
				{
					camz = 30.0;
					lz = -1.0;
					changez = -changez;
				}

				//std::cout << "z" << camz << std::endl;
				//std::cout << "lz" << lz << std::endl;
				break;

			case 'z':
				camz -= (lz + 0.5);
				//std::cout << "z" << camz << std::endl;
				//std::cout << "lz" << lz << std::endl;
				break;
			//reset to default
			case 'c':
			if(orientation == 2)
			{
				camx = 0.0;
				camy = 32.0;
				camz = 0.0;
				lx = 0.0;
				ly = -1.0;
				lz = -0.01;
			}

			else if(orientation == 3)
			{
				camx = 32.0;
				camy = 0.0;
				camz = 0.0;
				lx = -1.0;
				ly = 0.0;
				lz = 0.0; 
			}
			else
			{
				camx = 0.0;
				camy = 0.0;
				camz = 35.0;
				lx = 0.0;
				ly = 0.0;
				lz = -1.0;
			}
			choice = 0;
				break;
		}
	}
}

void Camera::setCoordinates(float v[])
{
	camx = v[0];
	camy = v[1];
	camz = v[2];
	lx = v[3];
	ly = v[4];
	lz = v[5];
}

void Camera::idle()
{
	if(choice == 1)
	{

		camz += ((lz + changez) / 4);
		if(camz == 10)
		{
			camz = -30.0;
			lz = 1.0;
			changez = -changez;
		}

		if(camz == -10 && lz == 1.0)
		{
			camz = 30.0;
			lz = -1.0;
			changez = -changez;
		}	
	}
	if(choice == 2)
	{
		camy += ((ly + changey) / 4);

		if(camy == 8)
		{
			camy = -10;
			ly = 1.0;
			changey = -changey;
		}

		if(camy == 0 && ly == 1)
		{
			camy = 30;
			ly = -1.0;
			changey = -changey;
		}
	}

	if(choice == 3)
	{
		camx += ((lx + changex) / 4);

		if(camx == 4)
		{
			camx = -30.0;
			lx = 1.0;
			changex = -changex;
		}

		if(camx == -4 && lx == 1.0)
		{
			camx = 30.0;
			lx = -1.0;
			changex = -changex;
		}
	}

	if(choice == 4)
	{
		camx += ((lx + changex) / 4);

		if(camx == 3)
		{
			camx = -15.0;
			lx = 1.0;
			changex = -changex;
		}

		if(camx == -3 && lx == 1.0)
		{
			camx = 15.0;
			lx = -1.0;
			changex = -changex;
		}
	}
}