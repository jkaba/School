%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% reads data and stores it in the right format for CNN
% Before reading the data, set up the required parameters
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

load(dataFile);
R = 16;
C = 16;
numTraining = size(X_train_full,1);

X_Train = single(reshape(X_train_full',R,C,1,numTraining));
Y_Train_V = ones(numTraining,1);     % 1 used for training, 2 for validation
I = randi(numTraining,numTraining*percentValidation/100,1);
Y_Train_V(I) = 2;

imdb.images.data = X_Train;
imdb.images.labels = Y_train_full';
imdb.images.set = Y_Train_V';     % sets validation samples

imdb.meta.classes = arrayfun(@(x)sprintf('%d',x),0:9,'uniformoutput',false) ;



