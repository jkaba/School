function out = stretch(im)

smallest = min(im(:));
largest = max(im(:));

[row,col] = size(im);

out = double(im);

if smallest == largest,
    out = zeros(row,col);
else
    ratio = 255/(largest-smallest);
    out = out-smallest;
    out = out*ratio;
end;