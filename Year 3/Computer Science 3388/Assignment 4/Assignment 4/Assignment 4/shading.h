/*
 * CS3388A Assignment 4
 * Name: Jameel Kaba
 * GAUL/UWO ID: jkaba
 * Student #: 250796017
 *
 * shading.h contains the method headers for performing the
 * shading in the program
 */

// define statements
#ifndef SHADING_H
#define SHADING_H

// include statements
#include "define.h"

// method headers
double lambertShading(SPHERE_INTERSECTION *intersection, VECTOR3D *light, double kd, double ka, double intensity, double ambIntensity);
double phongShading(SPHERE_INTERSECTION *intersection, VECTOR3D *light, VECTOR3D *viewpoint, double kd, double ks, double ka, double p, double intensity, double ambIntensity);
double shadow(double ka, double ambIntensity);
void setColorArray(double *colorArray, double red, double green, double blue);

#endif