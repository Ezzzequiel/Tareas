#include<GL/glut.h>
void init(void){
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(2,0,6,0,0,0,0,1,0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60,1,1,12);
}
	
void axis(){
	glBegin(GL_LINES);
	glVertex3i(-800,0,0);
	glVertex3i(800,0,0);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3i(0,-800,0);
	glVertex3i(0,800,0);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3i(0,0,-800);
	glVertex3i(0,0,800);
	glEnd();
}
	
void draw_3d(void){
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	for(int i=1;i<=360;i++){
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		axis();
		glPopMatrix();
		glPushMatrix();
		glRotated(i,0,1,0);
		glTranslated(0,2,0);
		glutWireSphere(1.0,50,50);
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
