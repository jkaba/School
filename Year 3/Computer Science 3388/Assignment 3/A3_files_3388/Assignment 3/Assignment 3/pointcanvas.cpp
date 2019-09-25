#include "pointcanvas.h"


bool PointCanvas::mouseDown(int button, float x, float y)
{
    if (button == 0) // Left mouse button
    {
        clickedPointIndex = -1;
        static const float EPSILON_DISTANCE = 0.03f;
        Vector2D clickLocation(x, y);

        // To find which point was clicked on (if any), check the distance
        // of each point to the click location.
        for (std::size_t i = 0; i < points.size(); ++i)
        {
            float h = (clickLocation - points[i]).norm();
            if (h < EPSILON_DISTANCE)
            {
                clickedPointIndex = i;
                break;
            }
        }

        if (clickedPointIndex >= 0)
        {
            return mouseMove(x, y);
        }
        else
        {
            // If no point was clicked, add a new point 
            // at the position where the click occurred.
            addPoint(x, y);
            clickedPointIndex = points.size()-1;
            return true;
        }
    }
    return false;
}


bool PointCanvas::mouseUp(int button, float x, float y)
{
    if (button == 0)
    {
        // We are no longer manipulating any points
        clickedPointIndex = -1;
    }
    return false;
}


bool PointCanvas::mouseMove(float x, float y)
{
    if (clickedPointIndex >= 0 && points.size() > 0)
    {
        if (x < 0.0) x = 0.0;
        if (x > 1.0) x = 1.0;
        if (y < 0.0) y = 0.0;
        if (y > 1.0) y = 1.0;
        points[clickedPointIndex] = Vector2D(x, y);
        return true;
    }
    return false;
}


