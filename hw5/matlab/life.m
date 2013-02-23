function livecounts = life(A, niters, display)
% life : Play Conway's Game of Life on a torus grid
%
% livecounts = life(A, niters, display);
%
% This takes as input an n-by-n array A of 0s and 1s and plays
% J. H. Conway's game of Life for "niters" generations on it.
% See http://en.wikipedia.org/wiki/Conway's_Game_of_Life
%
% The array is considered to be wrapped around at the edges,
% so that e.g. A(7,n) is the left neighbor of A(7,1),
% and A(1,9) is just above A(2,9) and just below A(n,9).
%
% For the purpose of validating the code, an output "livecounts"
% is returned with the number of nonzero cells in A at each of
% ten generations:  niters/10, 2*niters/10, ... , niters.
%
% If the optional third argument "display" is 1, 
% we draw a picture at each generation.
%
% John R. Gilbert    27 Jan 2006, modified 7 Feb 2011

if nargin < 3
    display = 0;
end;
if nargin < 2
    niters = 150;
end;
if nargin < 1
    A = gendata(50,2);
    display = 1;
end;
livecounts = [];
n = size(A,1);
north = [n, 1:n-1];
east  = [2:n, 1];
south = [2:n, 1];
west  = [n, 1:n-1];

if display, spy(A); title('Generation 0'); shg; pause(2.25); end;

for generation = 1:niters
    
    % count how many of the eight neighbors are alive.
    neighbors = A(north,:) + A(south,:) + A(:,east) + A(:,west) + ...
        A(north,east) + A(north,west) + A(south,east) + A(south,west);
        
    % The rules of Life are:
    %   A live cell with two live neighbors, 
    %   or any cell with three live neighbors, 
    %   is alive at the next time step
    A = ((A == 1) & (neighbors == 2)) | (neighbors == 3);  
        
    % record the live cell count if necessary
    if mod(generation, round(niters/10)) == 0
        livecounts = [livecounts nnz(A)];
    end;

    if display
        spy(A);
        title(['Generation ' int2str(generation)]);
        shg;
        pause(.02);
    end;  
end;
