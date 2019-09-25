% CS4442B Assignment 2
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 4d: Optimal Vertical Seam Dynamic Programming
% The code is heavily based on the one presented in lecture 9
function [M,P] = seamV_DP(E)

    % Get size of energy image
    s1 = size(E, 1);
    s2 = size(E, 2);
    
    % Initialize arrays M and P
    M = zeros(s1, s2);
    P = zeros(s1, s2);
    
    % Initialization L9, slide 60
    for c = 1:s2
        M(1,c) = E(1,c);
        
        % In slides it should be null, but example output has -1
        P(1,c) = -1;
    end

    % Iterations L9 slide 62
    for r = 2:s1
        for c = 1:s2
        
            % Boundary Check for option 1
            if (c-1 >= 1)
                
                % Set option 1 value as within boundary
                option1 = M(r-1,c-1);
                
            % Else, outside boundary set option1 to infinite
            else
                option1 = Inf;
            end
        
            % Set value for option 2
            option2 = M(r-1,c);  
        
            % Boundary check for option 3
            if (c+1 <= size(E,2))
                
                % Within boundary, set option 3 value
                option3 = M(r-1,c+1);
                
            % Outside of boundaries, set option 3 to infinite
            else
                option3 = Inf; 
            end
        
        
            % If option 1 is the smallest, use it
            if (option1 <= option2 && option1 <= option3)
                
                % Set values for M and P
                M(r,c) = E(r,c) + M(r-1,c-1);
                P(r,c) = c-1;
                
            % Else if option 2 is smallest, use it
            elseif (option2 <= option1 && option2 <= option3)
                
                % Set values for M and P
                M(r,c) = E(r,c) + M(r-1,c);
                P(r,c) = c;
                
            % Else option 3 is smallest, use it
            else
                
                % Set values for M and P
                M(r,c) = E(r,c) + M(r-1,c+1);
                P(r,c) = c+1;            
            end            
        end    
    end
end