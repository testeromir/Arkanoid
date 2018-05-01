
#include "Brick.h"
#include "Ball.h"
#include "Block.h"
#include<stdlib.h>
#include<math.h>
#include <thread>
#include"glut.h"
#include <fstream>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

Brick b[45];
Ball ball;
Block block;
float red1, red2, red3, red4, green1, green2, green3, green4, blue1, blue2, blue3, blue4;
int matrica[5][9];
float speed = 0.767345667;
int bricksnum;
bool withblock;
bool sides;
bool launched;
bool collision;
int lives = 5;
float velx;
float vely;
int mapnum = 0;
int mapmax = 6;
float red = 0.0;
float green = 0.0;
float blue = 0.0;
float delta = 0.05;

void speedup() {
	ball.velx += ball.velx * 0.1;
	ball.vely += ball.vely * 0.1;
	speed = ball.velx*ball.velx + ball.vely*ball.vely;
}

void speeddown() {
	ball.velx -= ball.velx  * 0.0909090909;
	ball.vely -= ball.vely  * 0.0909090909;
	speed = ball.velx*ball.velx + ball.vely*ball.vely;
}
void ballBlockReset() {
	block.x = 260;
	block.y = 0;
	block.width = 80;
	block.height = 20;
	block.left = false;
	block.right = false;

	ball.x = 285;
	ball.y = 22;
	ball.widthheight = 30;
	ball.velx = 0;
	ball.vely = 0;
	ball.up = false;
	ball.down = false;
	ball.left = false;
	ball.right = false;

	collision = false;
	launched = false;
	sides = false;
	withblock = false;
}


void initMatrix() {
	if (mapnum == mapmax) exit(0);
	
	ifstream file("map" + to_string(mapnum) + ".txt");
	int num;
	int i = 0;
	while (file >> num && i < 45) {
		matrica[i / 9][i % 9] = num;
		i++;
	}
	while (i < 45) {
		matrica[i / 9][i % 9] = 0;
		i++;
	}
	bricksnum = 0;
	for (int n = 0, x = 4, y = 380; n<45; n++, x += 66)
	{
		if (x>540)
		{
			x = 4;
			y -= 25;
		}
		b[n].x = x;
		b[n].y = y;
		b[n].width = 60;
		b[n].height = 20;
		
		if (matrica[n/9][n%9] == 1) {
			b[n].alive = true;
			bricksnum++;
		}
		else {
			b[n].alive = false;
		}

	}
	file.close();
}
void lifeLost() {
	lives--;
	ballBlockReset();
	initMatrix();
}
void initRand() {
	srand(time(NULL));
	bricksnum = 0;
	for (int n = 0, x = 4, y = 380; n<45; n++, x += 66)
	{
		if (x>540)
		{
			x = 4;
			y -= 25;
		}
		b[n].x = x;
		b[n].y = y;
		b[n].width = 60;
		b[n].height = 20;
		int num = rand() % 2;
		if (num == 1) {
			b[n].alive = true;
			bricksnum++;
		}
		else {
			b[n].alive = false;
		}

	}
}

void initColor() {
	red1 = 0.67;
	green1 = 1.83;
	blue1 = 0.45;

	red2 = 1.00;
	green2 = 0.96;
	blue2 = 0.41;


	red3 = 0.77;
	green3 = 0.12;;
	blue3 = 0.23;

	red4 = 0.00;
	green4 = 0.44;
	blue4 = 0.87;


	ball.red = 0.41;
	ball.green = 0.80;
	ball.blue = 0.94;


	block.red = 0.58;
	block.green = 0.51;
	block.blue = 0.79;

	
}
void initialize()	
{
	if (ball.velx != 0 || ball.vely != 0) {
		speedup();
	}
	mapnum++;
	ballBlockReset();
	initMatrix();
	//initRand();
}




