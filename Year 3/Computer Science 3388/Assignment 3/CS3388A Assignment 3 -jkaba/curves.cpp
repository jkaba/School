/*
 * CS3388A Assignment 3
 * Name: Jameel Kaba
 * Student #: 250796017
 * UWO Email: jkaba@uwo.ca
 * GAUL/UWO id: jkaba
 *
 * This program allows a user to draw the following curves
 * - Bezier
 * - Cubic B-Spline
 * - Beta Spline
 * - Closed Beta Spline
 * - Cubic B-Spline with phantom endpoints
 */

#include "curves.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <cassert>
#include <iostream>

Vector2D curveOperations::evaluateBezier(float t) const
{
    assert(t >= 0.0f && t <= 1.0f);
    assert(controlPoints.size() > 1);
    
    // Evaluate the Bezier curve at the given t parameter.
    // You may find the following functions useful:
    //  - curveOperations::binomialCoefficient(m,i) computes "m choose i",
    //      aka: (m over i)
    //  - std::pow(t,i) computes t raised to the power i
    
    //@@@@@@@@@@
    // YOUR CODE HERE
    
    // Create a vector to store the points
    Vector2D goal;
    
    // Set n to be the size of the controlpoint vector
    size_t n = controlPoints.size() - 1;
    
    // for loop that calculates the sum used for evaluating bezier curves
    for(int i = 0; i < controlPoints.size(); ++i){
        
        // Calculate the binomial coefficient for n choose i
        long binomialCoefficient = curveOperations::binomialCoefficient(n, i);
        
        // calculate the body of the sum
        float body = std::pow(1-t, n-i) * std::pow(t, i) * binomialCoefficient;
        
        // multiply point at i by the value of body
        Vector2D temp = controlPoints[i] * body;
        
        // store the point into goal
        goal = goal + temp;
    }
    
    // Return goal vector
    return goal;
    
    //@@@@@@@@@@
}

void curveOperations::drawBezier() const
{
    // Draw this Bezier curve.
    // Do this by evaluating the curve at some finite number of t-values,
    // and drawing line segments between those points.
    // You may use the curveOperations::drawLine() function to do the actual
    // drawing of line segments.
    
    //@@@@@@@@@@
    // YOUR CODE HERE
    
    // Create 2 vectors for the points
    Vector2D current;
    Vector2D next;
    
    // for loop that draws the line between points
    for(float t = 0.0; t < 0.99; t += 0.01){
        
        // Get the first point
        current = evaluateBezier(t);
        
        // Get the next point
        next = evaluateBezier(t + 0.01);
        
        // Draw the line between the first and next point
        curveOperations::drawLine(current, next);
    }
    
    //@@@@@@@@@@
    
}


void curveOperations::drawControlPolygon() const
{
    for (size_t i = 1; i < controlPoints.size(); ++i)
    {
        drawLine(controlPoints[i-1], controlPoints[i]);
    }
}


unsigned long curveOperations::binomialCoefficient(int n, int k)
{
    // Compute nCk ("n choose k")
    // WARNING: Vulnerable to overflow when n is very large!
    
    assert(k >= 0);
    assert(n >= k);
    
    unsigned long result = 1;
    for (int i = 1; i <= k; ++i)
    {
        result *= n-(k-i);
        result /= i;
    }
    return result;
}


void curveOperations::drawLine(const Vector2D& p1, const Vector2D& p2)
{
    glBegin(GL_LINES);
    glVertex2f(p1[0], p1[1]);
    glVertex2f(p2[0], p2[1]);
    glEnd();
}



