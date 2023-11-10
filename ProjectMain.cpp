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
Player player(-boundaryX + PLAYER_SIZE * 1.5f, -boundaryY + PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
Collision collision;
int stage_now;




bool bPressLeft;
bool bPressRight;
bool bPressUp;
bool falling;

void initialize() {
	light.setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	light.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	/*float playerboundary[4];*/
	/*cout << "player.getBoundary(): " << player.getBoundary()[0] << " " << player.getBoundary()[1] << " "
		<< player.getBoundary()[2] << " " << player.getBoundary()[3] << "\n";*/

	Platform ground(0.0f, -boundaryY + PLAYER_SIZE * 0.5f, 0.0f, boundaryX * 2, PLAYER_SIZE);
	Platform ground2(0.0f, -boundaryY + PLAYER_SIZE * 0.5f+100, 0.0f, boundaryX, PLAYER_SIZE);
	/*cout << "ground.getCenter(): " << ground.getCenter()[0] << " " << ground.getCenter()[1] << " "
		<< ground.getCenter()[2]<< "\n";
	cout << "ground.getWidth(): " << ground.getWidth()<< "\n";
	cout << "ground.getBoundary(): " << ground.getBoundary()[0] << " " << ground.getBoundary()[1] << " "
		<< ground.getBoundary()[2] << " " << ground.getBoundary()[3] << "\n";*/
	Stage stage;
	stage.setPlatform(ground);
	stage.setPlatform(ground2);
	/*cout << "stage.getPlatform(): " << stage.getPlatform()[0].getBoundary()[0] << " " << stage.getPlatform()[0].getBoundary()[1] << " "
		<< stage.getPlatform()[0].getBoundary()[2] << " " << stage.getPlatform()[0].getBoundary()[3] << "\n";*/
	stages.push_back(stage);
}


void collide() {



	for(auto bub : bubbles) collision.handleCollision(player, bub);
	for(auto enm: enemies) collision.handleCollision(player, enm);
	for (auto  plat : stages[stage_now].getPlatform() ) collision.handleCollision(player, plat);
	for (auto wal : stages[stage_now].getWall()) collision.handleCollision(player, wal);
	for (auto enm : enemies) {
		for (auto bub : bubbles) {
			collision.handleCollision(enm, bub); //오류 생길수 있음 
		}
	}
	for (auto enm : enemies) {
		for (auto wal : stages[stage_now].getWall()) {
			collision.handleCollision(enm, wal);
		}
	}


}

void idle() {
	/* Implement */

	end_t = clock();

	if ((float)(end_t - start_t) > 1000 / 60.0f) {
	
		//좌우 움직임
		if (bPressLeft == false && bPressRight == false) {
			player.setHorizontalState(Player::HSTOP);
		}
		else if (bPressLeft) {
			player.setFace(Player::LEFT);
			player.setHorizontalState(Player::MOVE);
		}
		else if (bPressRight) {
			player.setFace(Player::RIGHT);
			player.setHorizontalState(Player::MOVE);
		}

		if (bPressUp)
			if (player.getVerticalState() == Player::VSTOP) {
				player.setVelocityY(20.0f);
				player.setVerticalState(Player::JUMP);
			}

		collide();

		
		player.move();

		start_t = end_t;
	}

	glutPostRedisplay();
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
	default:
		break;
	}
	glutPostRedisplay();
}

void displayCharacters(void* font, string str, float x, float y) {
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
		glutBitmapCharacter(font, str[i]);
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
	player.draw();
	stages[stage_now].draw();
	

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);
	displayCharacters(GLUT_BITMAP_9_BY_15, "BUB", -boundaryX + 10.f, boundaryY - 30.f);
	//glFlush();

	/* Implement: Draw 3D (light and bubbles)*/
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	light.draw();

	for (const auto& bub : bubbles)
		bub.draw();

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
	glutCreateWindow("Move three bubbles and handle their collisions");
	initialize();

	// register callbacks
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
