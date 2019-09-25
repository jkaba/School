# Assignment 1 Machine Learning

## Description

The Assignment for the Machine Learning topic is Hand Written Digit Classification

In this assignment you will develop and test several classifiers for hand written digit recognition using the reduced version of the famous MNIST dataset1.

The images in the original dataset are of size 28 by 28 pixels.

We rescaled images to size 16 by 16 pixels for computational eficiency.
Each 2D image is stretched into a vector for training/testing. Thus each image is a 256 dimensional feature vector of raw pixel intensities.
Load data into matlab using command load A1.
Matrix X train (size 5000 by 256) contains 5000 samples to use for training.
Samples are stored as rows.
Thus the first training image is in X train(1,:).
You can visualize any digit image with the provided matlab function showImage.
For example, to see the 7th training image, use showImage(X train(7,:)).
Column vector Y train contains the true labels of samples in X train.
Thus its size is 5000 by 1. Since matlab starts indexing at 1, it is convenient to denote digit 0 with label 1, digit 1 with label 2, ..., digit 9 with label 10.
Thus Y train contains integers from 1 to 10, corresponding to digits from 0 to 9. For example, the label of the first training image is Y train(1) is 6, which means the first training image has digit 5.


