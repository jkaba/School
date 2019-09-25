/*
 * CS3388A Assignment 2
 * Name: Jameel Kaba
 * GAUL/UWO ID: jkaba
 * Student #: 250796017
 *
 * To run the program, check line 189, to reflect the file name and directory
 * Press 's' to run the bonus portion of the assignment
 */

// Include statements
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <iostream>

// Defining constants
#define SCREEN         900.0        // Screen Size
#define FAR            500.0        // Far value
#define NEAR           1.0          // Near value
#define EYEx           10.0         // Used for GluLookAt
#define EYEy           10.0         // Used for GluLookAt
#define EYEz           10.0         // Used for GluLookAt
#define GAZEx          0.0          // Used for GluLookAt
#define GAZEy          0.0          // Used for GluLookAt
#define GAZEz          5.0          // Used for GluLookAt
#define UPx            0.0          // Used for GluLookAt
#define UPy            0.0          // Used for GluLookAt
#define UPz            1.0          // Used for GluLookAt
#define VIEW_ANGLE     80.0         // Field of view angle
#define ASPECT_RATIO   1.0          // Aspect Ratio

using namespace std;

GLfloat specref[] = {0.0, 1.0, 0.0, 1.0};       // Used for specular lighting
vector<vector<vector<GLfloat>>> pts;            // list of points
vector<vector<GLfloat>> normals;                // list of normals
ifstream file;                                  // File containing the data
static int spin = 0;                            // spin variable used for bonus
bool animate = false;                           // boolean varibale used for bonus


/*
 * draw method
 * This method is for the bonus part of the assignment
 * This draws the x, y, and z axis represented in red, green, and blue
 */
void draw(){
    
    // X-axis represented in red
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    
    // Drawing the line
    glVertex3f(-10.0, 0.0f, 0.0f);
    glVertex3f(10.0, 0.0f, 0.0f);
    
    // Drawing the Arrow
    glVertex3f(8.0, 0.0f, 0.0f);
    glVertex3f(7.5, 0.5f, 0.0f);
    glVertex3f(8.0, 0.0f, 0.0f);
    glVertex3f(7.5, -0.5f, 0.0f);
    glEnd();
    glFlush();
    
    // Y-axis represented in green
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    
    // Drawing the line
    glVertex3f(0.0, -10.0f, 0.0f);
    glVertex3f(0.0, 10.0f, 0.0f);
    
    // Drawing the arrow
    glVertex3f(0.0, 8.0f, 0.0f);
    glVertex3f(0.5, 7.5f, 0.0f);
    glVertex3f(0.0, 8.0f, 0.0f);
    glVertex3f(-0.5, 7.5f, 0.0f);
    glEnd();
    glFlush();
    
    // Z-axis represented in blue
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    
    // Drawing the line
    glVertex3f(0.0, 0.0f ,-10.0f);
    glVertex3f(0.0, 0.0f ,10.0f);
    
    // Drawing the arrow
    glVertex3f(0.0, 0.0f ,8.0f);
    glVertex3f(0.0, 0.5f ,7.5f);
    glVertex3f(0.0, 0.0f ,8.0f);
    glVertex3f(0.0, -0.5f ,7.5f);
    glEnd();
    glFlush();
}

/*
 * points method
 * This method is used to calculate a series of points on a circle
 * based on the radius provided as input, this point along with its
 * z value are stored into a vector of points
 */
void points(const double &radius, const double &z) {
    
    // Vector of vectors containing floats used to store points
    vector<vector<GLfloat>> tempPts;
    
    // For loop that calculates the points, moving by 0.02 every iteration
    for(double i = 0.0; i < M_PI*2.0; i += 0.02 ) {
        
        // Vector containing floats used to store points
        vector<GLfloat> temp;
        
        // Store points into the vector
        temp.push_back(radius*cos(i));
        temp.push_back(radius*sin(i));
        temp.push_back(z);
        
        // Store the vector with points into the bigger vector
        tempPts.push_back(temp);
    }
    pts.push_back(tempPts);
}

/*
 * normalCalc method
 * This method calculates the normals for each 4 point section
 * of the polygon mesh, the normals are stored in a vector
 */
