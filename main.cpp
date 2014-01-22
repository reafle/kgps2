#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>	// OpenGL Graphics Utility Library
#include <time.h>
#include <string.h>

#define drawOnePoint(x1,y1)  glBegin(GL_POINTS); glVertex2f ((x1),(y1)); glEnd();
#define PROB_NESTING_LEVEL 10
#define PROB_ITERATIONS 10000
#define PROB_STEP 100
#define NESTING_LEVEL 10

// Number of step 
int CurrentNum = 0;
int CurrentProbabilisticNum = 0;
int mode = 1;

/*int** random = new int[iterations];*/

// These variables set the dimensions of the rectanglar region we wish to view.
const double Xmin = -0.1, Xmax = 1.1;
const double Ymin = -0.1, Ymax = 1.1;


void drawProbabilisticFractal(int num) {
	float x = 0.0f, y = 0.0f;
	int nesting_level = 0;
	int transformation = 0;

    glPushMatrix();
	drawOnePoint(0,0);
	
	for (int i = 0; i < num; i++ ){
		nesting_level = PROB_NESTING_LEVEL;
		
		glPushMatrix();
		for (int j=0; j<nesting_level; j++) {

			transformation = rand() % 4;
			
			if (transformation == 1) {
				glScalef(0.5f, 0.5f, 1.0f);
                glColor3f(1.0f, 0.0f, 0.0f);
                    
			} else if (transformation == 2) {
				glScalef(0.5f, 0.5f, 1.0f);
				glTranslatef(0, 2, 0.0f);
				glRotatef(180, 0, 1, 0);
				glRotatef(180, 0, 0, 1);
                glColor3f(0.0f, 1.0f, 0.0f);
                
			} else if (transformation == 3) {
				glScalef(0.5, 0.5, 1.0);
				glTranslatef(1, 1, 0);
				glRotatef(270, 0, 0, 1);
                		glColor3f(0.0f, 0.0f, 1.0f);

			} else if (transformation == 0) {
				glTranslatef(1, 0.75, 0);
				glScalef(0.25,0.25, 1);
				glRotatef(180, 0, 1, 0);
				glRotatef(270, 0, 0, 1);
                glColor3f(1.0f, 1.0f, 1.0f);
                
			}

		}

		drawOnePoint(x, y);
		glPopMatrix();

	}
		glPopMatrix();

}

void drawFractal(int num, int color = 0)
{
	if (color == 0) {
		glColor3f(1.0f, 1.0f, 1.0f);
	} else if (color == 1) {
		glColor3f(1.0f, 0.0f, 0.0f);
	} else if (color == 2) {
		glColor3f(0.0f, 1.0f, 0.0f);
	} else if (color == 3 ) {
		glColor3f(0.0f, 0.0f, 1.0f);
	} else if (color == 4 ) {
		glColor3f(0.0f, 1.0f, 1.0f);
	} else {
		glColor3f(1.0f, 0.0f, 1.0f);
	}
	
switch(num) {
   case 0:
		glBegin( GL_QUADS );
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		
		glEnd();
        break;
   default:

	   bool firstTime;
	   if (num == CurrentNum ) {
		   firstTime = true;
	   } else {
		   firstTime = false;
		}


        glPushMatrix();
		glPushMatrix();
        glPushMatrix();

        glScalef(0.5f, 0.5f, 1.0f);
		if (firstTime) {
			drawFractal(num - 1, 1);
		} else {
			drawFractal(num - 1, color);
		}
		
        glPopMatrix();
        glScalef(0.5f, 0.5f, 1.0f);
        glTranslatef(0, 2, 0.0f);
		//glRotatef(180, 0, 1, 0);
		glRotatef(180, 0, 1, 0);
		glRotatef(180, 0, 0, 1);
		if (firstTime) {
			drawFractal(num - 1, 2);
		} else {
			drawFractal(num - 1, color);
		}
		
        glPopMatrix();
        glScalef(0.5, 0.5, 1.0);
        glTranslatef(1, 1, 0);
		glRotatef(270, 0, 0, 1);
		if (firstTime) {
			drawFractal(num - 1, 3);
		} else {
			drawFractal(num - 1, color);
		}
		
		glPopMatrix();
        glTranslatef(1, 0.75, 0);
        glScalef(0.25,0.25, 1);
		//glRotatef(180, 1, 0, 0);
		glRotatef(180, 0, 1, 0);
		glRotatef(270, 0, 0, 1);
        if (firstTime) {
			drawFractal(num - 1, 4);
		} else {
			drawFractal(num - 1, color);
		}
		
        break;   
 }
}

/*
 * drawScene() handles the animation and the redrawing of the
 *		graphics window contents.
 */
