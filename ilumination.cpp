#include <GL/glut.h>

void init(void)
	
{ glClearColor(1,1,1,0.0);

glMatrixMode(GL_MODELVIEW);

gluLookAt(0, 0, 4 ,0 ,0 ,0 ,0,1,0);

glMatrixMode(GL_PROJECTION);

gluPerspective(35, 1, 1, 20);}

void material(void){
	GLfloat amb1[]={0.23125,0.23125,0.23125,1.0};
	GLfloat amb2[]={0.773911,0.773911,0.773911,1.0};
	GLfloat amb3[]={0.2775,0.2775,0.2775,1.0};
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,amb1);
	glMaterialfv(GL_FRONT,GL_SPECULAR,amb2);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,amb3);
	glMaterialf(GL_FRONT,GL_SHININESS,89.6);
	
	glEnable(GL_COLOR_MATERIAL);
	
}

void ilumina2(void){
	GLfloat Posicionytipo[]={6,6,6,2};
	GLfloat Colorambiente[]={230/255,230/255,230/255,0};
	GLfloat Colordifuso[]={0.0,0.9,0.0};
	GLfloat direccion[]={0,0,1};
	glLightfv(GL_LIGHT0, GL_POSITION, Posicionytipo);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Colorambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Colordifuso);
	
	//Atenuacion
	glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,0.9);
	glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,-0.2);
	glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,0);
	
	//Direcciones
	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION, direccion);
	glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,10);
	glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,20);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
	
}
	
	void desactiva_luz(void){
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_DEPTH_TEST);
	}


	


void esfera1(void)
	
{
	
	glColor3f(77.0/255.0,131.0/255.0,22.0/255.0);
	
	glPushMatrix();
	
	glScalef(0.8,1,1);
	
	glutSolidSphere(.2,40,30);
	
	glPopMatrix();
	
}

void esfera2(void)
	
{
	
	glColor3f(77.0/255.0,131.0/255.0,22.0/255.0);
	
	glPushMatrix();
	
	glScalef(0.9,1,1);
	
	glTranslatef(0,-0.5,0);
	
	glutSolidSphere(0.4,40,30);
	
	glPopMatrix();
	
}

void tallo(void)
	
{
	
	glColor3f(128.0/255.0,64.0/255.0,0.0);
	
	glPushMatrix();
	
	glScalef(0.2,1,1);
	
	glTranslatef(0,0.3,0);
	
	glutSolidSphere(0.1,40,30);
	
	glPopMatrix();}


void pera(void)
	
{
	
	
	
		glMatrixMode(GL_MODELVIEW);
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		glClear(GL_DEPTH_BUFFER_BIT);
		
		ilumina2();
		material();
		//glMaterialf(GL_FRONT,GL_SHININESS,1.0);
		//glColorMaterial(GL_FRONT,GL_SPECULAR);
		//glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
		//glEnable(GL_COLOR_MATERIAL);
		
		esfera1();
		
		esfera2();
		
		desactiva_luz();
		glDisable(GL_COLOR_MATERIAL);
		
		tallo();
		
		
		glFlush();
		Sleep(50);
	

}
	
	





int main(int argc, char **argv)
	
{
	
	glutInit(&argc, argv);
	
	glutInitWindowSize(600, 600);
	
	glutCreateWindow("Iluminación");
	
	init();
	
	glutDisplayFunc(pera);
	
	glutMainLoop();
	
	return 0;}
