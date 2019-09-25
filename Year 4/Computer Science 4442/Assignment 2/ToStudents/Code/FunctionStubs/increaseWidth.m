% CS4442B Assignment 2
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 4h: Increasing the width of an image
function [seam,im4Out,c] = increaseWidth(im,E)

    % Get M and P to find optimal vertical seam
    [M, P] = seamV_DP(E);
    
    % Get the best seam
    [seam, c] = bestSeamV(M, P);
    
    % Add the seam to the image
    im4Out = addSeamV(im, seam);
end