cdfunction score = validate(n, whichstart, niters, livecounts)
% VALIDATE : Validate output from Matlab life simulation
%
% score = validate(n, whichstart, niters, livecounts);
%
% Given an array of size "n" starting in configuration
% "whichstarts" and running the Game of Life for "niters"
% generations resulting in "livecounts(i)" live cells
% after i*niters/10 generations (for i from 1 to 10), return:
%   1: success, correct answer
%   0: failure, wrong answer
%  -1: unknown, don't have a validation for this configuration.
%
% John R. Gilbert    26 Jan 2006, modified 7 Feb 2011

%   whichstart = 0:  all 0s
%   whichstart = 1:  an interesting cell
%   whichstart = 2:  a glider

if length(livecounts) ~= 10
    fprintf('Validation needs exactly 10 live-cell counts\n');
    score = 0;
    return;
end;
if (mod(niters,10)~=0) || (niters~=5*n)
    fprintf('Can only validate if niters = 5*n and n is a multiple of 10\n');
    score = -1;
    return;
end;

if whichstart == 0
    score = all(livecounts==0);
    return;
end;

if whichstart == 1
    % values of n for which we can validate with whichstart=1
    sizes1 = [10 20 100 200];
    % answers1(n,1:10) is the correct livecounts
    answers1 = [ ...
        13    19    21     6     5     5     5     5     5     5 %n=10  
        19    35    66    70    49    43    60    52    36    31 %n=20
        55    72    95    94   118    82   204   121   143   142 %n=100
        72    94    82   121   142   154   185   206   216   185 %n=200
    ];
    i = find(sizes1 == n);
    if isempty(i)
        fprintf('Sorry, no validation available for n=%d\n',n);
        score = -1;
        return;
    end;
    score = all(livecounts(:) == answers1(i,:)');
    return;
end;

if whichstart == 2
    score = all(livecounts==5);
    return;
end;

fprintf('Sorry, no validation available for whichstart=%d\n',whichstart);
return;