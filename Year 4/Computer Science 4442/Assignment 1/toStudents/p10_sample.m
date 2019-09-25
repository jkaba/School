% the line below ensures that the result of NN training is always the same
% it removes any randomness during training
% do not use it in your own application, since training with randomness is
% better
setdemorandstream(pi);  

X = [1 2; -1 4; 3 2; 1 7; 3 5; 4 6; 9 8; 1 3 ]

% X =
% 
%      1     2
%     -1     4
%      3     2
%      1     7
%      3     5
%      4     6
%      9     8
%      1     3

Y = [4; 1 ; 3; 2; 3; 3; 1; 4]


% Y =
% 
%      4
%      1
%      3
%      2
%      3
%      3
%      1
%      4

H = [3, 2];
regularizerWeight = 0.1;
[net,valErr] = p10a(X,Y, H, regularizerWeight);

valErr

% 
% valErr =
% 
%     0.5000


X_test = [1 1; 0 4; 2 2]


% X_test =
% 
%      1     1
%      0     4
%      2     2


Y_test = [4;1;3]

% 
% Y_test =
% 
%      4
%      1
%      3

[err,CONF] = p10b(X_test,Y_test,net)


% err =
% 
%     0.6667
% 
% 
%  
% CONF =
% 
%     0     0     0     1
%     0     0     0     0
%     0     0     0     1
%    0     0     0     1
%
%   Side comment: the network outputs clasification vector Y_out
%    I'm showing what Y_out is in my case, although it is not one of the
%    required input/output for p10_b
%
%  Y_out =
%
%     4
%     4
%     4


