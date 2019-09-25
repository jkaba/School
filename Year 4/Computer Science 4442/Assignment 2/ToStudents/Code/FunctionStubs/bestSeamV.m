% CS4442B Assignment 2
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 4e: Finding best seam and cost
function [seam,c] = bestSeamV(M,P)

    % Get sizes
    s1 = size(M,1);
    s2 = size(M,2);
    
    % Initialize seam matrix
    seam = zeros(s1, 1);
    
    % Cost is smallest value in M
    c = min(M(:));
    
    % Loop to find the index where cost is smallest
    for i = 1:s1
        for j = 1:s2
            
            % When smallest cost found, then save location
            if (c == M(i,j))
                temp = j;
            end
        end
    end
    
    % Set the location in the seam matrix
    seam(:) = temp;
    
    % Go from end to front
    for r = s1-1:-1:1  
        
        % Set the optimal seam location
        seam(r) = P(r+1, seam(r+1));
    end
end