/* bool check_collisionX(float Ax, float Aw, float Bx, float Bw) //Function for checking collision
{
	if (Ax + Aw < Bx) return false; //if A is higher than B
	else if (Ax > Bx + Bw) return false; //if A is lower than B

	return true; //There is a collision because none of above returned false
} */

void specialUp(int key,int x,int y)
{
	switch(key)
	{
	
		case (GLUT_KEY_LEFT): 
			block.left=false;
			break;
		case (GLUT_KEY_RIGHT): 
			block.right=false;
			break;
	}
}
void specialDown(int key,int x,int y)
{
	switch(key)
	{
		case (GLUT_KEY_UP) : if (!launched) { 
			ball.up = true;
			ball.vely = sqrt(speed); 
			launched = true; 
		} else { 
			speedup();
		}
			break;
		case (GLUT_KEY_DOWN) : if (launched) {
			speeddown();
		}
			break;
		case (GLUT_KEY_LEFT): 
			block.left=true;
			break;
		case (GLUT_KEY_RIGHT): 
			block.right=true;
			break;
	}
}

void init()
{
	glViewport(0,-35,600,435);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,600,-35,400);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(red,green,blue,1);
	glDisable(GL_DEPTH_TEST);


	if (block.x < 0)
		block.x = 0;
	if (block.x + block.width>600)
		block.x = 520;
	if (block.left == true) {
		block.x = block.x - delta;
		if (((sides && ball.left) || (!launched)) && (block.x > 0.05)) {
			ball.x = ball.x - delta;
		}

	}
	if (block.right == true) {
		block.x = block.x + delta;
		if (((sides && ball.right) || (!launched)) && (block.x < 519.95)) {
			ball.x = ball.x + delta;
		}
	}



	ball.x += delta*ball.velx;
	ball.y += delta*ball.vely;

	collision = false;
	for (int n = 0; n < 45; n++)
	{
		if (b[n].alive == true)
		{


			if (ball.collisionX(b[n]))
			{
				withblock = false;
				ball.velx = -ball.velx;
				b[n].alive = false;
				bricksnum--;
				if (bricksnum == 0) {
					initialize();
					break;
				}
				if (ball.velx > 0) {
					ball.right = true;
					ball.left = false;
				}
				else {
					ball.right = false;
					ball.left = true;
				}

				break;
			}



			if (ball.collisionY(b[n]))
			{
				withblock = false;
				ball.vely = -ball.vely;
				b[n].alive = false;
				bricksnum--;
				if (bricksnum == 0) {
					initialize();
					break;
				}
				if (ball.vely > 0) {
					ball.up = true;
					ball.down = false;
				}
				else {
					ball.up = false;
					ball.down = true;
				}
				break;
			}

		}
	}
	if (ball.x < 0 && !sides)
	{
		sides = false;
		withblock = false;
		ball.velx = -ball.velx;
		ball.right = true;
		ball.left = false;
	}
	if (ball.x + ball.widthheight>600 && !sides)
	{
		sides = false;
		withblock = false;
		ball.right = false;
		ball.left = true;
		ball.velx = -ball.velx;
	}
	if (ball.y + ball.widthheight > 400) {
		ball.vely = -ball.vely;
		withblock = false;
		ball.up = false;
		ball.down = true;
	}
	else if (ball.y + ball.widthheight / 2 < 0)
	{
		if (lives > 0) {
			lifeLost();
		}
		else {
			ball.velx = 0;
			ball.vely = 0;
			ball.x = -500;
			ball.y = -500;
		}
		
	}
	if (!withblock) {


		if (ball.collisionX(block))
		{
			sides = true;
			withblock = true;
			ball.velx = -ball.velx;
			if (ball.velx > 0) {
				ball.right = true;
				ball.left = false;
			}
			else {
				ball.right = false;
				ball.left = true;
			}

		}
	}

	if (!withblock) {
		if (ball.collisionY(block))
		{
			float term = speed - ball.velx*ball.velx;
			if (term > 0) {
				if (block.left && block.x > 0) {
					ball.velx += sqrt(speed) * 15 / 100;

				}
				if (block.right && block.x < 520) {
					ball.velx -= sqrt(speed) * 15 / 100;
				}

				float abs = sqrt(term);
				if (ball.up) {
					ball.vely = abs;
				}

				if (ball.down) {
					ball.vely = -abs;
				}
			}

			withblock = true;
			ball.vely = -ball.vely;
			if (ball.vely > 0) {
				ball.up = true;
				ball.down = false;
			}
			else {
				ball.up = false;
				ball.down = true;
			}

		}
	}




	for (int i = 0; i<45; i++)
	{
		if (b[i].alive == true)
		{
			if (i % 2 == 0) {
				if ((i / 9) % 2 == 0) {
					glColor3f(red4, green4, blue4);
				}
				else {
					glColor3f(red2, green2, blue2);
				}
			}
			else {
				if ((i / 9) % 2 == 0) {
					glColor3f(red3, green3, blue3);
				}
				else {
					glColor3f(red1, green1, blue1);
				}
			}

			glBegin(GL_POLYGON);
			glVertex2f(b[i].x, b[i].y);
			glVertex2f(b[i].x + b[i].width, b[i].y);
			glVertex2f(b[i].x + b[i].width, b[i].y + b[i].height);
			glVertex2f(b[i].x, b[i].y + b[i].height);
			glEnd();
		}
	}

	glColor3f(1.0, 0.49, 0.04);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(600.0, 0.0);

	glVertex2f(600.0, 0.0);
	glVertex2f(600.0, 399.0);

	glVertex2f(600.0, 399.0);
	glVertex2f(1.0, 399.0);

	glVertex2f(1.0, 400.0);
	glVertex2f(1.0, 0.0);
	glEnd();

	glColor3f(block.red, block.green, block.blue);
	glBegin(GL_POLYGON);
	glVertex2f(block.x, block.y);
	glVertex2f(block.x + block.width, block.y);
	glVertex2f(block.x + block.width, block.y + block.height);
	glVertex2f(block.x, block.y + block.height);
	glEnd();

	glColor3f(ball.red, ball.green, ball.blue);
	float x, y;
	x = ball.x + ball.widthheight / 2;
	y = ball.y + ball.widthheight / 2;
	double radius = ball.widthheight / 2;
	int i = 0;
	double twicePi = 2.0 * 3.142;
	glBegin(GL_TRIANGLE_FAN); 
	glVertex2f(x, y); 
	for (i = 0; i <= 20; i++) {
		glVertex2f(
			(x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20)))
			);
	}
	glEnd(); 

	for (int j = 0; j < lives; j++) {
		x = 20 + j * 35;
		y = -17.5;
		double radius = ball.widthheight / 2;
		int i = 0;
		double twicePi = 2.0 * 3.142;
		glBegin(GL_TRIANGLE_FAN); 
		glVertex2f(x, y); 
		for (i = 0; i <= 20; i++) {
			glVertex2f(
				(x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20)))
				);
		}
		glEnd(); 
	}


	
	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
	
}

void reshape(int w, int h)
{
	
	glutReshapeWindow(600, 400);
	glViewport(0, -35, 600, 435);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 600, -35, 435);
	glTranslatef(0, 35, 0);
	
}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowSize(600,435);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Block Breaker");
	initColor();
	initialize();
	init();
	
	glutDisplayFunc(display);
        glutSpecialFunc(specialDown);
    	glutSpecialUpFunc(specialUp);
		glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}




/* rezolucija je 600 x 400  plocice su dimenzija 60x20 i
redjaju se odozgo od y = 380 i sleva od x = 6 (rupe izmedju
plocica su 6 odnosno 5 piksela po x i y osi
60 * 9 + 10 * 6 = 540 + 60 = 600
20 * 5 + 4 * 5 = 120
*/