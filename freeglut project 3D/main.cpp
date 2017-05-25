#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>

//#include "Tetraedro.h"

#include <iostream>
#include "Cono.h"
#include "CurvaHipotrocoide.h"
#include "MallaExtrusion.h"
#include "Tanque.h"
#include "Camara.h"
using namespace std;

//#define __ORTHO

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH= 500, HEIGHT= 500;

// Viewing frustum parameters
GLdouble xRight=10, xLeft=-xRight, yTop=10, yBot=-yTop, N=1, F=1000;

// Camera parameters
GLdouble eyeX=5.0, eyeY=5.0, eyeZ=5.0;
GLdouble lookX=0.0, lookY=0.0, lookZ=0.0;
GLdouble upX=0, upY=1, upZ=0;

// Scene variables
GLfloat angX, angY, angZ; 
//Tetraedro* tet;

Camara * camara;
Camara * camaraInside;
bool isInside = false;
Cono * cono;
CurvaHipotrocoide * c;
MallaExtrusion * me;
Tanque * tanque;
float tankPos = 0.0f;
float tt = PI;
bool ldirectional;

void buildSceneObjects() {	 
    angX=0.0f;
    angY=0.0f;
    angZ=0.0f;	
	//tet=new Tetraedro();
	cono = new Cono(200, 5, 10);
	c = new CurvaHipotrocoide(7.0f, 4.0f, 2.0f);
	me = new MallaExtrusion(20, 400, 0.5f, 4, c);
	tanque = new Tanque(1,0.5,0.5);
	camara = new Camara();
	camara->setEye(new PuntoVector3D(eyeX, eyeY, eyeZ, 1));
	camara->setLook(new PuntoVector3D(lookX, lookY, lookZ, 0));
	camara->setUp(new PuntoVector3D(upX, upY, upZ, 0));
	camaraInside = new Camara();
	camaraInside->setUp(new PuntoVector3D(upX, upY, upZ, 0));
	camaraInside->inside(c, tanque, tt);
}

void initGL() {	 		 
	glClearColor(0.6f,0.7f,0.8f,1.0);
      
	glEnable(GL_COLOR_MATERIAL);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.9f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH); // Shading by default
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	buildSceneObjects();

	// Ambient Light
	GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	// Light0 Directional
	glEnable(GL_LIGHTING);  
    glEnable(GL_LIGHT0);
	GLfloat l0Black[] = { 0.3f, 1.0f, 0.3f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0Black);
	GLfloat l0BlackAmbient[] = { 0.15f, 0.5f, 0.15f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0BlackAmbient);
	GLfloat l0BlackSpecular[] = { 0.3f, 1.0f, 0.3f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0BlackSpecular);
	// TODO: the position have to be where the angle with XZ plane is 45º
	GLfloat l0Position[] = { 0.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, l0Position);
	glDisable(GL_LIGHT0);
	ldirectional = false;

	// TODO: tank lights have to be "yellow"

    /*GLfloat d[]={0.7f,0.5f,0.5f,1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
    GLfloat a[]={0.3f,0.3f,0.3f,1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	GLfloat s[]={1.0f,1.0f,1.0f,1.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, s);
	GLfloat p[]={25.0f, 25.0f, 25.0f, 1.0f};	 
	glLightfv(GL_LIGHT0, GL_POSITION, p);*/

	// Camera set up
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (isInside) {
		camaraInside->setInverse();
	}
	else {
		camara->setInverse();
	}
	//gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);

	// Frustum set up
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    

#ifdef __ORTHO
	glOrtho(xLeft, xRight, yBot, yTop, N, F);
#else
	gluPerspective(60, 1, 0.1, 200);
