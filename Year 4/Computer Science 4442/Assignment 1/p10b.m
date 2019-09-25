% CS4442B Assignment 1
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 10: Neural Network
% Due to time constraints and other assignments due at the same time
% This program was unable to be completed, below is what I've got for
% 10b, unable to test it however as 10a was never completed.
function [err,CONF] = p10b(X_test,Y_test,net)

    % Use net(X_test) to classify samples in X_test store in Y2
    Y2 = net(X_test);

    % Get error, and confusion matrix from p2
    [err,CONF] = p2(Y2, Y_test);
end