// draw cubic bspline
void curveOperations::drawCubicBspline() const
{
    //@@@@@@@@@@
    // YOUR CODE HERE
    
    // Set n to represent the number of control points
    size_t n = controlPoints.size();
    
    // glBegin used for drawing lines
    glBegin(GL_LINE_STRIP);
    
    // For loop used for Calculating P(u)
    for (float u = 0; u < 0.75; u += 0.01){
        
        // setting x and y values to 0
        float x = 0;
        float y = 0;
        
        // Calculating the sum of PiB(nu-i) from nu-2 to nu+2
        for (float i = floor(n*u - 2); i < ceil(n*u + 2); i++){
            
            // Boolean check to ensure that i is a valid location in the vector
            bool check = (i >= 0 && i <= n);
            
            // Calculate the value of tau (tau = nu - i)
            float tau = n*u - i;
            
            // Initialize B
            float B;
            
            // If-Else statements to calculate the blending function B(tau)
            
            // If -2 <= tau <= -1 and i is a position in the point vector
            if (tau >= -2 && tau <= -1 && check){
                
                // Calculate B(tau)
                B = (std::pow((2 + tau), 3)) /6;
                
                // Calculate the x and y coordinates
                x += B * controlPoints[i][0];
                y += B * controlPoints[i][1];
            }
            
            // If -1 <= tau <= 0 and i is valid
            else if(tau >= -1 && tau <= 0 && check){
                
                // Calculate B(tau)
                B = (4 - (6 * std::pow((tau), 2)) - (3 * std::pow((tau), 3))) /6;
                
                // Calculate the x and y coordinates
                x += B * controlPoints[i][0];
                y += B * controlPoints[i][1];
            }
            
            // If 0 <= tau <= 1 and i is valid
            else if(tau >= 0 && tau <= 1 && check){
                
                // Calculate B(tau)
                B = (4 - (6 * std::pow((tau), 2)) + (3 * std::pow((tau), 3))) /6;
                
                // Calculate the x and y coordinates
                x += B * controlPoints[i][0];
                y += B * controlPoints[i][1];
            }
            
            // If 1 <= tau <= 2 and i is valid
            else if(tau >= 1 && tau <= 2 && check){
                
                // Calculate B(tau)
                B = (std::pow((2 - tau), 3)) /6;
                
                // Calculate the x and y coordinates
                x += B * controlPoints[i][0];
                y += B * controlPoints[i][1];
            }
            
            // Otherwise add 0 to x and y
            else{
                x += 0;
                y += 0;
            }
        }
        
        // Check if x and y are both greater than 0 then draw the line
        if(x > 0 && y > 0){
            glVertex2f(x, y);
        }
    }
    
    // glEnd to signal the end of line drawing
    glEnd();
    
    //@@@@@@@@@@
}


// draw betaspline
void curveOperations::drawBetaspline() const
{
    //@@@@@@@@@@
    // YOUR CODE HERE
    
    // Set n to be 1 less than the number of control points
    size_t n = controlPoints.size()-1;
    
    // glBegin used to draw the line
    glBegin(GL_LINE_STRIP);
    
    // For loop used to Calculate P(u)
    for (float u = 0; u < 1; u += 0.01){
        
        // Initialize x and y to both be 0
        float x = 0;
        float y = 0;
        
        // For loop used to calculate the sum of PiBeta(nu-i) from nu-2 to nu+2
        for (float i = floor(n*u - 2); i < ceil(n*u + 2); i++){
            
            // float point equal to i to represent a position in the control point vector
            float point = i;
            
            // If point is less than 0 then set it to 0
            if (point < 0){
                point = 0;
            }
            
            // if point is larger than n, then set it to n
            else if (point > n){
                point = n;
            }
            
            // Calculate tau (tau = nu -i)
            float tau = n*u - i;
            
            // initialize beta
            float beta;
            
            // set tension and skew values
            float t = 10.0;
            float s = 1.0;
            
            // calculate the value of delta
            float delta = t + (2 * std::pow(s, 3)) + (4 * std::pow(s, 2)) + (4 * s) + 2;
            
            // If-Else block used to determine blending function
            
            // If -2 <= tau <= -1
            if (tau >= -2 && tau <= -1){
                
                // Calculate Beta(tau)
                beta = (2*(std::pow((2+tau), 3))) /delta;
                
                // Calculate the x and y coordinates
                x += beta * controlPoints[point][0];
                y += beta * controlPoints[point][1];
            }
            
            // If -1 <= tau <= 0
            else if(tau >= -1 && tau <= 0){
                
                // Calculate Beta(tau)
                beta = ((t + (4 * s) + (4 * std::pow(s,2)))
                        - (6 * (1 - std::pow(s,2))) * tau
                        -((3 * std::pow(tau,2)) * (2 + t + (2 * s)))
                        -((2 * std::pow(tau,3)) * (1 + t + s + std::pow(s,2)))) /delta;
                
                // Calculate x and y coordinates
                x += beta * controlPoints[point][0];
                y += beta * controlPoints[point][1];
            }
            
            // If 0 <= tau <= 1
            else if(tau >= 0 && tau <= 1){
                
                // Calculate Beta(tau)
                beta = ((t + (4 * s) + (4 * std::pow(s,2)))
                        - ((6*tau) * (s - std::pow(s,3)))
                        -((3 * std::pow(tau,2)) * (t + (2 * std::pow(s, 2)) + (2 * std::pow(s, 3))))
                        +((2 * std::pow(tau,3)) * (t + s + std::pow(s,2) + std::pow(s, 3)))) /delta;
                
                // Calculate x and y coordinates
                x += beta * controlPoints[point][0];
                y += beta * controlPoints[point][1];
            }
            
            // If 1 <= tau <= 2
            else if(tau >= 1 && tau <= 2){
                
                // Calculate Beta(tau)
                beta = (2 * (std::pow(s, 3) * (std::pow((2 - tau), 3)))) / delta;
                
                // Calculate x and y coordinates
                x += beta * controlPoints[point][0];
                y += beta * controlPoints[point][1];
            }
        }
        
        // Draw line using x and y coordinate
        glVertex2f(x, y);
    }
    
    // glEnd to signal end of line drawing
    glEnd();
    
    //@@@@@@@@@@
}


