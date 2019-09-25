% CS4442B Assignment 1
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 8: Perceptron Single Sample
function W = p8(X, Y, iterNum, wInit, alpha)

    % Setup for augmented feature vector
    num = size(X,1);
    B = ones(num, 1);
    Z = [B, X];
    
    % more variable setup
    s1 = size(wInit,1);
    s2 = size(wInit,2);
    
    % Algorithm loop
    for q = 1:iterNum
        
        % Loop through each row in Z
        for i = 1:num           
            
            % Zero matrix same size as wInit
            copyW = zeros(s1,s2);
            
            % Calculate Wz(i), dot product of wInit and row i of Z 
            C = wInit * Z(i,:).';
            C = C.';
            
            % Subtract max from actual
            A = max(C) - C(Y(i));
            
            % If the result is 0, do nothing
            if(A == 0)
            else
                
                % Save row Z(i) in location of class in zero matrix
                copyW(Y(i),:) = Z(i,:).';
                
                % Save the max value
                xLoc = max(C);
                
                % Find the location for the max value
                save2 = find((C) == xLoc);
                
                % Save -Z(i) in row of predicted class in zero matrix
                copyW(save2,:) = -Z(i,:).';
                
                % Update wInit
                wInit = wInit+(copyW*alpha);
            end   
        end
        % Save W as wInit
        W = wInit;
    end
end