#include <iostream>
#include <vector>


#include "Constants.h"
#include "Bubble.h"
#include "Light.h"
#include "Enemy.h"
#include "Player.h"
#include "Platform.h"

#include "Stage.h"
#include "Collision.h"
#include <GL/freeglut.h>

using namespace std;

clock_t start_t = clock();
clock_t end_t;

vector<Bubble> bubbles;
vector<Enemy> enemies;
vector<Stage> stages;
Light light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);

Collision collision;
int stage_now=2; //0일 경우 game over
bool bPressLeft;
bool bPressRight;
bool bPressUp;
bool bPressSpace;
bool falling;

void initialize() {
	light.setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	light.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	//stage _restart(사망화면)
	Stage stage_restart(Stage::RESTART);
	stages.push_back(stage_restart);
	//stage _start(시작화면)
	Stage stage_start(Stage::START);
	stages.push_back(stage_start);
	//stage 1;
	Stage stage_1(Stage::FIRST);
	Player player(-boundaryX + PLAYER_SIZE * 1.5f, -boundaryY + PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
	Platform ground(0.0f, -boundaryY + PLAYER_SIZE * 0.5f, 0.0f, boundaryX * 2, PLAYER_SIZE, Platform::IMPASSABLE);
	Platform platform1(0.0f, -boundaryY + PLAYER_SIZE * 0.5f+ 150, 0.0f, boundaryX, PLAYER_SIZE, Platform::IMPASSABLE);
	Platform platform2(0.0f, -boundaryY + PLAYER_SIZE * 0.5f + 300, 0.0f, boundaryX, PLAYER_SIZE, Platform::ISPASSABLE);
	Platform platform3(-boundaryX+ PLAYER_SIZE * 0.5f, -boundaryY/2- PLAYER_SIZE, 0.0f, PLAYER_SIZE, boundaryY, Platform::IMPASSABLE);
	Platform platform4(+boundaryX- PLAYER_SIZE * 0.5f, -boundaryY / 2-PLAYER_SIZE, 0.0f, PLAYER_SIZE, boundaryY, Platform::IMPASSABLE);
	Platform platform5(-boundaryX + PLAYER_SIZE * 0.5f, +boundaryY / 2+ PLAYER_SIZE, 0.0f, PLAYER_SIZE,  boundaryY, Platform::IMPASSABLE);
	Platform platform6(+boundaryX - PLAYER_SIZE * 0.5f, +boundaryY / 2+ PLAYER_SIZE, 0.0f, PLAYER_SIZE, boundaryY, Platform::IMPASSABLE);
	Enemy enemy1(-boundaryX + PLAYER_SIZE * 3.0f, PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
	Enemy enemy2( PLAYER_SIZE * 3.0f, PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
	Enemy enemy3(boundaryX - PLAYER_SIZE * 3.0f, PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
	stage_1.setPlayer(player);
	stage_1.setPlatform(ground);
	stage_1.setPlatform(platform1);
	stage_1.setPlatform(platform2);
	stage_1.setPlatform(platform3);
	stage_1.setPlatform(platform4);
	stage_1.setPlatform(platform5);
	stage_1.setPlatform(platform6);
	
	stage_1.setEnemy(enemy1);
	stage_1.setEnemy(enemy2);
	stage_1.setEnemy(enemy3);
	stages.push_back(stage_1);


	
}




void idle() {
	/* Implement */

	end_t = clock();

	if ((float)(end_t - start_t) > 1000 / 60.0f) {
	
		//player 방향 설정-> collide-> move 순서로 해줘야지만 버그가 없다. 
		stages[stage_now].setplayermove(bPressLeft, bPressRight, bPressUp, bPressSpace);


		if (bPressSpace && (stages[stage_now].getBubblesize() < 9)) {

			stages[stage_now].setBubble();
			printf("pushback bubble\n");

		}

		bPressSpace = false;

		

		collision.collide( stages[stage_now]);

		//체력0이될시 Restart 
		if ((stages[stage_now].player).getLife() <= 0) {

			stage_now = 0; 

		}
		
		stages[stage_now].move();


		start_t = end_t;
	}

	glutPostRedisplay();
}

void keyboardDown(unsigned char key, int x, int y) {
	if (key == 32) {
		bPressSpace = true;
		
	}
}

void specialKeyDown
(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_LEFT:
		bPressLeft = true;
		break;
	case GLUT_KEY_RIGHT:
		bPressRight = true;
		break;
	case GLUT_KEY_UP:
		bPressUp = true;
		break;
	case 32:
		
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void specialKeyUp
(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_LEFT:
		bPressLeft = false;
		break;
	case GLUT_KEY_RIGHT:
		bPressRight = false;
		break;
	case GLUT_KEY_UP:
		bPressUp = false;
		break;
	case 32:
		
		break;
	default:
		break;
	}
	glutPostRedisplay();
}




void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);
	//gluOrtho2D(-boundaryX, boundaryX, -boundaryY, boundaryY);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* Implement: Draw 2D (player, ground, and [student ID, name])*/
	
	
	stages[stage_now].draw();	//stage에 속한 platforms, walls, bubbles, enemies 그리기


	//glFlush();

	/* Implement: Draw 3D (light and bubbles)*/
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	light.draw();


	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Bubble Bobble");
	initialize();

	// register callbacks
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboardDown);
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
