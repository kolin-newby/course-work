/*
 *  Homework 6
 *
 *  Creates a simple scene with lighting and textures.
 *
 *  Key bindings:
 *  l          Toggle lighting on/off
 *  t          Change textures
 *  m          Toggles texture mode modulate/replace
 *  a/A        decrease/increase ambient light
 *  d/D        decrease/increase diffuse light
 *  s/S        decrease/increase specular light
 *  e/E        decrease/increase emitted light
 *  n/N        Decrease/increase shininess
 *  []         Lower/rise light
 *  x          Toggle axes
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"
int mode=0;       //  Texture mode
int axes=1;       //  Display axes
int th=-30;         //  Azimuth of view angle
int ph=30;         //  Elevation of view angle
int light=1;      //  Lighting
int rep=1;        //  Repitition
double asp=1;     //  Aspect ratio
double dim=4.5;   //  Size of world
// Light values
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;    // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light
unsigned int texture[7]; // Texture names


static void scene(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glColor3f(1,1,1);
   
   glBegin(GL_POLYGON);
   
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0);
   glTexCoord2f(0,1);
   for (int theta = 0; theta < 360; theta++) {
      glTexCoord2f(0.5 * Cos(theta) + 0.5,0.5 * Sin(theta) + 0.5); glVertex3f(Sin(theta), 0, Cos(theta));
   }

   glEnd();

   glBegin(GL_QUAD_STRIP);
   
   for (int theta = 0; theta < 361; theta++) {
      glNormal3f(Sin(theta),0,Cos(theta));
      glTexCoord2f(theta/67.5,0); glVertex3f(Sin(theta), 0, Cos(theta));
      glTexCoord2f(theta/67.5,6); glVertex3f(Sin(theta), 4.5, Cos(theta));
   }

   glEnd();

   // -------------------------------Door Frame x-dir

   glBegin(GL_POLYGON);
   
   glNormal3f(0,0,1);

   glTexCoord2f(0.08,0); glVertex3f(0.38, 0, 1.1);
   glTexCoord2f(0,0); glVertex3f(0.30, 0, 1.1);
   glTexCoord2f(0,1); glVertex3f(0.30, 1, 1.1);
   glTexCoord2f(0.08,1); glVertex3f(0.38, 1, 1.1);

   glEnd();

   glBegin(GL_POLYGON);
   
   glNormal3f(0,0,1);

   glTexCoord2f(0.08,0); glVertex3f(-0.38, 0, 1.1);
   glTexCoord2f(0,0); glVertex3f(-0.30, 0, 1.1);
   glTexCoord2f(0,1); glVertex3f(-0.30, 1, 1.1);
   glTexCoord2f(0.08,1); glVertex3f(-0.38, 1, 1.1);

   glEnd();

   glBegin(GL_POLYGON);
   
   glNormal3f(0,0,1);

   glTexCoord2f(0.76,0); glVertex3f(0.38, 1, 1.1);
   glTexCoord2f(0,0); glVertex3f(-0.38, 1, 1.1);
   glTexCoord2f(0,0.08); glVertex3f(-0.38, 1.08, 1.1);
   glTexCoord2f(0.76,0.08); glVertex3f(0.38, 1.08, 1.1);

   glEnd();

   glBegin(GL_POLYGON);
   
   glNormal3f(0,0,1);

   glTexCoord2f(0.76,0); glVertex3f(0.38, 1, 1.1);
   glTexCoord2f(0,0); glVertex3f(-0.38, 1, 1.1);
   glTexCoord2f(0,0.08); glVertex3f(-0.38, 1.08, 1.1);
   glTexCoord2f(0.76,0.08); glVertex3f(0.38, 1.08, 1.1);

   glEnd();

   // --------------------------Door Frame z-dir

   glBegin(GL_POLYGON);
   
   glNormal3f(1,0,0);

   glTexCoord2f(1.1,1.08); glVertex3f(0.38, 1.08, 1.1); //glTexCoord2f(z,y); 
   glTexCoord2f(1.1,0); glVertex3f(0.38, 0, 1.1);
   glTexCoord2f(0,0); glVertex3f(0.38, 0, 0);
   glTexCoord2f(0,1.08); glVertex3f(0.38, 1.08, 0);

   glEnd();

   glBegin(GL_POLYGON);
   
   glNormal3f(-1,0,0);

   glTexCoord2f(1.1,1.08); glVertex3f(-0.38, 1.08, 1.1); //glTexCoord2f(z,y); 
   glTexCoord2f(1.1,0); glVertex3f(-0.38, 0, 1.1);
   glTexCoord2f(0,0); glVertex3f(-0.38, 0, 0);
   glTexCoord2f(0,1.08); glVertex3f(-0.38, 1.08, 0);

   glEnd();

   glBegin(GL_POLYGON);
   
   glNormal3f(0,1,0);

   glTexCoord2f(1.1,0.76); glVertex3f(0.38, 1.08, 1.1); //glTexCoord2f(z,x);
   glTexCoord2f(0,0.76); glVertex3f(0.38, 1.08, 0);
   glTexCoord2f(0,0); glVertex3f(-0.38, 1.08, 0);
   glTexCoord2f(1.1,0); glVertex3f(-0.38, 1.08, 1.1);

   glEnd();

   glBegin(GL_POLYGON);
   
   glNormal3f(0,-1,0);

   glTexCoord2f(1.1,0.76); glVertex3f(0.38, 0, 1.1); //glTexCoord2f(z,x);
   glTexCoord2f(0,0.76); glVertex3f(0.38, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-0.38, 0, 0);
   glTexCoord2f(1.1,0); glVertex3f(-0.38, 0, 1.1);

   glEnd();

   // -----------------------------------Window Frame x-dir

   glBegin(GL_POLYGON);
   
   glNormal3f(0,0,1);

   glTexCoord2f(0.08,0); glVertex3f(0.38, 2.75, 1.01);
   glTexCoord2f(0,0); glVertex3f(0.30, 2.75, 1.01);
   glTexCoord2f(0,1.25); glVertex3f(0.30, 4, 1.01);
   glTexCoord2f(0.08,1.25); glVertex3f(0.38, 4, 1.01);

   glEnd();

   glBegin(GL_POLYGON);
   
   glNormal3f(0,0,1);

   glTexCoord2f(0,0); glVertex3f(-0.38, 2.75, 1.01);
   glTexCoord2f(0.08,0); glVertex3f(-0.30, 2.75, 1.01);
   glTexCoord2f(0.08,1.25); glVertex3f(-0.30, 4, 1.01);
   glTexCoord2f(0,1.25); glVertex3f(-0.38, 4, 1.01);

   glEnd();

   glBegin(GL_POLYGON);
   
   glNormal3f(0,0,1);

   glTexCoord2f(0.76,0); glVertex3f(0.38, 4, 1.01);
   glTexCoord2f(0,0); glVertex3f(-0.38, 4, 1.01);
   glTexCoord2f(0,0.08); glVertex3f(-0.38, 4.08, 1.01);
   glTexCoord2f(0.76,0.08); glVertex3f(0.38, 4.08, 1.01);

   glEnd();

   glBegin(GL_POLYGON);
   
   glNormal3f(0,0,1);

   glTexCoord2f(0.76,0); glVertex3f(0.38, 4, 1.01);
   glTexCoord2f(0,0); glVertex3f(-0.38, 4, 1.01);
   glTexCoord2f(0,0.08); glVertex3f(-0.38, 4.08, 1.01);
   glTexCoord2f(0.76,0.08); glVertex3f(0.38, 4.08, 1.01);

   glEnd();

   glBegin(GL_POLYGON);
   
   glNormal3f(0,0,1);

   glTexCoord2f(0.76,0.08); glVertex3f(0.38, 2.75, 1.01);
   glTexCoord2f(0,0.08); glVertex3f(-0.38, 2.75, 1.01);
   glTexCoord2f(0,0); glVertex3f(-0.38, 2.67, 1.01);
   glTexCoord2f(0.76,0); glVertex3f(0.38, 2.67, 1.01);

   glEnd();

   // -------------------------------------Window Frame z-dir

   glBegin(GL_POLYGON);
   
   glNormal3f(1,0,0);

   glTexCoord2f(1.01,1.41); glVertex3f(0.38, 4.08, 1.01);
   glTexCoord2f(1.01,0); glVertex3f(0.38, 2.67, 1.01);
   glTexCoord2f(0,0); glVertex3f(0.38, 2.67, 0);
   glTexCoord2f(0,1.41); glVertex3f(0.38, 4.08, 0);

   glEnd();

   glBegin(GL_POLYGON);
   
   glNormal3f(-1,0,0);

   glTexCoord2f(1.01,1.41); glVertex3f(-0.38, 4.08, 1.01);
   glTexCoord2f(1.01,0); glVertex3f(-0.38, 2.67, 1.01);
   glTexCoord2f(0,0); glVertex3f(-0.38, 2.67, 0);
   glTexCoord2f(0,1.41); glVertex3f(-0.38, 4.08, 0);

   glEnd();

   glBegin(GL_POLYGON);
   
   glNormal3f(0,1,0);

   glTexCoord2f(1.01,0.76); glVertex3f(0.38, 4.08, 1.01);
   glTexCoord2f(0,0.76); glVertex3f(0.38, 4.08, 0);
   glTexCoord2f(0,0); glVertex3f(-0.38, 4.08, 0);
   glTexCoord2f(1.01,0); glVertex3f(-0.38, 4.08, 1.01);

   glEnd();

   glBegin(GL_POLYGON);
   
   glNormal3f(0,-1,0);

   glTexCoord2f(1.01,0.67); glVertex3f(0.38, 2.67, 1.01);
   glTexCoord2f(0,0.67); glVertex3f(0.38, 2.67, 0);
   glTexCoord2f(0,0); glVertex3f(-0.38, 2.67, 0);
   glTexCoord2f(1.01,0); glVertex3f(-0.38, 2.67, 1.01);

   glEnd();

   //------------------------------------Roof

   glColor4f(0.22,0.14,0.05,1);

   glBindTexture(GL_TEXTURE_2D,texture[1]);

   glBegin(GL_POLYGON);
   
   glNormal3f(0,-1,0);
   for (int theta = 0; theta < 361; theta++) {
      glTexCoord2f((0.5 * Cos(theta) + 0.5) * 1.1,(0.5 * Sin(theta) + 0.5) * 1.1);
      glVertex3f(1.1 * Sin(theta), 4.5, 1.1 * Cos(theta));
   }

   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[2]);

   glBegin(GL_TRIANGLE_FAN);
   
   for (int theta = 0; theta < 362; theta++) {
      glNormal3f(Sin(theta),1,Cos(theta)); //45-45 triangle

      glTexCoord2f((Sin(theta)*0.5) + 0.5,(Cos(theta)*0.5) + 0.5); glVertex3f(1.1 * Sin(theta), 4.5, 1.1 * Cos(theta));

      glTexCoord2f(0.5, 0.5); glVertex3f(0, 5.6, 0);
   }

   glEnd();

   // -----------------------------Door

   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);

   glTexCoord2f(0.3,0); glVertex3f(0.3, 0, 1.1);
   glTexCoord2f(-0.3,0); glVertex3f(-0.3, 0, 1.1);
   glTexCoord2f(-0.3,1); glVertex3f(-0.3, 1, 1.1);
   glTexCoord2f(0.3,1); glVertex3f(0.3, 1, 1.1);

   glEnd();

   // ------------------------------Window

   glColor4f(0.5,0.5,1,1);

   glBindTexture(GL_TEXTURE_2D,texture[3]);

   glBegin(GL_POLYGON);
   
   glNormal3f(0,0,1);

   glTexCoord2f(0.48,0); glVertex3f(0.3, 2.75, 1.01);
   glTexCoord2f(0,0); glVertex3f(-0.3, 2.75, 1.01);
   glTexCoord2f(0,1); glVertex3f(-0.3, 4, 1.01);
   glTexCoord2f(0.48,1); glVertex3f(0.3, 4, 1.01);

   glEnd();

   // ------------------------Pole

   glColor4f(0.22,0.14,0.05,1);

   glBindTexture(GL_TEXTURE_2D,texture[4]);

   glBegin(GL_QUAD_STRIP);
   
   for (int theta = 0; theta < 361; theta++) {
      glNormal3f(Sin(theta),0,Cos(theta));
      glTexCoord2f(theta/360,1); glVertex3f(0.05 * Sin(theta), 5, 0.05 * Cos(theta));
      glTexCoord2f(theta/360,0); glVertex3f(0.05 * Sin(theta), 6.25, 0.05 * Cos(theta));
   }

   glEnd();

   glBegin(GL_POLYGON);
   
   glNormal3f(0,1,0);
   for (int theta = 0; theta < 361; theta++) {
      glTexCoord2f(0.5 * Cos(theta) + 0.5,0.5 * Sin(theta) + 0.5); glVertex3f(0.05 * Sin(theta), 6.25, 0.05 * Cos(theta));
   }

   glEnd();

   // ----------------------------------Flag

   glColor4f(1,0,0,1);

   glBindTexture(GL_TEXTURE_2D,texture[5]);

   glBegin(GL_TRIANGLES);
   
   glNormal3f(0,0,1);

   glTexCoord2f(0,1); glVertex3f(0, 6.25, 0);
   glTexCoord2f(0,0); glVertex3f(0, 5.75, 0);
   glTexCoord2f(1,0.5); glVertex3f(-1.2, 6, 0);

   glNormal3f(0,0,-1);

   glTexCoord2f(0,1); glVertex3f(0, 6.25, -0.001);
   glTexCoord2f(0,0); glVertex3f(0, 5.75, -0.001);
   glTexCoord2f(1,0.5); glVertex3f(-1.2, 6, -0.001);

   glEnd();

   glBindTexture(GL_TEXTURE_2D,0);

   //  Undo transformations
   glPopMatrix();
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius r
 */
