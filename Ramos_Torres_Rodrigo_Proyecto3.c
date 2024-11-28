#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
	
float posY = 0.0f;
float delta = 0.1f;
float anguloAlas = 0.0f;
float velocidadAlas = 5.0f;
//Variables globales para el texto animado en los carteles
float textY1 = 50.0f;  // Posicion inical para el dato curioso de la mariposa
float textY2 = 70.0f;  // Posicion inicial para la primer regla de preservacion
float textY3 = 90.0f;  // Posicion inicial para la segunda regla de preservacion
float textY4 = 110.0f; // Posicion inicial para la tercer regla de preservacion
float textVelocity1 = 3.0f; //Velocidad de cada texto
float textVelocity2 = 3.0f;
float textVelocity3 = 3.0f;
float textVelocity4 = 3.0f;
float dampening = 0.0f; // Controlara la intensidad del rebote del texto
const float TARGET_Y1 = 3.0f; //Constantes para que el texto vuelva siempre a su posicion original
const float TARGET_Y2 = 0.0f;
const float TARGET_Y3 = -2.5f;
const float TARGET_Y4 = -5.0f;
//Animacion nubes y sol
float cloudOffset1 = 0.0f;
float cloudOffset2 = 0.0f;
float sunRotation = 0.0f;
//Animacion de cartel de no pesticidas
float signScale = 1.0f;


void inicializa(void) {
	glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	// Increase ambient light to make colors more visible
	GLfloat lightPos[] = {100.0f, 100.0f, 100.0f, 1.0f};
	GLfloat lightAmb[] = {0.4f, 0.4f, 0.4f, 1.0f};
	GLfloat lightDiff[] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat lightSpec[] = {1.0f, 1.0f, 1.0f, 1.0f};
	
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 1.0f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 50, 200, 0, 0, 0, 0, 1, 0);
}

void setMaterial(GLfloat amb[], GLfloat diff[], GLfloat spec[], GLfloat shine) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}

void dibujarBase() {
	GLfloat bronzeAmb[] = {0.2125f, 0.1275f, 0.054f};
	GLfloat bronzeDiff[] = {0.714f, 0.4284f, 0.18144f};
	GLfloat bronzeSpec[] = {0.393548f, 0.271906f, 0.166721f};
	
	setMaterial(bronzeAmb, bronzeDiff, bronzeSpec, 25.6f);
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-200.0f, -50.0f, -100.0f);
	glVertex3f(200.0f, -50.0f, -100.0f);
	glVertex3f(200.0f, -50.0f, 100.0f);
	glVertex3f(-200.0f, -50.0f, 100.0f);
	glEnd();
}


void arbol(float x, float z) {
	// Material bronce para el tronco
	GLfloat bronzeAmb[] = {0.2125f, 0.1275f, 0.054f};
	GLfloat bronzeDiff[] = {0.714f, 0.4284f, 0.18144f};
	GLfloat bronzeSpec[] = {0.393548f, 0.271906f, 0.166721f};
	
	setMaterial(bronzeAmb, bronzeDiff, bronzeSpec, 25.6f);
	glPushMatrix();
	glTranslatef(x, 0.0f, z);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glutSolidCone(3.0, 30.0, 20, 20);
	glPopMatrix();
	
	// Material naranja otoñal para las hojas
	GLfloat autumnAmb[] = {0.4f, 0.2f, 0.0f};
	GLfloat autumnDiff[] = {0.8f, 0.3f, 0.0f};
	GLfloat autumnSpec[] = {0.6f, 0.4f, 0.2f};
	
	setMaterial(autumnAmb, autumnDiff, autumnSpec, 32.0f);
	glPushMatrix();
	glTranslatef(x, 30.0f, z);
	glutSolidSphere(15.0, 20, 20);
	glTranslatef(-5.0f, 5.0f, 0.0f);
	glutSolidSphere(10.0, 20, 20);
	glTranslatef(10.0f, -2.0f, 0.0f);
	glutSolidSphere(12.0, 20, 20);
	glPopMatrix();
}

void pasto() {
	GLfloat autumnAmb[] = {0.4f, 0.2f, 0.0f};
	GLfloat autumnDiff[] = {0.8f, 0.3f, 0.0f};
	GLfloat autumnSpec[] = {0.6f, 0.4f, 0.2f};
	
	setMaterial(autumnAmb, autumnDiff, autumnSpec, 32.0f);
	
	for(int i = -100; i < 100; i += 5) {
		for(int j = -100; j < 100; j += 5) {
			glBegin(GL_TRIANGLES);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(i + 0.0f, 0.0f, j + 0.0f);
			glVertex3f(i + 2.0f, 5.0f, j + 0.0f);
			glVertex3f(i + 4.0f, 0.0f, j + 0.0f);
			glEnd();
		}
	}
}

void abdomenmariposa() {
	GLfloat blackAmb[] = {0.0f, 0.0f, 0.0f};
	GLfloat blackDiff[] = {0.01f, 0.01f, 0.01f};
	GLfloat blackSpec[] = {0.5f, 0.5f, 0.5f};
	
	setMaterial(blackAmb, blackDiff, blackSpec, 32.0f);
	
	// Cabeza
	glPushMatrix();
	glTranslatef(0.0f, 15.0f, 0.0f);
	glutSolidSphere(1.8, 20, 20);
	glPopMatrix();
	
	// Torax
	glPushMatrix();
	glTranslatef(0.0f, 12.0f, 0.0f);
	glScalef(1.0f, 1.5f, 1.0f);
	glutSolidSphere(2.0, 20, 20);
	glPopMatrix();
	
	// Abdomen segmentado y conectado
	for(int i = 0; i < 5; i++) {
		glPushMatrix();
		glTranslatef(0.0f, 10.0f - i*2.0f, 0.0f);
		glScalef(1.0f, 1.2f, 1.0f);
		glutSolidSphere(1.5 - i*0.15, 20, 20);
		glPopMatrix();
		
		// Conectores entre segmentos
		if(i < 4) {
			glPushMatrix();
			glTranslatef(0.0f, 9.0f - i*2.0f, 0.0f);
			glScalef(0.8f, 0.3f, 0.8f);
			glutSolidSphere(1.5 - i*0.15, 20, 20);
			glPopMatrix();
		}
	}
}


void antenasmariposa() {
	GLfloat blackAmb[] = {0.0f, 0.0f, 0.0f};
	GLfloat blackDiff[] = {0.01f, 0.01f, 0.01f};
	GLfloat blackSpec[] = {0.5f, 0.5f, 0.5f};
	
	setMaterial(blackAmb, blackDiff, blackSpec, 32.0f);
	
	glBegin(GL_LINES);
	glVertex3f(-1.0f, 15.0f, 0.0f);
	glVertex3f(-3.0f, 20.0f, 2.0f);
	glVertex3f(1.0f, 15.0f, 0.0f);
	glVertex3f(3.0f, 20.0f, 2.0f);
	glEnd();
}

