/*
 * CS3388A Assignment 4
 * Name: Jameel Kaba
 * GAUL/UWO ID: jkaba
 * Email: jkaba@uwo.ca
 * Student #: 250796017
 *
 * This program is a ray-tracing application where the scene 
 * consists of three colored spheres bouncing up and down off 
 * of a floor. The scene also contains ambient, diffuse, and specular
 * lighting. The spheres cast shadows on the floor and on each other
 * based on where the light source is
 *
 * I used the following online resources for reference in regards to shading and ray-tracing
 * https://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/lighting.php
 * http://ruh.li/GraphicsPhongBlinnPhong.html
 * https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing/ray-tracing-practical-example
 * http://homepages.paradise.net.nz/nickamy/simpleraytracer/simpleraytracer.htm
 */

// Include Statements
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "vectors.h"
#include "sphere.h"
#include "shading.h"
#include "ray.h"

// Define Statements
#define NSPHERES 4
#define VIEWPLANE 400
#define SCREEN 800
#define FOCALDIST 1000
#define RADIUS 200

// Defining global variables
VEC_BASIS cameraFrame;
VECTOR3D viewPoint;
VECTOR3D light;
SPHERE sphere[NSPHERES];
VIEWPORT viewport;

double focalDistance;
double color;
double lightIntensity;
double ambientLightIntensity;

DIRECTION direction[NSPHERES];

static int window;

/*
 * initialize method
 * This method sets up the camera, viewpoint, camera frame, light, and spheres
 */
void initialize(void) {
    
    // Set direction vector to contain up and down
	direction[0] = up;
	direction[1] = down;
	direction[2] = up;
    
    // Set up the x/y min and max to be -/+ VIEWPLANE
	viewport.xvmin = -VIEWPLANE;
	viewport.yvmin = -VIEWPLANE;
	viewport.xvmax = VIEWPLANE;
	viewport.yvmax = VIEWPLANE;
    
    // Set the u, v, n vectores for the camera frame
	cameraFrame.u.x = 1.0;
	cameraFrame.u.y = 0.0;
	cameraFrame.u.z = 0.0;
	cameraFrame.v.x = 0.0;
	cameraFrame.v.y = 1.0;
	cameraFrame.v.z = 0.0;
	cameraFrame.n.x = 0.0;
	cameraFrame.n.y = 0.0;
	cameraFrame.n.z = 1.0;
    
    // Set up the view point x, y, z values
	viewPoint.x = (viewport.xvmax - viewport.xvmin) / 2.0;
	viewPoint.y = (viewport.yvmax - viewport.yvmin) / 2.0;
	viewPoint.z = 0.0;
    
    // Calculate the light x, y, z values
	light.x = viewPoint.x - 1300;
	light.y = viewPoint.y + 1300;
	light.z = viewPoint.z - 300;
    
    // Set the value for ambient light, and regular light intensity
	ambientLightIntensity = 1.0;
	lightIntensity = 1.0;
    
    // Set the focal distance
	focalDistance = FOCALDIST;
    
    // Sphere 0 is the small blue ball
    // Set the radius for sphere 0
	sphere[0].radius = RADIUS/1.5;
    
    // Calculate and set the center position for sphere 0
	sphere[0].center.x  = viewPoint.x - (RADIUS+30);
	sphere[0].center.y  = viewPoint.y ;
	sphere[0].center.z  = viewPoint.z - focalDistance - (2*RADIUS+20);
    
    // Set the color for sphere 0 (green)
	setColorArray(sphere[0].kd_rgb, 0.0, 1.0, 0.0);
	setColorArray(sphere[0].ks_rgb, 1.0, 1.0, 1.0);
	setColorArray(sphere[0].ka_rgb, 0.0, 0.2, 0.0);
    
    // Set the shininess value for sphere 0
	sphere[0].shininess = 100.0;
    
    // Sphere 1 is the medium green ball
    // Set the radius for sphere 1
	sphere[1].radius = RADIUS/1.2;
    
    // Calculate and set the center position for sphere 1
	sphere[1].center.x  = viewPoint.x + 0;
	sphere[1].center.y  = viewPoint.y + 50;
	sphere[1].center.z  = viewPoint.z - focalDistance - (3*RADIUS+20);
    
    // Set the color for sphere 1 (blue)
	setColorArray(sphere[1].kd_rgb, 0.0, 0.0, 1.0);
	setColorArray(sphere[1].ks_rgb, 1.0, 1.0, 1.0);
	setColorArray(sphere[1].ka_rgb, 0.0, 0.0, 0.2);
    
    // Set the shininess value for sphere 1
	sphere[1].shininess = 10.0;
	
    // Sphere 2 is the large red ball
    // Set the radius of sphere 2
    sphere[2].radius = RADIUS;
    
    // Calculate and set the center position for sphere 2
	sphere[2].center.x  = viewPoint.x + (2*RADIUS+30);
	sphere[2].center.y  = viewPoint.y + 100;
    sphere[2].center.z  = viewPoint.z - focalDistance - (4*RADIUS+20);

    // Set the color for sphere 2 (red)
    setColorArray(sphere[2].kd_rgb, 1.0, 0.0, 0.0);
	setColorArray(sphere[2].ks_rgb, 1.0, 1.0, 1.0);
	setColorArray(sphere[2].ka_rgb, 0.2, 0.0, 0.0);
    
    // Set the shininess value for sphere 2
	sphere[2].shininess = 100.0;
    
    // Sphere 3 is the ground plane which the balls bounce off of
    // Set the radius for sphere 3
	sphere[3].radius = 100*RADIUS;
    
    // Calculate and Set the center position for sphere 3
	sphere[3].center.x  = viewPoint.x ;
	sphere[3].center.y  = viewPoint.y - 100*RADIUS-130;
	sphere[3].center.z  = viewPoint.z - focalDistance - (4*RADIUS+20);
    
    // Set the color for sphere 3 (light brown)
	setColorArray(sphere[3].kd_rgb, 0.75, 0.5, 0.25);
	setColorArray(sphere[3].ks_rgb, 1.0, 1.0, 1.0);
	setColorArray(sphere[3].ka_rgb, 0.5, 0.5, 0.5);
    
    // Set the shininess value for sphere 3
	sphere[3].shininess = 100.0;
    
    // Set the background and set to orthographic projection
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, SCREEN, 0.0, SCREEN);
}

