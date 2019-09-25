% normalizes data by finding average image and subtracting it from each
% image

dataMean = mean(imdb.images.data(:,:,:,imdb.images.set == 1), 4);  % finds mean on the training set
imdb.images.data = bsxfun(@minus, imdb.images.data, dataMean);     % subtrac the mean from all training data
imdb.images.data_mean = dataMean;




