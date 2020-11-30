/*
    Hello Triangle, OpenGL 2 level
    No shaders
*/

#include "GL/glut.h"
#include <stdio.h>
#include <math.h>
//#include <iostream>
//submenue
static int submenu1;
int choice;

//default angel
double angle = 45.0;

//rotation variables
float startX;
float startY;
float endX;
float endY;
float difX;
float difY;
float X = 0;
float Y = 0;


//translation
float translationX = 0;
float translationY = 0;
float vertex1[3] = { 10, -20, 30 };
float vertex2[3] = { 30, -30, 20 };
float vertex3[3] = { -20, 30, 40 };
float vertex4[3] = { -30, -30, 60 };
float vertex5[3] = { 0, -40, 60 };

//zoom
float translationZ = 0;

//perspective
bool show = false;

void menu(int num) {  // num: id of the added item
	printf("menu called with arg %d\n", num);
	if (num == 0) {
		choice = 0;
		angle = 30;
		glutPostRedisplay();
	}
	else if (num == 1) {
		choice = 1;
		angle = 45;
		glutPostRedisplay();
	}
	else if (num == 2) {
		choice = 2;
		angle = 60;
		glutPostRedisplay();
	}
	else if (num == 3) {
		choice = 3;
		angle = 75;
		glutPostRedisplay();
	}
	else if (num == 4) {
		choice = 4;
		angle = 45;
		X = Y = 0;
		difX = difY = 0;
		translationX = translationY = 0;
		vertex1[0] = 10;
		vertex1[1] = -20;
		vertex1[2] = 30;
		vertex2[0] = 30;
		vertex2[1] = -30;
		vertex2[2] = 20;
		vertex3[0] = -20;
		vertex3[1] = 30;
		vertex3[2] = 40;
		vertex4[0] = -30;
		vertex4[1] = -30;
		vertex4[2] = 60;
		vertex5[0] = 0;
		vertex5[1] = -40;
		vertex5[2] = 60;

		show = false;
		glutPostRedisplay();
	}
	else if (num == 5) {
		exit(0);
	}
	else if (num == 6) {
		choice = 6;
	}
	else if (num == 7) {
		show = true;
		glutPostRedisplay();
	}
	else if (num == 8) {
		show = false;
		glutPostRedisplay();
	}
}

void createMenu(void) {
	submenu1 = glutCreateMenu(menu);     // create menu, assign a callback
	glutAddMenuEntry("30 degrees", 0);
	glutAddMenuEntry("45 degrees", 1);
	glutAddMenuEntry("60 degrees", 2);
	glutAddMenuEntry("75 degrees", 3);

	glutCreateMenu(menu);
	glutAddSubMenu(" Set Aperture ", submenu1);     // add submenus to the menu
	glutAddMenuEntry(" Rotation ", 6);  //rotation function
	glutAddMenuEntry(" Show perspective ", 7);
	glutAddMenuEntry(" Hide perspective ", 8);
	//glutAddMenuEntry(" Translation ", 7);  //translation function
	//glutAddMenuEntry(" Zoom ", 8);  //zoom function
	glutAddMenuEntry(" Reset ", 4);
	glutAddMenuEntry(" Exit ", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);  // bind to the event: clicking the right button
}

void mouseClick(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON) {
		int mod = glutGetModifiers();
		if (state == GLUT_DOWN) {
			if (mod == GLUT_ACTIVE_SHIFT || mod == GLUT_ACTIVE_CTRL) {
				startX = x;
				startY = y;
			}
			else if (choice == 6) {
				startX = x;
				startY = y;
			}
		}
		else if (state == GLUT_UP) {
			if (mod == GLUT_ACTIVE_SHIFT) {
				vertex1[0] = vertex1[0] + translationX;
				vertex1[1] = vertex1[1] + translationY;
				vertex2[0] = vertex2[0] + translationX;
				vertex2[1] = vertex2[1] + translationY;
				vertex3[0] = vertex3[0] + translationX;
				vertex3[1] = vertex3[1] + translationY;
				vertex4[0] = vertex4[0] + translationX;
				vertex4[1] = vertex4[1] + translationY;
				vertex5[0] = vertex5[0] + translationX;
				vertex5[1] = vertex5[1] + translationY;
				translationX = 0;
				translationY = 0;
			}
			else if (mod == GLUT_ACTIVE_CTRL) {
				vertex1[2] = vertex1[2] + translationZ;
				vertex2[2] = vertex2[2] + translationZ;
				vertex3[2] = vertex3[2] + translationZ;
				vertex4[2] = vertex4[2] + translationZ;
				vertex5[2] = vertex5[2] + translationZ;
				translationZ = 0;
			}
			else if (choice == 6) {
				X = X + difX;
				Y = Y + difY;
				difX = 0;
				difY = 0;
			}
		}
	}
}

