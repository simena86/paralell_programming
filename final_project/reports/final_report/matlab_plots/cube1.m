close all; clc; clear all;

%define the 8 vertices of a cube
v = [0 0 0; 1 0 0; 1 1 0; 0 1 0; 0 0 1; 1 0 1; 1 1 1; 0 1 1]; 
%define the 6 faces in terms of the 8 vertices
f = [1 2 3 4; 5 6 7 8; 2 3 7 6; 1 4 8 5; 3 4 8 7; 1 2 6 5];
%set the color to 0 red, 0.3 green, and 0 blue for the 8 vertices

fvc = [0 .3 0; 0 .3 0; 0 .3 0; 0 .3 0; 0 .3 0; 0 .3 0; 0 .3 0; 0 .3 0;];


myh = figure(1);
%set up the standard 3D view
view(3); axis square



%image the green translucent cube
patch('Vertices',v,'Faces',f,'FaceVertexCData',fvc,...
         'FaceColor','interp','EdgeColor','flat',...
          'FaceAlpha', 0.2)
