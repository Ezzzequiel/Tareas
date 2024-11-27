#include<GL/glut.h>

void init(void){
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0,0,15,0,0,0,0,1,0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60,1,1,20);
}
	
	
void axis() {
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex3i(-20,0,0);
	glVertex3i(20,0,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3i(0,-20,0);
	glVertex3i(0,20,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3i(0,0,-20);
	glVertex3i(0,0,20);
	glEnd();
}
	

void draw_3d(void){
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	for(int i=1;i<=360;i++){
		glClear(GL_COLOR_BUFFER_BIT);
		
		glPushMatrix();
		glTranslated(0,0,0);
		glRotated(i,0,1,0);
		
		glutWireTeapot(1.0);
		glPopMatrix();
		
		glPushMatrix();
		glTranslated(-5,0,0);
		glRotated(i,0,1,0);
		
		glutWireTeapot(1.0);
		glPopMatrix();
		
		glPushMatrix();
		glTranslated(5,0,0);
		glRotated(i,0,1,0);
		
		glutWireTeapot(1.0);
		glPopMatrix();
		
		Sleep(20);
		glFlush();
	}
}
	
void draw_3d2(void){
	
	glMatrixMode(GL_MODELVIEW);
	float posx=-6.5;
	float posy=-6.5;
	for(int i=0;i<=360;i++){
		glClear(GL_COLOR_BUFFER_BIT);
		
		
		glPushMatrix();
		glColor3f(1.0,0,0);
		glTranslatef(posx,posy,0);
		glutSolidSphere(1.5,30,10);
		glPopMatrix();
		
		
		glPushMatrix();
		glColor3f(0.0,1.0,0.0);
		glTranslatef(posx,posy,0);
		glRotatef(i,0.0,0.0,1.0);
		glScalef(0.3,1.0,0.3);
		glutSolidSphere(1.5,30,10);
		glPopMatrix();
		
		posx+=0.035;
		posy+=0.035;
		glFlush();
		Sleep(20);
	}
}
	
void draw_3d3(void){
	glMatrixMode(GL_MODELVIEW);
	float posx=-6.5;
	float posy=-6.5;
	for(int i=0;i<=360;i++){
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0,0.0,0.0);
		axis();
		glPushMatrix();
		glTranslatef(posx,posy,0.0);
		glRotatef(i,0.0,0.0,1.0);
		glTranslatef(0.0,0.0,2.0);
		glScalef(0.3,1.0,0.3);
		glutSolidSphere(2.0,30,10);
		glPopMatrix();
		posx+=0.035;
		posy+=0.035;
		Sleep(20);
		glFlush();
	}
}
	
int main(int argc, char** argv){
	glutInit (&argc, argv);
	glutInitWindowSize(800,600);
	glutCreateWindow("3d");
	init();
	glutDisplayFunc(draw_3d2);
	glutMainLoop();
	return 0;
	
}
