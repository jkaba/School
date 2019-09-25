/* 
    CS3388A Assignment 1
    Name: Jameel Kaba
    GAUL ID: jkaba
    Email: jkaba@uwo.ca
    Student #: 250796017
 */

// Include statements
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctime>

// Define constants
#define SCREEN 640                                          // Screen size
#define numRec 16                                           // Number of rectangles
#define color (rand() % 256)                                // Random RGB value
#define displacement (float(rand() % 10) + (10)) / 100      // To be added to randCorner to make rectangles spaced
#define corner (float(rand() % 160) - 80) / 100             // Value of x/y co-ordinate
#define rotate (rand() % 2)                                 // Rotate value
#define direct (float(rand() % 7) + (-3))                   // Direction value
#define speed (float(rand() % 5+1) /5000)                   // Value of speed

/* 
 RECTANGLE CLASS
 
 This class is used to create a rectangle object which will be transformed
 These rectangle objects are stored in an array
 
 */

class Rectangle{
public:
    Rectangle();
    Rectangle(float, float, float, float, int, int, int);
};

/* 
 STANDARD CONSTRUCTOR
 
 This constrcutor is used to create the array which stores rectangles
 
 */
Rectangle::Rectangle(){
}

/* 
 SPECIFIC CONSTRUCTOR
 
 This constructor takes in 4 floats, and 3 int values and creates a colored rectangle
 Input: 4 floats to specify the x and y positions, and 3 ints to specifiy the colors
 Output: A rectangle at the specified position and colors
 
 */
Rectangle::Rectangle(float x, float y, float x2, float y2, int red, int green, int blue){
    glColor3ub(red, green, blue);
    glRectf(x, y, x2, y2);
}

/* VARIABLE DECLARATIONS */

float xVal[numRec];                                 // Array of X values
float yVal[numRec];                                 // Array of Y values
float xDisp[numRec];                                // Array of displacement values to be added to X
float yDisp[numRec];                                // Array of displacement values to be added to Y
float direction[numRec][2];                         // Direction array to determine movement direction
int redVal[numRec];                                 // Array of Red values
int greenVal[numRec];                               // Array of Green values
int blueVal[numRec];                                // Array of Blue values
int rotVal[numRec];                                 // Array of rotation values
float countArray[numRec];                           // Array of counter values

/*
 INITIALIZE
 
 This function provides each array with an appropriate number
 The random numbers are the constants that were defined at the top
 
 */
void initialize(void){
    srand(time(NULL));
    for(int i = 0; i < numRec; i++){
        xVal[i] = corner;                               // X1 value
        yVal[i] = corner;                               // Y1 value
        xDisp[i] = displacement;                        // Displacement to be subtracted from X1 value
        yDisp[i] = displacement;                        // Displacement to be subtracted from Y1 value
        
        direction[i][0] = (direct * speed);              // Direction in the x direction will be moving in a random direction
        direction[i][1] = (direct * speed);              // Direction in the y direction will be moving in a random direction
        
        // If the direction value in either the x or y direction is 0 then use 2 * speed
        if(direction[i][0] == 0 || direction[i][1] == 0){
            direction[i][0] = (2 * speed);                   // Direction in the x direction will be moving in a random direction
            direction[i][1] = (2 * speed);                   // Direction in the y direction will be moving in a random direction
        }
        
        redVal[i] = color;                              // Red value
        greenVal[i] = color;                            // Green value
        blueVal[i] = color;                             // Blue value
        rotVal[i] = rotate;                             // Rotation value used to determine wether to rotate clock/counter direction
        countArray[i] = 0;                              // Value for counters are set to 0 to start
    }
}

/* 
 DISPLAY
 
 This function will create the rectangles and perform the transformations on them
 
 */