void drawScene(void)
{
	// Clear the rendering window

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set drawing color to white
	glColor3f( 1.0, 1.0, 1.0 );		

	if (mode == 1) {
        glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
		drawFractal(CurrentNum);
	} else if (mode == 2) {
		drawProbabilisticFractal(CurrentProbabilisticNum);
	} 

 // Flush the pipeline.  (Not usually necessary.)
	glFlush();
}

// Initialize OpenGL's rendering modes
void initRendering()
{

	glEnable ( GL_DEPTH_TEST );

	// Uncomment out the first block of code below, and then the second block,
	//		to see how they affect line and point drawing.

	// The following commands should cause points and line to be drawn larger
	//	than a single pixel width.
	glPointSize(1);
	glLineWidth(8);



	// The following commands should induce OpenGL to create round points and 
	//	antialias points and lines.  (This is implementation dependent unfortunately).
//	glEnable(GL_POINT_SMOOTH);
//	glEnable(GL_LINE_SMOOTH);
//	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);	// Make round points, not square points
//	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);		// Antialias the lines
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}

// glutKeyboardFunc is called below to set this function to handle
//		all "normal" ascii key presses.
// Only space bar and escape key have an effect.
void myKeyboardFunc( unsigned char key, int x, int y )
{
	switch ( key ) {

	case ' ':									// Space bar
		// Increment the current step number, and tell operating system screen needs redrawing
		/*CurrentNum = (CurrentNum+1)%MaxNum;*/
		CurrentProbabilisticNum = (CurrentProbabilisticNum + PROB_STEP);
		CurrentNum = (CurrentNum+1) % NESTING_LEVEL;
		glutPostRedisplay();
		break;

	case 27:									// "27" is theEscape key
		exit(1);

	}
}


// Called when the window is resized
//		w, h - width and height of the window in pixels.
void resizeWindow(int w, int h)
{
	double scale, center;
	double windowXmin, windowXmax, windowYmin, windowYmax;

	// Define the portion of the window used for OpenGL rendering.
	glViewport( 0, 0, w, h );	// View port uses whole window

	// Set up the projection view matrix: orthographic projection
	// Determine the min and max values for x and y that should appear in the window.
	// The complication is that the aspect ratio of the window may not match the
	//		aspect ratio of the scene we want to view.
	w = (w==0) ? 1 : w;
	h = (h==0) ? 1 : h;
	if ( (Xmax-Xmin)/w < (Ymax-Ymin)/h ) {
		scale = ((Ymax-Ymin)/h)/((Xmax-Xmin)/w);
		center = (Xmax+Xmin)/2;
		windowXmin = center - (center-Xmin)*scale;
		windowXmax = center + (Xmax-center)*scale;
		windowYmin = Ymin;
		windowYmax = Ymax;
	}
	else {
		scale = ((Xmax-Xmin)/w)/((Ymax-Ymin)/h);
		center = (Ymax+Ymin)/2;
		windowYmin = center - (center-Ymin)*scale;
		windowYmax = center + (Ymax-center)*scale;
		windowXmin = Xmin;
		windowXmax = Xmax;
	}
	
	// Now that we know the max & min values for x & y that should be visible in the window,
	// we set up the orthographic projection.
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( windowXmin, windowXmax, windowYmin, windowYmax, -1, 1 );

}


// Main routine
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
    
    if (argc != 2) {
        printf("Usage: ./main [rec|prob]");
        printf("\n");
        return 1;
    }

    char* number_of_iterations = argv[1];
    if (strcmp(number_of_iterations, "prob") == 0) {
        mode = 2;
    } else if (strcmp(number_of_iterations, "rec") == 0) {
        mode = 1;
    } else {
        printf("Usage: ./main [rec|prob]");
        printf("\n");
        return 1;
    }

	srand(time(NULL));

	glutInit(&argc,argv);

	// The image is not animated so single buffering is OK. 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );

	// Window position (from top corner), and size (width and hieght)
	glutInitWindowPosition( 20, 60 );
	glutInitWindowSize( 500, 500 );
	glutCreateWindow( "2014 KGPS2 Oleg Popok. Press space bar for the next step" );

	// Initialize OpenGL as we like it..
	initRendering();

	// Set up callback functions for key presses
	glutKeyboardFunc( myKeyboardFunc );			// Handles "normal" ascii symbols
	// glutSpecialFunc( mySpecialKeyFunc );		// Handles "special" keyboard keys

	// Set up the callback function for resizing windows
	glutReshapeFunc( resizeWindow );

	// Call this for background processing
	// glutIdleFunc( myIdleFunction );

	// call this whenever window needs redrawing
	glutDisplayFunc( drawScene );

	fprintf(stdout, "Fraktalas 50.png.\n");
	
	// Start the main loop.  glutMainLoop never returns.
	glutMainLoop(  );

	return(0);	// This line is never reached.
}

