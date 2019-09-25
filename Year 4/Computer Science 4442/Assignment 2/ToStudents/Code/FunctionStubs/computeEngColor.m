% CS4442B Assignment 2
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 3: Compute color energy
function eng = computeEngColor(im,W)
    
    % Get size of the array to use in loop
    s1 = size(im(:,:,:), 1);
    s2 = size(im(:,:,:), 2);
    
    % Initialize output
    eng = zeros(s1,s2);
    
    % Calculate energy and store as output
    for i = 1:s1
        for j = 1:s2
            eng(i,j) = (W(1) * im(i,j,1)) + (W(2) * im(i,j,2)) + (W(3) * im(i,j,3));
        end
    end
end