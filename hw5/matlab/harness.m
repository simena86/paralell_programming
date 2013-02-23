function [score, time] = harness(n,niters,whichstart)
% HARNESS : Test and validation harness for matlab life code
%
% [score, time] = harness(n,niters,whichstart);
%
% This generates an n-by-n array (default n=100),
% runs an external "life" routine to play the game
% of life on it for "niters" iterations (default niters=5*n),
% and reports timing and correctness.
% "whichstart" (default 1) is an integer specifying
%   which of several starting positions to use.
%
% John R. Gilbert    26 Jan 2006, updated 7 Feb 2011

% if nargin < 1
%     n = 100;
% end;
% if nargin < 2
%     niters = 5*n;
% end;
% if nargin < 3
%     whichstart = 1;
% end;
fprintf('Matlab test harness for Game of Life.\n');
fprintf('Number of processors = 1 (sequential Matlab code)\n');
fprintf('Array dimension = %d\n', n);
fprintf('Number of generations = %d\n', niters);
A = gendata(n, whichstart);
tic;
livecounts = life(A, niters,0);
time = toc;
fprintf('Elapsed time = %d\n', time);
fprintf('Final number of live cells = %d\n', livecounts(end));
score = validate(n, whichstart, niters, livecounts);
if score == 1
    fprintf('Answer is correct.\n');
elseif score == 0
    fprintf('Answer is not correct.\n');
end;