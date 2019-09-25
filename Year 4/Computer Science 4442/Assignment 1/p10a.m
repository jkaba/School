% CS4442B Assignment 1
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 10: Neural Network
% Due to time constraints and other assignments due at the same time
% This program was unable to be completed, below is what I've got for
% 10a, however it does not work (produce error).
function [net, valErr] = p10a(X,Y, H, regulizerWeight)

    % Below is the code given from the assignment
    net = patternnet(H);
    net.divideParam.testRatio = 0;
    net.divideParam.valRatio = 0.3;
    net.divideParam.trainRatio = 0.7;
    net.performParam.regularization = regulizerWeight;

    % Make a matrix of targets
    yFake = eye(max(Y));

    % Loop counter
    num = size(X,1);
    
    for i = 1:num
        % Error, as input and target have different numbers of samples
        % I assume the issue here, is that I need to run this through
        % a loop, and run this individually 1 column at a time
       [net,tr] = train(net,X(i,:).',yFake(i,:));

        % Classify samples
        Y2(i) = net(tr.valInd);
    end
    
    %Get error rate
    [err,CONF] = p2(Y2,Y);

    % validation error
    valErr = 1 - err;

    % Used this to display net, as I'm not sure if net will display on it's own
    disp(net);
end