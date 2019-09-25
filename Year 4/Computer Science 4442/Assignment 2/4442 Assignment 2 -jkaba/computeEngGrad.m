% CS4442B Assignment 2
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 2: Calculate Gradient magnitude 
function eng = computeEngGrad(im,F)

    % Combine the image and divide by 3 to convert to gray
    imG = im(:,:,1) + im(:,:,2) + im(:,:,3);
    imG = imG/3;

    % Apply the Filter to the new image
    r1 = applyFilter(imG,F);
    r2 = applyFilter(imG,F.');

    % Get the dimensions of the image
    s1 = size(imG, 1);
    s2 = size(imG, 2);

    % Calculate the energy for each element
    for i = 1:s1
        for j = 1:s2
            imG(i,j) = sqrt((abs(r1(i,j)).^2 + abs(r2(i,j)).^2));
        end
    end

    % Save the energy matrix as output
    eng = imG;
end