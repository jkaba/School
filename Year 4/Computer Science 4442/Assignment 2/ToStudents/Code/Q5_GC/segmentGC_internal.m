%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% called by brushStrokes_gui when "segment" button is pressed
% first checks for presence of file 'param.mat' with parameters
% if present, calls segmentGC_external with parameters stored in
% param.mat
% if file not present, calls segmentGC_external with defautl parameters
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [segm,eng]  = segmentGC_internal(im,scribbleMask)

   
   filename = 'param.mat';  % this file should have variables "lambda" and "numClusters"
                            % if you wish to change them from default
                            % values
   lambda = 50;      % some default value
   numClusters = 100; % some default value
   inftyCost   = 1000;
   
   if (exist(filename,'file') > 0)
      load(filename);
   end;
   
   [segm,eng] = segmentGC(im,scribbleMask,lambda,numClusters,inftyCost);