
function net = initializeCNN_basic(varargin)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% At each stage of the network, we have a 3D layer of size W x H x D
% We say that this layer has width W, height H, depth D
%
% 'conv' and 'pool' layer transforms the previous layer to a new size, W' x H x D
% Normalization and ReLu Layers leave the previous layer size unchanged
% 
% Final layer must be a 'softmaxloss' layer.
% Before the final  'softmaxloss' layer, there is usually at least one fully connected layer
% 
% To get a fully connected layer with q units you can reuse a convolutional
% layer.  Suppose your current layer has dimensions a x b x d
% Use convolutional layer with parameters [a,b,d] with a stride of '1' and
% no padding, namely
% 
% struct('type', 'conv', ...
%                            'weights', {{f*randn(a,b,d,q, 'single'), zeros(1,10,'single')}}, ...
%                            'stride', 1, ...
%                            'pad', 0) ;                      
%  If this fully connected layer connects to the 'softmaxloss' layer, then
% you want to make q = number of classes, which is 10 in our case
% If this fully connected layer connects to another fully connected layer,
% q can be arbitrary.  
% Example: say we want two fully connected layers before the final 'softmaxloss' layer.
% Suppose current layer has size 20 x 20 x 40. First create a fully
% connected layer, with, say 100 units:
% 
%  struct('type', 'conv', 'weights', f*randn(20,20,40,100, 'single'), ... 
%                           'biases', zeros(1, 100, 'single'), ...       
%                           'stride', 1,'pad', 0) ;
%
%  Now the current layer has size 1 x 1 x 100
%
%  Then create another connected layer with 2 units (w = number of classes)                   
% 
%  struct('type', 'conv', 'weights', f*randn(1,1,100,2, 'single'), ... 
%                           'biases', zeros(1, 2, 'single'), ...       
%                           'stride', 1,'pad', 0) ;                                                                                                      
% 
% Now current layer has size 1 x 1 x 10, which is good for 'softmaxloss'
%
%
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% IMPORTANT:  
% The input image is assumed to be 16x16x1
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  FIRST STAGE %%%%%%%%%%%%%%%%%%%%%


opts.batchNormalization = false ;
opts.networkType = 'simplenn' ;
opts = vl_argparse(opts, varargin) ;

rng('default');   % for random number generator
%rng(0) ;

% Meta parameters
net.meta.trainOpts.learningRate = 0.001 ;
net.meta.trainOpts.numEpochs =  1000;
net.meta.trainOpts.batchSize = 100 ;
net.meta.trainOpts.weightDecay = 0.0005 ; % weight regularization
net.meta.trainOpts.momentum = 0.9 ; % should be between 0.5 and 0.9
net.meta.trainOpts.continue = true;  % Set to true if continue training from previous point
                                     % set to false if you want the network
                                     % to start trainng from scratch
net.meta.trainOpts.expDir = 'data/mnist'; % directory where training information is stored
net.meta.inputSize = [16 16 1] ;


f=1/100 ;  % scaling factor for initial filter weights, want initial weights small
net.layers = {} ; % initial network is empty
% input has dimensions 16 by 16 by 1

% create a convolutional layer first.  Convolutions have size 5 by 5, and
% there is 25 of them. Stride is set to 1 and no padding
% command  zeros(1, 20, 'single')}} creates 20 bias weights initialized to
% for the 20 filter outputs, all initialized to 0

net.layers{end+1} = struct('type', 'conv', ...
                           'weights', {{f*randn(5,5,1,25, 'single'), zeros(1, 25, 'single')}}, ...
                           'stride', 1, ...
                           'pad', 0) ;                     
% output has dimensions 12 by 12 by 20

% create a pooling layer. Pool over 2 by 2 area, and stride is set to 2.
% Thus output is shrunk by 2 in the width and height dimension. Depth
% dimension (number of filters) is not shrunk
net.layers{end+1} = struct('type', 'pool', ...
                           'method', 'max', ...
                           'pool', [2 2], ...
                           'stride', 2, ...
                           'pad', 0) ;
% output has dimensions 6 by 6 by 25                       
                       

% create a rectified linear unit layer
net.layers{end+1} = struct('type', 'relu') ;
% output has dimensions 6 by 6 by 25                       
                      
% create a rectified linear unit layer
net.layers{end+1} = struct('type', 'relu') ;
% output has dimensions 6 by 6 by 25                       

% fully connected layer with 40 units, implemented as a convolutional layer
net.layers{end+1} = struct('type', 'conv', ...
                           'weights', {{f*randn(6,6,25,40, 'single'), zeros(1,40,'single')}}, ...
                           'stride', 1, ...
                           'pad', 0) ;
% output has dimensions 1 by 1 by 40                       
                       
% fully connected layer with 10 units, implemented as a convolutional layer
net.layers{end+1} = struct('type', 'conv', ...
                           'weights', {{f*randn(1,1,40,10, 'single'), zeros(1,10,'single')}}, ...
                           'stride', 1, ...
                           'pad', 0) ;

                       
% final "softmax" layer,performs classication                                               
net.layers{end+1} = struct('type', 'softmaxloss') ;

% optionally switch to batch normalization
if opts.batchNormalization
  net = insertBnorm(net, 1) ;
  net = insertBnorm(net, 4) ;
  net = insertBnorm(net, 7) ;
end

% Fill in defaul values
net = vl_simplenn_tidy(net) ;

% Switch to DagNN if requested
switch lower(opts.networkType)
  case 'simplenn'
    % done
  case 'dagnn'
    net = dagnn.DagNN.fromSimpleNN(net, 'canonicalNames', true) ;
    net.addLayer('top1err', dagnn.Loss('loss', 'classerror'), ...
      {'prediction', 'label'}, 'error') ;
    net.addLayer('top5err', dagnn.Loss('loss', 'topkerror', ...
      'opts', {'topk', 5}), {'prediction', 'label'}, 'top5err') ;
  otherwise
    assert(false) ;
end

% --------------------------------------------------------------------
function net = insertBnorm(net, l)
% --------------------------------------------------------------------
assert(isfield(net.layers{l}, 'weights'));
ndim = size(net.layers{l}.weights{1}, 4);
layer = struct('type', 'bnorm', ...
               'weights', {{ones(ndim, 1, 'single'), zeros(ndim, 1, 'single')}}, ...
               'learningRate', [1 1 0.05], ...
               'weightDecay', [0 0]) ;
net.layers{l}.biases = [] ;
net.layers = horzcat(net.layers(1:l), layer, net.layers(l+1:end)) ;


