function A = gendata(n,whichstart)
% GENDATA : Create sample data for the Game of Life
%
% A = gendata(n,whichstart)
%
% This returns an n-by-n array of 0s and 1s 
% as a starting position for the Game of Life.
%
% "whichstart" is an integer that specifies which
% which of several starting positions to use.
% This Matlab prototype has three possibilities:
%   whichstart = 0:  all 0s
%   whichstart = 1:  an interesting cell
%   whichstart = 2:  a glider
% You will want to try out more possibilities in your parallel code.
%
% John R. Gilbert    26 Jan 2006, modified 7 February 2011

A = zeros(n,n);
if whichstart == 0
    return
elseif whichstart == 1
    cell = [1 1 1 0 1 ; 1 0 0 0 0 ; 0 0 0 1 1 ; 0 1 1 0 1 ; 1 0 1 0 1];
    i = round(n/3);
    j = round(n/5);
    A(i:i+4,j:j+4) = cell;
    return
elseif whichstart == 2
    glider = [1 1 1 ; 1 0 0 ; 0 1 0 ];
    i = round(n/3);
    j = round(n/5);
    A(i:i+2,j:j+2) = glider;
    return
else
    error('whichstart must be 0, 1, or 2 for the Matlab data generator');
end;