// draw betaspline for closed curve
void curveOperations::drawBetasplineClosedCurve() const
{
    //@@@@@@@@@@
    // YOUR CODE HERE
    
    // Set n to be 1 less than the number of control points
    size_t n = controlPoints.size()-1;
    
    // glBegin used to start line drawing
    glBegin(GL_LINE_STRIP);
    
    // initialize X and Y to be used to store initial endpoint
    float initialX = 0;
    float initialY = 0;
    
    // initialize check
    int check = 0;
    
    // For loop used to calculate P(u)
    for (float u = 0; u < 1; u += 0.01){
        
        // initialize x and y
        float x = 0;
        float y = 0;
        
        // For loop to calculate sum PiBeta(nu-i) from nu-2 to nu+2
        for (float i = floor(n*u - 2); i < ceil(n*u + 2); i++){
            
            // Set float point to be equal to i to ensure it's a proper location in control point vector
            float point = i;
            
            // If point is less than 0 then set point to 0
            if (point < 0){
                point = 0;
            }
            
            // If point is greater than n then set point to n
            else if (point > n){
                point = n;
            }
            
            // Calculate the value of tau (tau = nu - i)
            float tau = n*u - i;
            
            // initialize beta
            float beta;
            
            // Set the tension and skew values
            float t = 10.0;
            float s = 1.0;
            
            // Calculate delta
            float delta = t + (2 * std::pow(s, 3)) + (4 * std::pow(s, 2)) + (4 * s) + 2;
            
            // If-Else statements used to calculate blending function
            
            // If -2 <= tau <= -1
            if (tau >= -2 && tau <= -1){
                
                // Calculate Beta(tau)
                beta = (2*(std::pow((2+tau), 3))) /delta;
                
                // Calculate x and y coordinates
                x += beta * controlPoints[point][0];
                y += beta * controlPoints[point][1];
            }
            
            // If -1 <= tau <= 0
            else if(tau >= -1 && tau <= 0){
                
                // Calculate Beta(tau)
                beta = ((t + (4 * s) + (4 * std::pow(s,2)))
                        - (6 * (1 - std::pow(s,2))) * tau
                        -((3 * std::pow(tau,2)) * (2 + t + (2 * s)))
                        -((2 * std::pow(tau,3)) * (1 + t + s + std::pow(s,2)))) /delta;
                
                // Calculate x and y coordinates
                x += beta * controlPoints[point][0];
                y += beta * controlPoints[point][1];
            }
            
            // If 0 <= tau <= 1
            else if(tau >= 0 && tau <= 1){
                
                // Calculate Beta(tau)
                beta = ((t + (4 * s) + (4 * std::pow(s,2)))
                        - ((6 * tau) * (s - std::pow(s,3)))
                        -((3 * std::pow(tau,2)) * (t + (2 * std::pow(s, 2)) + (2 * std::pow(s, 3))))
                        +((2 * std::pow(tau,3)) * (t + s + std::pow(s,2) + std::pow(s, 3)))) /delta;
                
                // Calculate x and y coordinates
                x += beta * controlPoints[point][0];
                y += beta * controlPoints[point][1];
            }
            
            // If 1 <= tau <= 2
            else if(tau >= 1 && tau <= 2){
                
                // Calculate Beta(tau)
                beta = (2 * (std::pow(s, 3) * (std::pow((2 - tau), 3)))) / delta;
                
                // Calculate x and y coordinates
                x += beta * controlPoints[point][0];
                y += beta * controlPoints[point][1];
            }
        }
        
        // Draw the line using the point at x, y
        glVertex2f(x, y);
        
        // If check is 0 (first time through)
        if (check == 0){
            
            // Set initialX to be the first x value
            initialX = x;
            
            // Set initialY to be the first y value
            initialY = y;
            
            // Set check to 1 so that the initial x and y values aren't overwritten
            check = 1;
        }
    }
    
    // Close the beta spline
    glVertex2f(initialX, initialY);
    
    // glEnd used to signal the end of line drawing
    glEnd();
    
    //@@@@@@@@@@
}

