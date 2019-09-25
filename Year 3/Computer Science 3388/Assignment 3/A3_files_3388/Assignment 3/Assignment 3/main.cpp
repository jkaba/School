/************************************************************************************/
/********************************** Acknowledgement: ********************************/
/****         The basic structure of the code is taken from an assignment        ****/
/****                    of a computer graphics course at UBC                    ****/
/************************************************************************************/

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<iostream>
#include "vector.h"
#include "pointcanvas.h"
#include "curves.h"


// Global window properties
unsigned int windowWidth, windowHeight;

// Global canvas on which points are drawn and manipulated
PointCanvas pointCanvas;

// Global curve manager for creating and drawing Bezier curves
CurveManager curveManager;

// Menu identifiers
enum MenuItem 
{
    MENU_EXIT,
    MENU_CLEAR,
    MENU_BEZIER,
	MENU_CUBIC_BSPLINE,
	MENU_BETA_SPLINE,
	MENU_BETA_SPLINE_CLOSEDCURVE_MODE,
	MENU_CUBIC_BSPLINE_PHANTOM_MODE
};

// Callback to draw to the screen
void draw()
{
    // Clear buffers
    glClearColor(0.9, 0.9, 0.9, 0.9);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Generic 2D orthographic transform
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw all the points
    const std::vector<Vector2D>& points = pointCanvas.getPoints();
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5);
    glBegin(GL_POINTS);
    for (size_t i = 0; i < points.size(); ++i)
    {
        glVertex2f(points[i][0], points[i][1]);
    }
    glEnd();

    // Update current set of points.
    curveManager.updatePoints(&points);

    // Draw the curves
    curveManager.drawCurves();

    // Swap buffers to display to screen
    glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y)
{
    switch(c)
    {
    case 27: // ESC
    case 'q':
        exit(0);
        break;
	}
	glutPostRedisplay();
}

// Callback for mouse button presses
void mouse(int button, int state, int x, int y)
{
    bool redraw = false;

    float mouseX = (float)x/(windowWidth-1);
    float mouseY = 1.0 - (float)y/(windowHeight-1);

    if (state)
    {
        redraw |= pointCanvas.mouseUp(button, mouseX, mouseY);
    }
    else
    {
        redraw |= pointCanvas.mouseDown(button, mouseX, mouseY);
    }

    if (redraw)
    {
        glutPostRedisplay();
    }
}

// Callback for mouse movements
void motion(int x, int y)
{
    bool redraw = false;

    float mouseX = (float)x/(windowWidth-1);
    float mouseY = 1.0 - (float)y/(windowHeight-1);

    redraw |= pointCanvas.mouseMove(mouseX, mouseY);

    if (redraw)
    {
        glutPostRedisplay();
    }
}

// Callback for changes to the shape and size of the window
void reshape(int w, int h)
{
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

// Callback for menu buttons
void menu(int which)
{
    switch(which)
    {
	case MENU_BEZIER:
		curveManager.setCurveMode(BEZIER_MODE);
		break;
	case MENU_CUBIC_BSPLINE:
		curveManager.setCurveMode(CUBIC_BSPLINE_MODE);
		break;
	case MENU_BETA_SPLINE:
		curveManager.setCurveMode(BETA_SPLINE_MODE);
		break;
	case MENU_BETA_SPLINE_CLOSEDCURVE_MODE:
		curveManager.setCurveMode(BETA_SPLINE_CLOSEDCURVE_MODE);
		break;
	case MENU_CUBIC_BSPLINE_PHANTOM_MODE:
		curveManager.setCurveMode(CUBIC_BSPLINE_PHANTOM_MODE);
		break;
	case MENU_CLEAR: 
		pointCanvas.clearPoints();
        break;
	case MENU_EXIT: 
		exit(0);
        break;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv) {
    
    // Initialize window in GLUT
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("CurveEditor");

    // Register GLUT callbacks
    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);

	// Add menus for state selection
    int modeMenu = glutCreateMenu(menu); // Menu for program mode
    glutAddMenuEntry("Basic Bezier Curve", MENU_BEZIER);
	glutAddMenuEntry("Cubic Bspline Curve", MENU_CUBIC_BSPLINE);
	glutAddMenuEntry("Beta spline Curve", MENU_BETA_SPLINE);
	glutAddMenuEntry("Beta spline closed Curve", MENU_BETA_SPLINE_CLOSEDCURVE_MODE);
	glutAddMenuEntry("Cubic Bspline Curve (Phantom endpoints)", MENU_CUBIC_BSPLINE_PHANTOM_MODE);

	glutAddMenuEntry("Clear Points", MENU_CLEAR);
    glutAddMenuEntry("Exit", MENU_EXIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // Begin GLUT main loop
    glutMainLoop();

	return 0;
}