void motion(int x, int y)
{
	int mod = glutGetModifiers();
	if (mod == GLUT_ACTIVE_SHIFT) {
		translationX = (x - startX) / 10;
		translationY = (startY - y) / 10;
		glutPostRedisplay();
	}
	else if (mod == GLUT_ACTIVE_CTRL) {
		translationZ = (x - y - startX + startY) / 10;
		glutPostRedisplay();
	}
	else if (choice == 6) {
		endX = x;
		endY = y;

		difY = (endY - startY) / 5;
		glutPostRedisplay();
		difX = (endX - startX) / 5;
		glutPostRedisplay();
	}
}


void myDisplay(void)

{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, 1.0, 1.0, 10000000000); // aperture, aspect, near, far
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(0, 0, -200);	

	glColor3f(1.0, 0.0, 0.0); // red
	glBegin(GL_LINES);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);
	glEnd();

	//cube 1
	glPushMatrix();
	glRotatef(Y + difY, 1.0f, 0.0f, 0.0f);
	glRotatef(X + difX, 0.0f, 1.0f, 0.0f);
	if (show == true) {
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f((vertex1[0] + translationX + 5), (vertex1[1] + translationY + 5),-100000);
		glVertex3f((vertex1[0] + translationX + 5), (vertex1[1] + translationY + 5), 100000);
		

		glVertex3f((vertex1[0] + translationX + 5), (vertex1[1] + translationY - 5), -100000);
		glVertex3f((vertex1[0] + translationX + 5), (vertex1[1] + translationY - 5), 100000);


		glVertex3f((vertex1[0] + translationX - 5), (vertex1[1] + translationY + 5), -100000);
		glVertex3f((vertex1[0] + translationX - 5), (vertex1[1] + translationY + 5), 100000);

		glVertex3f((vertex1[0] + translationX - 5), (vertex1[1] + translationY - 5), -100000);
		glVertex3f((vertex1[0] + translationX - 5), (vertex1[1] + translationY - 5), 100000);
		glEnd();
	}	
	glColor3f(1, 1, 1);
	glTranslatef((vertex1[0] + translationX), (vertex1[1] + translationY), (vertex1[2] + translationZ));
	glutSolidCube(10);
	glPopMatrix();
	
	//cube 2
	glPushMatrix();
	glRotatef(Y + difY, 1.0f, 0.0f, 0.0f);
	glRotatef(X + difX, 0.0f, 1.0f, 0.0f);
	if (show == true) {
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f((vertex2[0] + translationX + 5), (vertex2[1] + translationY + 5), -1000000);
		glVertex3f((vertex2[0] + translationX + 5), (vertex2[1] + translationY + 5), 1000000);

		glVertex3f((vertex2[0] + translationX + 5), (vertex2[1] + translationY - 5), -1000000);
		glVertex3f((vertex2[0] + translationX + 5), (vertex2[1] + translationY - 5), 1000000);

		glVertex3f((vertex2[0] + translationX - 5), (vertex2[1] + translationY + 5), -1000000);
		glVertex3f((vertex2[0] + translationX - 5), (vertex2[1] + translationY + 5), 1000000);

		glVertex3f((vertex2[0] + translationX - 5), (vertex2[1] + translationY - 5), -1000000);
		glVertex3f((vertex2[0] + translationX - 5), (vertex2[1] + translationY - 5), 1000000);
		glEnd();
	}
	glColor3f(1, 1, 1);
	glTranslatef((vertex2[0] + translationX), (vertex2[1] + translationY), (vertex2[2] + translationZ));
	glutSolidCube(10);
	glPopMatrix();

	//cube 3
	glPushMatrix();
	glRotatef(Y + difY, 1.0f, 0.0f, 0.0f);
	glRotatef(X + difX, 0.0f, 1.0f, 0.0f);
	if (show == true) {
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f((vertex3[0] + translationX + 5), (vertex3[1] + translationY + 5), -1000000);
		glVertex3f((vertex3[0] + translationX + 5), (vertex3[1] + translationY + 5), 1000000);

		glVertex3f((vertex3[0] + translationX + 5), (vertex3[1] + translationY - 5), -1000000);
		glVertex3f((vertex3[0] + translationX + 5), (vertex3[1] + translationY - 5), 1000000);

		glVertex3f((vertex3[0] + translationX - 5), (vertex3[1] + translationY + 5), -1000000);
		glVertex3f((vertex3[0] + translationX - 5), (vertex3[1] + translationY + 5), 1000000);

		glVertex3f((vertex3[0] + translationX - 5), (vertex3[1] + translationY - 5), -1000000);
		glVertex3f((vertex3[0] + translationX - 5), (vertex3[1] + translationY - 5), 1000000);
		glEnd();
	}
	glColor3f(1, 1, 1);
	glTranslatef((vertex3[0] + translationX), (vertex3[1] + translationY), (vertex3[2] + translationZ));
	glutSolidCube(10);
	glPopMatrix();

	//cube 4
	glPushMatrix();
	glRotatef(Y + difY, 1.0f, 0.0f, 0.0f);
	glRotatef(X + difX, 0.0f, 1.0f, 0.0f);
	if (show == true) {
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f((vertex4[0] + translationX + 5), (vertex4[1] + translationY + 5), -1000000);
		glVertex3f((vertex4[0] + translationX + 5), (vertex4[1] + translationY + 5), 1000000);

		glVertex3f((vertex4[0] + translationX + 5), (vertex4[1] + translationY - 5), -1000000);
		glVertex3f((vertex4[0] + translationX + 5), (vertex4[1] + translationY - 5), 1000000);

		glVertex3f((vertex4[0] + translationX - 5), (vertex4[1] + translationY + 5), -1000000);
		glVertex3f((vertex4[0] + translationX - 5), (vertex4[1] + translationY + 5), 1000000);

		glVertex3f((vertex4[0] + translationX - 5), (vertex4[1] + translationY - 5), -1000000);
		glVertex3f((vertex4[0] + translationX - 5), (vertex4[1] + translationY - 5), 1000000);
		glEnd();
	}
	glColor3f(1, 1, 1);
	glTranslatef((vertex4[0] + translationX), (vertex4[1] + translationY), (vertex4[2] + translationZ));
	glutSolidCube(10);
	glPopMatrix();

	//cube 5
	glPushMatrix();
	glRotatef(Y + difY, 1.0f, 0.0f, 0.0f);
	glRotatef(X + difX, 0.0f, 1.0f, 0.0f);
	if (show == true) {
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f((vertex5[0] + translationX + 5), (vertex5[1] + translationY + 5), -1000000);
		glVertex3f((vertex5[0] + translationX + 5), (vertex5[1] + translationY + 5), 1000000);

		glVertex3f((vertex5[0] + translationX + 5), (vertex5[1] + translationY - 5), -1000000);
		glVertex3f((vertex5[0] + translationX + 5), (vertex5[1] + translationY - 5), 1000000);

		glVertex3f((vertex5[0] + translationX - 5), (vertex5[1] + translationY + 5), -1000000);
		glVertex3f((vertex5[0] + translationX - 5), (vertex5[1] + translationY + 5), 1000000);

		glVertex3f((vertex5[0] + translationX - 5), (vertex5[1] + translationY - 5), -1000000);
		glVertex3f((vertex5[0] + translationX - 5), (vertex5[1] + translationY - 5), 1000000);
		glEnd();
	}
	glColor3f(1, 1, 1);
	glTranslatef((vertex5[0] + translationX), (vertex5[1] + translationY), (vertex5[2] + translationZ));
	glutSolidCube(10);
	glPopMatrix();
	
	//glFlush();
	glutSwapBuffers();
}

void resize(int x, int y)
{
	int dis;
	if (x < y) {
		dis = x;
	}
	else {
		dis = y;
	}
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, 1.0, 1.0, 100.01); // aperture, aspect, near, far
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glViewport(0, 0, dis, dis);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glViewport(0, 0, 800, 800);
	glutCreateWindow("Program 3");

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(resize);
	createMenu();
	glutMouseFunc(mouseClick);
	glutMotionFunc(motion);
	glutMainLoop();
	return 0;
}