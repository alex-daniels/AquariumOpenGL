#include <GLUT/glut.h>
#include <iostream>
#include "DisplayClass.h"

void displayfunc();
void reshapefunc(int w, int h);
void keyboardfunc(unsigned char key, int x, int y);
//void mouse(int button, int state, int x, int y);
void idle();
void init();
void createMenu();
void leftClick(int choice);

Display display;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Asssignment4");
	createMenu();
	init();
	glutDisplayFunc(displayfunc);
	glutReshapeFunc(reshapefunc);
	glutKeyboardFunc(keyboardfunc);
	glutIdleFunc(idle);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutMainLoop();
}

void init()
{
	display.init();
}

void displayfunc()
{
	display.display();
}

void reshapefunc(int w, int h)
{
	display.reshape(w, h);
}

void keyboardfunc(unsigned char key, int x, int y)
{
	display.keyboard(key, x, y);
}

void createMenu()
{
	int left;
	left = glutCreateMenu(leftClick);
	glutAddMenuEntry("Flythrough | Z", 1);
	glutAddMenuEntry("Flythrough | Y", 2);
	glutAddMenuEntry("Flythrough | X", 3);
	glutAddMenuEntry("Offset 1 | (No Camera Movement)", 4);
	glutAddMenuEntry("Offset 2 | (No Camera Movement)", 5);
	glutAddMenuEntry("Offset 3 | (No Camera Movement)", 6);
	glutAddMenuEntry("Offset 4 | (No Camera Movement)", 7);
	glutAddMenuEntry("Custom", 8);
	glutAddMenuEntry("Follow", 9);
	glutAddMenuEntry("Exit", 10);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void leftClick(int choice)
{
	float vec[6];
	switch(choice)
	{
		case 1:
			//std::cout << "z" << std::endl;
			vec[0] = 0.0; vec[1] = 0.0; vec[2] = 32.0;
			vec[3] = 0.0; vec[4] = 0.0; vec[5] = -1.0;
			display.setCoords(vec, false, 1);
			display.setChoice(1);
			break;
		case 2:
			//std::cout << "y" << std::endl;
			vec[0] = 0.0; vec[1] = 32.0; vec[2] = 0.0;
			vec[3] = 0.0; vec[4] = -1.0; vec[5] = -0.01;
			display.setCoords(vec, false, 2);
			display.setChoice(2);
			break;
		case 3:
			//std::cout << "x" << std::endl;
			vec[0] = 32.0; vec[1] = 0.0; vec[2] = 0.0;
			vec[3] = -1.0; vec[4] = 0.0; vec[5] = 0.0;
			display.setCoords(vec, false, 3);
			display.setChoice(3);
			break;
		case 4:
			//offset 1
			vec[0] = 25.0; vec[1] = 0; vec[2] = 25;
			vec[3] = -1.0; vec[4] = 0.0; vec[5] = -1.0;
			display.setCoords(vec, true, 0);
			break;
		case 5:
			//offset 2
			vec[0] = -25.0; vec[1] = 0; vec[2] = 25;
			vec[3] = 1; vec[4] = 0; vec[5] = -1.0;
			display.setCoords(vec, true, 0);
			break;
		case 6:
			//offset 3
			vec[0] = -25.0; vec[1] = 0; vec[2] = -25;
			vec[3] = 1; vec[4] = 0; vec[5] = 1.0;
			display.setCoords(vec, true, 0);
			break;
		case 7:
			//offset 4
			vec[0] = 25.0; vec[1] = 0; vec[2] = -25;
			vec[3] = -1; vec[4] = 0; vec[5] = 1.0;
			display.setCoords(vec, true, 0);
			break;
		case 8:
			//std::cout << "Custom" <<std::endl;
			std::cout << "Enter 5 Custom Coordinates" <<std::endl;
			std::cout << "Camera X, Camera Y, Camera Z, Pos X, Pos Y" <<std::endl;
			std::cin >> vec[0]; std::cin >> vec[1]; std::cin >> vec[2];
			std::cin >> vec[3]; std::cin >> vec[4]; vec[5] = -0.001;
			display.setCoords(vec, false, 0);
			break;
		case 9:
			vec[0] = 0.0; vec[1] = 5.0; vec[2] = -4.0;
			vec[3] = 0.0; vec[4] = -1.0; vec[5] = -0.001;
			display.setCoords(vec, false, 3);
			display.setChoice(4);
			break;
		case 10:
			exit(0);
			break;
	}
}

void idle()
{
	display.display();
	display.idle();
}