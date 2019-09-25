% CS4442B Assignment 1
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 1: 2 class problem

function [X_out, Y_out] = p1(X,Y,l1,l2)

    % Find the label locations
    labelA = find(Y == l1);
    labelB = find(Y == l2);

    % If l1 is smaller
    if(l1 < l2)
    
        % Make matrices X_out and Y_out
        X_out = [X(labelA,:) ; X(labelB,:)];
        Y_out = [Y(labelA); Y(labelB)];
    
        % l1 becomes 1, and l2 becomes 2
        Y_out(Y_out == l1) = 1;
        Y_out(Y_out == l2) = 2;
    
    % Else l2 is smaller
    else
    
        % Make matrices X_out and Y_out
        X_out = [X(labelB,:) ; X(labelA,:)];
        Y_out = [Y(labelB); Y(labelA)];
    
        % l2 becomes 1 and l1 becomes 2
        Y_out(Y_out == l1) = 2;
        Y_out(Y_out == l2) = 1;
    end
end