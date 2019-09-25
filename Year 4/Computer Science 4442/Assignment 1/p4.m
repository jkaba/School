% CS4442B Assignment 1
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 4: Linear Classification problem
function C = p4(w,X)    

    % Find values for n and d (dimensions of X)
    sizeN = size(X,1);
    sizeD = size(X,2);

    % Create column vector of n x 1
    C = zeros(sizeN,1);

    % Initialize output C to contain w(1) (start of equation)
    C(:) = w(1);

    % Nested for loops to perform calculation
    for n = 1:sizeN
        for d = 1:sizeD
        
            % Remainder of linear classification equation, repeats per loop
            C(n) = C(n) + (X(n,d)*w(d+1));
        end
    
        % If positive sample, then replace C(n) with 1
        if(C(n) >= 0)
            C(n) = 1;
        
        % Else negative sample, replace c(n) with 2
        else
            C(n) = 2;
        end
    end
end