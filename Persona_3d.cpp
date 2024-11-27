#include <GL/glut.h>


GLfloat x=-0.2;
GLfloat y = 0;
GLfloat z=0;
GLubyte label[]={'H','O','L','A'};
void init(void){
	glClearColor(1.0,1.0,1.0,0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0,0,5,0,0,0,0,1,0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(90,1,1,12);
}
	
	
	
void axis(){
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex3i(-20,0,0);
	glVertex3i(20,0,0);
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	glVertex3i(0,-20,0);
	glVertex3i(0,20,0);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
	glVertex3i(0,0,-20);
	glVertex3i(0,0,20);
	glEnd();
	
}
	
void head(){
	glColor3f(0.0,1.0,0.0);
	glutSolidSphere(1.3,30,30);
	
}
	
void right_eye(){
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
	glTranslatef(1.2,0.2,-0.4);
	glutSolidSphere(0.3,30,30);
	glPopMatrix();
	glColor3f(0.0,0.0,0.0);
	glPushMatrix();
	glTranslatef(1.5,0.2,-0.4);
	glutSolidSphere(0.1,30,30);
	glPopMatrix();
	
}
	
void right_eye_animated(){
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
	glTranslatef(1.2,0.2,-0.4);
	glutSolidSphere(0.3,30,30);
	glPopMatrix();
	glColor3f(0.0,0.0,0.0);
	glPushMatrix();
	glTranslatef(1.5,0.0,-0.4);
	glutSolidSphere(0.1,30,30);
	glPopMatrix();
}

void left_eye(){
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
	glTranslatef(1.2,0.2,0.4);
	glutSolidSphere(0.3,30,30);
	glPopMatrix();
	glColor3f(0.0,0.0,0.0);
	glPushMatrix();
	glTranslatef(1.5,0.2,0.4);
	glutSolidSphere(0.1,30,30);
	glPopMatrix();
}

void left_eye_animated(){
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
	glTranslatef(1.2,0.2,0.4);
	glutSolidSphere(0.3,30,30);
	glPopMatrix();
	glColor3f(0.0,0.0,0.0);
	glPushMatrix();
	glTranslatef(1.5,0.0,0.4);
	glutSolidSphere(0.1,30,30);
	glPopMatrix();
}

void mouth(){
	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
	glScalef(1,0.5,1.9);
	glTranslatef(1.2,-0.8,0.0);
	glutSolidSphere(0.2,30,30);
	glPopMatrix();
}
	
void mouth_animated(){
	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
	glScalef(1,1.9,1);
	glTranslatef(1.2,-0.2,0.0);
	glutSolidSphere(0.2,30,30);
	glPopMatrix();
}
	
void left_arm(){
	glColor3f(0.0,1.0,0.0);
	glPushMatrix();
	glScalef(1.0,0.8,1.7);
	glTranslatef(0.0,-2.6,-1.7);
	glutSolidSphere(1.2,50,30);
	glPopMatrix();
}
	
void right_arm(){
	glColor3f(0.0,1.0,0.0);
	glPushMatrix();
	glScalef(1,0.8,1.7);
	glTranslatef(0,-2.6,1.7);
	glutSolidSphere(1.2,50,30);
	glPopMatrix();
}
	
void body(){
	glColor3f(0.0,1.0,0.0);
	glPushMatrix();
	glScalef(1.0,1.8,1.0);
	glTranslatef(0,-1.8,0.0);
	glutSolidSphere(1.2,50,30);
	glPopMatrix();
}

void left_foot(){
	glColor3f(0.0,1.0,0.0);
	glPushMatrix();
	glScalef(1.0,1.2,0.8);
	glTranslatef(0.0,-4.8,-1.2);
	glutSolidSphere(1.2,50,30);
	glPopMatrix();
}

	void right_foot(){
		glColor3f(0.0,1.0,0.0);
		glPushMatrix();
		glScalef(1.0,1.2,0.8);
		glTranslatef(0.0,-4.8,1.2);
		glutSolidSphere(1.2,50,30);
		glPopMatrix();
	}

void sun(){
	glColor3f(1.0,1.0,0.0);
	glPushMatrix();
	glRotated(30,1,0,0);
	glScalef(1.0,0.6,1.4);
	glTranslatef(0.0,5,-6);
	glutSolidSphere(1.0,50,30);
	glPopMatrix();
}
void character(){
	head();
	right_eye();
	left_eye();
	mouth();
	left_arm();	
	right_arm();
	body();
	left_foot();
	right_foot();
}
	

	
void draw(void){
	bool key=true;
	float increment=0.5;
	//glMatrixMode(GL_MODELVIEW);
	//glutInitDisplayMode(GL_DEPTH);
	for(int i=0;i<=10;i++){
		
		glClear(GL_COLOR_BUFFER_BIT);
		//glClear(GL_DEPTH_BUFFER_BIT);
		
		//glEnable(GL_DEPTH_TEST);
		
		if(i==0){
			glPushMatrix();
			glScalef(increment,increment,increment);
			character();
			glPopMatrix();
		}else{
			glPushMatrix();
			glScalef(increment,increment,increment);
			head();
			if(i%2==0){
				right_eye();
				left_eye();
				mouth();
				right_arm();
				left_arm();
			}else{
				right_eye_animated();
				left_eye_animated();
				mouth_animated();
				
				glPushMatrix();
				glRotatef(70,0,-1,0);
				right_arm();
				glPopMatrix();
				
				glPushMatrix();
				glRotatef(70,0,1,0);
				left_arm();
				glPopMatrix();
			}
			
			
			
			body();
			left_foot();
			right_foot();
			glPopMatrix();
		}
		sun();
		increment+=0.05;
		glFlush();
		//glDisable(GL_DEPTH_TEST);
		Sleep(500);
	}
	
	
}
	
void draw2(void){
	glMatrixMode(GL_MODELVIEW);
	glutInitDisplayMode(GL_DEPTH);
	
	
	for (int i=0;i<=360;i++){
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		axis();
		glPushMatrix();
		glRotated(i,0,1,0);
		character();
		glPopMatrix();
		
		glDisable(GL_DEPTH_TEST);
		glFlush();
		Sleep(50);
	}
}
	
void Trans2d(void){
	GLint k;
	glColor3f(0.0,0.0,0.0);
	for(k=0;k<4;k++){
		glRasterPos3f(x,y,z);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, label[k]);
		x+=0.1;
	}
}
	
void draw3(void){
	glColor3f(1.0,0.0,0.0);
	glutSolidCube(1.0);
}
	
void Todo(void){
	glMatrixMode(GL_MODELVIEW);
	for(int i=0;i<360;i++){
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		
		glRotatef(i,0,1,0);
		glTranslatef(-1,0,1);
		draw3();
		Trans2d();
		glPopMatrix();
		Sleep(50);
		glFlush();
	}
	
}

	
int main(int argc, char**argv){
	glutInit(&argc,argv);
	glutInitWindowSize(800,800);
	glutCreateWindow("3d");
	init();
	glutDisplayFunc(Todo);
	glutMainLoop();
	return 0;
}
