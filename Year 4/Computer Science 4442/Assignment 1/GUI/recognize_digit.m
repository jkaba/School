% You need to load some matlab data to use for your classifier
% You can either do it with "load data.m" command inside this 
% function. Or, alternatively, you can store your
% data in file named "myData.mat". This file is loaded
% one time into environment when brushStrokes_gui is first envoked
% To access your data,use handle myData
% For example, if you file contains matrix "W",
% use myData.W to get to that matrix
% For displaying digit class in the gui, remember that
% label "i" actually means digit "i-1", so you want to adjust for that
% to display the correct digit to the user


function label = recognize_digit(img, myData)

%disp('replace the call to this function with your classifier!')
label = 5;


