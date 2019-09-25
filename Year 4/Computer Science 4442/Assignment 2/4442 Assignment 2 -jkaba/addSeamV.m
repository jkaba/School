% CS4442B Assignment 2
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 4c: Adding a Seam
function imOut = addSeamV(im4,seam)

    % Get the dimensions for output array
    s1 = size(im4, 1);
    s2 = size(im4, 2) + 1;
    s3 = size(im4, 3);

    % Get the length of seam
    l1 = length(seam);

    % Initialize output array
    imOut = zeros(s1, s2, s3);

    % Set positions to NaN where seam gets added
    for i=1:l1
        imOut(i, seam(i), :) = NaN; 
    end
        
    % Loops to add a seam
    for j = 1:s1
    
        % Flag used to determine placement of elements
        flag = 0;
        for k = 1:s2-1
        
            % If NaN, adjust the positioning of elements
            if(isnan(imOut(j, k)))
            
                % Add the seam
                imOut(j, k, :) = im4(j, k, :);
                imOut(j, k+1, :) = im4(j,k,:);
            
                % Flag to 1, to denote position adjustment
                flag = 1;
            else
            
                % Flag is 0
                if(flag ~= 1)
                
                    % Place element in corresponding position
                    imOut(j, k, :) = im4(j, k, :);
                
                % Else, place element in next position
                else
                    imOut(j, k+1, :) = im4(j, k, :);
                end
            end
        end
    end
end
