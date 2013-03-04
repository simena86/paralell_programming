clear all;clc;close all;
%----------------------------------------
%
%   generate polygons with json-parsing
%   
%
%
%----------------------------------------


%% OBSTACLES
p1x=[  1.0860,    0.8762,    0.4395,    0.2524,    0.6323 ]';
p1y=[ 1.2717,    2.0116,    1.7457,    0.4046,   -0.0809 ]';
if(p1x(end) ~= p1x(1)),  p1x=[p1x;p1x(1)]; end
if(p1x(end) ~= p1y(1)),  p1y=[p1y;p1y(1)]; end

poly1=zeros(length(p1x),2);
p1x=p1x+1.2 ;
poly1(:,1)=p1x;
poly1(:,2)=p1y;



p2x=[ -0.6493,   -0.4395,   -1.0917,   -1.8913,   -1.3185]';
p2y=[-1.1792,   -0.3931,    0.4162,   -0.7283,   -2.0925]';
if(p2x(end) ~= p2x(1)),  p2x=[p2x;p2x(1)]; end
if(p2x(end) ~= p2y(1)),  p2y=[p2y;p2y(1)]; end

poly2=zeros(length(p1x),2);
p2x=p2x-0.7;
p2y=p2y-0.7 ;
poly2(:,1)=p2x;
poly2(:,2)=p2y;

obstacles=struct('obstacle1x',p1x','obstacle1y',p1y','nVertices1',length(p1x),'obstacle2x',p2x','obstacle2y',p2y','nVertices2',length(p2x));

%% LINKS
close all;
link1Poly = [-.1,-.2; .5,-.3; 1.1,-.2; 1.1,.1; .5,.3; -.1,.1];
link2Poly = [-.1,-.1; .5,-.2; 1.7,-.1; 1.7,.05; .5,.2; -.1,.05];
link3Poly = [-.1,-.1; .5,-.2; 1.7,-.1; 1.7,.05; .5,.2; -.1,.05];
% close the polygons - first vertex is equal to last
if max((link1Poly(1,:)  == link1Poly(end,:))) >0 , link1Poly=[link1Poly;link1Poly(1,:)]; end
if max((link2Poly(1,:)  == link2Poly(end,:))) >0 , link2Poly=[link2Poly;link2Poly(1,:)]; end
if max((link3Poly(1,:)  == link3Poly(end,:))) >0 , link3Poly=[link3Poly;link3Poly(1,:)]; end


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
fill(poly2(:,1),poly2(:,2), 'g');

axis([-3 3 -3 3]);