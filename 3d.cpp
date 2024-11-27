#include<GL/slut.h>
void init(void){
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0,0,5,0,0,0,0,1,5);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60,1,1,12);
}
	
void draw_3d(void){
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	for(int i=1;i<=360;i++){
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glRotated(i,1,0,0);
		glTranslated(2,0,0);
		glutWireCube(1.0);
		Sleep(5);
		glPopMatrix();
		glFlush();
	}
}

int main(int argc, char** argv){
	glutInit (&argc, argv);
	glutInitWindowSize(800,600);
	glutCreateWindow("3d");
	init();
	glutDisplayFunc(draw_3d);
	glutMainLoop();
	return 0;
	
}