/*
 * bounce method
 * This method causes the spheres to bounce up and down
 */
void bounce(void){
    
    // If direction 0 is up
	if (direction[0] == up){
        
        // Is the center of sphere 0's y value within the boundary
		if (sphere[0].center.y < viewport.yvmax+300){
            
            // Move sphere 0 up
			sphere[0].center.y += 10;
		}
        
        // Else set the direction down
		else{
			direction[0] = down;
		}
	}
    
    // If direction 0 is down
	else if (direction[0] == down){
        
        // If sphere 0 is within the boundary
		if (sphere[0].center.y > viewport.yvmin+900){
            
            // Move sphere 0 down
			sphere[0].center.y -= 10;
		}
        
        // Else set direction 0 to up
		else{
			direction[0] = up;
		}
	}
    
    // If direction 1 is up
	if (direction[1] == up){
        
        // If sphere 1 is within the boundary
		if (sphere[1].center.y < viewport.yvmax+300){
            
            // Move sphere 1 up
			sphere[1].center.y += 20;
		}
        
        // Else set direction 1 to down
		else {
			direction[1] = down;
		}
	}
    
    // If direction 1 is down
	else if (direction[1] == down){
        
        // If sphere 1 is within the boundary
		if (sphere[1].center.y > viewport.yvmin+900){
            
            // Move sphere 1 down
			sphere[1].center.y -= 20;
		}
        
        // Else set direction 1 to up
		else {
			direction[1] = up;
		}
	}
    
    // If direction 2 is up
	if (direction[2] == up){
        
        // If sphere 2 is within the boundary
		if (sphere[2].center.y < viewport.yvmax+300){
            
            // Move sphere 2 up
			sphere[2].center.y += 50;
		}
        
        // Else set direction 2 to down
		else {
			direction[2] = down;
		}
	}
    
    // If direction 2 is down
	else if (direction[2] == down){
        
        // If sphere 2 is within the boundary
		if (sphere[2].center.y > viewport.yvmin+900){
            
            // Move sphere 2 down
			sphere[2].center.y -= 50;
		}
        
        // Else set direction 2 to up
		else {
			direction[2] = up;
		}
	}
}

/*
 * display method
 * This method is where the ray-tracing and main program are contained
 */
