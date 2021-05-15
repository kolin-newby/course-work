/*
 *  Semester Project
 *
 *  A detailed scene of a haunted mansion
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
int axes=0;       //  Display axes
int th=-20;         //  Azimuth of view angle
int ph=5;         //  Elevation of view angle
int light=1;      //  Lighting
int rep=1;        //  Repitition
double asp=1;     //  Aspect ratio
double dim=11;   //  Size of world
int turn=1;       //turn scene
int orbit=0;      //orbit moon
// Light values
int emission  =   0;  // Emission intensity (%)
int ambient   =  10;  // Ambient intensity (%)
int diffuse   = 120;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;    // Shininess (value)
int zh        =  100;  // Light azimuth
unsigned int texture[10]; // Texture names

static void turntable(int t)
{
   if (t)
   {
      th = th + 1;
   }
   else
      return;
}


static void window_1(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01 * emission,1.0};
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
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   

   // glVertex3f(x,y,z);

   //Z ortho------------------------------------------
   
   glBindTexture(GL_TEXTURE_2D,texture[4]); //glass

   // panes-----------------
   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(1,0); glVertex3f(3,0.2,0.05);
   glTexCoord2f(1,1); glVertex3f(3,3,0.05);
   glTexCoord2f(0,1); glVertex3f(0.2,3,0.05);
   glTexCoord2f(0,0); glVertex3f(0.2,0.2,0.05);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0,0); glVertex3f(-3,0.2,0.05);
   glTexCoord2f(0,1); glVertex3f(-3,3,0.05);
   glTexCoord2f(1,1); glVertex3f(-0.2,3,0.05);
   glTexCoord2f(1,0); glVertex3f(-0.2,0.2,0.05);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(1,1); glVertex3f(3,-0.2,0.05);
   glTexCoord2f(1,0); glVertex3f(3,-3,0.05);
   glTexCoord2f(0,0); glVertex3f(0.2,-3,0.05);
   glTexCoord2f(0,1); glVertex3f(0.2,-0.2,0.05);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0,1); glVertex3f(-3,-0.2,0.05);
   glTexCoord2f(0,0); glVertex3f(-3,-3,0.05);
   glTexCoord2f(1,0); glVertex3f(-0.2,-3,0.05);
   glTexCoord2f(1,1); glVertex3f(-0.2,-0.2,0.05);

   glEnd();

   // frame-----------------

   glBindTexture(GL_TEXTURE_2D,texture[1]); //wood grain

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0,0); glVertex3f(-0.2,3,0.2);
   glTexCoord2f(6.5,0); glVertex3f(-0.2,-3,0.2);
   glTexCoord2f(6.5,1); glVertex3f(0.2,-3,0.2);
   glTexCoord2f(0,1); glVertex3f(0.2,3,0.2);

   glEnd();   

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0,1); glVertex3f(-3,0.2,0.2);
   glTexCoord2f(2,1); glVertex3f(-0.2,0.2,0.2);
   glTexCoord2f(2,0); glVertex3f(-0.2,-0.2,0.2);
   glTexCoord2f(0,0); glVertex3f(-3,-0.2,0.2);

   glEnd();   

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(2,1); glVertex3f(3,0.2,0.2);
   glTexCoord2f(0,1); glVertex3f(0.2,0.2,0.2);
   glTexCoord2f(0,0); glVertex3f(0.2,-0.2,0.2);
   glTexCoord2f(2,0); glVertex3f(3,-0.2,0.2);

   glEnd();  

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(2,1); glVertex3f(3.25,3.25,0.2);
   glTexCoord2f(0,1); glVertex3f(-3.25,3.25,0.2);
   glTexCoord2f(0,0); glVertex3f(-3.25,3,0.2);
   glTexCoord2f(2,0); glVertex3f(3.25,3,0.2);

   glEnd(); 

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(2,0); glVertex3f(3.25,-3.25,0.2);
   glTexCoord2f(0,0); glVertex3f(-3.25,-3.25,0.2);
   glTexCoord2f(0,1); glVertex3f(-3.25,-3,0.2);
   glTexCoord2f(2,1); glVertex3f(3.25,-3,0.2);

   glEnd(); 

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0,0); glVertex3f(3,-3,0.2);
   glTexCoord2f(1,0); glVertex3f(3.25,-3,0.2);
   glTexCoord2f(1,2); glVertex3f(3.25,3,0.2);
   glTexCoord2f(0,2); glVertex3f(3,3,0.2);

   glEnd();  

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(1,0); glVertex3f(-3,-3,0.2);
   glTexCoord2f(0,0); glVertex3f(-3.25,-3,0.2);
   glTexCoord2f(0,2); glVertex3f(-3.25,3,0.2);
   glTexCoord2f(1,2); glVertex3f(-3,3,0.2);

   glEnd();

   //X ortho------------------------------------------

   glBegin(GL_POLYGON);

   glNormal3f(-1,0,0);
   
   glTexCoord2f(0.2,0); glVertex3f(-3.25,-3.25,0.2);
   glTexCoord2f(0.2,2); glVertex3f(-3.25,3.25,0.2);
   glTexCoord2f(0,2); glVertex3f(-3.25,3.25,0);
   glTexCoord2f(0,0); glVertex3f(-3.25,-3.25,0);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(1,0,0);
   
   glTexCoord2f(0.2,0); glVertex3f(3.25,-3.25,0.2);
   glTexCoord2f(0.2,2); glVertex3f(3.25,3.25,0.2);
   glTexCoord2f(0,2); glVertex3f(3.25,3.25,0);
   glTexCoord2f(0,0); glVertex3f(3.25,-3.25,0);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(-1,0,0);
   
   glTexCoord2f(0.2,0); glVertex3f(3,-3.25,0.2);
   glTexCoord2f(0.2,2); glVertex3f(3,3.25,0.2);
   glTexCoord2f(0,2); glVertex3f(3,3.25,0);
   glTexCoord2f(0,0); glVertex3f(3,-3.25,0);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(1,0,0);
   
   glTexCoord2f(0.2,0); glVertex3f(-3,-3.25,0.2);
   glTexCoord2f(0.2,2); glVertex3f(-3,3.25,0.2);
   glTexCoord2f(0,2); glVertex3f(-3,3.25,0);
   glTexCoord2f(0,0); glVertex3f(-3,-3.25,0);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(1,0,0);
   
   glTexCoord2f(0.2,0); glVertex3f(0.2,-3.25,0.2);
   glTexCoord2f(0.2,2); glVertex3f(0.2,3.25,0.2);
   glTexCoord2f(0,2); glVertex3f(0.2,3.25,0);
   glTexCoord2f(0,0); glVertex3f(0.2,-3.25,0);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(-1,0,0);
   
   glTexCoord2f(0.2,0); glVertex3f(-0.2,-3.25,0.2);
   glTexCoord2f(0.2,2); glVertex3f(-0.2,3.25,0.2);
   glTexCoord2f(0,2); glVertex3f(-0.2,3.25,0);
   glTexCoord2f(0,0); glVertex3f(-0.2,-3.25,0);

   glEnd();

   //Y ortho------------------------------------------

   glBegin(GL_POLYGON);

   glNormal3f(0,1,0);
   
   glTexCoord2f(0,0.2); glVertex3f(-3.25,3.25,0.2);
   glTexCoord2f(0,0); glVertex3f(-3.25,3.25,0);
   glTexCoord2f(2,0); glVertex3f(3.25,3.25,0);
   glTexCoord2f(2,0.2); glVertex3f(3.25,3.25,0.2);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(0,-1,0);
   
   glTexCoord2f(0,0.2); glVertex3f(-3.25,3,0.2);
   glTexCoord2f(0,0); glVertex3f(-3.25,3,0);
   glTexCoord2f(2,0); glVertex3f(3.25,3,0);
   glTexCoord2f(2,0.2); glVertex3f(3.25,3,0.2);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(0,1,0);
   
   glTexCoord2f(0,0.2); glVertex3f(-3.25,0.2,0.2);
   glTexCoord2f(0,0); glVertex3f(-3.25,0.2,0);
   glTexCoord2f(2,0); glVertex3f(3.25,0.2,0);
   glTexCoord2f(2,0.2); glVertex3f(3.25,0.2,0.2);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(0,-1,0);
   
   glTexCoord2f(0,0.2); glVertex3f(-3.25,-0.2,0.2);
   glTexCoord2f(0,0); glVertex3f(-3.25,-0.2,0);
   glTexCoord2f(2,0); glVertex3f(3.25,-0.2,0);
   glTexCoord2f(2,0.2); glVertex3f(3.25,-0.2,0.2);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(0,1,0);
   
   glTexCoord2f(0,0.2); glVertex3f(-3.25,-3,0.2);
   glTexCoord2f(0,0); glVertex3f(-3.25,-3,0);
   glTexCoord2f(2,0); glVertex3f(3.25,-3,0);
   glTexCoord2f(2,0.2); glVertex3f(3.25,-3,0.2);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(0,-1,0);
   
   glTexCoord2f(0,0.2); glVertex3f(-3.25,-3.25,0.2);
   glTexCoord2f(0,0); glVertex3f(-3.25,-3.25,0);
   glTexCoord2f(2,0); glVertex3f(3.25,-3.25,0);
   glTexCoord2f(2,0.2); glVertex3f(3.25,-3.25,0.2);

   glEnd();

   //  Undo transformations
   glPopMatrix();
}



static void window_2(double x,double y,double z,
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
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   

   // glVertex3f(x,y,z);

   //Z ortho------------------------------------------
   
   glBindTexture(GL_TEXTURE_2D,texture[4]); //glass

   // panes-----------------
   
   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);

   for (int theta = 0; theta < 361; theta++) {

      glTexCoord2f(Sin(theta), Cos(theta)); glVertex3f(3*Sin(theta), 3*Cos(theta), 0.05);
   }

   glEnd();

   // frame-----------------

   glBindTexture(GL_TEXTURE_2D,texture[1]); //wood grain

   //Curve

   glBegin(GL_QUAD_STRIP);

   for (int theta = 0; theta < 361; theta++) {
      glNormal3f(-Sin(theta),-Cos(theta),0);

      glTexCoord2f(2*acos(-1)*theta/90,0); glVertex3f(3*Sin(theta), 3*Cos(theta), 0);
      glTexCoord2f(2*acos(-1)*theta/90,0.2); glVertex3f(3*Sin(theta), 3*Cos(theta), 0.2);
   }

   glEnd();

   glBegin(GL_QUAD_STRIP);

   for (int theta = 0; theta < 361; theta++) {
      glNormal3f(Sin(theta),Cos(theta),0);

      glTexCoord2f((2*acos(-1)*theta)/360,0); glVertex3f(3.3*Sin(theta), 3.3*Cos(theta), 0);
      glTexCoord2f((2*acos(-1)*theta)/360,0.2); glVertex3f(3.3*Sin(theta), 3.3*Cos(theta), 0.2);
   }

   glEnd();

   glBegin(GL_QUAD_STRIP);

   glNormal3f(0,0,1);

   for (int theta = 0; theta < 361; theta++) {
      glTexCoord2f((2*acos(-1)*theta)/360,0); glVertex3f(3*Sin(theta), 3*Cos(theta), 0.2);
      glTexCoord2f((2*acos(-1)*theta)/360,0.3); glVertex3f(3.3*Sin(theta), 3.3*Cos(theta), 0.2);
   }

   glEnd();

   //Z ortho

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0,0); glVertex3f(-0.2,3,0.2);
   glTexCoord2f(6.5,0); glVertex3f(-0.2,-3,0.2);
   glTexCoord2f(6.5,1); glVertex3f(0.2,-3,0.2);
   glTexCoord2f(0,1); glVertex3f(0.2,3,0.2);

   glEnd();   

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0,1); glVertex3f(-3,0.2,0.2);
   glTexCoord2f(2,1); glVertex3f(-0.2,0.2,0.2);
   glTexCoord2f(2,0); glVertex3f(-0.2,-0.2,0.2);
   glTexCoord2f(0,0); glVertex3f(-3,-0.2,0.2);

   glEnd();   

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(2,1); glVertex3f(3,0.2,0.2);
   glTexCoord2f(0,1); glVertex3f(0.2,0.2,0.2);
   glTexCoord2f(0,0); glVertex3f(0.2,-0.2,0.2);
   glTexCoord2f(2,0); glVertex3f(3,-0.2,0.2);

   glEnd();  

   //X ortho------------------------------------------

   glBegin(GL_POLYGON);

   glNormal3f(1,0,0);
   
   glTexCoord2f(0.2,0); glVertex3f(0.2,-3.21,0.2);
   glTexCoord2f(0.2,2); glVertex3f(0.2,3.21,0.2);
   glTexCoord2f(0,2); glVertex3f(0.2,3.21,0);
   glTexCoord2f(0,0); glVertex3f(0.2,-3.21,0);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(-1,0,0);
   
   glTexCoord2f(0.2,0); glVertex3f(-0.2,-3.21,0.2);
   glTexCoord2f(0.2,2); glVertex3f(-0.2,3.21,0.2);
   glTexCoord2f(0,2); glVertex3f(-0.2,3.21,0);
   glTexCoord2f(0,0); glVertex3f(-0.2,-3.21,0);

   glEnd();

   //Y ortho------------------------------------------

   glBegin(GL_POLYGON);

   glNormal3f(0,1,0);
   
   glTexCoord2f(0,0.2); glVertex3f(-3.21,0.2,0.2);
   glTexCoord2f(0,0); glVertex3f(-3.21,0.2,0);
   glTexCoord2f(2,0); glVertex3f(3.21,0.2,0);
   glTexCoord2f(2,0.2); glVertex3f(3.21,0.2,0.2);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(0,-1,0);
   
   glTexCoord2f(0,0.2); glVertex3f(-3.21,-0.2,0.2);
   glTexCoord2f(0,0); glVertex3f(-3.21,-0.2,0);
   glTexCoord2f(2,0); glVertex3f(3.21,-0.2,0);
   glTexCoord2f(2,0.2); glVertex3f(3.21,-0.2,0.2);

   glEnd();

   //  Undo transformations
   glPopMatrix();
}


static void door(double x,double y,double z,
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
   glBindTexture(GL_TEXTURE_2D,texture[8]); //door
   

   //Z ortho--------------------

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(1,0); glVertex3f(2,0,0.05);
   glTexCoord2f(0,0); glVertex3f(-2,0,0.05);
   glTexCoord2f(0,1); glVertex3f(-2,8,0.05);
   glTexCoord2f(1,1); glVertex3f(2,8,0.05);

   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[1]); //wood grain

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0,0); glVertex3f(-2,8,0.15);
   glTexCoord2f(1,0); glVertex3f(2,8,0.15);
   glTexCoord2f(1,0.15); glVertex3f(2,8.15,0.15);
   glTexCoord2f(0,0.15); glVertex3f(-2,8.15,0.15);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0,0.15); glVertex3f(2.15,0,0.15);
   glTexCoord2f(0,0); glVertex3f(2,0,0.15);
   glTexCoord2f(2.2,0); glVertex3f(2,8.15,0.15);
   glTexCoord2f(2.2,0.15); glVertex3f(2.15,8.15,0.15);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0,0.15); glVertex3f(-2.15,0,0.15);
   glTexCoord2f(0,0); glVertex3f(-2,0,0.15);
   glTexCoord2f(2.2,0); glVertex3f(-2,8.15,0.15);
   glTexCoord2f(2.2,0.15); glVertex3f(-2.15,8.15,0.15);

   glEnd();

   //X ortho----------------------

   glBegin(GL_POLYGON);

   glNormal3f(1,0,0);
   
   glTexCoord2f(2.2,0.15); glVertex3f(-2,8.15,0.15);
   glTexCoord2f(0,0.15); glVertex3f(-2,0,0.15);
   glTexCoord2f(0,0); glVertex3f(-2,0,0);
   glTexCoord2f(2.2,0); glVertex3f(-2,8.15,0);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(-1,0,0);
   
   glTexCoord2f(2.2,0.15); glVertex3f(-2.15,8.15,0.15);
   glTexCoord2f(0,0.15); glVertex3f(-2.15,0,0.15);
   glTexCoord2f(0,0); glVertex3f(-2.15,0,0);
   glTexCoord2f(2.2,0); glVertex3f(-2.15,8.15,0);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(1,0,0);
   
   glTexCoord2f(2.2,0.15); glVertex3f(2.15,8.15,0.15);
   glTexCoord2f(0,0.15); glVertex3f(2.15,0,0.15);
   glTexCoord2f(0,0); glVertex3f(2.15,0,0);
   glTexCoord2f(2.2,0); glVertex3f(2.15,8.15,0);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(-1,0,0);
   
   glTexCoord2f(2.2,0.15); glVertex3f(2,8.15,0.15);
   glTexCoord2f(0,0.15); glVertex3f(2,0,0.15);
   glTexCoord2f(0,0); glVertex3f(2,0,0);
   glTexCoord2f(2.2,0); glVertex3f(2,8.15,0);

   glEnd();

   //Y ortho-----------

   glBegin(GL_POLYGON);

   glNormal3f(0,1,0);
   
   glTexCoord2f(1,0.15); glVertex3f(2.15,8.15,0.15);
   glTexCoord2f(0,0.15); glVertex3f(-2.15,8.15,0.15);
   glTexCoord2f(0,0); glVertex3f(-2.15,8.15,0);
   glTexCoord2f(1,0); glVertex3f(2.15,8.15,0);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(0,-1,0);
   
   glTexCoord2f(1,0.15); glVertex3f(2.15,8,0.15);
   glTexCoord2f(0,0.15); glVertex3f(-2.15,8,0.15);
   glTexCoord2f(0,0); glVertex3f(-2.15,8,0);
   glTexCoord2f(1,0); glVertex3f(2.15,8,0);

   glEnd();

   //  Undo transformations
   glPopMatrix();
}


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

   float frnt_sec = -10.25;
   float tow_x = 9;
   float tow_y = -14.25;

   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   
   glColor3f(0.4,0.4,0.4);

   // glVertex3f(x,y,z);

   //Ground

   glBegin(GL_POLYGON);

   glNormal3f(0,1,0);
   
   glTexCoord2f(0,0); glVertex3f(-1000,0,-1000);
   glTexCoord2f(0,250); glVertex3f(-1000,0,1000);
   glTexCoord2f(250,250); glVertex3f(1000,0,1000);
   glTexCoord2f(0,250); glVertex3f(1000,0,-1000);

   glEnd();
   

   // --------Front (z-axis)---------------------------------------------------------------------------------------

   glBindTexture(GL_TEXTURE_2D,texture[3]); //brick

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0,0); glVertex3f(-8,0,2);
   glTexCoord2f(3,0); glVertex3f(-0.75,0,2);
   glTexCoord2f(3,0.580645*3); glVertex3f(-0.75,4.5,2);
   glTexCoord2f(0.5*3,3); glVertex3f(-4.375,7.75,2);
   glTexCoord2f(0,0.580645*3); glVertex3f(-8,4.5,2);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0,0); glVertex3f(8,0,2);
   glTexCoord2f(3,0); glVertex3f(0.75,0,2);
   glTexCoord2f(3,0.580645*3); glVertex3f(0.75,4.5,2);
   glTexCoord2f(0.5*3,3); glVertex3f(4.375,7.75,2);
   glTexCoord2f(0,0.580645*3); glVertex3f(8,4.5,2);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0 , 0); glVertex3f(-1.25,0,2.5);
   glTexCoord2f(2 , 0); glVertex3f(1.25,0,2.5);
   glTexCoord2f(2 , 0.667*2); glVertex3f(1.25,4,2.5);
   glTexCoord2f(0.5*2 , 2); glVertex3f(0,6,2.5);
   glTexCoord2f(0 , 0.667*2); glVertex3f(-1.25,4,2.5);

   glEnd();


   // ----------------------------------Back (z-axis)---------------------------------------------------------


   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0 , 0); glVertex3f(-9,0,-6.25);
   glTexCoord2f(0 , 2.2); glVertex3f(-9,6.5,-6.25);
   glTexCoord2f(7 , 2.2); glVertex3f(9,6.5,-6.25);
   glTexCoord2f(7 , 0); glVertex3f(9,0,-6.25);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(0,0,-1);
   
   glTexCoord2f(0 , 0); glVertex3f(-9,0,-14.25);
   glTexCoord2f(0 , 2.2); glVertex3f(-9,6.5,-14.25);
   glTexCoord2f(7 , 2.2); glVertex3f(9,6.5,-14.25);
   glTexCoord2f(7 , 0); glVertex3f(9,0,-14.25);

   glEnd();


   // ----------------------------------Back (x-axis)---------------------------------------------------------


   glBegin(GL_POLYGON);

   glNormal3f(-1,0,0);
   
   glTexCoord2f(0 , 0); glVertex3f(-9,0,-6.25);
   glTexCoord2f(3 , 0); glVertex3f(-9,0,-14.25);
   glTexCoord2f(3 , 0.556869*3.2); glVertex3f(-9,6.5,-14.25);
   glTexCoord2f(0.5*3 , 3.2); glVertex3f(-9,11.6724,-10.25);
   glTexCoord2f(0 , 0.556869*3.2); glVertex3f(-9,6.5,-6.25);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(1,0,0);
   
   glTexCoord2f(0 , 0); glVertex3f(9,0,-6.25);
   glTexCoord2f(3 , 0); glVertex3f(9,0,-14.25);
   glTexCoord2f(3 , 0.556869*3.2); glVertex3f(9,6.5,-14.25);
   glTexCoord2f(0.5*3 , 3.2); glVertex3f(9,11.6724,-10.25);
   glTexCoord2f(0 , 0.556869*3.2); glVertex3f(9,6.5,-6.25);

   glEnd();


   // --------------------Back Roofs-----------------------------------------

   glBindTexture(GL_TEXTURE_2D,texture[5]); //shingles

   glBegin(GL_POLYGON);

   glNormal3f(0,0.9375,1);
   
   glTexCoord2f(7 , 0); glVertex3f(9,6.5,-6.25);
   glTexCoord2f(7 , 3); glVertex3f(9,11.6724,-10.25);
   glTexCoord2f(0 , 3); glVertex3f(-9,11.6724,-10.25);
   glTexCoord2f(0 , 0); glVertex3f(-9,6.5,-6.25);

   glEnd();

   glBegin(GL_POLYGON);

   glNormal3f(0,0.9375,-1);
   
   glTexCoord2f(0 , 0); glVertex3f(9,6.5,-14.25);
   glTexCoord2f(0 , 3); glVertex3f(9,11.6724,-10.25);
   glTexCoord2f(7 , 3); glVertex3f(-9,11.6724,-10.25);
   glTexCoord2f(7 , 0); glVertex3f(-9,6.5,-14.25);

   glEnd();

   // ---------Front side walls--------------------------------------------------------------------------------------------------------

   glBindTexture(GL_TEXTURE_2D,texture[3]); //wht_brk

   glBegin(GL_POLYGON);

   glNormal3f(-1,0,0);
   
   glTexCoord2f(0.3 , 0); glVertex3f(-1.25,0,2.5);
   glTexCoord2f(0.3 , 1.4); glVertex3f(-1.25,4,2.5);
   glTexCoord2f(0 , 1.4); glVertex3f(-1.25,4,2);
   glTexCoord2f(0 , 0); glVertex3f(-1.25,0,2);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(1,0,0);
   
   glTexCoord2f(0.3 , 0); glVertex3f(1.25,0,2.5);
   glTexCoord2f(0.3 , 1.4); glVertex3f(1.25,4,2.5);
   glTexCoord2f(0 , 1.4); glVertex3f(1.25,4,2);
   glTexCoord2f(0 , 0); glVertex3f(1.25,0,2);

   glEnd();

   // --------------Front Roofs-----------------------------------------------------------------------------------------------

   // --------------Middle--------------------------------

   glBindTexture(GL_TEXTURE_2D,texture[5]); //shingles

   glBegin(GL_POLYGON);

   glNormal3f(0.625,1,0);
   
   glTexCoord2f(0 , 0); glVertex3f(1.25,4,2.5);
   glTexCoord2f(0 , 1.1); glVertex3f(0,6,2.5);
   glTexCoord2f(4.2 , 1.1); glVertex3f(0,6,frnt_sec);
   glTexCoord2f(4.2 , 0); glVertex3f(1.25,4,frnt_sec);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(-0.625,1,0);
   
   glTexCoord2f(0 , 0); glVertex3f(-1.25,4,2.5);
   glTexCoord2f(0 , 1.1); glVertex3f(0,6,2.5);
   glTexCoord2f(4.2 , 1.1); glVertex3f(0,6,frnt_sec);
   glTexCoord2f(4.2 , 0); glVertex3f(-1.25,4,frnt_sec);

   glEnd();

   // ------------Left------------------------------------

   glBegin(GL_POLYGON);

   glNormal3f(1,0.896552,0);
   
   glTexCoord2f(0 , 0); glVertex3f(-0.75,4.5,2);
   glTexCoord2f(0 , 2); glVertex3f(-4.375,7.75,2);
   glTexCoord2f(4.2 , 2); glVertex3f(-4.375,7.75,frnt_sec);
   glTexCoord2f(4.2 , 0); glVertex3f(-0.75,4.5,frnt_sec);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(-1,0.896552,0);
   
   glTexCoord2f(0 , 0); glVertex3f(-8,4.5,2);
   glTexCoord2f(0 , 2); glVertex3f(-4.375,7.75,2);
   glTexCoord2f(4.2 , 2); glVertex3f(-4.375,7.75,frnt_sec);
   glTexCoord2f(4.2 , 0); glVertex3f(-8,4.5,frnt_sec);

   glEnd();

// --------------Right-------------------------------------

   glBegin(GL_POLYGON);

   glNormal3f(-1,0.896552,0);
   
   glTexCoord2f(0 , 0); glVertex3f(0.75,4.5,2);
   glTexCoord2f(0 , 2); glVertex3f(4.375,7.75,2);
   glTexCoord2f(4.2 , 2); glVertex3f(4.375,7.75,frnt_sec);
   glTexCoord2f(4.2 , 0); glVertex3f(0.75,4.5,frnt_sec);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(1,0.896552,0);
   
   glTexCoord2f(0 , 0); glVertex3f(8,4.5,2);
   glTexCoord2f(0 , 2); glVertex3f(4.375,7.75,2);
   glTexCoord2f(4.2 , 2); glVertex3f(4.375,7.75,frnt_sec);
   glTexCoord2f(4.2 , 0); glVertex3f(8,4.5,frnt_sec);

   glEnd();


   // -------------------------------------------------------------------------------------------------------------
   // ----------Z (side) walls--------------------------------------------------------------------------------------------

   glBindTexture(GL_TEXTURE_2D,texture[3]); //brick

   glBegin(GL_POLYGON);

   glNormal3f(1,0,0);
   
   glTexCoord2f(0 , 0); glVertex3f(8,0,2);
   glTexCoord2f(0 , 2); glVertex3f(8,4.5,2);
   glTexCoord2f(5 , 2); glVertex3f(8,4.5,frnt_sec);
   glTexCoord2f(5 , 0); glVertex3f(8,0,frnt_sec);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(-1,0,0);
   
   glTexCoord2f(0 , 0); glVertex3f(-8,0,2);
   glTexCoord2f(0 , 2); glVertex3f(-8,4.5,2);
   glTexCoord2f(5 , 2); glVertex3f(-8,4.5,frnt_sec);
   glTexCoord2f(5 , 0); glVertex3f(-8,0,frnt_sec);

   glEnd();


   // ---------------------Left Chimney Stack

   glBindTexture(GL_TEXTURE_2D,texture[2]); //stone

   // ----------z-------
   glBegin(GL_POLYGON);

   glNormal3f(-1,0,0);
   
   glTexCoord2f(0 , 0); glVertex3f(-9.65,0,-12);
   glTexCoord2f(0 , 4); glVertex3f(-9.65,12,-12);
   glTexCoord2f(2 , 4); glVertex3f(-9.65,12,-7.75);
   glTexCoord2f(2 , 0); glVertex3f(-9.65,0,-7.75);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(1,0,0);
   
   glTexCoord2f(0 , 0); glVertex3f(-8.35,0,-12);
   glTexCoord2f(0 , 4); glVertex3f(-8.35,12,-12);
   glTexCoord2f(2 , 4); glVertex3f(-8.35,12,-7.75);
   glTexCoord2f(2 , 0); glVertex3f(-8.35,0,-7.75);

   glEnd();

   // --------------x

   glBegin(GL_POLYGON);

   glNormal3f(0,0,-1);
   
   glTexCoord2f(0 , 0); glVertex3f(-9.65,0,-12);
   glTexCoord2f(0 , 4); glVertex3f(-9.65,12,-12);
   glTexCoord2f(0.5 , 4); glVertex3f(-8.35,12,-12);
   glTexCoord2f(0.5 , 0); glVertex3f(-8.35,0,-12);

   glEnd();  


   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0 , 0); glVertex3f(-9.65,0,-7.75);
   glTexCoord2f(0 , 4); glVertex3f(-9.65,12,-7.75);
   glTexCoord2f(0.5 , 4); glVertex3f(-8.35,12,-7.75);
   glTexCoord2f(0.5 , 0); glVertex3f(-8.35,0,-7.75);

   glEnd();   

   // ---------------------y

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(2 , 0.5); glVertex3f(-9.65,12,-7.75);
   glTexCoord2f(0 , 0.5); glVertex3f(-9.65,12,-12);
   glTexCoord2f(0 , 0); glVertex3f(-8.35,12,-12);
   glTexCoord2f(2 , 0); glVertex3f(-8.35,12,-7.75);

   glEnd(); 

   // -----------------Chimney stacks------------

   glBindTexture(GL_TEXTURE_2D,texture[6]); //metal

   glBegin(GL_QUAD_STRIP);

   for (int theta = 0; theta < 361; theta++) {
      glNormal3f(Sin(theta),0,Cos(theta));

      glTexCoord2f((theta*2*acos(-1))/360 , 0); glVertex3f((0.25 * Sin(theta)) + (-9), 12, (0.25 * Cos(theta)) + (-8.28125));
      glTexCoord2f((theta*2*acos(-1))/360 , 1); glVertex3f((0.25 * Sin(theta)) + (-9), 13.75, (0.25 * Cos(theta)) + (-8.28125));
   }

   glEnd();

   glBegin(GL_QUAD_STRIP);

   for (int theta = 0; theta < 361; theta++) {
      glNormal3f(-Sin(theta),0,-Cos(theta));

      glTexCoord2f((theta*2*acos(-1))/360 , 0); glVertex3f((0.2 * Sin(theta)) + (-9), 12, (0.2 * Cos(theta)) + (-8.28125));
      glTexCoord2f((theta*2*acos(-1))/360 , 1); glVertex3f((0.2 * Sin(theta)) + (-9), 13.75, (0.2 * Cos(theta)) + (-8.28125));
   }

   glEnd();

   glBegin(GL_QUAD_STRIP);

   glNormal3f(0,1,0);

   for (int theta = 0; theta < 361; theta++) {
      glTexCoord2f(0.25*Sin(theta) , 0.25*Cos(theta)); glVertex3f((0.25 * Sin(theta)) + (-9), 13.75, (0.25 * Cos(theta)) + (-8.28125));
      glTexCoord2f(0.2*Sin(theta) , 0.2*Cos(theta)); glVertex3f((0.2 * Sin(theta)) + (-9), 13.75, (0.2 * Cos(theta)) + (-8.28125));
   }

   glEnd();

// ----------

   glBegin(GL_QUAD_STRIP);

   for (int theta = 0; theta < 361; theta++) {
      glNormal3f(Sin(theta),0,Cos(theta));

      glTexCoord2f((theta*2*acos(-1))/360 , 0); glVertex3f((0.25 * Sin(theta)) + (-9), 12, (0.25 * Cos(theta)) + (-9.34375));
      glTexCoord2f((theta*2*acos(-1))/360 , 1); glVertex3f((0.25 * Sin(theta)) + (-9), 13.75, (0.25 * Cos(theta)) + (-9.34375));
   }

   glEnd();

   glBegin(GL_QUAD_STRIP);

   for (int theta = 0; theta < 361; theta++) {
      glNormal3f(-Sin(theta),0,-Cos(theta));

      glTexCoord2f((theta*2*acos(-1))/360 , 0); glVertex3f((0.2 * Sin(theta)) + (-9), 12, (0.2 * Cos(theta)) + (-9.34375));
      glTexCoord2f((theta*2*acos(-1))/360 , 1); glVertex3f((0.2 * Sin(theta)) + (-9), 13.75, (0.2 * Cos(theta)) + (-9.34375));
   }

   glEnd();

   glBegin(GL_QUAD_STRIP);

   glNormal3f(0,1,0);

   for (int theta = 0; theta < 361; theta++) {
      glTexCoord2f(0.25*Sin(theta) , 0.25*Cos(theta)); glVertex3f((0.25 * Sin(theta)) + (-9), 13.75, (0.25 * Cos(theta)) + (-9.34375));
      glTexCoord2f(0.2*Sin(theta) , 0.2*Cos(theta)); glVertex3f((0.2 * Sin(theta)) + (-9), 13.75, (0.2 * Cos(theta)) + (-9.34375));
   }

   glEnd();

// ----------


   glBegin(GL_QUAD_STRIP);

   for (int theta = 0; theta < 361; theta++) {
      glNormal3f(Sin(theta),0,Cos(theta));

      glTexCoord2f((theta*2*acos(-1))/360 , 0); glVertex3f((0.25 * Sin(theta)) + (-9), 12, (0.25 * Cos(theta)) + (-10.4063));
      glTexCoord2f((theta*2*acos(-1))/360 , 1); glVertex3f((0.25 * Sin(theta)) + (-9), 13.75, (0.25 * Cos(theta)) + (-10.4063));
   }

   glEnd();

   glBegin(GL_QUAD_STRIP);

   for (int theta = 0; theta < 361; theta++) {
      glNormal3f(-Sin(theta),0,-Cos(theta));

      glTexCoord2f((theta*2*acos(-1))/360 , 0); glVertex3f((0.2 * Sin(theta)) + (-9), 12, (0.2 * Cos(theta)) + (-10.4063));
      glTexCoord2f((theta*2*acos(-1))/360 , 1); glVertex3f((0.2 * Sin(theta)) + (-9), 13.75, (0.2 * Cos(theta)) + (-10.4063));
   }

   glEnd();

   glBegin(GL_QUAD_STRIP);

   glNormal3f(0,1,0);

   for (int theta = 0; theta < 361; theta++) {
      glTexCoord2f(0.25*Sin(theta) , 0.25*Cos(theta)); glVertex3f((0.25 * Sin(theta)) + (-9), 13.75, (0.25 * Cos(theta)) + (-10.4063));
      glTexCoord2f(0.2*Sin(theta) , 0.2*Cos(theta)); glVertex3f((0.2 * Sin(theta)) + (-9), 13.75, (0.2 * Cos(theta)) + (-10.4063));
   }

   glEnd();

// -----------------

   glBegin(GL_QUAD_STRIP);

   for (int theta = 0; theta < 361; theta++) {
      glNormal3f(Sin(theta),0,Cos(theta));

      glTexCoord2f((theta*2*acos(-1))/360 , 0); glVertex3f((0.25 * Sin(theta)) + (-9), 12, (0.25 * Cos(theta)) + (-11.4688));
      glTexCoord2f((theta*2*acos(-1))/360 , 1); glVertex3f((0.25 * Sin(theta)) + (-9), 13.75, (0.25 * Cos(theta)) + (-11.4688));
   }

   glEnd();

   glBegin(GL_QUAD_STRIP);

   for (int theta = 0; theta < 361; theta++) {
      glNormal3f(-Sin(theta),0,-Cos(theta));

      glTexCoord2f((theta*2*acos(-1))/360 , 0); glVertex3f((0.2 * Sin(theta)) + (-9), 12, (0.2 * Cos(theta)) + (-11.4688));
      glTexCoord2f((theta*2*acos(-1))/360 , 1); glVertex3f((0.2 * Sin(theta)) + (-9), 13.75, (0.2 * Cos(theta)) + (-11.4688));
   }

   glEnd();

   glBegin(GL_QUAD_STRIP);

   glNormal3f(0,1,0);

   for (int theta = 0; theta < 361; theta++) {
      glTexCoord2f(0.25*Sin(theta) , 0.25*Cos(theta)); glVertex3f((0.25 * Sin(theta)) + (-9), 13.75, (0.25 * Cos(theta)) + (-11.4688));
      glTexCoord2f(0.2*Sin(theta) , 0.2*Cos(theta)); glVertex3f((0.2 * Sin(theta)) + (-9), 13.75, (0.2 * Cos(theta)) + (-11.4688));
   }

   glEnd();



   // --------------------------Tower------------------------------------------------------------------

   glBindTexture(GL_TEXTURE_2D,texture[2]); //stone

   // --------------base---------------

   glBegin(GL_QUAD_STRIP);

   for (int theta = 0; theta < 361; theta++) {
      glNormal3f(Sin(theta),0,Cos(theta));

      glTexCoord2f((theta*2*acos(-1))/450,0); glVertex3f((2 * Sin(theta)) + (tow_x), 0, (2 * Cos(theta)) + (tow_y));
      glTexCoord2f((theta*2*acos(-1))/450,5); glVertex3f((2 * Sin(theta)) + (tow_x), 12, (2 * Cos(theta)) + (tow_y));
   }

   glEnd();

   // -------------------Top-------------

   glBegin(GL_QUAD_STRIP);

   for (int theta = 0; theta < 361; theta++) {
      glNormal3f(Sin(theta),-1,Cos(theta));

      glTexCoord2f((theta*2*acos(-1))/450,0); glVertex3f((2 * Sin(theta)) + (tow_x), 11.6, (2 * Cos(theta)) + (tow_y));
      glTexCoord2f((theta*2*acos(-1))/450,0.2); glVertex3f((2.4 * Sin(theta)) + (tow_x), 12, (2.4 * Cos(theta)) + (tow_y));
   }

   glEnd();

   glBegin(GL_QUAD_STRIP);

   for (int theta = 0; theta < 361; theta++) {
      glNormal3f(Sin(theta),0,Cos(theta));

      glTexCoord2f((theta*2*acos(-1))/450,0); glVertex3f((2.4 * Sin(theta)) + (tow_x), 12.5, (2.4 * Cos(theta)) + (tow_y));
      glTexCoord2f((theta*2*acos(-1))/450,0.2); glVertex3f((2.4 * Sin(theta)) + (tow_x), 12, (2.4 * Cos(theta)) + (tow_y));
   }

   glEnd();


   glBegin(GL_QUAD_STRIP);

   for (int theta = 0; theta < 361; theta++) {
      glNormal3f(-Sin(theta),0,-Cos(theta));

      glTexCoord2f((theta*2*acos(-1))/450,0); glVertex3f((2.1 * Sin(theta)) + (tow_x), 12.5, (2.1 * Cos(theta)) + (tow_y));
      glTexCoord2f((theta*2*acos(-1))/450,0.2); glVertex3f((2.1 * Sin(theta)) + (tow_x), 12, (2.1 * Cos(theta)) + (tow_y));
   }

   glEnd();


   glBegin(GL_QUAD_STRIP);
   glNormal3f(0,1,0);

   for (int theta = 0; theta < 361; theta++) {
      glTexCoord2f((theta*2*acos(-1))/450,0); glVertex3f((2.1 * Sin(theta)) + (tow_x), 12.5, (2.1 * Cos(theta)) + (tow_y));
      glTexCoord2f((theta*2*acos(-1))/450,0.1); glVertex3f((2.4 * Sin(theta)) + (tow_x), 12.5, (2.4 * Cos(theta)) + (tow_y));
   }

   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[7]); //wood planks

   glBegin(GL_POLYGON);

   glNormal3f(0,1,0);

   for (int theta = 0; theta < 361; theta++) {
      glTexCoord2f(Sin(theta) , Cos(theta)); glVertex3f((2.4 * Sin(theta)) + (tow_x), 12, (2.4 * Cos(theta)) + (tow_y));
   }

   glEnd();

   // --------------------top nubs-------------------

   glBindTexture(GL_TEXTURE_2D,texture[2]); //stone


   for (int theta = 0; theta < 360; theta += 36)
   {

      glBegin(GL_POLYGON);
      glNormal3f(-Cos(theta),0,Sin(theta));

      glTexCoord2f(0.1,0); glVertex3f((2.4 * Sin(theta)) + (tow_x), 12.5, (2.4 * Cos(theta)) + (tow_y));
      glTexCoord2f(0,0); glVertex3f((2.1 * Sin(theta)) + (tow_x), 12.5, (2.1 * Cos(theta)) + (tow_y));
      glTexCoord2f(0,0.1); glVertex3f((2.1 * Sin(theta)) + (tow_x), 13, (2.1 * Cos(theta)) + (tow_y));
      glTexCoord2f(0.1,0.1); glVertex3f((2.4 * Sin(theta)) + (tow_x), 13, (2.4 * Cos(theta)) + (tow_y)); 

      glEnd();

      glBegin(GL_QUAD_STRIP);
      for (int i = 0; i < 19; i++)
      {
         glNormal3f(Sin(theta + i),0,Cos(theta + i));

         glTexCoord2f((i*2*acos(-1))/360,0); glVertex3f((2.4 * Sin(theta + i)) + (tow_x), 12.5, (2.4 * Cos(theta + i)) + (tow_y));
         glTexCoord2f((i*2*acos(-1))/360,0.1); glVertex3f((2.4 * Sin(theta + i)) + (tow_x), 13, (2.4 * Cos(theta + i)) + (tow_y)); 
      }
      glEnd();

      glBegin(GL_QUAD_STRIP);
      for (int i = 0; i < 19; i++)
      {
         glNormal3f(-Sin(theta + i),0,-Cos(theta + i));

         glTexCoord2f((i*2*acos(-1))/360,0); glVertex3f((2.1 * Sin(theta + i)) + (tow_x), 12.5, (2.1 * Cos(theta + i)) + (tow_y));
         glTexCoord2f((i*2*acos(-1))/360,0.1); glVertex3f((2.1 * Sin(theta + i)) + (tow_x), 13, (2.1 * Cos(theta + i)) + (tow_y)); 
      }
      glEnd();

      glBegin(GL_QUAD_STRIP);
      for (int i = 0; i < 19; i++)
      {
         glNormal3f(0,1,0);

         glTexCoord2f((i*2*acos(-1))/360,0.1); glVertex3f((2.4 * Sin(theta + i)) + (tow_x), 13, (2.4 * Cos(theta + i)) + (tow_y));
         glTexCoord2f((i*2*acos(-1))/360,0); glVertex3f((2.1 * Sin(theta + i)) + (tow_x), 13, (2.1 * Cos(theta + i)) + (tow_y)); 
      }
      glEnd();

      glBegin(GL_POLYGON);
      glNormal3f(Cos(theta),0,-Sin(theta));

      glTexCoord2f(0.1,0); glVertex3f((2.4 * Sin(theta + 18)) + (tow_x), 12.5, (2.4 * Cos(theta + 18)) + (tow_y));
      glTexCoord2f(0,0); glVertex3f((2.1 * Sin(theta + 18)) + (tow_x), 12.5, (2.1 * Cos(theta + 18)) + (tow_y));
      glTexCoord2f(0,0.1); glVertex3f((2.1 * Sin(theta + 18)) + (tow_x), 13, (2.1 * Cos(theta + 18)) + (tow_y));
      glTexCoord2f(0.1,0.1); glVertex3f((2.4 * Sin(theta + 18)) + (tow_x), 13, (2.4 * Cos(theta + 18)) + (tow_y)); 

      glEnd();
   }

   // -----------------Middle Balcony-------------------------------------------------------------------------------------------

// -----------------------x------------------

   glBegin(GL_POLYGON);

   glNormal3f(-1,0,0);
   
   glTexCoord2f(0.75 , 0); glVertex3f(2,2,0.5);
   glTexCoord2f(0.75 , 0.75); glVertex3f(2,6.75,0.5);
   glTexCoord2f(0 , 0.75); glVertex3f(2,6.75,-0.75);
   glTexCoord2f(0 , 0); glVertex3f(2,2,-0.75);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(1,0,0);
   
   glTexCoord2f(0.75 , 0); glVertex3f(-2,2,0.5);
   glTexCoord2f(0.75 , 0.75); glVertex3f(-2,6.75,0.5);
   glTexCoord2f(0 , 0.75); glVertex3f(-2,6.75,-0.75);
   glTexCoord2f(0 , 0); glVertex3f(-2,2,-0.75);

   glEnd();

// -----------------z------------------

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(3.5 , 0); glVertex3f(4,2,0);
   glTexCoord2f(0 , 0); glVertex3f(-4,2,0);
   glTexCoord2f(0 , 1.5); glVertex3f(-4,6.5,0);
   glTexCoord2f(3.5 , 1.5); glVertex3f(4,6.5,0);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(0,0,-1);
   
   glTexCoord2f(3.5 , 0); glVertex3f(4,2,-0.25);
   glTexCoord2f(0 , 0); glVertex3f(-4,2,-0.25);
   glTexCoord2f(0 , 1.5); glVertex3f(-4,6.5,-0.25);
   glTexCoord2f(3.5 , 1.5); glVertex3f(4,6.5,-0.25);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0.5 , 0); glVertex3f(-2,2,0.5);
   glTexCoord2f(0.5 , 1.5); glVertex3f(-2,6.75,0.5);
   glTexCoord2f(0 , 1.5); glVertex3f(-3.5,6.75,0.5);
   glTexCoord2f(0 , 0); glVertex3f(-3.5,2,0.5);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0 , 0); glVertex3f(2,2,0.5);
   glTexCoord2f(0 , 1.5); glVertex3f(2,6.75,0.5);
   glTexCoord2f(0.5 , 1.5); glVertex3f(3.5,6.75,0.5);
   glTexCoord2f(0.5 , 0); glVertex3f(3.5,2,0.5);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(0,0,-1);
   
   glTexCoord2f(0.5 , 0); glVertex3f(-2,2,-0.75);
   glTexCoord2f(0.5 , 1.5); glVertex3f(-2,6.75,-0.75);
   glTexCoord2f(0 , 1.5); glVertex3f(-3.5,6.75,-0.75);
   glTexCoord2f(0 , 0); glVertex3f(-3.5,2,-0.75);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(0,0,-1);
   
   glTexCoord2f(0 , 0); glVertex3f(2,2,-0.75);
   glTexCoord2f(0 , 1.5); glVertex3f(2,6.75,-0.75);
   glTexCoord2f(0.5 , 1.5); glVertex3f(3.5,6.75,-0.75);
   glTexCoord2f(0.5 , 0); glVertex3f(3.5,2,-0.75);

   glEnd();


// ------------------------y-------------------

   glBindTexture(GL_TEXTURE_2D,texture[7]); //wood planks

   glBegin(GL_POLYGON);

   glNormal3f(0,1,0);
   
   glTexCoord2f(0 , 4); glVertex3f(-4,6,-5);
   glTexCoord2f(0 , 0); glVertex3f(-4,6,0);
   glTexCoord2f(3.5 , 0); glVertex3f(4,6,0);
   glTexCoord2f(3.5 , 4); glVertex3f(4,6,-5);

   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[2]); //stone

   glBegin(GL_POLYGON);

   glNormal3f(0,1,0);
   
   glTexCoord2f(0.8 , 0); glVertex3f(-2,6.75,0.5);
   glTexCoord2f(0 , 0); glVertex3f(-3.5,6.75,0.5);
   glTexCoord2f(0 , 0.4); glVertex3f(-3.5,6.75,-0.75);
   glTexCoord2f(0.8 , 0.4); glVertex3f(-2,6.75,-0.75);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(0,1,0);
   
   glTexCoord2f(0 , 0); glVertex3f(2,6.75,0.5);
   glTexCoord2f(0.8 , 0); glVertex3f(3.5,6.75,0.5);
   glTexCoord2f(0.8 , 0.4); glVertex3f(3.5,6.75,-0.75);
   glTexCoord2f(0 , 0.4); glVertex3f(2,6.75,-0.75);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(0,1,0);
   
   glTexCoord2f(3 , 0); glVertex3f(4,6.5,0);
   glTexCoord2f(0 , 0); glVertex3f(-4,6.5,0);
   glTexCoord2f(0 , 0.1); glVertex3f(-4,6.5,-0.25);
   glTexCoord2f(3 , 0.1); glVertex3f(4,6.5,-0.25);

   glEnd();

   // ----------------------------------------Upper floor----------------------------------------------------------------

   //-------------------------------x----------------

   glBindTexture(GL_TEXTURE_2D,texture[3]); //bricks

   glBegin(GL_POLYGON);

   glNormal3f(-1,0,0);
   
   glTexCoord2f(0 , 0); glVertex3f(0,6,-3.25);
   glTexCoord2f(0 , 0.75); glVertex3f(0,7.75,-3.25);
   glTexCoord2f(0.5 , 0.75); glVertex3f(0,7.75,-5);
   glTexCoord2f(0.5 , 0); glVertex3f(0,6,-5);

   glEnd();

   //-------------------------------roof---------------- 

   glBindTexture(GL_TEXTURE_2D,texture[5]); //shingles

   glBegin(GL_POLYGON);

   glNormal3f(1,0.896552,0);
   
   glTexCoord2f(2 , 2); glVertex3f(0,11.6724,-10.25);
   glTexCoord2f(2 , 0); glVertex3f(4.375,7.75,-10.25);
   glTexCoord2f(0 , 0); glVertex3f(4.375,7.75,-5);
   glTexCoord2f(0 , 2); glVertex3f(0,11.6724,-5);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(-1,0.896552,0);
   
   glTexCoord2f(2 , 2); glVertex3f(0,11.6724,-10.25);
   glTexCoord2f(2 , 0); glVertex3f(-4.375,7.75,-10.25);
   glTexCoord2f(0 , 0); glVertex3f(-4.375,7.75,-5);
   glTexCoord2f(0 , 2); glVertex3f(0,11.6724,-5);

   glEnd();


// ---------------------------------

   glBegin(GL_POLYGON);

   glNormal3f(-1,0.896552,0);
   
   glTexCoord2f(0.65 , 1); glVertex3f(2.1875,9.7112,-5);
   glTexCoord2f(0.65 , 0); glVertex3f(0,7.75,-5);
   glTexCoord2f(0 , 0); glVertex3f(0,7.75,-3.25);
   glTexCoord2f(0 , 1); glVertex3f(2.1875,9.7112,-3.25);

   glEnd();


   glBegin(GL_POLYGON);

   glNormal3f(1,0.896552,0);
   
   glTexCoord2f(0.65 , 1); glVertex3f(2.1875,9.7112,-5);
   glTexCoord2f(0.65 , 0); glVertex3f(4.375,7.75,-5);
   glTexCoord2f(0 , 0); glVertex3f(4.375,7.75,-3.25);
   glTexCoord2f(0 , 1); glVertex3f(2.1875,9.7112,-3.25);

   glEnd();


   //-------------------------------z----------------

   glBindTexture(GL_TEXTURE_2D,texture[3]); //bricks

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0 , 0); glVertex3f(-4.375,6,-5);
   glTexCoord2f(2 , 0); glVertex3f(4.375,6,-5);
   glTexCoord2f(2 , 0.308511*2.25); glVertex3f(4.375,7.75,-5);
   glTexCoord2f(0.5*2 , 2.25); glVertex3f(0,11.6724,-5);
   glTexCoord2f(0 , 0.308511*2.25); glVertex3f(-4.375,7.75,-5);

   glEnd();

// ---------------------------------

   glBegin(GL_POLYGON);

   glNormal3f(0,0,1);
   
   glTexCoord2f(0 , 0); glVertex3f(0,6,-3.25);
   glTexCoord2f(1 , 0); glVertex3f(4.375,6,-3.25);
   glTexCoord2f(1 , 0.471546*1.125); glVertex3f(4.375,7.75,-3.25);
   glTexCoord2f(0.5 , 1.125); glVertex3f(2.1875,9.7112,-3.25);
   glTexCoord2f(0 , 0.471546*1.125); glVertex3f(0,7.75,-3.25);

   glEnd();

   // ------------Populating windows and doors-----------------------------------------
   //front th = 0

   //ground level
   door(0,0,2.5 , 0.42,0.42,0.47 , 0);
   window_1(4.375,2.25,2 , 0.42,0.42,0.47 , 0);
   window_1(-4.375,2.25,2 , 0.42,0.42,0.47 , 0);

   window_2(4.375,5.7,2 , 0.22,0.22,0.25 , 0);
   window_2(-4.375,5.7,2 , 0.22,0.22,0.25 , 0);

   //balcony
   window_1(2.1875,7.5,-3.25 , 0.25,0.25,0.3 , 0);
   window_2(0,10.2,-5 , 0.2,0.2,0.25 , 0);
   door(-1.25,6,-5 , 0.4,0.38,0.47 , 0);

   //right th = 90

   window_1(8,2.25,-0.5 , 0.25,0.5,0.47 , 90);
   window_1(8,2.25,-4 , 0.25,0.5,0.47 , 90);
   window_1(9,2.25,-8 , 0.25,0.5,0.47 , 90);
   window_1(9,2.25,-10.6 , 0.25,0.5,0.47 , 90);

   window_2(9,8.5,-10.25 , 0.3,0.3,0.35 , 90);

   //right th = -90

   window_1(-8,2.25,-0.5 , 0.25,0.5,0.47 , -90);
   window_1(-8,2.25,-4 , 0.25,0.5,0.47 , -90);
   window_1(-9,2.25,-13 , 0.25,0.5,0.47 , -90);

   //back th = 180

   door(5,0,-14.25 , 0.42,0.42,0.47 , 180);
   window_1(0.5,2.25,-14.25 , 0.42,0.42,0.47 , 180);
   window_1(-4.5,2.25,-14.25 , 0.42,0.42,0.47 , 180);

   //  Undo transformations
   glPopMatrix();
}

static void Vertex(int th,int ph)
{
   double x = Cos(th)*Cos(ph);
   double y = Sin(th)*Cos(ph);
   double z =         Sin(ph);
   glNormal3d(x,y,z);
   glTexCoord2d(th/360.0,ph/180.0+0.5);
   glVertex3d(x,y,z);
}

/*
 *  Draw the moon
 *     at (x,y,z)
 *     radius r
 */
