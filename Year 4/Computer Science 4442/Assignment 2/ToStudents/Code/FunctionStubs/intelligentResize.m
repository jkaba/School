% CS4442B Assignment 2
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 4j: Resizing an image based on parameters
function [totalCost,imOut] = intelligentResize(imInput,v,h,W,mask,maskWeight)

    % Combine image with mask
    im4 = cat(3,imInput,mask);
    
    % Filter given from assignment
    F = [-1, 0, 1];
    
    % Compute the Energy matrix
    eng = computeEng(im4,F,W,maskWeight);

    % Determine how many seams to be removed/added
    numV = abs(v);
    numH = abs(h);
    total = numV + numH;
    
    % Initial total cost is 0
    totalCost = 0;
    
    for i = 1:total
        
        % Horizontal seams first
        if(numH > 0)
            
            % If positive input, then increase height by add seam
            if(h > 0)
                [seam,im4Out,c] = increaseHeight(im4,eng);
                im4 = im4Out;
                
                % Recalculate total cost and energy
                eng = computeEng(im4, F, W, maskWeight);
                totalCost = totalCost + c;
                
            % If negative input, reduce height by removing seam
            elseif(h < 0)
                [seam,im4Out,c] = reduceHeight(im4,eng);
                im4 = im4Out;
                
                % Recalculate total energy and cost
                eng = computeEng(im4, F, W, maskWeight);
                totalCost = totalCost + c;
            end
            
            % Decrement counter for horizontal seams
            numH = numH - 1;
        end
        
        % Vertical seams second
        if(numV > 0)
            
            % Positive input, increase width by adding seam
            if(v > 0)
                [seam,im4Out,c] = increaseWidth(im4,eng);
                im4 = im4Out;
                
                % Recalculate energy and total cost
                eng = computeEng(im4, F, W, maskWeight);
                totalCost = totalCost + c;
                
            % Negative input, reduce width by removing seam
            elseif(v < 0)
                [seam,im4Out,c] = reduceWidth(im4,eng);
                im4 = im4Out;
                
                % Recalculate energy and total cost
                eng = computeEng(im4, F, W, maskWeight);
                totalCost = totalCost + c;
            end
            
            % Decrement vertical counter
            numV = numV - 1;
        end
    end

    % Get size of final image
    s1 = size(im4, 3);
    
    % Save final image as output
    for j = 1:s1-1;
        imOut(:,:,j) = im4(:,:,j);
    end
    
end
