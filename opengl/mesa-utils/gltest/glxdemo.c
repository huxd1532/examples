

/*
 * A demonstration of using the GLX functions.  This program is in the
 * public domain.
 *
 * Brian Paul
 */

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int m_xRotated = 0;
unsigned int m_yRotated = 0;
unsigned int m_zRotated = 0;


static void redraw( Display *dpy, Window w )
{
   printf("Redraw event\n");

   glMatrixMode(GL_MODELVIEW);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

   GLfloat ambientColor[] = {0.6f, 0.3f, 0.7f, 1.0f};
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

   GLfloat lightColor0[] = {1.0f, 0.0f, 0.0f, 1.0f};
   GLfloat lightPos0[] = {10.0f, 10.0f, 0.0f, 1.0f};
   glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
   glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

   GLfloat lightColor1[] = {0.4f, 0.7f, 0.2f, 1.0f};
   GLfloat lightPos1[] = {0.0f, 0.0f, -5.0f, 0.0f};
   glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
   glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

   // glColor3f(0.3, 0.4, 0.7);
   glRotatef(m_xRotated, 1.0, 0.0, 0.0);
   glRotatef(m_yRotated, 0.0, 1.0, 0.0);
   glRotatef(m_zRotated, 0.0, 0.0, 1.0);
   glScalef(.4f, .4f, .4f);
   glColor3f(0.3f, 0.4f, 0.4f);
   glutSolidTeapot(1.0);
}

static void initGL()
{
   glClearColor(0.3f, 0.3f, 0.6f, 1);
   glClearDepth(1.0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   glEnable(GL_NORMALIZE);
   // glEnable(GL_POLYGON_OFFSET_FILL);
   // glPolygonMode(GL_FRONT, GL_LINE);
   glShadeModel(GL_SMOOTH);
}

static void resize( unsigned int width, unsigned int height )
{
   printf("Resize event\n");
   glViewport( 0, 0, width, height );
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho( -1.0, 1.0, -1.0, 1.0, -1.0, 1.0 );
}



static Window make_rgb_db_window( Display *dpy,
				  unsigned int width, unsigned int height )
{
   int attrib[] = { GLX_RGBA,
		    GLX_RED_SIZE, 1,
		    GLX_GREEN_SIZE, 1,
		    GLX_BLUE_SIZE, 1,
		    GLX_DOUBLEBUFFER,
		    None };
   int scrnum;
   XSetWindowAttributes attr;
   unsigned long mask;
   Window root;
   Window win;
   GLXContext ctx;
   XVisualInfo *visinfo;

   scrnum = DefaultScreen( dpy );
   root = RootWindow( dpy, scrnum );

   visinfo = glXChooseVisual( dpy, scrnum, attrib );
   if (!visinfo) {
      printf("Error: couldn't get an RGB, Double-buffered visual\n");
      exit(1);
   }

   /* window attributes */
   attr.background_pixel = 0;
   attr.border_pixel = 0;
   attr.colormap = XCreateColormap( dpy, root, visinfo->visual, AllocNone);
   attr.event_mask = StructureNotifyMask | ExposureMask;
   mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

   win = XCreateWindow( dpy, root, 0, 0, width, height,
		        0, visinfo->depth, InputOutput,
		        visinfo->visual, mask, &attr );

   ctx = glXCreateContext( dpy, visinfo, NULL, True );
   if (!ctx) {
      printf("Error: glXCreateContext failed\n");
      exit(1);
   }

   glXMakeCurrent( dpy, win, ctx );

   return win;
}


static void event_loop( Display *dpy )
{
   XEvent event;

   while (1) {
      XNextEvent( dpy, &event );

      switch (event.type) {
	 case Expose:
	    redraw( dpy, event.xany.window );
	    break;
	 case ConfigureNotify:
	    resize( event.xconfigure.width, event.xconfigure.height );
	    break;
      }
   }
}



int main( int argc, char *argv[] )
{
   Display *dpy;
   Window win;

   dpy = XOpenDisplay(NULL);

   win = make_rgb_db_window( dpy, 300, 300 );

   glShadeModel( GL_FLAT );
   glClearColor( 0.5, 0.5, 0.5, 1.0 );

   XMapWindow( dpy, win );

   event_loop( dpy );
   return 0;
}
