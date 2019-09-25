% note that the output will vary between different invocations due to
% randomness in weight training 

X = [1 2; -1 4; 3 2; 1 7; 3 5; 4 6; 9 8]


%X =
% 
%  1     2
%     -1     4
%      3     2
%      1     7
%      3     5
%      4     6
%      9     8
%      
Y = [1; 1 ; 2; 2; 2; 1; 1]

% Y =
%      1
%      1
%      2
%      2
%      2
%      1
%      1
% 
w = p5(X,Y,100)
% 
% 
% w =
% 
%    -1.3492
%    -0.8714
%     1.5286