void alasmariposa1() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	glRotatef(30.0f * sin(anguloAlas), 0.0f, 0.0f, 1.0f);
	glRotatef(15, 0.0f, 1.0f, 0.0f);
	
	float scaleX = 0.35f;   
	float scaleY = 0.35f;    
	float offsetX = -280.0f;  // Ajusta distancia
	float offsetY = -265.0f;  
	
	
	// Contorno negro
	GLfloat blackAmb[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat blackDiff[] = {0.01f, 0.01f, 0.01f, 1.0f};
	GLfloat blackSpec[] = {0.1f, 0.1f, 0.1f, 1.0f};
	setMaterial(blackAmb, blackDiff, blackSpec, 32.0f);
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	
	glVertex3f((301+offsetX)*scaleX, (298+offsetY)*scaleY, 4.0f);
	glVertex3f((310+offsetX)*scaleX, (303+offsetY)*scaleY, 4.2f);
	glVertex3f((317+offsetX)*scaleX, (306+offsetY)*scaleY, 4.3f);
	glVertex3f((326+offsetX)*scaleX, (309+offsetY)*scaleY, 4.4f);
	glVertex3f((334+offsetX)*scaleX, (312+offsetY)*scaleY, 4.5f);
	glVertex3f((342+offsetX)*scaleX, (314+offsetY)*scaleY, 4.6f);
	glVertex3f((351+offsetX)*scaleX, (316+offsetY)*scaleY, 4.7f);
	glVertex3f((360+offsetX)*scaleX, (316+offsetY)*scaleY, 4.8f);
	glVertex3f((367+offsetX)*scaleX, (316+offsetY)*scaleY, 4.8f);
	glVertex3f((371+offsetX)*scaleX, (316+offsetY)*scaleY, 4.8f);
	glVertex3f((375+offsetX)*scaleX, (314+offsetY)*scaleY, 4.7f);
	glVertex3f((379+offsetX)*scaleX, (311+offsetY)*scaleY, 4.6f);
	glVertex3f((381+offsetX)*scaleX, (309+offsetY)*scaleY, 4.5f);
	glVertex3f((380+offsetX)*scaleX, (305+offsetY)*scaleY, 4.4f);
	glVertex3f((379+offsetX)*scaleX, (302+offsetY)*scaleY, 4.3f);
	glVertex3f((377+offsetX)*scaleX, (299+offsetY)*scaleY, 4.2f);
	glVertex3f((374+offsetX)*scaleX, (296+offsetY)*scaleY, 4.1f);
	glVertex3f((371+offsetX)*scaleX, (295+offsetY)*scaleY, 4.0f);
	glVertex3f((367+offsetX)*scaleX, (293+offsetY)*scaleY, 3.9f);
	glVertex3f((363+offsetX)*scaleX, (291+offsetY)*scaleY, 3.8f);
	glVertex3f((360+offsetX)*scaleX, (288+offsetY)*scaleY, 3.7f);
	glVertex3f((357+offsetX)*scaleX, (285+offsetY)*scaleY, 3.6f);
	glVertex3f((355+offsetX)*scaleX, (282+offsetY)*scaleY, 3.5f);
	glVertex3f((352+offsetX)*scaleX, (278+offsetY)*scaleY, 3.4f);
	glVertex3f((350+offsetX)*scaleX, (275+offsetY)*scaleY, 3.3f);
	glVertex3f((346+offsetX)*scaleX, (272+offsetY)*scaleY, 3.2f);
	glVertex3f((341+offsetX)*scaleX, (270+offsetY)*scaleY, 3.1f);
	glVertex3f((336+offsetX)*scaleX, (272+offsetY)*scaleY, 3.0f);
	glVertex3f((329+offsetX)*scaleX, (276+offsetY)*scaleY, 2.9f);
	glVertex3f((324+offsetX)*scaleX, (278+offsetY)*scaleY, 2.8f);
	glVertex3f((318+offsetX)*scaleX, (281+offsetY)*scaleY, 2.7f);
	glVertex3f((314+offsetX)*scaleX, (284+offsetY)*scaleY, 2.6f);
	glVertex3f((310+offsetX)*scaleX, (286+offsetY)*scaleY, 2.5f);
	glVertex3f((306+offsetX)*scaleX, (289+offsetY)*scaleY, 2.4f);
	glVertex3f((303+offsetX)*scaleX, (292+offsetY)*scaleY, 2.3f);
	glVertex3f((302+offsetX)*scaleX, (294+offsetY)*scaleY, 2.2f);
	glVertex3f((301+offsetX)*scaleX, (298+offsetY)*scaleY, 2.1f);
	glEnd();
	
	// Seccion naranja de las alas
	GLfloat orangeAmb[] = {0.96f, 0.60f, 0.11f};
	GLfloat orangeDiff[] = {0.96f, 0.60f, 0.11f};
	GLfloat orangeSpec[] = {0.5f, 0.5f, 0.5f};
	setMaterial(orangeAmb, orangeDiff, orangeSpec, 32.0f);
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((302+offsetX)*scaleX, (296+offsetY)*scaleY, 4.1f);
	glVertex3f((323+offsetX)*scaleX, (296+offsetY)*scaleY, 4.2f);
	glVertex3f((334+offsetX)*scaleX, (299+offsetY)*scaleY, 4.3f);
	glVertex3f((339+offsetX)*scaleX, (302+offsetY)*scaleY, 4.4f);
	glVertex3f((341+offsetX)*scaleX, (304+offsetY)*scaleY, 4.5f);
	glVertex3f((339+offsetX)*scaleX, (307+offsetY)*scaleY, 4.4f);
	glVertex3f((335+offsetX)*scaleX, (308+offsetY)*scaleY, 4.3f);
	glVertex3f((333+offsetX)*scaleX, (309+offsetY)*scaleY, 4.2f);
	glVertex3f((323+offsetX)*scaleX, (307+offsetY)*scaleY, 4.1f);
	glVertex3f((314+offsetX)*scaleX, (303+offsetY)*scaleY, 4.0f);
	glVertex3f((303+offsetX)*scaleX, (299+offsetY)*scaleY, 3.9f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((340+offsetX)*scaleX, (301+offsetY)*scaleY, 4.3f);
	glVertex3f((344+offsetX)*scaleX, (302+offsetY)*scaleY, 4.4f);
	glVertex3f((350+offsetX)*scaleX, (301+offsetY)*scaleY, 4.4f);
	glVertex3f((355+offsetX)*scaleX, (300+offsetY)*scaleY, 4.3f);
	glVertex3f((353+offsetX)*scaleX, (295+offsetY)*scaleY, 4.2f);
	glVertex3f((351+offsetX)*scaleX, (293+offsetY)*scaleY, 4.1f);
	glVertex3f((347+offsetX)*scaleX, (294+offsetY)*scaleY, 4.0f);
	glVertex3f((342+offsetX)*scaleX, (295+offsetY)*scaleY, 4.0f);
	glVertex3f((338+offsetX)*scaleX, (297+offsetY)*scaleY, 4.1f);
	glVertex3f((336+offsetX)*scaleX, (299+offsetY)*scaleY, 4.2f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((326+offsetX)*scaleX, (296+offsetY)*scaleY, 4.1f);
	glVertex3f((329+offsetX)*scaleX, (297+offsetY)*scaleY, 4.2f);
	glVertex3f((332+offsetX)*scaleX, (298+offsetY)*scaleY, 4.3f);
	glVertex3f((335+offsetX)*scaleX, (297+offsetY)*scaleY, 4.3f);
	glVertex3f((339+offsetX)*scaleX, (295+offsetY)*scaleY, 4.2f);
	glVertex3f((342+offsetX)*scaleX, (293+offsetY)*scaleY, 4.1f);
	glVertex3f((346+offsetX)*scaleX, (292+offsetY)*scaleY, 4.0f);
	glVertex3f((350+offsetX)*scaleX, (290+offsetY)*scaleY, 3.9f);
	glVertex3f((350+offsetX)*scaleX, (288+offsetY)*scaleY, 3.8f);
	glVertex3f((349+offsetX)*scaleX, (285+offsetY)*scaleY, 3.7f);
	glVertex3f((346+offsetX)*scaleX, (284+offsetY)*scaleY, 3.6f);
	glVertex3f((343+offsetX)*scaleX, (284+offsetY)*scaleY, 3.6f);
	glVertex3f((339+offsetX)*scaleX, (286+offsetY)*scaleY, 3.7f);
	glVertex3f((336+offsetX)*scaleX, (288+offsetY)*scaleY, 3.8f);
	glVertex3f((333+offsetX)*scaleX, (289+offsetY)*scaleY, 3.9f);
	glVertex3f((330+offsetX)*scaleX, (291+offsetY)*scaleY, 4.0f);
	glVertex3f((327+offsetX)*scaleX, (294+offsetY)*scaleY, 4.1f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((308+offsetX)*scaleX, (295+offsetY)*scaleY, 4.0f);
	glVertex3f((314+offsetX)*scaleX, (295+offsetY)*scaleY, 4.1f);
	glVertex3f((323+offsetX)*scaleX, (294+offsetY)*scaleY, 4.2f);
	glVertex3f((327+offsetX)*scaleX, (292+offsetY)*scaleY, 4.1f);
	glVertex3f((331+offsetX)*scaleX, (289+offsetY)*scaleY, 4.0f);
	glVertex3f((335+offsetX)*scaleX, (287+offsetY)*scaleY, 3.9f);
	glVertex3f((340+offsetX)*scaleX, (285+offsetY)*scaleY, 3.8f);
	glVertex3f((343+offsetX)*scaleX, (282+offsetY)*scaleY, 3.7f);
	glVertex3f((345+offsetX)*scaleX, (280+offsetY)*scaleY, 3.6f);
	glVertex3f((343+offsetX)*scaleX, (278+offsetY)*scaleY, 3.5f);
	glVertex3f((342+offsetX)*scaleX, (277+offsetY)*scaleY, 3.4f);
	glVertex3f((340+offsetX)*scaleX, (276+offsetY)*scaleY, 3.3f);
	glVertex3f((335+offsetX)*scaleX, (276+offsetY)*scaleY, 3.3f);
	glVertex3f((331+offsetX)*scaleX, (278+offsetY)*scaleY, 3.4f);
	glVertex3f((327+offsetX)*scaleX, (281+offsetY)*scaleY, 3.5f);
	glVertex3f((323+offsetX)*scaleX, (282+offsetY)*scaleY, 3.6f);
	glVertex3f((318+offsetX)*scaleX, (284+offsetY)*scaleY, 3.7f);
	glVertex3f((315+offsetX)*scaleX, (287+offsetY)*scaleY, 3.8f);
	glVertex3f((311+offsetX)*scaleX, (289+offsetY)*scaleY, 3.9f);
	glVertex3f((309+offsetX)*scaleX, (291+offsetY)*scaleY, 4.0f);
	glVertex3f((306+offsetX)*scaleX, (293+offsetY)*scaleY, 4.1f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((341+offsetX)*scaleX, (309+offsetY)*scaleY, 4.4f);
	glVertex3f((343+offsetX)*scaleX, (307+offsetY)*scaleY, 4.3f);
	glVertex3f((345+offsetX)*scaleX, (307+offsetY)*scaleY, 4.3f);
	glVertex3f((347+offsetX)*scaleX, (308+offsetY)*scaleY, 4.4f);
	glVertex3f((347+offsetX)*scaleX, (310+offsetY)*scaleY, 4.5f);
	glVertex3f((344+offsetX)*scaleX, (310+offsetY)*scaleY, 4.4f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((360+offsetX)*scaleX, (308+offsetY)*scaleY, 4.4f);
	glVertex3f((365+offsetX)*scaleX, (308+offsetY)*scaleY, 4.4f);
	glVertex3f((369+offsetX)*scaleX, (305+offsetY)*scaleY, 4.3f);
	glVertex3f((366+offsetX)*scaleX, (303+offsetY)*scaleY, 4.2f);
	glVertex3f((359+offsetX)*scaleX, (306+offsetY)*scaleY, 4.3f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((360+offsetX)*scaleX, (311+offsetY)*scaleY, 4.5f);
	glVertex3f((363+offsetX)*scaleX, (312+offsetY)*scaleY, 4.6f);
	glVertex3f((368+offsetX)*scaleX, (312+offsetY)*scaleY, 4.6f);
	glVertex3f((371+offsetX)*scaleX, (311+offsetY)*scaleY, 4.5f);
	glVertex3f((372+offsetX)*scaleX, (308+offsetY)*scaleY, 4.4f);
	glVertex3f((366+offsetX)*scaleX, (309+offsetY)*scaleY, 4.4f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((355+offsetX)*scaleX, (315+offsetY)*scaleY, 4.6f);
	glVertex3f((358+offsetX)*scaleX, (314+offsetY)*scaleY, 4.5f);
	glVertex3f((357+offsetX)*scaleX, (312+offsetY)*scaleY, 4.4f);
	glVertex3f((356+offsetX)*scaleX, (308+offsetY)*scaleY, 4.3f);
	glVertex3f((353+offsetX)*scaleX, (309+offsetY)*scaleY, 4.4f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((348+offsetX)*scaleX, (314+offsetY)*scaleY, 4.5f);
	glVertex3f((349+offsetX)*scaleX, (315+offsetY)*scaleY, 4.6f);
	glVertex3f((353+offsetX)*scaleX, (315+offsetY)*scaleY, 4.6f);
	glVertex3f((352+offsetX)*scaleX, (314+offsetY)*scaleY, 4.5f);
	glEnd();
	glPopMatrix();
}



void alasmariposa2() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	float scaleX = 0.35f;   
	float scaleY = 0.35f;    
	float offsetX = -295.0f;  // Ajusta distancia
	float offsetY = -255.0f;  
	
	GLfloat blackAmb[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat blackDiff[] = {0.01f, 0.01f, 0.01f, 1.0f};
	GLfloat blackSpec[] = {0.1f, 0.1f, 0.1f, 1.0f};
	setMaterial(blackAmb, blackDiff, blackSpec, 32.0f);
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((304+offsetX)*scaleX, (288+offsetY)*scaleY, 4.0f);
	glVertex3f((318+offsetX)*scaleX, (279+offsetY)*scaleY, 4.1f);
	glVertex3f((340+offsetX)*scaleX, (270+offsetY)*scaleY, 4.2f);
	glVertex3f((342+offsetX)*scaleX, (264+offsetY)*scaleY, 4.3f);
	glVertex3f((343+offsetX)*scaleX, (259+offsetY)*scaleY, 4.4f);
	glVertex3f((341+offsetX)*scaleX, (258+offsetY)*scaleY, 4.4f);
	glVertex3f((340+offsetX)*scaleX, (270+offsetY)*scaleY, 4.3f);
	glVertex3f((342+offsetX)*scaleX, (264+offsetY)*scaleY, 4.2f);
	glVertex3f((343+offsetX)*scaleX, (259+offsetY)*scaleY, 4.1f);
	glVertex3f((343+offsetX)*scaleX, (257+offsetY)*scaleY, 4.0f);
	glVertex3f((343+offsetX)*scaleX, (256+offsetY)*scaleY, 3.9f);
	glVertex3f((342+offsetX)*scaleX, (253+offsetY)*scaleY, 3.8f);
	glVertex3f((340+offsetX)*scaleX, (250+offsetY)*scaleY, 3.7f);
	glVertex3f((338+offsetX)*scaleX, (248+offsetY)*scaleY, 3.6f);
	glVertex3f((335+offsetX)*scaleX, (244+offsetY)*scaleY, 3.5f);
	glVertex3f((329+offsetX)*scaleX, (241+offsetY)*scaleY, 3.4f);
	glVertex3f((325+offsetX)*scaleX, (240+offsetY)*scaleY, 3.3f);
	glVertex3f((320+offsetX)*scaleX, (238+offsetY)*scaleY, 3.2f);
	glVertex3f((313+offsetX)*scaleX, (238+offsetY)*scaleY, 3.1f);
	glVertex3f((306+offsetX)*scaleX, (239+offsetY)*scaleY, 3.0f);
	glVertex3f((302+offsetX)*scaleX, (242+offsetY)*scaleY, 2.9f);
	glVertex3f((301+offsetX)*scaleX, (251+offsetY)*scaleY, 2.8f);
	glVertex3f((301+offsetX)*scaleX, (263+offsetY)*scaleY, 2.7f);
	glVertex3f((301+offsetX)*scaleX, (275+offsetY)*scaleY, 2.6f);
	glVertex3f((301+offsetX)*scaleX, (283+offsetY)*scaleY, 2.5f);
	glEnd();
	
	GLfloat orangeAmb[] = {0.96f, 0.60f, 0.11f};
	GLfloat orangeDiff[] = {0.96f, 0.60f, 0.11f};
	GLfloat orangeSpec[] = {0.5f, 0.5f, 0.5f};
	setMaterial(orangeAmb, orangeDiff, orangeSpec, 32.0f);
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((304+offsetX)*scaleX, (286+offsetY)*scaleY, 4.1f);
	glVertex3f((309+offsetX)*scaleX, (283+offsetY)*scaleY, 4.2f);
	glVertex3f((316+offsetX)*scaleX, (279+offsetY)*scaleY, 4.3f);
	glVertex3f((319+offsetX)*scaleX, (273+offsetY)*scaleY, 4.3f);
	glVertex3f((321+offsetX)*scaleX, (270+offsetY)*scaleY, 4.2f);
	glVertex3f((323+offsetX)*scaleX, (266+offsetY)*scaleY, 4.1f);
	glVertex3f((323+offsetX)*scaleX, (261+offsetY)*scaleY, 4.0f);
	glVertex3f((317+offsetX)*scaleX, (264+offsetY)*scaleY, 3.9f);
	glVertex3f((313+offsetX)*scaleX, (267+offsetY)*scaleY, 3.8f);
	glVertex3f((310+offsetX)*scaleX, (271+offsetY)*scaleY, 3.9f);
	glVertex3f((308+offsetX)*scaleX, (275+offsetY)*scaleY, 4.0f);
	glVertex3f((305+offsetX)*scaleX, (280+offsetY)*scaleY, 4.1f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((320+offsetX)*scaleX, (277+offsetY)*scaleY, 4.2f);
	glVertex3f((321+offsetX)*scaleX, (274+offsetY)*scaleY, 4.3f);
	glVertex3f((325+offsetX)*scaleX, (270+offsetY)*scaleY, 4.3f);
	glVertex3f((330+offsetX)*scaleX, (267+offsetY)*scaleY, 4.2f);
	glVertex3f((335+offsetX)*scaleX, (264+offsetY)*scaleY, 4.1f);
	glVertex3f((337+offsetX)*scaleX, (267+offsetY)*scaleY, 4.0f);
	glVertex3f((335+offsetX)*scaleX, (270+offsetY)*scaleY, 4.1f);
	glVertex3f((330+offsetX)*scaleX, (272+offsetY)*scaleY, 4.2f);
	glVertex3f((325+offsetX)*scaleX, (275+offsetY)*scaleY, 4.2f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((312+offsetX)*scaleX, (265+offsetY)*scaleY, 4.1f);
	glVertex3f((318+offsetX)*scaleX, (260+offsetY)*scaleY, 4.2f);
	glVertex3f((320+offsetX)*scaleX, (245+offsetY)*scaleY, 4.1f);
	glVertex3f((317+offsetX)*scaleX, (245+offsetY)*scaleY, 4.0f);
	glVertex3f((314+offsetX)*scaleX, (247+offsetY)*scaleY, 3.9f);
	glVertex3f((314+offsetX)*scaleX, (251+offsetY)*scaleY, 4.0f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((320+offsetX)*scaleX, (259+offsetY)*scaleY, 4.1f);
	glVertex3f((324+offsetX)*scaleX, (258+offsetY)*scaleY, 4.2f);
	glVertex3f((326+offsetX)*scaleX, (253+offsetY)*scaleY, 4.1f);
	glVertex3f((328+offsetX)*scaleX, (248+offsetY)*scaleY, 4.0f);
	glVertex3f((323+offsetX)*scaleX, (246+offsetY)*scaleY, 3.9f);
	glVertex3f((321+offsetX)*scaleX, (253+offsetY)*scaleY, 4.0f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((302+offsetX)*scaleX, (281+offsetY)*scaleY, 4.1f);
	glVertex3f((306+offsetX)*scaleX, (276+offsetY)*scaleY, 4.2f);
	glVertex3f((309+offsetX)*scaleX, (270+offsetY)*scaleY, 4.1f);
	glVertex3f((310+offsetX)*scaleX, (262+offsetY)*scaleY, 4.0f);
	glVertex3f((312+offsetX)*scaleX, (246+offsetY)*scaleY, 3.9f);
	glVertex3f((306+offsetX)*scaleX, (246+offsetY)*scaleY, 3.8f);
	glVertex3f((303+offsetX)*scaleX, (248+offsetY)*scaleY, 3.9f);
	glVertex3f((303+offsetX)*scaleX, (257+offsetY)*scaleY, 4.0f);
	glVertex3f((303+offsetX)*scaleX, (267+offsetY)*scaleY, 4.1f);
	glVertex3f((302+offsetX)*scaleX, (273+offsetY)*scaleY, 4.2f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((324+offsetX)*scaleX, (269+offsetY)*scaleY, 4.2f);
	glVertex3f((329+offsetX)*scaleX, (266+offsetY)*scaleY, 4.3f);
	glVertex3f((335+offsetX)*scaleX, (262+offsetY)*scaleY, 4.2f);
	glVertex3f((338+offsetX)*scaleX, (259+offsetY)*scaleY, 4.1f);
	glVertex3f((336+offsetX)*scaleX, (256+offsetY)*scaleY, 4.0f);
	glVertex3f((333+offsetX)*scaleX, (253+offsetY)*scaleY, 3.9f);
	glVertex3f((330+offsetX)*scaleX, (256+offsetY)*scaleY, 4.0f);
	glVertex3f((327+offsetX)*scaleX, (259+offsetY)*scaleY, 4.1f);
	glVertex3f((325+offsetX)*scaleX, (264+offsetY)*scaleY, 4.2f);
	glEnd();
	
	glPopMatrix();
}

//Esta ala no se mueve
void alasmariposa1simetrica() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	glScalef(-1.0f, 1.0f, 1.0f);
	
	float scaleX = 0.35f;   
	float scaleY = 0.35f;    
	float offsetX = -280.0f;  // Ajusta distancia
	float offsetY = -275.0f;  
	
	// Main black outline
	GLfloat blackAmb[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat blackDiff[] = {0.01f, 0.01f, 0.01f, 1.0f};
	GLfloat blackSpec[] = {0.1f, 0.1f, 0.1f, 1.0f};
	setMaterial(blackAmb, blackDiff, blackSpec, 32.0f);
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((301+offsetX)*scaleX, (298+offsetY)*scaleY, 4.0f);
	glVertex3f((310+offsetX)*scaleX, (303+offsetY)*scaleY, 4.1f);
	glVertex3f((317+offsetX)*scaleX, (306+offsetY)*scaleY, 4.2f);
	glVertex3f((326+offsetX)*scaleX, (309+offsetY)*scaleY, 4.3f);
	glVertex3f((334+offsetX)*scaleX, (312+offsetY)*scaleY, 4.4f);
	glVertex3f((342+offsetX)*scaleX, (314+offsetY)*scaleY, 4.5f);
	glVertex3f((351+offsetX)*scaleX, (316+offsetY)*scaleY, 4.6f);
	glVertex3f((360+offsetX)*scaleX, (316+offsetY)*scaleY, 4.7f);
	glVertex3f((367+offsetX)*scaleX, (316+offsetY)*scaleY, 4.7f);
	glVertex3f((371+offsetX)*scaleX, (316+offsetY)*scaleY, 4.6f);
	glVertex3f((375+offsetX)*scaleX, (314+offsetY)*scaleY, 4.5f);
	glVertex3f((379+offsetX)*scaleX, (311+offsetY)*scaleY, 4.4f);
	glVertex3f((381+offsetX)*scaleX, (309+offsetY)*scaleY, 4.3f);
	glVertex3f((380+offsetX)*scaleX, (305+offsetY)*scaleY, 4.2f);
	glVertex3f((379+offsetX)*scaleX, (302+offsetY)*scaleY, 4.1f);
	glVertex3f((377+offsetX)*scaleX, (299+offsetY)*scaleY, 4.0f);
	glVertex3f((374+offsetX)*scaleX, (296+offsetY)*scaleY, 3.9f);
	glVertex3f((371+offsetX)*scaleX, (295+offsetY)*scaleY, 3.8f);
	glVertex3f((367+offsetX)*scaleX, (293+offsetY)*scaleY, 3.7f);
	glVertex3f((363+offsetX)*scaleX, (291+offsetY)*scaleY, 3.6f);
	glVertex3f((360+offsetX)*scaleX, (288+offsetY)*scaleY, 3.5f);
	glVertex3f((357+offsetX)*scaleX, (285+offsetY)*scaleY, 3.4f);
	glVertex3f((355+offsetX)*scaleX, (282+offsetY)*scaleY, 3.3f);
	glVertex3f((352+offsetX)*scaleX, (278+offsetY)*scaleY, 3.2f);
	glVertex3f((350+offsetX)*scaleX, (275+offsetY)*scaleY, 3.1f);
	glVertex3f((346+offsetX)*scaleX, (272+offsetY)*scaleY, 3.0f);
	glVertex3f((341+offsetX)*scaleX, (270+offsetY)*scaleY, 2.9f);
	glVertex3f((336+offsetX)*scaleX, (272+offsetY)*scaleY, 2.8f);
	glVertex3f((329+offsetX)*scaleX, (276+offsetY)*scaleY, 2.7f);
	glVertex3f((324+offsetX)*scaleX, (278+offsetY)*scaleY, 2.6f);
	glVertex3f((318+offsetX)*scaleX, (281+offsetY)*scaleY, 2.5f);
	glVertex3f((314+offsetX)*scaleX, (284+offsetY)*scaleY, 2.4f);
	glVertex3f((310+offsetX)*scaleX, (286+offsetY)*scaleY, 2.3f);
	glVertex3f((306+offsetX)*scaleX, (289+offsetY)*scaleY, 2.2f);
	glVertex3f((303+offsetX)*scaleX, (292+offsetY)*scaleY, 2.1f);
	glVertex3f((302+offsetX)*scaleX, (294+offsetY)*scaleY, 2.0f);
	glVertex3f((301+offsetX)*scaleX, (298+offsetY)*scaleY, 2.0f);
	glEnd();
	
	GLfloat orangeAmb[] = {0.96f, 0.60f, 0.11f};
	GLfloat orangeDiff[] = {0.96f, 0.60f, 0.11f};
	GLfloat orangeSpec[] = {0.5f, 0.5f, 0.5f};
	setMaterial(orangeAmb, orangeDiff, orangeSpec, 32.0f);
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((302+offsetX)*scaleX, (296+offsetY)*scaleY, 4.1f);
	glVertex3f((323+offsetX)*scaleX, (296+offsetY)*scaleY, 4.2f);
	glVertex3f((334+offsetX)*scaleX, (299+offsetY)*scaleY, 4.3f);
	glVertex3f((339+offsetX)*scaleX, (302+offsetY)*scaleY, 4.3f);
	glVertex3f((341+offsetX)*scaleX, (304+offsetY)*scaleY, 4.2f);
	glVertex3f((339+offsetX)*scaleX, (307+offsetY)*scaleY, 4.1f);
	glVertex3f((335+offsetX)*scaleX, (308+offsetY)*scaleY, 4.0f);
	glVertex3f((333+offsetX)*scaleX, (309+offsetY)*scaleY, 3.9f);
	glVertex3f((323+offsetX)*scaleX, (307+offsetY)*scaleY, 3.8f);
	glVertex3f((314+offsetX)*scaleX, (303+offsetY)*scaleY, 3.9f);
	glVertex3f((303+offsetX)*scaleX, (299+offsetY)*scaleY, 4.0f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((340+offsetX)*scaleX, (301+offsetY)*scaleY, 4.2f);
	glVertex3f((344+offsetX)*scaleX, (302+offsetY)*scaleY, 4.3f);
	glVertex3f((350+offsetX)*scaleX, (301+offsetY)*scaleY, 4.3f);
	glVertex3f((355+offsetX)*scaleX, (300+offsetY)*scaleY, 4.2f);
	glVertex3f((353+offsetX)*scaleX, (295+offsetY)*scaleY, 4.1f);
	glVertex3f((351+offsetX)*scaleX, (293+offsetY)*scaleY, 4.0f);
	glVertex3f((347+offsetX)*scaleX, (294+offsetY)*scaleY, 3.9f);
	glVertex3f((342+offsetX)*scaleX, (295+offsetY)*scaleY, 3.9f);
	glVertex3f((338+offsetX)*scaleX, (297+offsetY)*scaleY, 4.0f);
	glVertex3f((336+offsetX)*scaleX, (299+offsetY)*scaleY, 4.1f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((326+offsetX)*scaleX, (296+offsetY)*scaleY, 4.1f);
	glVertex3f((329+offsetX)*scaleX, (297+offsetY)*scaleY, 4.2f);
	glVertex3f((332+offsetX)*scaleX, (298+offsetY)*scaleY, 4.2f);
	glVertex3f((335+offsetX)*scaleX, (297+offsetY)*scaleY, 4.1f);
	glVertex3f((339+offsetX)*scaleX, (295+offsetY)*scaleY, 4.0f);
	glVertex3f((342+offsetX)*scaleX, (293+offsetY)*scaleY, 3.9f);
	glVertex3f((346+offsetX)*scaleX, (292+offsetY)*scaleY, 3.8f);
	glVertex3f((350+offsetX)*scaleX, (290+offsetY)*scaleY, 3.7f);
	glVertex3f((350+offsetX)*scaleX, (288+offsetY)*scaleY, 3.6f);
	glVertex3f((349+offsetX)*scaleX, (285+offsetY)*scaleY, 3.7f);
	glVertex3f((346+offsetX)*scaleX, (284+offsetY)*scaleY, 3.8f);
	glVertex3f((343+offsetX)*scaleX, (284+offsetY)*scaleY, 3.9f);
	glVertex3f((339+offsetX)*scaleX, (286+offsetY)*scaleY, 4.0f);
	glVertex3f((336+offsetX)*scaleX, (288+offsetY)*scaleY, 4.1f);
	glVertex3f((333+offsetX)*scaleX, (289+offsetY)*scaleY, 4.1f);
	glVertex3f((330+offsetX)*scaleX, (291+offsetY)*scaleY, 4.0f);
	glVertex3f((327+offsetX)*scaleX, (294+offsetY)*scaleY, 3.9f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((341+offsetX)*scaleX, (309+offsetY)*scaleY, 4.2f);
	glVertex3f((343+offsetX)*scaleX, (307+offsetY)*scaleY, 4.3f);
	glVertex3f((345+offsetX)*scaleX, (307+offsetY)*scaleY, 4.3f);
	glVertex3f((347+offsetX)*scaleX, (308+offsetY)*scaleY, 4.2f);
	glVertex3f((347+offsetX)*scaleX, (310+offsetY)*scaleY, 4.1f);
	glVertex3f((344+offsetX)*scaleX, (310+offsetY)*scaleY, 4.0f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((360+offsetX)*scaleX, (308+offsetY)*scaleY, 4.2f);
	glVertex3f((365+offsetX)*scaleX, (308+offsetY)*scaleY, 4.3f);
	glVertex3f((369+offsetX)*scaleX, (305+offsetY)*scaleY, 4.2f);
	glVertex3f((366+offsetX)*scaleX, (303+offsetY)*scaleY, 4.1f);
	glVertex3f((359+offsetX)*scaleX, (306+offsetY)*scaleY, 4.0f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((360+offsetX)*scaleX, (311+offsetY)*scaleY, 4.2f);
	glVertex3f((363+offsetX)*scaleX, (312+offsetY)*scaleY, 4.3f);
	glVertex3f((368+offsetX)*scaleX, (312+offsetY)*scaleY, 4.3f);
	glVertex3f((371+offsetX)*scaleX, (311+offsetY)*scaleY, 4.2f);
	glVertex3f((372+offsetX)*scaleX, (308+offsetY)*scaleY, 4.1f);
	glVertex3f((366+offsetX)*scaleX, (309+offsetY)*scaleY, 4.0f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((355+offsetX)*scaleX, (315+offsetY)*scaleY, 4.2f);
	glVertex3f((358+offsetX)*scaleX, (314+offsetY)*scaleY, 4.3f);
	glVertex3f((357+offsetX)*scaleX, (312+offsetY)*scaleY, 4.2f);
	glVertex3f((356+offsetX)*scaleX, (308+offsetY)*scaleY, 4.1f);
	glVertex3f((353+offsetX)*scaleX, (309+offsetY)*scaleY, 4.0f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((348+offsetX)*scaleX, (314+offsetY)*scaleY, 4.2f);
	glVertex3f((349+offsetX)*scaleX, (315+offsetY)*scaleY, 4.3f);
	glVertex3f((353+offsetX)*scaleX, (315+offsetY)*scaleY, 4.2f);
	glVertex3f((352+offsetX)*scaleX, (314+offsetY)*scaleY, 4.1f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((308+offsetX)*scaleX, (295+offsetY)*scaleY, 4.2f);
	glVertex3f((314+offsetX)*scaleX, (295+offsetY)*scaleY, 4.3f);
	glVertex3f((323+offsetX)*scaleX, (294+offsetY)*scaleY, 4.2f);
	glVertex3f((327+offsetX)*scaleX, (292+offsetY)*scaleY, 4.1f);
	glVertex3f((331+offsetX)*scaleX, (289+offsetY)*scaleY, 4.0f);
	glVertex3f((335+offsetX)*scaleX, (287+offsetY)*scaleY, 3.9f);
	glVertex3f((340+offsetX)*scaleX, (285+offsetY)*scaleY, 3.8f);
	glVertex3f((343+offsetX)*scaleX, (282+offsetY)*scaleY, 3.9f);
	glVertex3f((345+offsetX)*scaleX, (280+offsetY)*scaleY, 4.0f);
	glVertex3f((343+offsetX)*scaleX, (278+offsetY)*scaleY, 4.1f);
	glVertex3f((342+offsetX)*scaleX, (277+offsetY)*scaleY, 4.2f);
	glVertex3f((340+offsetX)*scaleX, (276+offsetY)*scaleY, 4.1f);
	glVertex3f((335+offsetX)*scaleX, (276+offsetY)*scaleY, 4.0f);
	glVertex3f((331+offsetX)*scaleX, (278+offsetY)*scaleY, 3.9f);
	glVertex3f((327+offsetX)*scaleX, (281+offsetY)*scaleY, 4.0f);
	glVertex3f((323+offsetX)*scaleX, (282+offsetY)*scaleY, 4.1f);
	glVertex3f((318+offsetX)*scaleX, (284+offsetY)*scaleY, 4.2f);
	glVertex3f((315+offsetX)*scaleX, (287+offsetY)*scaleY, 4.1f);
	glVertex3f((311+offsetX)*scaleX, (289+offsetY)*scaleY, 4.0f);
	glVertex3f((309+offsetX)*scaleX, (291+offsetY)*scaleY, 3.9f);
	glVertex3f((306+offsetX)*scaleX, (293+offsetY)*scaleY, 4.0f);
	glEnd();

	glPopMatrix();
}

void alasmariposa2simetrica() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	glScalef(-1.0f, 1.0f, 1.0f);
	
	float scaleX = 0.35f;   
	float scaleY = 0.35f;    
	float offsetX = -295.0f;  // Ajusta distancia
	float offsetY = -255.0f;  
	
	// Main black outline
	GLfloat blackAmb[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat blackDiff[] = {0.01f, 0.01f, 0.01f, 1.0f};
	GLfloat blackSpec[] = {0.1f, 0.1f, 0.1f, 1.0f};
	setMaterial(blackAmb, blackDiff, blackSpec, 32.0f);
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((304+offsetX)*scaleX, (288+offsetY)*scaleY, 4.0f);
	glVertex3f((318+offsetX)*scaleX, (279+offsetY)*scaleY, 4.1f);
	glVertex3f((340+offsetX)*scaleX, (270+offsetY)*scaleY, 4.2f);
	glVertex3f((342+offsetX)*scaleX, (264+offsetY)*scaleY, 4.3f);
	glVertex3f((343+offsetX)*scaleX, (259+offsetY)*scaleY, 4.4f);
	glVertex3f((341+offsetX)*scaleX, (258+offsetY)*scaleY, 4.4f);
	glVertex3f((340+offsetX)*scaleX, (270+offsetY)*scaleY, 4.3f);
	glVertex3f((342+offsetX)*scaleX, (264+offsetY)*scaleY, 4.2f);
	glVertex3f((343+offsetX)*scaleX, (259+offsetY)*scaleY, 4.1f);
	glVertex3f((343+offsetX)*scaleX, (257+offsetY)*scaleY, 4.0f);
	glVertex3f((343+offsetX)*scaleX, (256+offsetY)*scaleY, 3.9f);
	glVertex3f((342+offsetX)*scaleX, (253+offsetY)*scaleY, 3.8f);
	glVertex3f((340+offsetX)*scaleX, (250+offsetY)*scaleY, 3.7f);
	glVertex3f((338+offsetX)*scaleX, (248+offsetY)*scaleY, 3.6f);
	glVertex3f((335+offsetX)*scaleX, (244+offsetY)*scaleY, 3.5f);
	glVertex3f((329+offsetX)*scaleX, (241+offsetY)*scaleY, 3.4f);
	glVertex3f((325+offsetX)*scaleX, (240+offsetY)*scaleY, 3.3f);
	glVertex3f((320+offsetX)*scaleX, (238+offsetY)*scaleY, 3.2f);
	glVertex3f((313+offsetX)*scaleX, (238+offsetY)*scaleY, 3.1f);
	glVertex3f((306+offsetX)*scaleX, (239+offsetY)*scaleY, 3.0f);
	glVertex3f((302+offsetX)*scaleX, (242+offsetY)*scaleY, 2.9f);
	glVertex3f((301+offsetX)*scaleX, (251+offsetY)*scaleY, 2.8f);
	glVertex3f((301+offsetX)*scaleX, (263+offsetY)*scaleY, 2.7f);
	glVertex3f((301+offsetX)*scaleX, (275+offsetY)*scaleY, 2.6f);
	glVertex3f((301+offsetX)*scaleX, (283+offsetY)*scaleY, 2.5f);
	glEnd();
	
	GLfloat orangeAmb[] = {0.96f, 0.60f, 0.11f};
	GLfloat orangeDiff[] = {0.96f, 0.60f, 0.11f};
	GLfloat orangeSpec[] = {0.5f, 0.5f, 0.5f};
	setMaterial(orangeAmb, orangeDiff, orangeSpec, 32.0f);

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((304+offsetX)*scaleX, (286+offsetY)*scaleY, 4.1f);
	glVertex3f((309+offsetX)*scaleX, (283+offsetY)*scaleY, 4.2f);
	glVertex3f((316+offsetX)*scaleX, (279+offsetY)*scaleY, 4.3f);
	glVertex3f((319+offsetX)*scaleX, (273+offsetY)*scaleY, 4.3f);
	glVertex3f((321+offsetX)*scaleX, (270+offsetY)*scaleY, 4.2f);
	glVertex3f((323+offsetX)*scaleX, (266+offsetY)*scaleY, 4.1f);
	glVertex3f((323+offsetX)*scaleX, (261+offsetY)*scaleY, 4.0f);
	glVertex3f((317+offsetX)*scaleX, (264+offsetY)*scaleY, 3.9f);
	glVertex3f((313+offsetX)*scaleX, (267+offsetY)*scaleY, 3.8f);
	glVertex3f((310+offsetX)*scaleX, (271+offsetY)*scaleY, 3.9f);
	glVertex3f((308+offsetX)*scaleX, (275+offsetY)*scaleY, 4.0f);
	glVertex3f((305+offsetX)*scaleX, (280+offsetY)*scaleY, 4.1f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((320+offsetX)*scaleX, (277+offsetY)*scaleY, 4.2f);
	glVertex3f((321+offsetX)*scaleX, (274+offsetY)*scaleY, 4.3f);
	glVertex3f((325+offsetX)*scaleX, (270+offsetY)*scaleY, 4.3f);
	glVertex3f((330+offsetX)*scaleX, (267+offsetY)*scaleY, 4.2f);
	glVertex3f((335+offsetX)*scaleX, (264+offsetY)*scaleY, 4.1f);
	glVertex3f((337+offsetX)*scaleX, (267+offsetY)*scaleY, 4.0f);
	glVertex3f((335+offsetX)*scaleX, (270+offsetY)*scaleY, 4.1f);
	glVertex3f((330+offsetX)*scaleX, (272+offsetY)*scaleY, 4.2f);
	glVertex3f((325+offsetX)*scaleX, (275+offsetY)*scaleY, 4.2f);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((312+offsetX)*scaleX, (265+offsetY)*scaleY, 4.1f);
	glVertex3f((318+offsetX)*scaleX, (260+offsetY)*scaleY, 4.2f);
	glVertex3f((320+offsetX)*scaleX, (245+offsetY)*scaleY, 4.1f);
	glVertex3f((317+offsetX)*scaleX, (245+offsetY)*scaleY, 4.0f);
	glVertex3f((314+offsetX)*scaleX, (247+offsetY)*scaleY, 3.9f);
	glVertex3f((314+offsetX)*scaleX, (251+offsetY)*scaleY, 4.0f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((320+offsetX)*scaleX, (259+offsetY)*scaleY, 4.1f);
	glVertex3f((324+offsetX)*scaleX, (258+offsetY)*scaleY, 4.2f);
	glVertex3f((326+offsetX)*scaleX, (253+offsetY)*scaleY, 4.1f);
	glVertex3f((328+offsetX)*scaleX, (248+offsetY)*scaleY, 4.0f);
	glVertex3f((323+offsetX)*scaleX, (246+offsetY)*scaleY, 3.9f);
	glVertex3f((321+offsetX)*scaleX, (253+offsetY)*scaleY, 4.0f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((302+offsetX)*scaleX, (281+offsetY)*scaleY, 4.1f);
	glVertex3f((306+offsetX)*scaleX, (276+offsetY)*scaleY, 4.2f);
	glVertex3f((309+offsetX)*scaleX, (270+offsetY)*scaleY, 4.1f);
	glVertex3f((310+offsetX)*scaleX, (262+offsetY)*scaleY, 4.0f);
	glVertex3f((312+offsetX)*scaleX, (246+offsetY)*scaleY, 3.9f);
	glVertex3f((306+offsetX)*scaleX, (246+offsetY)*scaleY, 3.8f);
	glVertex3f((303+offsetX)*scaleX, (248+offsetY)*scaleY, 3.9f);
	glVertex3f((303+offsetX)*scaleX, (257+offsetY)*scaleY, 4.0f);
	glVertex3f((303+offsetX)*scaleX, (267+offsetY)*scaleY, 4.1f);
	glVertex3f((302+offsetX)*scaleX, (273+offsetY)*scaleY, 4.2f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 0.5f);
	glVertex3f((324+offsetX)*scaleX, (269+offsetY)*scaleY, 4.2f);
	glVertex3f((329+offsetX)*scaleX, (266+offsetY)*scaleY, 4.3f);
	glVertex3f((335+offsetX)*scaleX, (262+offsetY)*scaleY, 4.2f);
	glVertex3f((338+offsetX)*scaleX, (259+offsetY)*scaleY, 4.1f);
	glVertex3f((336+offsetX)*scaleX, (256+offsetY)*scaleY, 4.0f);
	glVertex3f((333+offsetX)*scaleX, (253+offsetY)*scaleY, 3.9f);
	glVertex3f((330+offsetX)*scaleX, (256+offsetY)*scaleY, 4.0f);
	glVertex3f((327+offsetX)*scaleX, (259+offsetY)*scaleY, 4.1f);
	glVertex3f((325+offsetX)*scaleX, (264+offsetY)*scaleY, 4.2f);
	glEnd();
	
	glPopMatrix();
}

void dibujarTexto(const char* texto, float x, float y, float z) {
	glDisable(GL_LIGHTING);  // Disable lighting for text
	glColor3f(0.0f, 0.0f, 0.0f);  // Black text
	
	glRasterPos3f(x, y, z);
	while (*texto) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *texto);
		texto++;
	}
	
	glEnable(GL_LIGHTING);  // Re-enable lighting
}

void dibujarAlgodoncillo(float x, float z) {
	// Tallo verde 
	GLfloat stemAmb[] = {0.0f, 0.3f, 0.0f};
	GLfloat stemDiff[] = {0.0f, 0.6f, 0.0f};
	GLfloat stemSpec[] = {0.0f, 0.2f, 0.0f};
	setMaterial(stemAmb, stemDiff, stemSpec, 32.0f);
	
	glPushMatrix();
	glTranslatef(x, -35.0f, z);  // Adjusted height
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.4f, 12.0f, 8, 8);  // Made stem taller
	glPopMatrix();
	
	// Flores pequeñas en racimo
	GLfloat flowerAmb[] = {0.9f, 0.9f, 0.9f};  // Increased ambient
	GLfloat flowerDiff[] = {1.0f, 0.95f, 0.95f};
	GLfloat flowerSpec[] = {0.7f, 0.7f, 0.7f};  // Increased specular
	setMaterial(flowerAmb, flowerDiff, flowerSpec, 64.0f);
	
	glPushMatrix();
	glTranslatef(x, -25.0f, z);  // Adjusted flower cluster height
	
	// Increased scale of flower clusters
	for(int nivel = 0; nivel < 3; nivel++) {
		float radio = 2.0f - nivel * 0.3f;  // Wider radius
		float altura = nivel * 1.2f;  // More vertical spacing
		
		for(int flor = 0; flor < 8; flor++) {
			float angulo = flor * (360.0f / 8) + nivel * 22.5f;
			glPushMatrix();
			glRotatef(angulo, 0.0f, 1.0f, 0.0f);
			glTranslatef(radio, altura, 0.0f);
			glutSolidSphere(0.6f, 8, 8);  // Bigger flowers
			
			// Bigger petals
			for(int petalo = 0; petalo < 5; petalo++) {
				glPushMatrix();
				glRotatef(petalo * 72.0f, 0.0f, 1.0f, 0.0f);
				glTranslatef(0.5f, 0.0f, 0.0f);
				glScalef(0.6f, 0.6f, 0.3f);
				glutSolidSphere(0.4f, 6, 6);
				glPopMatrix();
			}
			glPopMatrix();
		}
	}
	glPopMatrix();
}

void dibujarCempasuchil(float x, float z) {
	// Tallo verde
	GLfloat stemAmb[] = {0.0f, 0.3f, 0.0f};
	GLfloat stemDiff[] = {0.0f, 0.5f, 0.0f};
	GLfloat stemSpec[] = {0.0f, 0.2f, 0.0f};
	setMaterial(stemAmb, stemDiff, stemSpec, 32.0f);
	
	glPushMatrix();
	glTranslatef(x, -45.0f, z);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.3f, 5.0f, 8, 8);
	glPopMatrix();
	
	// Pétalos naranjas brillantes
	GLfloat petalAmb[] = {0.8f, 0.3f, 0.0f};
	GLfloat petalDiff[] = {1.0f, 0.5f, 0.0f};
	GLfloat petalSpec[] = {0.8f, 0.6f, 0.0f};
	setMaterial(petalAmb, petalDiff, petalSpec, 64.0f);
	
	// Centro de la flor
	glPushMatrix();
	glTranslatef(x, -40.0f, z);
	glutSolidSphere(0.8f, 16, 16);
	
	// Pétalos en capas
	for(int i = 0; i < 2; i++) {
		float radio = 1.0f + i * 0.5f;
		float altura = 0.2f + i * 0.2f;
		
		for(int j = 0; j < 16; j++) {
			glPushMatrix();
			float angulo = j * (360.0f / 16);
			glRotatef(angulo, 0.0f, 1.0f, 0.0f);
			glTranslatef(radio, 0.0f, 0.0f);
			glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
			glScalef(1.5f, 0.3f, 0.3f);
			glutSolidSphere(0.8f, 8, 8);
			glPopMatrix();
		}
	}
	glPopMatrix();
}

void dibujarSimboloPesticidas() {
	glPushMatrix();
	glTranslatef(50.0f, 30.0f, 10.0f);  // Moved forward on Z axis
	float scale = 1.0f + sin(signScale) * 0.1f;
	glScalef(scale, scale, scale);
	
	// Contorno negro
	glDisable(GL_LIGHTING);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f,-0.5f);
	for(int i = 0; i <= 360; i += 10) {
		float angle = i * 3.14159f / 180.0f;
		glVertex2f(11.0f * cos(angle), 11.0f * sin(angle));
	}
	glEnd();
	
	// Círculo blanco
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f,0.0f);
	for(int i = 0; i <= 360; i += 10) {
		float angle = i * 3.14159f / 180.0f;
		glVertex2f(10.0f * cos(angle), 10.0f * sin(angle));
	}
	glEnd();
	
	// Línea diagonal
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3f(-7.0f, -7.0f,0.0f);
	glVertex3f(7.0f, 7.0f,0.0f);
	glEnd();
	
	// Texto (ligeramente adelante del símbolo)
	glColor3f(0.0f, 0.0f, 0.0f);
	dibujarTexto("NO", -3.0f, 2.0f, 0.5f);
	dibujarTexto("PESTICIDAS", -8.0f, -2.0f, 0.5f);
	
	glEnable(GL_LIGHTING);
	glPopMatrix();
	signScale += 0.03f;
}

void dibujarCartel() {
	glPushMatrix();
	glTranslatef(-50.0f, 30.0f, 10.0f);
	
	// Cartel base (same as before)
	GLfloat brownAmb[] = {0.2f, 0.1f, 0.0f};
	GLfloat brownDiff[] = {0.4f, 0.2f, 0.0f};
	GLfloat brownSpec[] = {0.2f, 0.2f, 0.2f};
	setMaterial(brownAmb, brownDiff, brownSpec, 32.0f);
	
	glBegin(GL_POLYGON);
	glVertex3f(-20.0f, -10.0f, 0.0f);
	glVertex3f(30.0f, -10.0f, 0.0f);
	glVertex3f(30.0f, 10.0f, 0.0f);
	glVertex3f(-20.0f, 10.0f, 0.0f);
	glEnd();
	
	// Animated text with target positions
	dibujarTexto("Las mariposas monarca viajan hasta 4800 km en su migracion", -19.0f, textY1, 0.5f);
	dibujarTexto("1. Plantar flores nativas", -19.0f, textY2, 0.5f);
	dibujarTexto("2. Evitar pesticidas", -19.0f, textY3, 0.5f);
	dibujarTexto("3. Crear espacios con flores para nectar", -19.0f, textY4, 0.5f);
	
	// Update positions
	textY1 -= textVelocity1;
	textY2 -= textVelocity2;
	textY3 -= textVelocity3;
	textY4 -= textVelocity4;
	
	// Improved bounce logic with target positions
	if (textY1 < TARGET_Y1) {
		textY1 = TARGET_Y1 + (TARGET_Y1 - textY1) * dampening;
		textVelocity1 *= -dampening;
		if (fabs(textY1 - TARGET_Y1) < 0.01f) textY1 = TARGET_Y1;
	}
	
	if (textY2 < TARGET_Y2) {
		textY2 = TARGET_Y2 + (TARGET_Y2 - textY2) * dampening;
		textVelocity2 *= -dampening;
		if (fabs(textY2 - TARGET_Y2) < 0.01f) textY2 = TARGET_Y2;
	}
	
	if (textY3 < TARGET_Y3) {
		textY3 = TARGET_Y3 + (TARGET_Y3 - textY3) * dampening;
		textVelocity3 *= -dampening;
		if (fabs(textY3 - TARGET_Y3) < 0.01f) textY3 = TARGET_Y3;
	}
	
	if (textY4 < TARGET_Y4) {
		textY4 = TARGET_Y4 + (TARGET_Y4 - textY4) * dampening;
		textVelocity4 *= -dampening;
		if (fabs(textY4 - TARGET_Y4) < 0.01f) textY4 = TARGET_Y4;
	}
	
	glPopMatrix();
}

void dibujarNubesYSol() {
	// Material para las nubes
	GLfloat cloudAmb[] = {0.8f, 0.8f, 0.8f};
	GLfloat cloudDiff[] = {1.0f, 1.0f, 1.0f};
	GLfloat cloudSpec[] = {0.0f, 0.0f, 0.0f};
	
	// Primera nube
	setMaterial(cloudAmb, cloudDiff, cloudSpec, 0.0f);
	glPushMatrix();
	glTranslatef(-60.0f, 80.0f, -50.0f);
	glutSolidSphere(10.0, 20, 20);
	glTranslatef(8.0f, -2.0f, 0.0f);
	glutSolidSphere(8.0, 20, 20);
	glTranslatef(8.0f, 2.0f, 0.0f);
	glutSolidSphere(10.0, 20, 20);
	glPopMatrix();
	
	// Segunda nube
	glPushMatrix();
	glTranslatef(60.0f, 90.0f, -50.0f);
	glutSolidSphere(12.0, 20, 20);
	glTranslatef(-10.0f, -3.0f, 0.0f);
	glutSolidSphere(9.0, 20, 20);
	glTranslatef(-8.0f, 3.0f, 0.0f);
	glutSolidSphere(11.0, 20, 20);
	glPopMatrix();
	
	// Sol
	GLfloat sunAmb[] = {0.8f, 0.6f, 0.0f};
	GLfloat sunDiff[] = {1.0f, 0.8f, 0.0f};
	GLfloat sunSpec[] = {1.0f, 1.0f, 0.0f};
	setMaterial(sunAmb, sunDiff, sunSpec, 128.0f);
	
	glPushMatrix();
	glTranslatef(0.0f, 85.0f, -60.0f);
	glBegin(GL_POLYGON);
	for(int i = 0; i < 360; i++) {
		float theta = i * 3.1416f / 180.0f;
		glVertex3f(15.0f * cos(theta), 15.0f * sin(theta), 0.0f);
	}
	glEnd();
	glPopMatrix();
}

void dibujarNubesYSolAnimados() {
	// Material para las nubes
	GLfloat cloudAmb[] = {0.8f, 0.8f, 0.8f};
	GLfloat cloudDiff[] = {1.0f, 1.0f, 1.0f};
	GLfloat cloudSpec[] = {0.0f, 0.0f, 0.0f};
	
	// Primera nube con movimiento ondulante
	setMaterial(cloudAmb, cloudDiff, cloudSpec, 0.0f);
	glPushMatrix();
	glTranslatef(-60.0f + cloudOffset1, 80.0f + sin(cloudOffset1/20.0f) * 2.0f, -50.0f);
	glutSolidSphere(10.0, 20, 20);
	glTranslatef(8.0f, -2.0f, 0.0f);
	glutSolidSphere(8.0, 20, 20);
	glTranslatef(8.0f, 2.0f, 0.0f);
	glutSolidSphere(10.0, 20, 20);
	glPopMatrix();
	
	// Segunda nube con movimiento contrario
	glPushMatrix();
	glTranslatef(60.0f - cloudOffset2, 90.0f + sin(cloudOffset2/15.0f) * 1.5f, -50.0f);
	glutSolidSphere(12.0, 20, 20);
	glTranslatef(-10.0f, -3.0f, 0.0f);
	glutSolidSphere(9.0, 20, 20);
	glTranslatef(-8.0f, 3.0f, 0.0f);
	glutSolidSphere(11.0, 20, 20);
	glPopMatrix();
	
	// Sol giratorio con rayos
	GLfloat sunAmb[] = {0.8f, 0.6f, 0.0f};
	GLfloat sunDiff[] = {1.0f, 0.8f, 0.0f};
	GLfloat sunSpec[] = {1.0f, 1.0f, 0.0f};
	setMaterial(sunAmb, sunDiff, sunSpec, 128.0f);
	
	glPushMatrix();
	glTranslatef(0.0f, 85.0f, -60.0f);
	glRotatef(sunRotation, 0.0f, 0.0f, 1.0f);
	
	// Disco solar
	glBegin(GL_POLYGON);
	for(int i = 0; i < 360; i++) {
		float theta = i * 3.1416f / 180.0f;
		glVertex3f(15.0f * cos(theta), 15.0f * sin(theta), 0.0f);
	}
	glEnd();
	
	// Rayos del sol
	glBegin(GL_LINES);
	for(int i = 0; i < 12; i++) {
		float angle = i * 30.0f * 3.1416f / 180.0f;
		glVertex3f(15.0f * cos(angle), 15.0f * sin(angle), 0.0f);
		glVertex3f(20.0f * cos(angle), 20.0f * sin(angle), 0.0f);
	}
	glEnd();
	
	glPopMatrix();
	
	// Actualizar animaciones
	cloudOffset1 += 0.1f;
	if(cloudOffset1 > 120.0f) cloudOffset1 = -120.0f;
	
	cloudOffset2 += 0.15f;
	if(cloudOffset2 > 120.0f) cloudOffset2 = -120.0f;
	
	sunRotation += 0.2f;
	if(sunRotation > 360.0f) sunRotation = 0.0f;
}

void dibujarSimbolosPreservacion() {
	static float anguloRotacion = 0.0f;
	glPushMatrix();
	glTranslatef(-50.0f, 20.0f, 0.0f);
	glRotatef(anguloRotacion, 0.0f, 1.0f, 0.0f);
	// Dibujar botella de pesticida tachada
	glPopMatrix();
	
	static float alturaplanta = 0.0f;
	glPushMatrix();
	glTranslatef(50.0f, -40.0f + alturaplanta, 0.0f);
	// Dibujar planta creciendo
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0f, 30.0f, -20.0f);
	// Dibujar señal de santuario
	glPopMatrix();
	
	anguloRotacion += 1.0f;
	alturaplanta = 5.0f * sin(glutGet(GLUT_ELAPSED_TIME) / 1000.0f);
}



void display(void) {
	while(1) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(0, 50, 200, 0, 0, 0, 0, 1, 0);
		
		// Actualizar el ángulo de las alas
		anguloAlas += velocidadAlas * 0.016f; // 0.016 es aproximadamente 1/60 para 60 FPS
		
		// Base y elementos estáticos
		dibujarNubesYSolAnimados();
		dibujarBase();
		
		dibujarCartel();
		dibujarSimboloPesticidas();
		dibujarSimbolosPreservacion();
		
		for(int i = -150; i < 150; i += 40) {
			for(int j = -80; j < 80; j += 40) {
				if((i + j) % 2 == 0) {
					dibujarCempasuchil(i + (rand() % 10), j + (rand() % 10));
				} else {
					dibujarAlgodoncillo(i + (rand() % 5), j + (rand() % 5));
				}
			}
		}
		glPushMatrix();
		glTranslatef(0.0f, -49.0f, 0.0f);
		pasto();
		arbol(30.0f, -20.0f);
		arbol(-40.0f, -30.0f);
		arbol(60.0f, 10.0f);
		arbol(-20.0f, 20.0f);
		glPopMatrix();
		
		// Mariposa con movimiento
		glPushMatrix();
		glTranslatef(0.0f, posY, 0.0f);
		abdomenmariposa();
		antenasmariposa();
		alasmariposa1();
		alasmariposa1simetrica();
		alasmariposa2();
		alasmariposa2simetrica();
		glPopMatrix();
		
		glutSwapBuffers();
		
		posY += delta;
		if(posY > 10.0f || posY < -10.0f) {
			delta = -delta;
		}
		
		Sleep(16);
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1600,1200);
	glutCreateWindow("Mariposa Monarca 3D");
	
	inicializa();
	glutDisplayFunc(display);
	glutMainLoop();
	
	return 0;
}
