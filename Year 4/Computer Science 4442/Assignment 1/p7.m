% CS4442B Assignment 1
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 7: Multi-linear classifiation problem
function C = p7(W,X)

    % Find values for n and d (dimensions of X)
    sizeN = size(X,1);
    sizeD = size(X,2);

    % Find value for the # of rows in W
    sizeDP = size(W,1);

    % Set current value to 0 
    current = 0;

    % Create 2 matrices, 1 to contain values for comparison
    % The other containing the classes to be assigned
    temp = zeros(sizeN,1);
    count = zeros(sizeN,1);

    % Initiallizing the matrix C
    C = zeros(sizeN,1);

    % Nested for loops to perform calculation
    for n = 1:sizeN
    
        % Count initially starts at 1, but can go to d+1
        count(n) = 1;
    
        % Second loop, goes through the rows of W
        for e = 1:sizeDP
        
            % Bias weight is put at the start
            current = W(e);
        
            % Calculate the linear classification for each row
            for d = 1:sizeD
                current = current + (X(n,d)*W(d*sizeDP+e));
            end
        
            % If it is the first calculation, store the current value in temp
            if(e == 1)
                temp(n) = current;
            else
            
                % Else, we need to compare current value against temp
                if(current > temp(n))
                
                    % If current is bigger, then temp now holds current
                    temp(n) = current;
                
                    % Class label is now set to the current class/row
                    count(n) = e;
                end
            end        
        end
    end
   
    % C contains the classes to be assigned to X
    C = count;
    
end