#endif

	// Viewport set up
    glViewport(0, 0, WIDTH, HEIGHT);  	
 }

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  



	glMatrixMode(GL_MODELVIEW);	 

	glLoadIdentity();
	if (isInside) {
		camaraInside->inside(c, tanque, tt);
		camaraInside->setInverse();
	}
	else {
		camara->setInverse();
	}

	



	glPushMatrix();
	
		// Rotating the scene
		glRotatef(angX, 1.0f, 0.0f, 0.0f);
        glRotatef(angY, 0.0f, 1.0f, 0.0f);
        glRotatef(angZ, 0.0f, 0.0f, 1.0f);
		
		glLineWidth(1.5f);
		// Drawing axes
		glBegin( GL_LINES );			
			glColor3f(1.0,0.0,0.0); 
			glVertex3f(0, 0, 0);
			glVertex3f(20, 0, 0);	     
	 
			glColor3f(0.0,1.0,0.0); 
			glVertex3f(0, 0, 0);
			glVertex3f(0, 20, 0);	 
	 
			glColor3f(0.0,0.0,1.0); 
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 20);	     
		glEnd();
		 		
		//cono->dibuja();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		/*glMatrixMode(GL_COLOR);
		glPushMatrix();
		glEnable(GL_COLOR_MATERIAL);
		GLfloat v[4]; v[0] = 1; v[1] = 0; v[2] = 0; v[3] = 1;
		GLfloat w[4]; w[0] = 0; w[1] = 1; w[2] = 0; w[3] = 1;
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glColor4f(v[0], v[1], v[2], v[3]);
		glColorMaterial(GL_BACK, GL_AMBIENT_AND_DIFFUSE);
		glColor4f(w[0], w[1], w[2], w[3]);*/
		//glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, w);

		me->dibuja();
		//glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		//glDisable(GL_COLOR_MATERIAL);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		//crear matriz 4x4
		float matrix[16];

		
		PuntoVector3D *n, *b, *t, *p, *c2;
		n = c->getN(tt);
		b = c->getB(tt);
		t = c->getT(tt);
		p = c->getC(tt);
		c2 = c->getC2(tt);
		float derrape = c2->getNorm();
		

		//rellenada por columnas
		matrix[0] = n->getX();
		matrix[1] = n->getY();
		matrix[2] = n->getZ();
		matrix[3] = 0;
		matrix[4] = b->getX();
		matrix[5] = b->getY();
		matrix[6] = b->getZ();
		matrix[7] = 0;
		matrix[8] = t->getX();
		matrix[9] = t->getY();
		matrix[10] = t->getZ();
		matrix[11] = 0;
		matrix[12] = p->getX();
		matrix[13] = p->getY();
		matrix[14] = p->getZ();
		matrix[15] = 1;
		

		//aplicarla a openglç
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glMultMatrixf(matrix);
			glTranslatef(0, 0, tankPos);
			glRotatef(180, 1, 0, 0);
			glRotatef(derrape*5, 0, 1, 0);
			//cout << derrape * 5 << endl;

			if (!isInside)
				tanque->dibuja();

		//hacer pop matriz
		glPopMatrix();

		//glutSolidSphere(5, 50, 50);
		// Cuadrado
		/*
		glBegin( GL_LINE_LOOP);
		//glBegin(GL_POLYGON);  	 
			glColor3f(0.0,1.0,0.0); 
			glVertex3f(5.0f, 0.0f, 5.0f);
			glVertex3f(5.0f, 0.0f, -5.0f);
			glVertex3f(-5.0f, 0.0f, -5.0f);
			glVertex3f(-5.0f, 0.0f, 5.0f);		 
		glEnd();
		*/

		// Rincón
		/* 
		glBegin(GL_POLYGON); // Cara inferior
			glColor3f(0.0,1.0,0.0); 
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 10.0f);
			glVertex3f(10.0f, 0.0f, 10.0f);
			glVertex3f(10.0f, 0.0f, 0.0f);		
		glEnd();	
		glBegin(GL_POLYGON); // Cara lateral izquierda
			glColor3f(1.0,0.0,0.0); 
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 10.0f);
			glVertex3f(0.0f, 10.0f, 10.0f);
			glVertex3f(0.0f, 10.0f, 0.0f);
		glEnd();	 	
		glBegin(GL_POLYGON); // Cara trasera
			glColor3f(0.0,0.0,1.0); 
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(10.0f, 0.0f, 0.0f);
			glVertex3f(10.0f, 10.0f, 0.0f);
			glVertex3f(0.0f, 10.0f, 0.0f);
		glEnd();
		*/
		
		// Drawing the scene	 
		//cubo->dibuja();		 
	glPopMatrix();
 
	glFlush();
	glutSwapBuffers();
}


