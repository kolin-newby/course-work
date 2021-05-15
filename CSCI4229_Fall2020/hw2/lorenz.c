/*
	Lorenz Attractor

	Kolin Newby
	CSCI4229 Fall 2020

	Key bindings
		s      select s parameter to edit
		b      select b parameter to edit
		r      select r parameter to edit
		+/-    Increase/decrease s, b, or r depending on current selection (sometimes you must hold shift to use '+')
		arrows Change view angle
		z      Reset Lorenz Parameters
		0      Reset view angle
		ESC    Exit

	Citation
		-Functions are taken from or based on functions in ex6.c from class and a lorenz.c file provided for this assignment

  Time Taken:
    This assignment took me around 4 hours to complete, but I ran into bug that I couldn't fix so I partially started over.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//  Globals
// Lorenz Parameters
double s  = 10;
double b  = 2.6666;
double r  = 28;

int th=0;       // Azimuth of view angle
int ph=0;       // Elevation of view angle
int mode=0;     // Default mode does nothing when '+' and '-' are pressed
double dim=2;   // Dimension of orthogonal box
const char* text[] = {"","Change s","Change b","Change r"};  // Indicates changing parameter

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  // Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

/*
 *  Display the scene
 */
void display()
{
   //  Clear the image
   glClear(GL_COLOR_BUFFER_BIT);
   //  Reset previous transforms
   glLoadIdentity();
   //  Set view angle
   glRotated(ph,1,0,0);
   glRotated(th,0,1,0);
   glPointSize(1);
   glBegin(GL_LINE_STRIP);
   
   /*  Coordinates  */
   double x = 1;
   double y = 1;
   double z = 1;
   /*  Time step  */
   double dt = 0.001;
   double scale = 28; //coordinates are divided by scale to fit in space

   for (int i = 0; i < 50000; i++) {
      double dx = s*(y-x);
      double dy = x*(r-z)-y;
      double dz = x*y - b*z;
      x += dt*dx;
      y += dt*dy;
      z += dt*dz;
      
      if (i < 10000) {
      	glColor3f(1,0,0);
      	glVertex3d(x/scale, y/scale, z/scale);
      }
      else if (i >= 10000 && i < 30000) {
      	glColor3f(1,0.5,0);
      	glVertex3d(x/scale, y/scale, z/scale);
      }
      else if (i >= 30000 && i < 50000) {
      	glColor3f(1,1,0);
      	glVertex3d(x/scale, y/scale, z/scale);
      }
   }

   glEnd();
   //  Draw axes in white
   glColor3f(1,1,1);
   glBegin(GL_LINES);
   glVertex3d(0,0,0);
   glVertex3d(1.5,0,0);
   glVertex3d(0,0,0);
   glVertex3d(0,1.5,0);
   glVertex3d(0,0,0);
   glVertex3d(0,0,1.5);
   glEnd();
   //  Label axes
   glRasterPos3d(1.5,0,0);
   Print("X");
   glRasterPos3d(0,1.5,0);
   Print("Y");
   glRasterPos3d(0,0,1.5);
   Print("Z");
   //  Display parameters
   glWindowPos2i(5,5);
   Print("View Angle=%d,%d  %s | s=%f b=%f r=%f",th,ph,text[mode],s,b,r);
   //  Flush and swap
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //Exit on ESC
   if (ch == 27)
      exit(0);
   //Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //Reset Lorenz Parameters
   else if (ch == 'z') {
      s  = 10;
	  b  = 2.6666;
	  r  = 28;
	}
   //Switch to edit s parameter
   else if (ch == 's')
      mode = 1;
   //Switch to edit b parameter
   else if (ch == 'b')
      mode = 2;
   //Switch to edit r parameter
   else if (ch == 'r')
      mode = 3;
   //  Increase s, b, or r by 1
   else if (ch == '+')
   {
    	if (mode == 0)
        	return;
    	else if (mode == 1)
        	s += 1;
        else if (mode == 2)
        	b += 1;
    	else if (mode == 3)
        	r += 1;
   }
   //  Decrease s, b, or r by 1
   else if (ch == '-')
   {
      if (mode == 0)
        	return;
    	else if (mode == 1)
        	s -= 1;
        else if (mode == 2)
        	b -= 1;
    	else if (mode == 3)
        	r -= 1;
   }
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase azimuth by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease azimuth by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection box adjusted for the
   //  aspect ratio of the window
   glOrtho(-dim*w2h,+dim*w2h, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
  //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window 
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   //  Request 500 x 500 pixel window
   glutInitWindowSize(600,600);
   //  Create the window
   glutCreateWindow("HW2: Kolin Newby");
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
  //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   //  Return code
   return 0;
}
