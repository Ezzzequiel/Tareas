//Buffer de Profundidad
#include <GL/glut.h>

void init(void){
	glClearColor(0.5,0.5,0.5,0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0,4,4,0,0,0,0,1,0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(90,1,1,12);
}
	
	
void cubos(void){
	glMatrixMode(GL_MODELVIEW);
	//glutInitDisplayMode(GL_DEPTH);
	for(int i=0;i<=360;i++){
		glRotated(1,1,0,0);
		glClear(GL_DEPTH_BUFFER_BIT);
		//glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1,0.0,0.0);
		glutSolidSphere(1.0,20,20);
		glColor3f(0.8,0.8,0);
		glutWireSphere(1.0,20,20);
		glColor3f(0,0,1);
		glutSolidTorus(1,2,40,40);
		glFlush();
		//glDisable(GL_DEPTH_TEST);
		Sleep(20);
	}
}
	
int main(int argc, char**argv){
	glutInit(&argc,argv);
	glutInitWindowSize(600,600);
	glutCreateWindow("3d");
	init();
	glutDisplayFunc(cubos);
	glutMainLoop();
	return 0;
}
