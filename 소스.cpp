#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include "Constants.h"
#include "Sphere.h"
#include "Light.h"

#include "Player.h"
#include "Platform.h"



using namespace std;

clock_t start_t = clock();
clock_t end_t;

vector<Sphere> spheres;
Light light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);
Player player(-boundaryX + PLAYER_SIZE * 1.5f, -boundaryY + PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
Platform ground(0.0f, -boundaryY + PLAYER_SIZE * 0.5f, 0.0f, boundaryX * 2, PLAYER_SIZE);

void initialize() {
	light.setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	light.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

	Material mtl1;
	mtl1.setEmission(0.1f, 0.1f, 0.1f, 1.0f);
	mtl1.setAmbient(0.4f, 0.4f, 0.1f, 1.0f);
	mtl1.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	mtl1.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	mtl1.setShininess(10.0f);

	Material mtl2(mtl1), mtl3(mtl1);
	mtl2.setAmbient(0.1f, 0.4f, 0.4f, 1.0f);
	mtl3.setAmbient(0.4f, 0.1f, 0.4f, 1.0f);

	Sphere sphere1(50.0f, 20, 20);
	sphere1.setCenter(0.0f, -200.0f, 0.0f);
	sphere1.setVelocity(-1.0f, -1.8f, 0.0f);
	sphere1.setMTL(mtl1);
	cout << sphere1.getCenterX() << endl;
	cout << sphere1.getCenterY() << endl;
	cout << sphere1.getCenterZ() << endl;
	spheres.push_back(sphere1);
	cout << spheres[0].getCenterX() << endl;
	cout << spheres[0].getCenterY() << endl;
	cout << spheres[0].getCenterZ() << endl;

	Sphere sphere2(sphere1);
	sphere2.setCenter(100.0f, 200.0f, 0.0f);
	sphere2.setVelocity(1.5f, 1.0f, 0.0f);
	sphere2.setMTL(mtl2);
	spheres.push_back(sphere2);

	Sphere sphere3(sphere1);
	sphere3.setCenter(-100.0f, 0.0f, 0.0f);
	sphere3.setVelocity(-3.0f, -3.0f, 0.0f);
	sphere3.setMTL(mtl3);
	spheres.push_back(sphere3);



}

void displayCharacters(void* font, string str, float x, float y) {
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
		glutBitmapCharacter(font, str[i]);
}

bool isCollisionDetected(const Sphere& sph1, const Sphere& sph2) {
	/* Implement */
	
			if ((pow(sph1.getCenterX()+sph1.getVelocityX() - sph2.getCenterX()- sph2.getVelocityX(),2) + pow(sph1.getCenterY()+ sph1.getVelocityY() - sph2.getCenterY()- sph2.getVelocityY(), 2) + pow(sph1.getCenterZ()+ sph1.getVelocityZ() - sph2.getCenterZ()- sph2.getVelocityZ(), 2) <= pow(sph1.getRadius() + sph2.getRadius(), 2))) return TRUE;
			

	


	return 0;
}

void handleCollision(Sphere& sph1, Sphere& sph2) {
	/* Implement */


			if (isCollisionDetected(sph1, sph2)) {
				float v11 = sph1.getVelocityX();
				float v12 = sph1.getVelocityY();
				float c11 = sph1.getCenterX();
				float c12 = sph1.getCenterY();
				float v21 = sph2.getVelocityX();
				float v22 = sph2.getVelocityY();
				float c21 = sph2.getCenterX();
				float c22 = sph2.getCenterY();
				float dis2 = pow(c11-c21,2)+pow(c12-c22,2);
				sph1.setVelocity(v11 - ((v11 - v21)*(c11-c21) + (v12 - v22)*(c12-c22))/dis2*(c11-c21), v12 - ((v11 - v21) * (c11 - c21) + (v12 - v22) * (c12 - c22)) / dis2 * (c12 - c22),0);
				

				sph2.setVelocity(v21 - ((v11 - v21) * (c11 - c21) + (v12 - v22) * (c12 - c22)) / dis2 * (c21 - c11), v22 - ((v11 - v21) * (c11 - c21) + (v12 - v22) * (c12 - c22)) / dis2 * (c22 - c12), 0);
				
				


			
	}
	


}

void idle() {
	/* Implement */
	end_t = clock();

	if ((float)(end_t - start_t) > 1000 / 30.0f) {
		
		

		for (int i = 0; i < 3; i++) {

			for (int j = i + 1; j < 3; j++) {

				handleCollision(spheres[i], spheres[j]);

			}
		}


		for (int i = 0; i < 3; i++) {

			if ((spheres[i].getCenterX()+ spheres[i].getVelocityX() + spheres[i].getRadius() > boundaryX) || (spheres[i].getCenterX() + spheres[i].getVelocityX() - spheres[i].getRadius() < -boundaryX)) spheres[i].setVelocity(-spheres[i].getVelocityX(), spheres[i].getVelocityY(), spheres[i].getVelocityZ());
			if ((spheres[i].getCenterY() + spheres[i].getVelocityY() + spheres[i].getRadius() > boundaryY) || (spheres[i].getCenterY() + spheres[i].getVelocityY() - spheres[i].getRadius() < -boundaryY)) spheres[i].setVelocity(spheres[i].getVelocityX(), -spheres[i].getVelocityY(), spheres[i].getVelocityZ());
		}
		for (int i = 0; i < 3; i++) {

			spheres[i].move();
		}
		cout << spheres[0].getVelocityX() << " " << spheres[0].getVelocityY() << endl;
		start_t = end_t;
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
	player.draw();
	ground.draw();

	glColor3f(0.0f, 1.0f, 0.0f);

	displayCharacters(GLUT_BITMAP_9_BY_15, "2018_17583 Seongjin Park", -boundaryX+ PLAYER_SIZE, boundaryY- PLAYER_SIZE);


	/* Implement: Draw 3D (light and spheres)*/
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	light.draw();
	for (int i = 0; i < 3; i++) spheres[i].draw();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Move three spheres and handle their collisions");
	initialize();

	// register callbacks
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