void normalCalc(){
    
    // variable declarations
    GLfloat normalize;
    GLfloat m1[3];
    GLfloat m2[3];
    GLfloat normal[3];
    
    // For loop that goes through all points
    for(int i = 0; i < pts.size()-1; ++i){
        for(int j = 0; j < pts[0].size(); ++j){
            
            // Create 3x3 matrices and store into an array
            m1[0] = pts[i][j][0];
            m1[1] = pts[i][j][1];
            m1[2] = pts[i][j][2];
            m2[0] = pts[i+1][j][0];
            m2[1] = pts[i+1][j][1];
            m2[2] = pts[i+1][j][2];
            
            
            // Calculate the normals
            normal[0] = m1[1] * m2[2] - m1[2] * m2[1];
            normal[1] = m1[2] * m2[0] - m1[0] * m2[2];
            normal[2] = m1[0] * m2[1] - m1[1] * m2[0];
            
            // Calculate the normalized surface area
            normalize = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
            normal[0] = normal[0] / normalize;
            normal[1] = normal[1] / normalize;
            normal[2] = normal[2] / normalize;
            
            // Create a vector to store the normals
            vector<GLfloat> temp;
            
            // Store the normals in the vector
            temp.push_back(normal[0]);
            temp.push_back(normal[1]);
            temp.push_back(normal[2]);
            
            // Store the vector containing the normals
            normals.push_back(temp);
        }
    }
}

/*
 * load method
 * Loads points from a file and gets them ready for rotation
 */
void load() {
    
    // Open the file ** PLEASE CHANGE THIS TO REFLECT WHERE THE FILE IS FOR YOU **
    file.open("vase.txt", ios::in);
    
    // Declare variables
    string line;
    int i = 0;
    
    // Check if the file is open
    if(file.is_open()) {
        
        // While the line read is not the end of file
        while(getline(file,line)) {
            
            // Saves a copy of the string in s1
            istringstream s1(line);
            double x,z;
            
            // Set the values for x and z
            s1 >> x >> z >> z;
            
            // Calculate the points for x and z
            points(x/4,z/4);
            i++;
        }
        
        // Calculate the normals for the points
        normalCalc();
    }
    
    // Close the file
    file.close();
}

/*
 * display method
 * This method renders the scene and generates the polygonal mesh
 */
