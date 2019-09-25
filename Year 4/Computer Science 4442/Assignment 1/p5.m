% CS4442B Assignment 1
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 5: linear classification (random)
function w = p5(X,Y,iterNum)

    % Variable to store the error values
    copyErr = 0;

    % Loop through algorithm for number of iterations specified
    for i = 1:iterNum
    
        % Get the size of columns for X
        numD = size(X,2);

        % matrix of random weight values 
        copyWeight = randn(numD+1, 1);

        % Call p4 to get classification labels using random weight
        C = p4(copyWeight, X);
        
        % Get error rate by calling p2
        [err,CONF] = p2(C,Y);
        
        % If this is the initial run, save the error
        if(i == 1)
            copyErr = err;
        else
            
            % Else compare current error with previous
            if(err < copyErr)
                
                %If the current error is smaller, then save it
                copyErr = err;
                
                % Save these weights if error is smaller
                w = copyWeight;
            end
        end
    end
end
