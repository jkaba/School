% CS4442B Assignment 1
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 2: Error/Confusion problem
function [err, CONF] = p2(C, T)

    % Get "m" largest value from labels
    large = max(T);

    % Use sign to figure out which values are labeled correctly
    thirdmatrix = sign(T-C);

    % denominator for error, is the size of label vector
    denominator = size(T, 1);

    % numerator for error, is the number of non zero values in the third matrix
    numerator = nnz(thirdmatrix);

    % error is the number of misclassed values over total value
    err = numerator/denominator;

    % Making CONF matrix of size m x m
    CONF = zeros(large, large);

    % for loop to assign values to the CONF matrix
    for i = 1:denominator
        CONF(T(i),C(i)) = CONF(T(i), C(i)) + 1;
    end
end