/*
 * CS3388A Assignment 4
 * Name: Jameel Kaba
 * GAUL/UWO ID: jkaba
 * Student #: 250796017
 *
 * vectors.cpp is used for vector calculations
 */

// Include statements
#include "vectors.h"
#include "math.h"

/*
 * vectorSubtract method
 * This method takes 3 pointers to vectors as parameters
 *      - the first vector is the vector containing the results
 *      - the second and third vectors are used for performing the calculation
 */
void vectorSubtract(VECTOR3D *v1, VECTOR3D *v2, VECTOR3D *v3) {
	v1->x = v2->x - v3->x;
	v1->y = v2->y - v3->y;
	v1->z = v2->z - v3->z;
}

/*
 * vectorAdd method
 * This method takes 3 pointers to vectors as parameters 
 *      - the first vector is the vector containing the results
 *      - the second and third vectors are used for performing the calculation
 */
void vectorAdd(VECTOR3D *v1, VECTOR3D *v2, VECTOR3D *v3) {
	v1->x = v2->x + v3->x;
	v1->y = v2->y + v3->y;
	v1->z = v2->z + v3->z;
}

/*
 * vectorScale method
 * This method takes a scale factor and 2 pointers to vectors as parameters
 *      - The first vector will store the result
 *      - The second vector will be multiplied by the scale factor
 */
void vectorScale(double scale, VECTOR3D *v1, VECTOR3D *v2) {
	v1->x = scale * v2->x;
	v1->y = scale * v2->y;
	v1->z = scale * v2->z;
}

/*
 * dotProduct method
 * This method calculates the dot product between 2 vectors
 * Parameters are 2 pointers to vectors
 * Method returns the dot product of those 2 vectors
 */
double dotProduct(VECTOR3D *v1, VECTOR3D *v2) {
	return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
}

/*
 * vectorNormalize method
 * This method normalizes a vector that is passed as a parameter
 */
void vectorNormalize(VECTOR3D *v) {
	double magnitude;
	magnitude = sqrt(dotProduct(v,v));
	v->x = v->x / magnitude;
	v->y = v->y / magnitude;
	v->z = v->z / magnitude;
}