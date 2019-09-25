% CS4442B Assignment 2
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 4g: Reducing the height of an image
function [seam,im4Out,c] = reduceHeight(im,E)

    % Transpose the image matrix, need to use permute
    im = permute(im, [2 1 3]);
    
    % Transpose the energy matrix as well
    E = E.';
    
    % Reduce the width of the transposed image
    [seam,im4Out,c] = reduceWidth(im,E);
 
    % Transpose the output image, use permute again
    im4Out = permute(im4Out, [2 1 3]);

end