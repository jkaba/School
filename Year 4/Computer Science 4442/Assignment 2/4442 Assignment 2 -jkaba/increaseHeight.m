% CS4442B Assignment 2
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 4i: Increasing the Height 
function [seam,im4Out,c] = increaseHeight(im,E)

    % Transpose the matrix, has to be done with permute
    im = permute(im, [2 1 3]);
    
    % Transpose the energy matrix
    E = E.';
    
    % Call increase width 
    [seam,im4Out,c] = increaseWidth(im,E);
    
    % Transpose the output matrix
    im4Out = permute(im4Out, [2 1 3]);
end