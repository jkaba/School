#ifndef POINTCANVAS_H
#define POINTCANVAS_H

#include "vector.h"
#include <vector>

//
// PointCanvas
//
// A 2D surface on which points are created and positioned.
// Mouse commands can be issued to manipulate the points on the canvas.
//
class PointCanvas
{
public:
    // Default constructor
    PointCanvas() : clickedPointIndex(-1) {}

    // Return the points currently on the canvas.
    const std::vector<Vector2D>& getPoints() const { return points; }
   
    // Add the given 2D point to the canvas.
    //It will be added to the end of the list of points.
    void addPoint(float x, float y) { points.push_back(Vector2D(x,y)); }
    void addPoint(const Vector2D& p) { points.push_back(p); }

    // Remove all points from the canvas.
    void clearPoints() { points.clear(); }

    // Mouse event handler functions.
    // Returns true iff the state of the canvas has changed.
    bool mouseDown(int button, float x, float y);
    bool mouseUp(int button, float x, float y);
    bool mouseMove(float x, float y);

private:
    std::vector<Vector2D> points;
    int clickedPointIndex;
    
};

#endif
