% CS4442B Assignment 2
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 5: Graph Cut Segmentation
% Due to time constraints kmeans is not implemented

function [segm,eng_finish]  = segmentGC(im,scribbleMask,lambda,numClusters,inftyCost)

    % If the user does not request kmeans clustering
    if(numClusters == 0)
        
        % Get image dimensions
        s1 = size(im,1);
        s2 = size(im,2);
        
        % Get # of rows + # of col
        s3 = s1*s2;
        
        % Initialize matrices for background and foreground data
        backgroundData = zeros(s1, s2);
        foregroundData = zeros(s1, s2);    
        
        % Assign the infinity cost where needed
        backgroundData((scribbleMask == 2)) = inftyCost;
        foregroundData((scribbleMask == 1)) = inftyCost;
        
        % Convert the data matrices into 1d vectors
        B = reshape(backgroundData, 1, []);
        F = reshape(foregroundData, 1, []);    
        
        % Convert the color image
        imG = im(:,:,1) + im(:,:,2) + im(:,:,3);
        imG = imG/3;
    
        % Making Pixel Names Matrix
        
        % Count used to represent pixel name
        count = 1;
        
        % Initialize pixel name matrix
        pixelNames = zeros(s1, s2);
        
        % For loops to assign pixel names
        for j = 1:s2
            for i = 1:s1
                pixelNames(i,j) = count;
                count = count + 1;
            end
        end
        
        % Finding Edges
    
        % Horizontal edges initialization
        spoint2 = zeros(s3-s1, 1);
        epoint2 = zeros(s3-s1, 1);
        count = 0;
        
        % Loop used to get the horizontal edges
        for i = 1:s3
            
            % If conditions are met then set the count flag
            if(i == s1+1)
                count = count + 1;
            elseif(i == s3-s1+1)
                count = count+1;
            end
            
            % Based on value of count, assign accordingly
            if(count >= 1)
                if(count >= 2)
                    epoint2(i-s1) = pixelNames(i);
                else
                    epoint2(i-s1) = pixelNames(i);
                    spoint2(i) = pixelNames(i);
                end
            else
                spoint2(i) = pixelNames(i);
            end
        end
        
        % Vertical edges only wanted to cooperate using this method
        % Assign Edge starting point
        spoint1 = reshape(pixelNames(1:end-1,:),[],1);
        
        % Initialize vertical edge end points
        epoint1 = zeros(s3-s2, 1);
        sX = size(spoint1(:));
        
        % Assign the vertical edge end points
        for i = 1:sX
            epoint1(i) = spoint1(i) + 1;
        end
        
        % Create matrices of edges
        hEdges = [spoint2, epoint2];
        vEdges = [spoint1, epoint1];
    
        % Reverse edges
        reverseH = [epoint2, spoint2];
        reverseV = [epoint1, spoint1];
    
        % Create list of all edges
        edgeList = [hEdges; vEdges];
        
        % Get the size of the edge list
        s4 = size(edgeList,1);
        
        % Create a matrix for edge weights
        weights = zeros(s4,1);
        
        % Initialize sigma to 0
        sigma = 0;
        % Calculate value of sigma, based on lecture slide
        for i = 1:s4
            sigma = sigma + ((imG(edgeList(i,1)) - imG(edgeList(i,2))).^2)/s4;
        end
        
        % Calculating the weight at each edge, based on formula in
        % assignment
        for i = 1:s4
            weights(i) = lambda*exp(-abs(((imG(edgeList(i,1)) - imG(edgeList(i,2)))).^2)/(2*sigma));
        end
        
        % Add the reverse edges to the edge list
        edgeList = [hEdges; vEdges; reverseH; reverseV];
        
        % Make a matrix of weights for edges both ways
        edgeWeights = [weights; weights];
        
        % Concatenate the edges with there weights
        W = [edgeList, edgeWeights];

        % Call solveMinCut, this gives us the end energy
        [labels,eng_start,eng_finish] = solveMinCut(B, F, W);
        
        % Need to reshape the output to get proper segmentation
        segm = reshape(labels, s1, s2);
        
    % If user wants kmeans clustering return a message
    else
        disp("Kmeans Clustering is not implemented");
    end
end