static void moon(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[9]);

   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);

   // glutSolidSphere(10.0,16,16);

   glColor3f(1,1,1);
   for (int i = -90; i < 90; i += 5)
   {
      glBegin(GL_QUAD_STRIP);
      for (int j = 0; j <= 360; j += 5)
      {
         Vertex(j,i);
         Vertex(j,i + 5);
      }
      glEnd();
   }
   
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
      float Position[4];
      if (orbit)
      {
         // {-100*Cos(zh),40,100*Sin(zh),1};
         Position[0] = -100*Cos(zh);
         Position[1] = 40;
         Position[2] = 100*Sin(zh);
         Position[3] = 1;
      }
      else
      {
         Position[0] = -100;
         Position[1] = 40;
         Position[2] = 100;
         Position[3] = 1;
      }
      //  Draw light position moon (still no lighting here)
      glColor3f(1,1,1);
      moon(Position[0],Position[1],Position[2] , 8);
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
   turntable(turn);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT && turn == 0)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT && turn == 0)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP && turn == 0)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN && turn == 0)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.2;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.2;
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
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //Toggle turntable effect
   else if (ch == 't' || ch == 'T')
      turn = 1-turn;
   //Toggle moon orbit
   else if (ch == 'o' || ch == 'O')
      orbit = 1-orbit;
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
   glutInitWindowSize(1000,800);
   glutCreateWindow("Final Project: Kolin Newby");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load textures
   texture[0] = LoadTexBMP("tex/grass.bmp");
   texture[1] = LoadTexBMP("tex/wood_grain1.bmp");
   texture[2] = LoadTexBMP("tex/stone1.bmp");
   texture[3] = LoadTexBMP("tex/brick.bmp");
   texture[4] = LoadTexBMP("tex/glass.bmp");
   texture[5] = LoadTexBMP("tex/shingles.bmp");
   texture[6] = LoadTexBMP("tex/metal.bmp");
   texture[7] = LoadTexBMP("tex/wood_plank.bmp");
   texture[8] = LoadTexBMP("tex/door.bmp");
   texture[9] = LoadTexBMP("tex/moon.bmp");
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
