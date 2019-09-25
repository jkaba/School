%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% function for displaying images
% 
% INPUT: X is a row or column vector of size 784
% 
%  OUTPUT:
%           img resized input to be 28 by 28
%           displays figure with this image resized to be 28 by 28
%
% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function img = showImage(X)

X = reshape(X,16,16);
figure; 
imshow(X);