void display(void) {
    
    // Set the position of the light source
    GLfloat position[] = {5.0, 1.0, 1.0, 1.0};
    
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // If user presses 's', then start rotating light and axis
    if(animate){
        
        // Draw the axis and rotate them
        glPushMatrix();
        glRotated((GLdouble)spin,1.0,1.0,1.0) ;
        //draw();
        glPopMatrix();
        spin = (spin +2) % 360;
    }
    
    // Set the light
    glPushMatrix();
    
    // Moving the light around axis if 's' is pressed
    glRotated((GLdouble)spin,0.0,1.0,1.0);
    
    // Creating light source
    glLightfv(GL_LIGHT0,GL_POSITION,position);
    glPopMatrix();
    
    // Redraw the screen
    glutPostRedisplay();
    
    // Set the color of the object
    glColor3f(2.0,0.0,0.0) ;
    
    // Loop through the set of points
    for(int i = 0; i < pts.size()-1; ++i){
        for(int j = 0; j < pts[0].size(); ++j){
            
            // Get the normals
            vector<GLfloat> tempNormal = normals[i+j];
            
            // Triangulate the data to form the first polygon
            glBegin(GL_TRIANGLES) ;
            glNormal3d(tempNormal[0],tempNormal[1],tempNormal[2]);
            
            glVertex3d(pts[i][j][0],pts[i][j][1],pts[i][j][2]);
            
            // Calculate the line between points 1 and 2
            if(j < pts[0].size()-1){
                glVertex3d(pts[i][j+1][0],pts[i][j+1][1],pts[i][j+1][2]);
            }
            
            else{
                glVertex3d(pts[i][0][0],pts[i][0][1],pts[i][0][2]);
            }
            
            // Calculate the line between points 4 and 1
            if(j < pts[0].size()-1){
                glVertex3d(pts[i+1][j+1][0],pts[i+1][j+1][1],pts[i+1][j+1][2]);
            }
            
            else{
                glVertex3d(pts[i+1][0][0],pts[i+1][0][1],pts[i+1][0][2]);
            }
            
            
            glVertex3d(pts[i][j][0],pts[i][j][1],pts[i][j][2]);
            
            // Calculate the line between points 2 and 4
            if(j < pts[0].size()-1){
                glVertex3d(pts[i][j+1][0],pts[i][j+1][1],pts[i][j+1][2]);
                glVertex3d(pts[i+1][j+1][0],pts[i+1][j+1][1],pts[i+1][j+1][2]);
            }
            
            else{
                glVertex3d(pts[i][0][0],pts[i][0][1],pts[i][0][2]);
                glVertex3d(pts[i+1][0][0],pts[i+1][0][1],pts[i+1][0][2]);
            }
            
            glEnd() ;
            
            // Triangulate points to form the second polygon
            glBegin(GL_TRIANGLES);
            glNormal3d(tempNormal[0],tempNormal[1],tempNormal[2]);
            
            glVertex3d(pts[i][j][0],pts[i][j][1],pts[i][j][2]);
            
            // Calculate the line between points 1 and 3
            glVertex3d(pts[i+1][j][0],pts[i+1][j][1],pts[i+1][j][2]);
            
            // Calculate the line between points 4 and 1
            if(j < pts[0].size()-1){
                glVertex3d(pts[i+1][j+1][0],pts[i+1][j+1][1],pts[i+1][j+1][2]);
            }
            
            else{
                glVertex3d(pts[i+1][0][0],pts[i+1][0][1],pts[i+1][0][2]);
            }
            
            glVertex3d(pts[i][j][0],pts[i][j][1],pts[i][j][2]);
            
            // Calculate the line between points 3 and 4
            if(j < pts[0].size()-1){
                glVertex3d(pts[i+1][j][0],pts[i+1][j][1],pts[i+1][j][2]);
                glVertex3d(pts[i+1][j+1][0],pts[i+1][j+1][1],pts[i+1][j+1][2]);
            }
            
            else{
                glVertex3d(pts[i+1][j][0],pts[i+1][j][1],pts[i+1][j][2]);
                glVertex3d(pts[i+1][0][0],pts[i+1][0][1],pts[i+1][0][2]);
            }
            
            glEnd();
        }
    }
    
    // Redraw the screen
    glutSwapBuffers();
}

/*
 * view method
 * This method sets up the camera to view the object
 */
void view() {
    
    // Operation on the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Set up a perspective projection matrix
    gluPerspective(VIEW_ANGLE, ASPECT_RATIO, NEAR, FAR);
    
    // Operation on the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set the camera's view
    gluLookAt(EYEx,EYEy,EYEz,GAZEx,GAZEy,GAZEz,UPx,UPy,UPz) ;
}

/*
 * reshape method
 * This method handles reshaping the screen
 */
void reshape(int w, int h) {
    glViewport(0,0,(GLsizei) w,(GLsizei) h) ;
    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    glOrtho((double)-SCREEN/2,(double)SCREEN/2,(double)-SCREEN/2,(double)SCREEN/2,NEAR,FAR);
    glMatrixMode(GL_MODELVIEW) ;
    glLoadIdentity() ;
}

/*
 * keyboard method
 * This method allows the user to run the bonus part of the 
 * assignment by pressing 's'
 * The user can also exit the program by pressing 'q' 
 */
void keyboard(unsigned char key, int x, int y) {
    switch(key){
            
        // If 's' is pressed run the bonus animation
        case 's':
            animate = true;
            glutIdleFunc(display);
            break;
            
        // If 'q' is pressed then exit the program
        case 'q':
            exit(0);
            break;
        
        default:
            break;
    }
}

/*
 * Main method
 * The main method starts by generating the points
 * Next is setting up opengl, and finally running the program generate points
 */
int main(int argc, char** argv){
    
    // Load the points
    load();
    
    // Setting up the window
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(SCREEN, SCREEN);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Assignment 2 - jkaba");
    
    // Display the rendered mesh
    glutDisplayFunc(display);
    
    // Reshape function
    glutReshapeFunc(reshape);
    
    // Setting up faces, lighting, and materials
    glFrontFace(GL_CCW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specref);
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,45);
    
    // Setting up the view, and keyboard function
    glutIdleFunc(view);
    glutKeyboardFunc(keyboard);
    
    // Main loop
    glutMainLoop();
}