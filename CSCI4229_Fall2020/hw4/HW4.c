/*
 *  HW4
 *
 *  Draws Scene with 1st person, perspective, and orthoganal views.
 *
 *       Key bindings
           1                  Select 1st person view
           2                  Select Perspective View
           3                  Select Orthogonal View
           +/-                Changes field of view for perspective
           a                  Toggle axes
           arrows             hange view angle
           PgDn/PgUp or w/s   Zoom in and out
           0                  Reset view angle
           ESC                Exit


Work Cited:

This homework assignment heavily draws on my personal work from homework 3, from example 9 given in class, and lecture slides also provided in class

Time Taken:

This assignment took me roughly 3 hours and 30 minutes to complete.

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

int axes=0;       //  Display axes
int mode=1;       //  Projection mode
int th=0;         //  Azimuth of view angle
int ph=30;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=5.0;   //  Size of world

const char* text[] = {"1st Person","Perspective","Orthogonal"};

double Ex,Ey,Ez = 0;
double Cx,Cy,Cz = 0;


//  Macro for sin & cos in degrees
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

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

/*
 *  Set projection
 */
static void Project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  1st person
   if (mode == 1)
      gluPerspective(fov,asp,dim/4,4*dim);
   //  Perspective transformation
   else if (mode == 2)
      gluPerspective(fov,asp,dim/4,4*dim);
   //  Orthogonal projection
   else
      glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

// From my HW3...
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
   //  Perspective - set eye position
   if (mode == 1)
   {
      if (Ex == 0 && Ey == 0 && Ez == 0) 
      {
         Ex = -2*dim*Sin(th)*Cos(ph);
         Ey = +2*dim        *Sin(ph);
         Ez = +2*dim*Cos(th)*Cos(ph);
      }

      Cx = 2 * dim * Sin(th) + (Ex);
      Cz = -2 * dim * Cos(th) + (Ez);

      gluLookAt(Ex,Ey,Ez , Cx,Cy,Cz , 0,Cos(ph),0);
   }
   else if (mode == 2) 
   {
      Ex = -2*dim*Sin(th)*Cos(ph);
      Ey = +2*dim        *Sin(ph);
      Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }
   //  Draw scene

   glColor4f(0.14,0.38,0.06,1);

   glBegin(GL_QUADS); //draws green, grassy ground for scene

   glVertex3f(10000, 0, -10000);
   glVertex3f(-10000, 0, -10000);
   glVertex3f(-10000, 0, 10000);
   glVertex3f(10000, 0, 10000);


   glEnd();

   scene(0,0,0 , 0.6,0.6,0.6 , 0);
   scene(2,0,-1 , 0.6,0.6,0.6 , 0);
   scene(4,0,1 , 0.6,0.6,0.6 , 0);

   //  Draw axes
   glColor3f(1,1,1);
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
   //  Display parameters
   glWindowPos2i(5,5);
   Print("th=%d, ph=%d  Dim=%.1f FOV=%d Projection=%s",th,ph,dim,fov,text[mode - 1]);
   //  Render the scene and make it visible
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
   {
      th += 5;

      // if (mode == 1)
      // {
      //    Cz -= Sin(5);
      //    Cx += Cos(5);
      // }
      
   }
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
   {
      th -= 5;

      // if (mode == 1) 
      // {
      //    Cz += Sin(5);
      //    Cx -= Cos(5);
      // }
   }
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      if (mode != 1)
         ph += 5;
      else 
      {
         Ez -= Cos(th);
         Cz -= Cos(th);
         Ex += Sin(th);
         Cx += Sin(th);
      }
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      if (mode != 1)
         ph -= 5;
      else {
         Ez += Cos(th);
         Cz += Cos(th);
         Ex -= Sin(th);
         Cx -= Sin(th);
      }
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_UP)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_DOWN && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project();
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
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'a' || ch == 'A')
      axes = 1-axes;
   //  Select display mode 1
   else if (ch == '1')
      mode = 1;
   //  Select display mode 2
   else if (ch == '2')
      mode = 2;
   //  Select display mode 3
   else if (ch == '3')
      mode = 3;
   //  PageUp key - increase dim
   else if (ch == 's')
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (ch == 'w' && dim>1)
      dim -= 0.1;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   //  Reproject
   Project();
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(1000,900);
   glutCreateWindow("HW4: Kolin Newby");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}
