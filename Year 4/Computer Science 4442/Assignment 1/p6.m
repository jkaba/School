% CS4442B Assignment 1
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 6: logistic regression batch rule
function w = p6(X,Y,iterNum, wInit, alpha)

    % Convert label 2 into 0, otherwise calculations won't work
    Y(Y == 2) = 0;

    % Loop through the algorithm for number of iterations
    for j = 1:iterNum    
    
        % We want the number of rows in X
        num = size(X,1);
    
        % Make a column vector of 1's that is the same number of rows as X
        B = ones(num, 1);
    
        % Append the column of 1's to X for parameter fitting save as Z
        Z = [B, X];
    
        % Multiply matrix Z with the weights
        C = Z*wInit;
    
        % Sigmoid calculation
        C(:) = 1.0 ./ (1.0 + exp(-C(:)));
    
        % Create a clone of Y, perform Y-C
        cloneY = Y(:) - C(:);
    
        % Use repmat to make a matrix containing the weights
        A = repmat(cloneY,1,size(X, 2)+1).*Z;
    
        % Sum up the weights, and multiply by learning rate
        A = alpha*sum(A,1);
    
        % Add the summed weights with the initial weights
        wInit = wInit(:) + A(:);
    end

    % Save the new weight at the end of the algorithm
    w = wInit(:);
end
