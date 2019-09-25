/*
 * CS3388A Assignment 4
 * Name: Jameel Kaba
 * GAUL/UWO ID: jkaba
 * Student #: 250796017
 *
 * sphere.h contains the method headers used in regards to the
 * intersection between a sphere and a ray of light 
 */

// define statements
#ifndef SPHERE_H
#define SPHERE_H

// include statement
#include "define.h"

// method headers
bool sphereIntersection(RAY *ray, SPHERE *sphere, SPHERE_INTERSECTION *intersection);
void intersectionNormal(SPHERE *sphere, SPHERE_INTERSECTION *intersection, RAY *ray);
void copyIntersectionStruct(SPHERE_INTERSECTION *intersection1, SPHERE_INTERSECTION *intersection2);

#endif