void display(void)
{
    // Clears window and sets the background color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT) ;
    
    // For loop used to perform the bulk of the action
    for(int i = 0; i < numRec; i++){
        
        // Set the matrix mode to model view and push the matrix
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        
        // Define variables to be used in screen wrap checking and for translating
        
        // Calculate the X2 and Y2 positions by adding displacement to the initial x1 and y1 points
        float x2 = xVal[i] + xDisp[i];
        float y2 = yVal[i] + yDisp[i];
        
        // Initial translation (Translate to origin)
        float xTrans = (xVal[i]+(x2)/2)+(direction[i][0]*countArray[i]);
        float yTrans = (yVal[i]+(y2)/2)+(direction[i][1]*countArray[i]);
        
        // Second translation (Translate back to where it was)
        float negXTrans = -(xVal[i]+(x2)/2)+(direction[i][0]*countArray[i]);
        float negYTrans = -(yVal[i]+(y2)/2)+(direction[i][1]*countArray[i]);
        
        // Change the X and Y values by adding the direction to it
        xVal[i] = xVal[i] + (direction[i][0] * countArray[i]);
        yVal[i] = yVal[i] + (direction[i][1] * countArray[i]);
        
        /* TRANSLATE 1 */
        // Translate the rectangle to origin
        glTranslatef(xTrans, yTrans, 0.0);
        
        /* SCREEN WRAP AROUND */
        // If the x or y values are out of bounds
        if(xVal[i] > 1.2 || xVal[i] < -1.2 || yVal[i] > 1.2 || yVal[i] < -1.2){
            
            // If X is out of bounds to the right, shift the rectangle to the left
            if(xVal[i] > 1.2){
                xVal[i] = -1.1;
                x2 = xVal[i] + xDisp[i];
            }
            
            // If X is out of bounds to the left, shift the rectangle to the right
            if(xVal[i] < -1.2){
                xVal[i] = 1.1;
                x2 = xVal[i] + xDisp[i];
            }
            
            // If Y is out of bounds to the top, shift the rectangle to the bottom
            if(yVal[i] > 1.2){
                yVal[i] = -1.1;
                y2 = yVal[i] + yDisp[i];
            }
            
            // If Y is out of bounds to the bottom, shit the rectangle to the top
            if(yVal[i] < -1.2){
                yVal[i] = 1.1;
                y2 = yVal[i] + yDisp[i];
            }

            // Reset the Counter at position i to 0
            countArray[i] = 0;
        }

        /* ROTATIONS */
        // If the rotation value at i is 0, then rotate the rectangle counter-clockwise
        if(rotVal[i] == 0){
            glRotatef(100*countArray[i], 0, 0, -1.0);
        }
        
        // Else the rotation value is 1, so rotate the rectangle clockwise
        else{
            glRotatef(100*countArray[i], 0, 0, 1.0);
        }
        
        /* SCALING */
        // Scale the rectangle using sin and cos functions to periodically grow and shrink
        
        glScalef(sinf(90+countArray[i]), sinf(90+countArray[i]), 1.0);
        
        /* TRANSLATE 2 */
        // Translate the Rectangle back to it's starting position
        glTranslatef(negXTrans, negYTrans, 0.0);
        
        /* CREATION */
        // Create the rectangle using the appropriate variables 
        Rectangle r = Rectangle(xVal[i], yVal[i], x2, y2, redVal[i], blueVal[i], greenVal[i]);
        
        // Pop the matrix and increment the counter in position 'i' of the array
        glPopMatrix();
        countArray[i] = countArray[i] + 0.01;
    }
    
    // Redraw the screen
    glutSwapBuffers() ;
}

/*
 PLAY 
 
 Play function used to take the user's keyboard input
 - If the user presses 's' then run the program
 - If the user presses 'q' then quit the program
 - If the user presses any other key then wait till either 's' or 'q' are pressed
 
 */
void play(unsigned char key, int x, int y){
    switch (key) {
        
        case 's':
            glutIdleFunc(display) ;
            break;
        
        case 'q':
            exit(0);
            
        default:
            break;
    }
}

/*
 MAIN
 
 Main function which runs the program.
 Order of events
 - Initializes random variables
 - Creates initial window, displaying the x number of rectangles
 - Waits on user to press a key before either running/quiting the program
 
 */
int main(int argc, char** argv)
{
    initialize() ;
    glutInit(&argc, argv) ;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB) ;
    glutInitWindowSize(SCREEN,SCREEN) ;
    glutInitWindowPosition(100,100) ;
    glutCreateWindow("Assignment 1 - Jameel Kaba") ;
    glutDisplayFunc(display) ;
    glutKeyboardFunc(play);
    glutMainLoop() ;
    return 0;
}