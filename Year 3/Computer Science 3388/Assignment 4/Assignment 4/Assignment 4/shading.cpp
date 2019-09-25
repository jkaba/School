/*
 * CS3388A Assignment 4
 * Name: Jameel Kaba
 * GAUL/UWO ID: jkaba
 * Student #: 250796017
 *
 * shading.cpp contains methods used in regards to the shading of a sphere
 */

// include statements
#include "shading.h"
#include "vectors.h"
#include "math.h"

/*
 * lambertShading method
 * This method calculates lambert shading for an intersection at which light is shined on the sphere
 */
double lambertShading(SPHERE_INTERSECTION *intersection, VECTOR3D *light, double kd, double ka, double intensity, double ambIntensity) {
    
    // Initialize variables
	double color;
	VECTOR3D l;
    
    // Set l to be the vector subtraction of light and the intersection point
	vectorSubtract(&l, light, &intersection->point);
    
    // Normalize l
	vectorNormalize(&l);
    
    // Calculate the value of color
	color = (kd * intensity * dotProduct(&l, &intersection->normal)) + (ka * ambIntensity);
    
    // If color is greater than 0 return color
	if (color > 0.0) {
		return color;
	}
    
    // Else return 0 as the color value
	else {
		return 0.0;
	}
}

/*
 * phongShading method
 * This method calculates the phong shading using the blinn-phong shading calculations
 */
double phongShading(SPHERE_INTERSECTION *intersection, VECTOR3D *light, VECTOR3D *viewpoint, double kd, double ks, double ka, double p, double intensity, double ambIntensity){
    
    // Initialize variables
    double diffuse = 0.0;
	double specular = 0.0;
	VECTOR3D l;
	VECTOR3D h;
	VECTOR3D v;
    
    // Set v to be the vector subtraction between viewpoint and the intersection point
	vectorSubtract(&v, viewpoint, &intersection->point);
    
    // Normalize v
	vectorNormalize(&v);
    
    // Set l to be the vector subtraction between light and the intersection point
	vectorSubtract(&l, light, &intersection->point);
    
    // Normalize l
	vectorNormalize(&l);
    
    // Set h to be the vector addition between v and l
	vectorAdd(&h, &v, &l);
    
    // Normalize h
	vectorNormalize(&h);
    
    // Calculate the diffuse value
    diffuse = kd * intensity * dotProduct(&l, &intersection->normal);
    
    // If diffuse is greater than 0 then set it to 0
    if (diffuse < 0.0){
        diffuse = 0.0;
    }
    
    // Calculate the specular value
	specular = ks * intensity * pow (dotProduct(&h, &intersection->normal), p);
    
    // If specular is greater than 0 then set it to 0
    if (specular < 0.0){
        specular = 0.0;
    }
    
    // Return the color produced when adding diffuse, specular, ambient lighting
	return (diffuse + specular + (ka * ambIntensity));
}
 
/* 
 * shadow method
 * This calculates the value of the shadow produced
 */
double shadow(double ka, double ambIntensity) {
	return (ka * ambIntensity);
}

/*
 * setColorArray method
 * This method is used to set the colors rgb values in the color array
 */
void setColorArray(double *colorArray, double red, double green, double blue) {
	colorArray[RED] = red;
	colorArray[GREEN] = green;
	colorArray[BLUE] = blue;
}