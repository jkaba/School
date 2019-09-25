% CS4442B Assignment 2
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 4b: Removing a Seam
function imOut = removeSeamV(im4,seam)

    % Get the sizes from the matrix
    s1 = size(im4, 1);
    s2 = size(im4, 2) - 1;
    s3 = size(im4, 3);

    % Determine the length of the seam
    l1 = length(seam);

    % Initialize output matrix
    imOut = zeros(s1, s2, s3);

    % Where seam is removed, add NaN
    for i=1:l1
        imOut(i, seam(i), :) = NaN; 
    end
        
    % Loops to remove the seam
    for j = 1:s1
    
        % Flag used to determine element placement
        flag = 0;
        for k = 1:s2
        
            % If NaN
            if(isnan(imOut(j, k)))
            
                % Skip the current element, and place the next element 
                % in its place
                imOut(j, k, :) = im4(j, k+1, :);
            
                % Flag to 1, to denote the skipped element
                flag = 1;
            else
            
                % If flag is not set to 1
                if(flag ~= 1)
                
                    % Place current element in output matrix
                    imOut(j, k, :) = im4(j, k, :);  
                else
                
                    % Flag has been set, so place the next element in its place
                    imOut(j, k, :) = im4(j, k+1, :);
                end
            end
        end
    end
end
