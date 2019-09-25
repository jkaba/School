% CS4442B Assignment 2
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 4f: Reducing the width of an image
function [seam,im4Out,c] = reduceWidth(im,E)

    % Get M and P
    [M, P] = seamV_DP(E);
    
    % Find best seam and cost
    [seam, c] = bestSeamV(M, P);
    
    % Remove the seam from the image
    im4Out = removeSeamV(im, seam);
    
end