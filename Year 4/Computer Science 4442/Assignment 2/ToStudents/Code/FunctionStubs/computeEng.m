% CS4442B Assignment 2
% Name: Jameel Kaba
% UWO/GAUl id: jkaba
% student #: 250796017

% Program 4a: Compute Energy for Seam Carving
function eng = computeEng(im4,F,W,maskWeight)

    % Calculate the Energy based on the formula from assignment
    eng = computeEngGrad(im4(:, :, 1 : 3), F )+computeEngColor(im4(:, :, 1 : 3), W )+maskWeight*im4(:, :, 4);
    
end