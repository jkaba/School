% CS4442B Assignment 1
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 9: softmax
function W = p9(X,Y,iterNum,wInit,alpha)

    % Set up augmented feature vector
    num = size(X,1);
    B = ones(num, 1);
    Z = [B, X];
    
    % identity matrix of size based on largest class
    yFake = eye(max(Y));

    % Algorithm loop
    for q = 1:iterNum
        
        % Loop through each row of Z
        for i = 1:num
            
            % softmax setup
            smx = zeros(Z(i));
            sms = 0;            
            C = wInit * Z(i,:).';
            C = C.';
            num2 = size(C,2);
            
            % Loop that performs Softmax
            for j = 1:num2
                
                % Get the numerator
                smx(j) = exp(C(j));
                
                % Loop through the row to get the denominator
                for k = 1:num2
                    sms = sms + exp(C(k));
                end
                
                % Calculate and store softmax value
                smx(j) = smx(j)/sms;
                
                % Reset for softmax
                sms = 0;
            end
            
            % Find the location of 1 in the identity matrix for class
            save = find(yFake(:,Y(i)) == 1);
            
            % identity column of class - softmax values
            A = yFake(:,save) - smx(:);
            
            % Multiply the result, with the row used from Z
            A = A*Z(i,:);
            
            % Multiply by alpha
            A = alpha*A;
            
            % Add answer to wInit
            wInit = wInit+A;        
        end
        
        % Save wInit as W
        W = wInit;
    end
end