static void ball(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glutSolidSphere(1.0,16,16);
   //  Undo transofrmations
   glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Length of axes
   const double len=2.0;
   //  Eye position
   double Ex = -2*dim*Sin(th)*Cos(ph);
   double Ey = +2*dim        *Sin(ph);
   double Ez = +2*dim*Cos(th)*Cos(ph);
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Set perspective
   glLoadIdentity();
   gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   //  Light switch
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light direction
      float Position[]  = {5*Cos(zh),ylight,5*Sin(zh),1};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 0.1);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
      glDisable(GL_LIGHTING);
   //  Draw scene
   scene(0,0,0 , 0.5,0.5,0.5 , 0);
   
   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
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
   Print("Angle=%d,%d  Dim=%.1f Light=%s Texture=%s",th,ph,dim,light?"On":"Off",mode?"Replace":"Modulate");
   if (light)
   {
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
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
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(45,asp,dim);
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
   {
      th = -30;
      ph = 30;
   }
   //  Toggle texture mode
   else if (ch == 'm' || ch == 'M')
      mode = 1-mode;
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;
   //  Ambient level
   else if (ch=='a' && ambient>0)
      ambient -= 5;
   else if (ch=='A' && ambient<100)
      ambient += 5;
   //  Diffuse level
   else if (ch=='d' && diffuse>0)
      diffuse -= 5;
   else if (ch=='D' && diffuse<100)
      diffuse += 5;
   //  Specular level
   else if (ch=='s' && specular>0)
      specular -= 5;
   else if (ch=='S' && specular<100)
      specular += 5;
   //  Emission level
   else if (ch=='e' && emission>0)
      emission -= 5;
   else if (ch=='E' && emission<100)
      emission += 5;
   //  Shininess level
   else if (ch=='n' && shininess>-1)
      shininess -= 1;
   else if (ch=='N' && shininess<7)
      shininess += 1;
   //  Repitition
   else if (ch=='+')
      rep++;
   else if (ch=='-' && rep>1)
      rep--;
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(45,asp,dim);
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
   Project(45,asp,dim);
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
   glutInitWindowSize(800,600);
   glutCreateWindow("HW6: Kolin Newby");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load textures
   texture[0] = LoadTexBMP("stone.bmp");
   texture[1] = LoadTexBMP("wood.bmp");
   texture[2] = LoadTexBMP("roof.bmp");
   texture[3] = LoadTexBMP("glass.bmp");
   texture[4] = LoadTexBMP("grain.bmp");
   texture[5] = LoadTexBMP("flag.bmp");
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
