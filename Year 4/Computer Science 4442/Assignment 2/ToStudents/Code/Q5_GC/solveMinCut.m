%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Solves the minimum cut problem for foreground/background segmetnation
% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  EXAMPLE USAGE:
%  Let image have 3 nodes named {1,2,3}. 
%  Nodes {1,2} are neighbors with weight 5
%  Nodes {2,3} are neighbors with weight 7
%  Background data terms are {100 0 0}
%  Foreground data terms are {0 0 100}
%
%   dataB = [100 0 0];
%   dataF = [0 0 100];
%   W = [1 2 5;
%        2 1 5;
%        1 3 7;
%        3 1 7]
%
%   Rows in matrix W can be in any order. For example, W below is also fine
%
%   W = [1 2 5;
%        1 3 7;
%        2 1 5;
%        3 1 7]
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% OUTPUT: 
%     labels is a row vector of size n
%     labels(i) = 0 means node i is assigned to the background
%     labels(i) = 1 means node i is assigned to the foreground
%     on the example above the output should be labels = [1 1 0]
%      
%     eng_start: energy at the start of the labeling
%    eng_finish: energy of the computed labeling
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [labels,eng_start,eng_finish] = solveMinCut(dataB,dataF,W)


if size(dataF,1) ~= 1 ||  size(dataB,1) ~= 1,
    error('First and second input should be a row vector, i.e. size(dataF,1) = 1 and size(dataB,1) = 1');
end;

if size(dataF,2) ~= size(dataB,2 )
    error('First and second input arrays have to be of equal size');
end;

numNodes = size(dataF,2);

R = [W(:,1); W(:,2)];
if  min(R) < 1,
    error('invalid pixel index range (too small)  in the third input array');
end;
if  max(R) > numNodes,
    error('invalid pixel index range (too large)  in the third input array');
end;

data = [dataB',dataF']';



smoothness = sparse(W(:,1),W(:,2),W(:,3));

[segm,eng_start,eng_finish]  = GCMex(zeros(numNodes,1), single(data), smoothness, single([0 1; 1 0]),0);
labels = segm';

