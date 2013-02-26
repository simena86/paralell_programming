clc; close all; clear all;
% --------------------------
%
%   my_bug1_test
%
%---------------------------


% Define start and goal positions plus a couple of polygonal obstacles
start = [.3,.3]
goal = [3.8,4]
Poly1 = [-0.6,0.3;-0.4,-0.4;0.7,-0.3;0.6,0.4;0.2,0.3;-0.296057,0.596997];
Poly2 = [-0.8,-0.4;-0.1,-0.1;0.9,-0.4;0.3,0.2;0.102922,0.598169;-0.3,0.4];



% Shift polygons into positions along path to create obstacles
Poly1 = 1.5*Poly1 + 1.5;
Poly2 = 2.0*Poly2 + 3.5;

% Need to create a list of these obstacles to define the environment, the curly
% brackets define a MATLAB cell array which allows us to easily handle
% polygons of different lengths
PolyList = {Poly1, Poly2};

bugPath=computeBug1Path(start, goal, PolyList);