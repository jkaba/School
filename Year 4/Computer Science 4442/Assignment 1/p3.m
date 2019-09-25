% CS4442B Assignment 1
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 3: KNN classification
function C = p3(X_train,Y_train,X_test,k)

    % Code from/based on lecture slides
    
    % Renaming input
    combinedSamples = X_train;
    trueClass = Y_train;
    newSample = X_test;
    
    % Get the size of X and new_X
    totalSamples = size(X_train,1);
    cSize = size(newSample,1);
    
    % Matrix of zeros to initialize C
    C = zeros(cSize, 1);
    
    % Loop through until we reach the number of rows in the test data
    for i = 1:cSize
        
        % Accept any size of test data, save as nT
        nT = newSample(i,:);
        
        % Test matrix is repmat of nt and size of x
        testMatrix = repmat(nT, totalSamples, 1);
        
        % Get the absolute difference between training data and test matrix
        absDiff = abs(combinedSamples-testMatrix);
        
        % Square the absolute difference
        absDiff = absDiff.^2;
        
        % calculate the distance between elements
        dist = sum(absDiff,2);
        
        % Sort the distance
        [Y_train,I] = sort(dist);
        
        % Get the index for each neighbor
        neighborInd = I(1:k);
        
        % Get the neighbor
        neighbors = trueClass(neighborInd);
        
        % use mode to get the class of neighbors
        C(i) = mode(neighbors);
    end
end
