#ifndef CURVES_H
#define CURVES_H

#include "vector.h"
#include <vector>
#include <cstdlib>

// Enums indicating modes
enum CurveMode
{
    BEZIER_MODE,
	CUBIC_BSPLINE_MODE,
	BETA_SPLINE_MODE,
	BETA_SPLINE_CLOSEDCURVE_MODE,
	CUBIC_BSPLINE_PHANTOM_MODE
};


// Class representing different curves.  A curve is constructed with a set
// of control points, and can then be evaluated at any t=[0,1].
class curveOperations
{
public:
    // Default constructor
    curveOperations() {}

    // Construct from a list of control points.
    curveOperations(const std::vector<Vector2D>& points) : controlPoints(points) {}
   
    // Return the list of control points defining this curve.
    const std::vector<Vector2D>& getControlPoints() const 
    { return controlPoints; }

    // Change the control points that describe this curve.
    void setControlPoints(const std::vector<Vector2D>& points)
    { controlPoints = points; }
    
    // Add the given point to the end of the list of control points.
    void addControlPoint(const Vector2D& point) 
    { controlPoints.push_back(point); }

    // Remove all control points.
    void clearControlPoints() { controlPoints.clear(); }

    // Evaluate a Bezier curve at t = [0,1].
    Vector2D evaluateBezier(float t) const;  /*************** You have to write this function ***************/

	// Draw the curve as a sequence of line segments.
    void drawBezier() const;  /*************** You have to write this function ***************/


	// draw a cubic bspline curve
	void drawCubicBspline() const; /*************** You have to write this function ***************/


	// draw a Beta spline curve
	void drawBetaspline() const; /*************** You have to write this function ***************/


	// draw a closed betaspline curve
	void drawBetasplineClosedCurve() const; /*************** You have to write this function ***************/

	// draw cubic bspline with phantom endpoints
	void drawCubicBsplinePhantom() const; /*************** You have to write this function ***************/

    // Draw the control polygon of this bezier curve.
    void drawControlPolygon() const;

private:
    std::vector<Vector2D> controlPoints;

    // Compute the binomial coefficient (n k)
    // also known as nCk or "n choose k"
    // WARNING: Vulnerable to overflow if n is very large!
    static unsigned long binomialCoefficient(int n, int k);

    // Draw a line between the two given points.
    static void drawLine(const Vector2D& p1, const Vector2D& p2);
};




/*************************** You don't need to modify this block ***************************/
// CurveManager
// A class for keeping track curves and drawing them
class CurveManager
{
public:
    // Constructor
	CurveManager() : points(NULL), curveMode(BEZIER_MODE) {}
    
    // Mode modifiers
    void setCurveMode(CurveMode mode) { curveMode = mode; }
    
    // Update the set of points used to construct our curves.
    void updatePoints(const std::vector<Vector2D>* p) { points = p; }
    
    // Draw the curves formed by the current modes and set of points.
    void drawCurves() const;

private:
    const std::vector<Vector2D>* points; // Points used to construct curves
    CurveMode curveMode;                 // Current curve display mode
};
/*************************** You don't need to modify this block ***************************/



#endif
