# Assignment 3

## Description
This assignment is about implementing a curve editor using OpenGL. You are provided with C++ source code which uses OpenGL to draw points on the screen by mouse click. You have to write the code to draw Bezier curve, B- spline and Beta-spline curves using these points.

## Intro
- Unzip the files, compile and run.
- At this point you will see a drawing screen where you can click mouse and draw points. This is a simple user interface for manipulating curves.
- You should be able to create and move the control points by clicking and dragging with the mouse. This functionality is provided by the PointCanvas class.
- Right-clicking brings up a menu comprising of different types of curves that you have to implement: basic Bezier curve, cubic B-spline curve, Beta-spline curve, closed Beta-spline curve and cubic B-spline with phantom endpoints.
- Finally, last 2 menu items are for clearing the screen and exiting from the program, which are already implemented. You will need to write code at the specified places in curves.cpp (and curves.h if you add any new function).

## Implementation
1. Bezier curve evaluation: Implement simple evaluation and rendering of Bezier curve.
2. Implement curveOperations::evaluateBezier to return the point along the Bezier curve at the given t-value.
3. Next, implement curveOperations::drawBezier.
4. Draw the curve by evaluating it at uniformly-spaced t-values, and then drawing lines between those points.
5. Draw cubic B-spline curve: Implement curveOperations::drawCubicBspline to draw a cubic B-spline curve from the clicked control points.
6. Use curveOperations::drawLine() to draw the curve after generating the points.
7. Draw Beta-spline curve: Implement curveOperations::drawBetaspline to draw a Beta-spline curve from the clicked control points.
8. Draw closed Beta-spline curve: Implement the function curveOperations::drawBetasplineClosedCurve.
9. Draw cubic B-spline curve with phantom endpoints: Implement curveOperations::drawCubicBsplinePhantom.
10. Write a short report: Experiment with different values of skew and tension parameters of Beta spline and write a report (less than one page) on your observations on the comparison of the curve behaviour on these parameters, and also compare with cubic B-spline curve.


