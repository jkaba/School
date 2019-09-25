/*
 * CS3388A Assignment 4
 * Name: Jameel Kaba
 * GAUL/UWO ID: jkaba
 * Student #: 250796017
 *
 * vector.h contains method headers for vector calculations
 */

// Define statements
#ifndef VECTORS_H
#define VECTORS_H

// Include statement
#include "define.h"

// Method Headers
void vectorSubtract(VECTOR3D *v1, VECTOR3D *v2, VECTOR3D *v3);
void vectorAdd(VECTOR3D *v1, VECTOR3D *v2, VECTOR3D *v3);
void vectorScale(double scale, VECTOR3D *v1, VECTOR3D *v2);
double dotProduct(VECTOR3D *v1, VECTOR3D *v2);
void vectorNormalize(VECTOR3D *v);

#endif