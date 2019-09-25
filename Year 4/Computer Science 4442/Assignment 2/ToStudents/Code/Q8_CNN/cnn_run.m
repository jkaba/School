more off;
%setups paths and reads the data
setup;

% initializes network structure
net = initializeCNN_basic; 

% train network
[net, info] = cnn_trainMy(net,imdb);


% store the mean image with the network, need to subtract mean from any test
% image
net.imageMean = imdb.images.data_mean ;


% remove the last layer (softmax), as we don't need it for clasification
net.layers(end) = [] ;


% now perform classification on test data
[err,pred] = cnn_classify(net,X_test_full,Y_test_full);
fprintf('Test error is %f.\n',err);