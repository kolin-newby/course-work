/*
*  Kolin Newby  
*  Homework 3
*
*
*
*  Key bindings:
*  m/M        Cycle through different sets of objects
*  a          Toggle axes
*  arrows     Change view angle
*  0          Reset view angle
*  1          Go to view 1
*  2          Go to view 2
*  ESC        Exit
*
*
*  This Assignment took me about 5 hours and 30 minutes.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int th=-205;          //  Azimuth of view angle
int ph=-40;          //  Elevation of view angle
// int th=0;
// int ph=0;
int axes=0;        //  Display axes

//  Cosine and Sine in degrees
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  //  Maximum length of text string
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


static void scene(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

   glColor4f(0.59,0.59,0.59,1);
   
   glBegin(GL_POLYGON);
   
   for (int theta = 0; theta < 360; theta++) {
      glVertex3f(Sin(theta), 0, Cos(theta));
   }

   glEnd();

   glBegin(GL_QUAD_STRIP);
   
   for (int theta = 0; theta < 360; theta++) {
      glVertex3f(Sin(theta), 0, Cos(theta));
      glVertex3f(Sin(theta), 4.5, Cos(theta));
   }

   glEnd();

   // -------------------------------Door Frame x-dir

   glBegin(GL_POLYGON);
   
   glVertex3f(0.38, 0, 1.1);
   glVertex3f(0.30, 0, 1.1);
   glVertex3f(0.30, 1, 1.1);
   glVertex3f(0.38, 1, 1.1);

   glEnd();

   glBegin(GL_POLYGON);
   
   glVertex3f(-0.38, 0, 1.1);
   glVertex3f(-0.30, 0, 1.1);
   glVertex3f(-0.30, 1, 1.1);
   glVertex3f(-0.38, 1, 1.1);

   glEnd();

   glBegin(GL_POLYGON);
   
   glVertex3f(0.38, 1, 1.1);
   glVertex3f(-0.38, 1, 1.1);
   glVertex3f(-0.38, 1.08, 1.1);
   glVertex3f(0.38, 1.08, 1.1);

   glEnd();

   glBegin(GL_POLYGON);
   
   glVertex3f(0.38, 1, 1.1);
   glVertex3f(-0.38, 1, 1.1);
   glVertex3f(-0.38, 1.08, 1.1);
   glVertex3f(0.38, 1.08, 1.1);

   glEnd();

   // --------------------------Door Frame z-dir

   glBegin(GL_POLYGON);
   
   glVertex3f(0.38, 1.08, 1.1);
   glVertex3f(0.38, 0, 1.1);
   glVertex3f(0.38, 0, 0);
   glVertex3f(0.38, 1.08, 0);

   glEnd();

   glBegin(GL_POLYGON);
   
   glVertex3f(-0.38, 1.08, 1.1);
   glVertex3f(-0.38, 0, 1.1);
   glVertex3f(-0.38, 0, 0);
   glVertex3f(-0.38, 1.08, 0);

   glEnd();

   glBegin(GL_POLYGON);
   
   glVertex3f(0.38, 1.08, 1.1);
   glVertex3f(0.38, 1.08, 0);
   glVertex3f(-0.38, 1.08, 0);
   glVertex3f(-0.38, 1.08, 1.1);

   glEnd();

   glBegin(GL_POLYGON);
   
   glVertex3f(0.38, 0, 1.1);
   glVertex3f(0.38, 0, 0);
   glVertex3f(-0.38, 0, 0);
   glVertex3f(-0.38, 0, 1.1);

   glEnd();

   // -----------------------------------Window Frame x-dir

   glBegin(GL_POLYGON);
   
   glVertex3f(0.38, 2.75, 1.01);
   glVertex3f(0.30, 2.75, 1.01);
   glVertex3f(0.30, 4, 1.01);
   glVertex3f(0.38, 4, 1.01);

   glEnd();

   glBegin(GL_POLYGON);
   
   glVertex3f(-0.38, 2.75, 1.01);
   glVertex3f(-0.30, 2.75, 1.01);
   glVertex3f(-0.30, 4, 1.01);
   glVertex3f(-0.38, 4, 1.01);

   glEnd();

   glBegin(GL_POLYGON);
   
   glVertex3f(0.38, 4, 1.01);
   glVertex3f(-0.38, 4, 1.01);
   glVertex3f(-0.38, 4.08, 1.01);
   glVertex3f(0.38, 4.08, 1.01);

   glEnd();

   glBegin(GL_POLYGON);
   
   glVertex3f(0.38, 4, 1.01);
   glVertex3f(-0.38, 4, 1.01);
   glVertex3f(-0.38, 4.08, 1.01);
   glVertex3f(0.38, 4.08, 1.01);

   glEnd();

   glBegin(GL_POLYGON);
   
   glVertex3f(0.38, 2.75, 1.01);
   glVertex3f(-0.38, 2.75, 1.01);
   glVertex3f(-0.38, 2.67, 1.01);
   glVertex3f(0.38, 2.67, 1.01);

   glEnd();

   // -------------------------------------Window Frame z-dir

   glBegin(GL_POLYGON);
   
   glVertex3f(0.38, 4.08, 1.01);
   glVertex3f(0.38, 2.67, 1.01);
   glVertex3f(0.38, 2.67, 0);
   glVertex3f(0.38, 4.08, 0);

   glEnd();

   glBegin(GL_POLYGON);
   
   glVertex3f(-0.38, 4.08, 1.01);
   glVertex3f(-0.38, 2.67, 1.01);
   glVertex3f(-0.38, 2.67, 0);
   glVertex3f(-0.38, 4.08, 0);

   glEnd();

   glBegin(GL_POLYGON);
   
   glVertex3f(0.38, 4.08, 1.01);
   glVertex3f(0.38, 4.08, 0);
   glVertex3f(-0.38, 4.08, 0);
   glVertex3f(-0.38, 4.08, 1.01);

   glEnd();

   glBegin(GL_POLYGON);
   
   glVertex3f(0.38, 2.67, 1.01);
   glVertex3f(0.38, 2.67, 0);
   glVertex3f(-0.38, 2.67, 0);
   glVertex3f(-0.38, 2.67, 1.01);

   glEnd();

   //------------------------------------Roof

   glColor4f(0.22,0.14,0.05,1);

   glBegin(GL_POLYGON);
   
   for (int theta = 0; theta < 360; theta++) {
      glVertex3f(1.1 * Sin(theta), 4.5, 1.1 * Cos(theta));
   }

   glEnd();


   glBegin(GL_TRIANGLE_FAN);
   
   for (int theta = 0; theta < 360; theta++) {
      glVertex3f(1.1 * Sin(theta), 4.5, 1.1 * Cos(theta));
      glVertex3f(0, 5.5, 0);
   }

   glEnd();

   // -----------------------------Door

   glBegin(GL_POLYGON);
   
   glVertex3f(0.3, 0, 1.1);
   glVertex3f(-0.3, 0, 1.1);
   glVertex3f(-0.3, 1, 1.1);
   glVertex3f(0.3, 1, 1.1);

   glEnd();

   // ------------------------------Window

   glColor4f(0.5,0.5,1,1);

   glBegin(GL_POLYGON);
   
   glVertex3f(0.3, 2.75, 1.01);
   glVertex3f(-0.3, 2.75, 1.01);
   glVertex3f(-0.3, 4, 1.01);
   glVertex3f(0.3, 4, 1.01);

   glEnd();

   // ------------------------Pole

   glColor4f(0.22,0.14,0.05,1);

   glBegin(GL_QUAD_STRIP);
   
   for (int theta = 0; theta < 360; theta++) {
      glVertex3f(0.05 * Sin(theta), 5, 0.05 * Cos(theta));
      glVertex3f(0.05 * Sin(theta), 6.25, 0.05 * Cos(theta));
   }

   glEnd();

   glBegin(GL_POLYGON);
   
   for (int theta = 0; theta < 360; theta++) {
      glVertex3f(0.05 * Sin(theta), 6.25, 0.05 * Cos(theta));
   }

   glEnd();

   // ----------------------------------Flag

   glColor4f(1,0,0,1);

   glBegin(GL_TRIANGLES);
   
   glVertex3f(0, 6.25, 0);
   glVertex3f(0, 5.75, 0);
   glVertex3f(-1.2, 6, 0);

   glEnd();

   //  Undo transformations
   glPopMatrix();
}


/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   const double len=1.5;  //  Length of axes
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();

   glOrtho(-2, 2, -2, 2, -6, 6);
   // gluLookAt(2, 2, 2, 1, 0, 1, 0, 1, 1); //Attempted to us gluLookAt but could not get parameters to view scene properly
   //  Set view angle
   glRotatef(ph,1,0,0);
   glRotatef(th,0,1,0);
   

   glColor4f(0.14,0.38,0.06,1);

   glBegin(GL_QUADS); //draws green, grassy ground for scene

   glVertex3f(1000, 0, -1000);
   glVertex3f(-1000, 0, -1000);
   glVertex3f(-1000, 0, 1000);
   glVertex3f(1000, 0, 1000);


   glEnd();
   
   scene(1,0,1 , 0.5,0.5,0.5 , 0);
   scene(-1,0,1.2 , 0.75,0.75,0.75 , 22.5);
   scene(-3.5,0,1.8 , 1,1,1 , 45);
         
   
   glColor3f(1,1,1);
   //  Draw axes
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Five pixels from the lower left corner of the window
   glWindowPos2i(5,5);
   Print("View Angle=%d,%d",th,ph);
   //  Render the scene
   glFlush();
   //  Make the rendered scene visible
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
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
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0') {
      th = -205;
      ph = -40;
    }
   else if (ch == '1') {
      th = -195;
      ph = -5;
    }
   else if (ch == '2') {
      th = -160;
      ph = -25;
    }
   //  Toggle axes
   else if (ch == 'a' || ch == 'A')
      axes = 1-axes;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   const double dim=2.5;
   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection
   glOrtho(-w2h*dim,+w2h*dim, -dim,+dim, -dim,+dim);
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
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitWindowSize(1000,750);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   //  Create the window
   glutCreateWindow("HW3: Kolin Newby");
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
   return 0;
}
