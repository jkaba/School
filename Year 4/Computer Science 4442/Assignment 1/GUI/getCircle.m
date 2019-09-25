% function circleMask = getCircle(currentPoint, radius, imSize)
% returns logical mask with the circle around the current point
% currentPoint  = [row col]
function circleMask = getCircle(currentPoint, radius, imSize)
radius = ceil(abs(radius));
[C,R] = meshgrid(1:imSize(2),1:imSize(1));
circleMask = ((R-currentPoint(1)).^2 + (C-currentPoint(2)).^2)<=(radius^2);