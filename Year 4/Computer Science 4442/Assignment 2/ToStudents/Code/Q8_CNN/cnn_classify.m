%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
%  Takes as an input the network, samples to classify in X, correct labels
%  in Y. Applies network to samples in X and computes the test error

function [err,pred] = cnn_classify(net,X,Y)

R = 16;
C = 16;

% reshape data in X to be 16 by 16 by 1
X =  single(reshape(X',R,C,1,size(X,1)));

% subtract mean from samples in the test data
X =  bsxfun(@minus, X, net.imageMean);  % subtract mean from test data

% now classify samples in X
% Each sample is 16 by 16 by 1
res = vl_simplenn(net, X);

% now perform classification
score = [];
pred = [];

for i=1:size(res(end).x,4)
  [score(i),pred(i)] = max(squeeze(res(end).x(1,1,:,i))) ;
end

% compute classification error, labels stored in vector Y_test_full 
d = (pred-Y');
i = find(d ~= 0 );
err =size(i,2)/size(pred,2);