void resize(int newWidth, int newHeight) {
	WIDTH= newWidth;
	HEIGHT= newHeight;
	GLdouble RatioViewPort= (float)WIDTH/(float)HEIGHT;
	glViewport (0, 0, WIDTH, HEIGHT) ;
   
	GLdouble SVAWidth= xRight-xLeft;
	GLdouble SVAHeight= yTop-yBot;
	GLdouble SVARatio= SVAWidth/SVAHeight;
	if (SVARatio >= RatioViewPort) {		 
		GLdouble newHeight= SVAWidth/RatioViewPort;
		GLdouble yMiddle= ( yBot+yTop )/2.0;
		yTop= yMiddle + newHeight/2.0;
		yBot= yMiddle - newHeight/2.0;
    }
	else {      
		GLdouble newWidth= SVAHeight*RatioViewPort;
		GLdouble xMiddle= ( xLeft+xRight )/2.0;
		xRight= xMiddle + newWidth/2.0;
		xLeft=  xMiddle - newWidth/2.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();   

#ifdef __ORTHO
	if (isInside) {
		gluPerspective(60, 1, 0.1, 200);
	}
	else {
		glOrtho(xLeft, xRight, yBot, yTop, N, F);
	}
#else
	gluPerspective(60, 1, 0.1, 200);
#endif
}

void key(unsigned char key, int x, int y){
	bool need_redisplay = true;
	switch (key) {
		case 27:  /* Escape key */
			//continue_in_main_loop = false; // (**)
			//Freeglut's sentence for stopping glut's main loop (*)
			glutLeaveMainLoop (); 
			break;		 
		case 'i': isInside = !isInside; break;
		case 'a': angX=angX+5; break;
		case 'z': angX=angX-5; break; 
		case 's': angY=angY+5; break;
		case 'x': angY=angY-5; break;
		case 'd': angZ=angZ+5; break;
		case 'c': angZ=angZ-5; break;  
		case 'q': 
			tt += 0.1; 
			tanque->giraRueda(-10);
			break;
		case 'w': 
			tt -= 0.1; 
			tanque->giraRueda(10);
			break;
		case 'o': tanque->aumentaAngulo(1); break;
		case 'O': tanque->aumentaAngulo(-1); break;
		case '1': camara->rotationX(3.0f); break;
		case '2': camara->rotationX(-3.0f); break;
		case '3': camara->rotationY(3.0f); break;
		case '4': camara->rotationY(-3.0f); break;
		case '5': camara->rotationZ(3.0f); break;
		case '6': camara->rotationZ(-3.0f); break;
		case 'h': 
			glEnable(GL_LIGHT0);
			ldirectional = true;
			break;
		case 'n':
			glDisable(GL_LIGHT0);
			ldirectional = false;
			break;
		case 'f':  
			tankPos += 0.2;
			break;
		case 'v':
			tankPos -= 0.2;
			break;
		case 'g':
			// TODO: turn on tank lights
			break;
		case 'b':
			// TODO: turn off tank lights
			break;
		case 'r':
			camara->roll(3.0f);
			break;
		case 'R':
			camara->roll(-3.0f);
			break;
		case 't':
			camara->pitch(3.0f);
			break;
		case 'T':
			camara->pitch(-3.0f);
			break;
		case 'y':
			camara->yaw(3.0f);
			break;
		case 'Y':
			camara->yaw(-3.0f);
			break;


		default:
			need_redisplay = false;
			break;
	}

	if (need_redisplay)
		glutPostRedisplay();
}

int main(int argc, char *argv[]){
	cout<< "Starting console..." << endl;

	int my_window; // my window's identifier

	// Initialization
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition (0, 0);
	//glutInitWindowPosition (140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	// Window construction
	my_window = glutCreateWindow("Freeglut 3D-project");
    
	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutDisplayFunc(display);

	// OpenGL basic setting
	initGL();

	// Freeglut's main loop can be stopped executing (**)
	// while (continue_in_main_loop) glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION) ;
    
	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop(); 
  
	// We would never reach this point using classic glut
	system("PAUSE"); 
   
	return 0;
}