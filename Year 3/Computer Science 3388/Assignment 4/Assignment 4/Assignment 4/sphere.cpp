/*
 * CS3388A Assignment 4
 * Name: Jameel Kaba
 * GAUL/UWO ID: jkaba
 * Student #: 250796017
 *
 * sphere.cpp contains methods used in regards to the
 * intersection between the sphere and a ray of light
 */

// include statements
#include "sphere.h"
#include "math.h"
#include "vectors.h"

/*
 * sphereIntersection method
 * This method determines whether the intersection of where a ray of light hits the sphere
 * is valid or not
 * returns true if the ray is hitting the sphere at an intersection passed as parameter
 * returns false otherwise
 */
bool sphereIntersection (RAY *ray, SPHERE *sphere, SPHERE_INTERSECTION *intersection){
    
    // Initialize variables
	double discriminant;
    double A;
    double B;
    double C;
    double lambda1;
    double lambda2;
	VECTOR3D temp;
    
    // Set A to be the dot product of the ray's direction and the ray's direction
	A = dotProduct(&ray->direction, &ray->direction);
    
    // Set temp to contain the vector subtraction of the ray's origin and the sphere's center
	vectorSubtract(&temp, &ray->origin, &sphere->center);
    
    // Set B to be 2 times the dot product between temp and the ray's direction
	B = 2 * dotProduct(&temp, &ray->direction);
    
    // Set temp to contain the vector subtraction of the ray's origin and the sphere's center
	vectorSubtract(&temp, &ray->origin, &sphere->center);
    
    // Set C to be the (dot product of temp and temp) - (the sphere's radius times itself)
	C = dotProduct(&temp, &temp) - (sphere->radius * sphere->radius);
    
    // Calculate the discriminant value
	discriminant = B*B - 4*A*C;
    
    // if the discriminant is greater than or equal to 0
	if (discriminant >= 0) {
        
        // Calculate the values of lambda 1 and lambda 2
		lambda1 = (-B + sqrt(discriminant)) / (2*A);
		lambda2 = (-B - sqrt(discriminant)) / (2*A);
        
        // If both lambda 1 and 2 are greater than or equal to 0
		if (lambda1 >= 0 && lambda2 >= 0) {
            
            // Then compare if they are equal
			if (lambda1 == lambda2) {
                
                // If so then lambda in is equal to lambda out which is equal to lambda 1
				intersection->lambdaIn = intersection->lambdaOut = lambda1;
			}
            
            // Else if lambda 2 is larger than lambda 1
			else if (lambda1 < lambda2) {
                
                // lambda in is equal to lambda 1
				intersection->lambdaIn  = lambda1;
                
                // lambda out is equal to lambda 2
				intersection->lambdaOut = lambda2;
			}
            
            // Else lambda 1 is larger
			else {
                
                // lambda in is set to lambda 2
				intersection->lambdaIn  = lambda2;
                
                // lambda out is set to lambda 1
				intersection->lambdaOut = lambda1;
			}
            
            // The intersection is valid and return true
			intersection->valid = true;
			return true;
		}
        
        // Else one of the lambda values was less than 0
		else {
            
            // The intersection is not valid and return false
			intersection->valid = false;
			return false;
		}
	}
    
    // Else discriminant was less than 0
	else {
        
        // therefore the intersection is not valid and return false
		intersection->valid = false;
		return false;
	}
}

/*
 * intersectionNormal method
 * This method calculates the normalized intersection points
 * of where the ray hits a sphere
 */
void intersectionNormal(SPHERE *sphere, SPHERE_INTERSECTION *intersection, RAY *ray) {
    
    // initialize variables
    double lambda;
    double scale;
    VECTOR3D v1;
    VECTOR3D v2;
    VECTOR3D point;
    VECTOR3D normal;
    
    // Set lambda to equal the lambda in of the intersection
	lambda = intersection->lambdaIn;
    
    // Set v1 to be the ray's direction scaled by lambda
	vectorScale(lambda, &v1, &ray->direction);
    
    // Set point to be the vector addition between v1 and the ray's origin
	vectorAdd(&point, &v1, &ray->origin);
    
    // Set the intersection's x, y, and z points
	intersection->point.x = point.x;
	intersection->point.y = point.y;
	intersection->point.z = point.z;
    
    // Set v2 to be the vector subtraction between point and the center of the sphere
	vectorSubtract(&v2, &point, &sphere->center);
    
    // Set scale to be 1 over the radius of the sphere
	scale = 1.0 / sphere->radius;
    
    // Set normal to be v2 scaled by scale
	vectorScale(scale, &normal, &v2);
    
    // Normalize normal
	vectorNormalize(&normal);
    
    // Set the normalized intersection points
	intersection->normal.x = normal.x;
	intersection->normal.y = normal.y;
	intersection->normal.z = normal.z;
}

/*
 * copyIntersectionStruct method
 * This method copies the contents of a sphere intersection into another sphere intersection
 */
void copyIntersectionStruct(SPHERE_INTERSECTION *intersection1, SPHERE_INTERSECTION *intersection2) {
	intersection1->lambdaIn = intersection2->lambdaIn;
	intersection1->lambdaOut = intersection2->lambdaOut;
	intersection1->normal.x = intersection2->normal.x;
	intersection1->normal.y = intersection2->normal.y;
	intersection1->normal.z = intersection2->normal.z;
	intersection1->point.x = intersection2->point.x;
	intersection1->point.y = intersection2->point.y;
	intersection1->point.z = intersection2->point.z;
	intersection1->valid = intersection2->valid;
}
