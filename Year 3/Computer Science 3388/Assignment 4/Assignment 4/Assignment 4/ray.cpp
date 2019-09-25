/*
 * CS3388A Assignment 4
 * Name: Jameel Kaba
 * GAUL/UWO ID: jkaba
 * Student #: 250796017
 *
 * ray.cpp contains methods used in determining the rays
 */

// include statements
#include "ray.h"
#include "vectors.h"

/*
 * computeRay method
 * This method computes a ray's origin and direction vectors
 */
void computeRay(RAY *ray, VECTOR3D *viewPoint, VIEWPORT *viewport, PIXEL *pixel, VEC_BASIS *cameraFrame, double distance){
    
    // Initialize variables
    float u;
    float v;
    VECTOR3D v1;
    VECTOR3D v2;
    VECTOR3D v3;
    VECTOR3D v4;
    VECTOR3D dir;
    
    // Calculate the u and v values for the camera
	u = (double)(viewport->xvmin) + (double)(pixel->i) + 0.5;
	v = (double)(viewport->yvmin) + (double)(pixel->j) + 0.5;
    
    // Scale the n value of the camera by negative distance and store in v1
	vectorScale(-distance, &v1, &cameraFrame->n);
    
    // Scale the u value of the camera by u and store in v2
	vectorScale(u, &v2, &cameraFrame->u);
    
    // Scale the v value of the camera by v and store in v3
	vectorScale(v, &v3, &cameraFrame->v);
    
    // Set the ray's origin points to be the view point's x, y, z values
	ray->origin.x = viewPoint->x;
	ray->origin.y = viewPoint->y;
	ray->origin.z = viewPoint->z;
    
    // Add v1 and v2 and store the result in v4
	vectorAdd(&v4, &v1, &v2);
    
    // Add v4 and v3 and store the result in dir
	vectorAdd(&dir, &v4, &v3);
    
    // Normalize dir
	vectorNormalize(&dir);
    
    // Set the ray's direction points to be dir's x, y, z values
	ray->direction.x = dir.x;
	ray->direction.y = dir.y;
	ray->direction.z = dir.z;
}

/*
 * computeReflectedRay method
 * This method calculates the reflected ray's origin and direction vectors
 */
void computeReflectedRay(RAY *reflectedRay, RAY *incidenceRay, SPHERE_INTERSECTION *intersection){
    
    // initialize variables
	double dp1;
    VECTOR3D scaledNormal;
    VECTOR3D reflectedDirection;
    
    // Set dp1 to be the dot product between the intersections normal points and the incidence ray's direction points
	dp1 = dotProduct(&intersection->normal, &incidenceRay->direction);
    
    // Set dp1 to be 2 times itself
	dp1 = 2*dp1;
    
    // Scale the intersections normal points by dp1 and set the result to scaledNormal
	vectorScale(dp1, &scaledNormal, &intersection->normal);
    
    // Set reflected Direction to be the vector subtraction between the incidence ray's direction and scaled normal
    vectorSubtract(&reflectedDirection, &incidenceRay->direction, &scaledNormal);
    
    // Set the reflected ray's origin to be the intersections x, y, z points
	reflectedRay->origin.x = intersection->point.x;
	reflectedRay->origin.y = intersection->point.y;
	reflectedRay->origin.z = intersection->point.z;
    
    // Set the reflected ray's origin to be the reflected directions x, y, z points
	reflectedRay->direction.x = reflectedDirection.x;
	reflectedRay->direction.y = reflectedDirection.y;
	reflectedRay->direction.z = reflectedDirection.z;
}

/*
 * computeShadowRay method
 * This method calculates the shadow ray /  ray produced from the shadow
 */
void computeShadowRay(RAY *ray, SPHERE_INTERSECTION *intersection, VECTOR3D *light){
    
    // initialize direction vector
	VECTOR3D direction;
    
    // Set the ray's origin points to be the intersections x, y, z points
	ray->origin.x = intersection->point.x;
	ray->origin.y = intersection->point.y;
	ray->origin.z = intersection->point.z;
    
    // Set direction to be the vector subtraction between light and the intersections points
	vectorSubtract(&direction, light, &intersection->point);
    
    // normalize direction
	vectorNormalize(&direction);
    
    // Set the ray's direction points to be directions x, y, z values
	ray->direction.x = direction.x;
	ray->direction.y = direction.y;
	ray->direction.z = direction.z;
}