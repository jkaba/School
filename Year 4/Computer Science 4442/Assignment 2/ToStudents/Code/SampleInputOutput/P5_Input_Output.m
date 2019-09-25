rng(0);  % set  random number generator to the same starting point

A = [ 1 0 3; 2 1 2; 1 3 3 ];
imSmall = cat(3,A,A,A);
scribbleSmall = [1 0 0; 1 0 0; 0 2 2];

lambda = 1;
numClusters = 0;
inftyCost = 1000;

[segm,e2]  = segmentGC(imSmall,scribbleSmall,lambda,numClusters,inftyCost)

%sigma^2 =   2.0833   % the value of sigma computed on the input image
                    % I display it here for your debugging purposes
                    % but you are not required to have it as output

% segm =
% 
%      0     0     0
%      0     0     0
%      0     1     1
% 
% 
% e2 =
% 
%     1.5524

% 
% 
% dataB =
% 
%            0
%            0
%            0
%            0
%            0
%         1000
%            0
%            0
%         1000
% 
% 
% dataF =
% 
%         1000
%         1000
%            0
%            0
%            0
%            0
%            0
%            0
%            0
% 
% 
% W =
% 
%     1.0000    4.0000    0.7866
%     2.0000    5.0000    0.7866
%     3.0000    6.0000    0.3829
%     4.0000    7.0000    0.1153
%     5.0000    8.0000    0.7866
%     6.0000    9.0000    1.0000
%     2.0000    1.0000    0.7866
%     3.0000    2.0000    0.7866
%     5.0000    4.0000    0.7866
%     6.0000    5.0000    0.3829
%     8.0000    7.0000    0.7866
%     9.0000    8.0000    0.7866
%     4.0000    1.0000    0.7866
%     5.0000    2.0000    0.7866
%     6.0000    3.0000    0.3829
%     7.0000    4.0000    0.1153
%     8.0000    5.0000    0.7866
%     9.0000    6.0000    1.0000
%     1.0000    2.0000    0.7866
%     2.0000    3.0000    0.7866
%     4.0000    5.0000    0.7866
%     5.0000    6.0000    0.3829
%     7.0000    8.0000    0.7866
%     8.0000    9.0000    0.7866


numClusters = 3;

[segm,e2]  = segmentGC(imSmall,scribbleSmall,lambda,numClusters,inftyCost)

%  reshape(clusters,3,3)  % you don't have to display clustering that you
                          %  get with kmeans, but I'm displaying it for
                          %  debuggin purposes
% 
% ans =
% 
%      3     3     2
%      1     3     1
%      3     2     2
%
%
% segm =
% 
%     0     0     1
%     0     0     1
%     0     1     1
% 
% 
% e2 =
% 
%     9.3911

% Clusters I get with kmeans clustering
% clustersOut =
% 
%      3     3     2
%      1     3     1
%      3     2     2



% 
% dataB =
% 
%    1.0e+03 *
% 
%     0.0009
%     0.0009
%     0.0009
%     0.0009
%     0.0009
%     1.0000
%     0.0016
%     0.0009
%     1.0000
% 
% 
% dataF =
% 
%    1.0e+03 *
% 
%     1.0000
%     1.0000
%     0.0016
%     0.0016
%     0.0016
%     0.0005
%     0.0005
%     0.0016
%     0.0005
% 
% 
% W =
% 
%     1.0000    4.0000    0.7866
%     2.0000    5.0000    0.7866
%     3.0000    6.0000    0.3829
%     4.0000    7.0000    0.1153
%     5.0000    8.0000    0.7866
%     6.0000    9.0000    1.0000
%     2.0000    1.0000    0.7866
%     3.0000    2.0000    0.7866
%     5.0000    4.0000    0.7866
%     6.0000    5.0000    0.3829
%     8.0000    7.0000    0.7866
%     9.0000    8.0000    0.7866
%     4.0000    1.0000    0.7866
%     5.0000    2.0000    0.7866
%     6.0000    3.0000    0.3829
%     7.0000    4.0000    0.1153
%     8.0000    5.0000    0.7866
%     9.0000    6.0000    1.0000
%     1.0000    2.0000    0.7866
%     2.0000    3.0000    0.7866
%     4.0000    5.0000    0.7866
%     5.0000    6.0000    0.3829
%     7.0000    8.0000    0.7866
%     8.0000    9.0000    0.7866


load q5; % loads a larger example from file 

im = imread('square.png');
im = double(im);

lambda = 50;
numClusters = 50;
inftyCost = 1000;
[segm,e2]  = segmentGC(im,scribblesSquare,lambda,numClusters,inftyCost);
e2

% sigma^2 = 165.1678  % the value of sigma computed on the input image
% e2 = 4.0668e+04
% I also saved the segmentation you should get in file "squareOut.png"
% where 0 corresponds to the background and 255 to the object