void display(void){
    
    // Run the bounce method
	bounce();
    
    // Clear the Buffer
	glClear(GL_COLOR_BUFFER_BIT);
    
    // For loop to calculate the ray-tracing for each pixel
	for (int i=0; i<(viewport.xvmax - viewport.xvmin); i++){
		for (int j=0; j<(viewport.yvmax - viewport.yvmin); j++){
            
            // Initialize variables
			int intersectionObject = -1;
			int reflectedIntersectionObject = -1;
			double currentLambda = 0x7fefffffffffffff;
			double currentReflectedLambda = 0x7fefffffffffffff;
            RAY ray;
            RAY shadowRay;
            RAY reflectedRay;
			PIXEL pixel;
            SPHERE_INTERSECTION intersection;
            SPHERE_INTERSECTION currentIntersection;
            SPHERE_INTERSECTION shadowRayIntersection;
            SPHERE_INTERSECTION reflectedRayIntersection;
            SPHERE_INTERSECTION currentReflectedIntersection;
            double red;
            double green;
            double blue;
            double theta;
            double reflectedTheta;
			bool bShadow = false;
			pixel.i = i;
			pixel.j = j;
            
            // Compute the ray
			computeRay(&ray, &viewPoint, &viewport, &pixel, &cameraFrame, focalDistance);
            
            // For each sphere
			for (int k = 0; k < NSPHERES; k++){
                
                // If the sphere/ray intersection is valid
				if (sphereIntersection(&ray, &sphere[k], &intersection)){
                    
                    // Compute the normal for the intersection
					intersectionNormal(&sphere[k], &intersection, &ray);
                    
                    // If the lambda in value for the intersection is less than the current lambda value
					if (intersection.lambdaIn < currentLambda){

                        // Set current lambda to the lambda in value of the intersection
						currentLambda = intersection.lambdaIn;
                        
                        // Set the intersection object to k
						intersectionObject = k;
                        
                        // Set current intersection to intersection
						copyIntersectionStruct(&currentIntersection, &intersection);
					}
				}
			}
            
            // If the intersection object value is greater than -1
			if (intersectionObject > -1){
                
                // Compute the shadow ray
				computeShadowRay(&shadowRay, &intersection, &light);
                
                // Set theta to be the dotproduct between shadow ray's direction and intersection's normal
				theta = dotProduct(&(shadowRay.direction), &(intersection.normal));
                
                // For each sphere
				for (int l = 0; l < NSPHERES; l++){
                    
                    // If l is not the intersection object
					if (l != intersectionObject){
                        
                        // See if the sphere/ray intersection is valid and that theta is larger than 0
                        if (sphereIntersection(&shadowRay, &sphere[l], &shadowRayIntersection) && (theta > 0.0)){
                            
                            // Set bShadow to true
							bShadow = true;
                        }
					}
				}
                
                // If bShadow is true
				if (bShadow){
                    
                    // Calculate the shadow for the red, blue, green values
					red = shadow(sphere[intersectionObject].ka_rgb[RED], ambientLightIntensity);
					green = shadow(sphere[intersectionObject].ka_rgb[GREEN], ambientLightIntensity);
					blue = shadow(sphere[intersectionObject].ka_rgb[BLUE], ambientLightIntensity);
				}
                
                // Else the light is not a shadow
				else{
                    
                    // Calculate the red, blue, green values, using phong shading
					red = phongShading(&currentIntersection, &light, &viewPoint,
						sphere[intersectionObject].kd_rgb[RED], sphere[intersectionObject].ks_rgb[RED], sphere[intersectionObject].ka_rgb[RED], sphere[intersectionObject].shininess, lightIntensity, ambientLightIntensity);
                    
					green = phongShading(&currentIntersection, &light, &viewPoint,
						sphere[intersectionObject].kd_rgb[GREEN], sphere[intersectionObject].ks_rgb[GREEN], sphere[intersectionObject].ka_rgb[GREEN], sphere[intersectionObject].shininess, lightIntensity, ambientLightIntensity);
                    
					blue = phongShading(&currentIntersection, &light, &viewPoint,
						sphere[intersectionObject].kd_rgb[BLUE], sphere[intersectionObject].ks_rgb[BLUE], sphere[intersectionObject].ka_rgb[BLUE], sphere[intersectionObject].shininess, lightIntensity, ambientLightIntensity);
				}
                
                // Set color
				glColor3f(red, green, blue);
                
                // Draw points from point i to point j
				glBegin(GL_POINTS);
				glVertex2i(i, j);
				glEnd();
                
                // Set the intersection object to -1
				intersectionObject = -1;
                
                // Set bShadow to false
				bShadow = false;
			}
            
            // Else intersection object is not greater than -1
            else{
                
                // Set the color to 0,0,0
				glColor3f(0.0, 0.0, 0.0);
                
                // Draw points from point i to point j
				glBegin(GL_POINTS);
				glVertex2i(i, j);
				glEnd();
                
                // Set intersection Object to -1
				intersectionObject = -1;
                
                // Set bShadow to false
				bShadow = false;
			}
            
            // Set the values for currentLambda, and currentReflectedLambda
			currentLambda = 0x7fefffffffffffff;
			currentReflectedLambda = 0x7fefffffffffffff;
		}
	}
	glutSwapBuffers();
}

/*
 * timerFunction method
 * This method lets the program continuously run rather than stop after 1 run through
 */
void timerFunction(int time){
    glutPostRedisplay();
    glutTimerFunc(10, timerFunction, 0);
}

/*
 * keyboard method
 * This method allows the user to exit the program by pressing 'q'
 */
void keyboard(unsigned char key, int x, int y) {
    switch(key){
        
        case 'q':
            exit(0);
            break;
            
        default:
            break;
    }
}

/*
 * main method
 * This is where everything happens from initilizing glut and opengl
 * to actually running the programm in the glutMainLoop
 */
int main (int argc, char** argv) {
	
	// initialize glut
	glutInit (&argc, argv);

    // Set the display mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Set the window position
	glutInitWindowPosition(0,0);

    // Set the window size to be Screen x Screen (800x800)
	glutInitWindowSize(SCREEN, SCREEN);
	
    // Create the window
	window = glutCreateWindow("CS3388A Assignment 4 - jkaba");
	
    // initialize opengl (camera, lighting, etc.)
	initialize();
	
    // Run the display function
	glutDisplayFunc(display);
    
    // Run the timer function
    timerFunction(0);
    
    // Run the keyboard function
    glutKeyboardFunc(keyboard);
	
    // Enter glutMainLoop
	glutMainLoop();
	return 0;
}