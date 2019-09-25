/*
 * CS3388A Assignment 4
 * Name: Jameel Kaba
 * GAUL/UWO ID: jkaba
 * Student #: 250796017
 *
 * define.h is meant to provide definitions of 
 * structures used throughout the other files used in this program
 */

// define statements
#ifndef DEFINE_H
#define DEFINE_H
#define PHONG
#define RED 0
#define GREEN 1
#define BLUE 2
typedef enum {down=0, up=1} DIRECTION;

// Vectors structure contains x, y, z points
struct VECTOR3D{
	double x;
	double y;
	double z;
};


// Viewport structure contains x/y min and max values
struct VIEWPORT {
	int xvmin;
	int yvmin;
	int xvmax;
	int yvmax;
};

// Pixel structure contains i, j point
struct PIXEL{
	int i;
	int j;
};

// Sphere intersection structure contains lamda in/out, normal and point vectors, and a boolean valid
struct SPHERE_INTERSECTION {
	double lambdaIn;
	double lambdaOut;
	VECTOR3D normal;
	VECTOR3D point;
	bool valid;
};

// Sphere contains a vector of center points, a radius, kd + ks + ka rgb arrays, shininess factor, boolean mirror
struct SPHERE{
	VECTOR3D center;
	double radius;
	double kd_rgb[3];
	double ks_rgb[3];
	double ka_rgb[3];
	double shininess;
};


// Ray contains an origin and direction point vector
struct RAY {
	VECTOR3D origin;
	VECTOR3D direction;
};

// Vector Basis contains a u, v, and n vector
struct VEC_BASIS {
	VECTOR3D u;
	VECTOR3D v;
	VECTOR3D n;
};

#endif