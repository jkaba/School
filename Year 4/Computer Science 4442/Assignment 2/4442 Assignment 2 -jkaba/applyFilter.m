% CS4442B Assignment 2
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 1: apply filter to image
function outIm = applyFilter(im,F)

    % Get sizes of image and filter
    f1 = size(F, 1);
    f2 = size(F, 2);
    im1 = size(im, 1);
    im2 = size(im, 2);
    
    % Set values for u and v
    u = f1-1;
    v = f2-1;
    
    % Initialize the output
    outIm = zeros(im1, im2);
    
    % Pad the image array with a border of 0's
    im = padarray(im, [u/2, v/2]);
    
    % Apply the filter to the image
    for i = 1:im1
        for j = 1:im2
            
            % Multiply filter with portion of image
            val = sum(F .* im(i:i+u, j:j+v));
            
            % Save the filtered portion in the output
            outIm(i, j) = sum(val);
        end
    end
end