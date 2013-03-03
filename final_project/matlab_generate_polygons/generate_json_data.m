clear all;clc;close all;
%----------------------------------------
%
%   generate polygons with json-parsing
%   
%
%
%----------------------------------------


%% OBSTACLES
p1x=[  1.0860,    0.8762,    0.4395,    0.2524,    0.6323, 1.0860]';
p1y=[ 1.2717,    2.0116,    1.7457,    0.4046,   -0.0809 ,  1.217]';
poly1=zeros(length(p1x),2);
poly1(:,1)=p1x;
poly1(:,2)=p1y;



p2x=[ -0.6493,   -0.4395,   -1.0917,   -1.8913,   -1.3185,-0.6493]';
p2y=[-1.1792,   -0.3931,    0.4162,   -0.7283,   -2.0925, -1.1792]';
poly2=zeros(length(p1x),2);
poly2(:,1)=p1x;
poly2(:,2)=p1y;

obstacles=struct('obstacle1x',p1x','obstacle1y',p1y','nVertices1',length(p1x),'obstacle2x',p2x','obstacle2y',p2y','nVertices2',length(p2x));

%% LINKS
close all;
link1Poly = [-.1,-.2; .5,-.3; 1.1,-.2; 1.1,.1; .5,.3; -.1,.1 ; -.1 , -.2];
link2Poly = [-.1,-.1; .5,-.2; 1.7,-.1; 1.7,.05; .5,.2; -.1,.05; -.1 , -.1];
link3Poly = [-.1,-.1; .5,-.2; 1.7,-.1; 1.7,.05; .5,.2; -.1,.05; -.1, -.1];


link1Base = [0,0];  % In absolute coordinates
link2Base = [1,0];  % In relative coordinates, should be inside link1Poly
link3Base = [1.7,0];% In relative coordinates, should be inside link2Poly

linkPolys=struct('nVertices1',length(link1Poly(:,1)),'nVertices2',length(link2Poly(:,1)),'nVertices3',length(link3Poly(:,1)),'link1x', ...
    link1Poly(:,1)','link1y',link1Poly(:,2)','link2x',link2Poly(:,1)','link2y',link2Poly(:,2)','link3x',link3Poly(:,1)','link3y',link3Poly(:,2)');

linkBases=struct('base1',link1Base,'base2',link2Base,'base3',link3Base);
links=struct('linkPolys',linkPolys, 'linkBases',linkBases);



%% generate json file

root=struct('links',links,'obstacles',obstacles);
savejson('',root,'polygons.json');



%% PLOTTING



h(1)=figure(1);
fill(poly1(:,1), poly1(:,2), 'k');
%k=convhull(poly1(:,1), poly1(:,2));
hold on 
fill(poly1(:,1),poly1(:,2), 'g');
poly1
axis([-3 3 -3 3]);