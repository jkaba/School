/*
 * CS3388A Assignment 4
 * Name: Jameel Kaba
 * GAUL/UWO ID: jkaba
 * Student #: 250796017
 *
 * ray.h is the header file containing the method headers
 * for calculating the rays 
 */

// define statements
#ifndef RAY_H
#define RAY_H

// include statement
#include "define.h"

// method headers
void computeRay(RAY *ray, VECTOR3D *viewPoint, VIEWPORT *viewport, PIXEL *pixel, VEC_BASIS *cameraFrame, double distance);
void computeShadowRay(RAY *ray, SPHERE_INTERSECTION *intersection, VECTOR3D *light);
void computeReflectedRay(RAY *reflectedRay, RAY *incidenceRay, SPHERE_INTERSECTION *intersection);

#endif