// draw cubic bspline with phantom endpoints
void curveOperations::drawCubicBsplinePhantom() const
{
    //@@@@@@@@@@
    // YOUR CODE HERE
    
    // Set n to be the number of control points
    size_t n = controlPoints.size();
    
    // Set P(-1) and P(n+1)
    Vector2D negP = 2*controlPoints[0] - controlPoints[1];
    Vector2D afterP = controlPoints[n-1];
    
    // glBegin used to draw lines
    glBegin(GL_LINE_STRIP);
    
    // For loop to calculate P(u)
    for (float u = 0; u < 1; u += 0.01){
        
        // Initialize x and y values to 0
        float x = 0;
        float y = 0;
        
        // For loop to calculate sum of PiB(nu - i) from nu - 2 to nu + 2
        for (float i = floor(n*u - 2); i < ceil(n*u + 2); i++){
            
            // Boolean check used to ensure i is a valid position in the controlpoint vector
            bool check = (i >= 0 && i <= n-1);
            
            // point used to set up phantom end points
            Vector2D point;
            
            // If check is true, then point is equal to the point represented at location i of control points
            if(check){
                point = controlPoints[i];
            }
            
            // If i is less than 0, then point is equal the starting phantom endpoint
            else if(i < 0){
                point = negP;
            }
            
            // If i is greater than n-1, then point is equal to the ending phantom endpoint
            else if(i > n-1){
                point = afterP;
            }
            
            // Calculate tau
            float tau = n*u - i;
            
            // initialize B
            float B;
            
            // If-Else statements used for calculating blending function
            
            // If -2 <= tau <= -1
            if (tau >= -2 && tau <= -1){
                
                // Calculate Beta(tau)
                B = (std::pow((2+tau), 3)) /6;
                
                // Calculate x and y coordinates
                x += B * point[0];
                y += B * point[1];
            }
            
            // If -1 <= tau <= 0
            else if(tau >= -1 && tau <= 0){
                
                // Calculate Beta(tau)
                B = (4 - (6 * std::pow((tau), 2)) - (3 * std::pow((tau), 3))) /6;
                
                // Calculate x and y coordinates
                x += B * point[0];
                y += B * point[1];
            }
            
            // If 0 <= tau <= 1
            else if(tau >= 0 && tau <= 1){
                
                // Calculate Beta(tau)
                B = (4 - (6 * std::pow((tau), 2)) + (3 * std::pow((tau), 3))) /6;
                
                // Calculate x and y coordinates
                x += B * point[0];
                y += B * point[1];
            }
            
            // If 1 <= tau <= 2
            else if(tau >= 1 && tau <= 2){
                
                // Calculate Beta(tau)
                B = (std::pow((2 - tau), 3)) /6;
                
                // Calculate x and y coordinates
                x += B * point[0];
                y += B * point[1];
            }
        }
        
        // If x and y are greater than 0, then draw the line
        if(x > 0 && y > 0){
            glVertex2f(x, y);
        }
    }
    
    // glEnd used to signal the end of line drawing
    glEnd();
    
    //@@@@@@@@@@
}



/*************************** You don't need to modify this block ***************************/
void CurveManager::drawCurves() const
{
    if (points == NULL || points->size() < 2)
    {
        return;
    }
    
    if (curveMode == BEZIER_MODE)
    {
        // Basic Mode (default)
        // Create a Bezier curve from the entire set of points,
        // and then simply draw it to the screen.
        
        curveOperations curve(*points);
        curve.drawBezier();
        
    }
    else
        if (curveMode == CUBIC_BSPLINE_MODE)
        {
            // mode to draw a cubic b-spline
            curveOperations curve(*points);
            curve.drawCubicBspline();
        }
        else
            if (curveMode == BETA_SPLINE_MODE)
            {
                // mode to draw a beta-spline
                curveOperations curve(*points);
                curve.drawBetaspline();
            }
            else
                if (curveMode == BETA_SPLINE_CLOSEDCURVE_MODE)
                {
                    // mode to draw a beta-spline for closed curve
                    curveOperations curve(*points);
                    curve.drawBetasplineClosedCurve();
                }
                else
                    if (curveMode == CUBIC_BSPLINE_PHANTOM_MODE)
                    {
                        // mode to draw a cubic b-spline with phantom endpoints
                        curveOperations curve(*points);
                        curve.drawCubicBsplinePhantom();
                    }
}
/*************************** You don't need to modify this block ***************************/


