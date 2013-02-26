clear all; clc; close all;


link1Poly = [-.1,-.2; 1.1,-.2; 1.1,.2; -.1,.2];
link2Poly = [-.1,-.1; 1.7,-.1; 1.7,.1; -.1,.1];


link1Base = [0,0];  % In absolute coordinates
link2Base = [1,0];  % In relative coordinates, should be inside link1Poly

h(1)=figure(1);
hold on
[testPoly,testBase2] = displaceLinkPoly( link1Poly, 3*pi/4, link1Base, link2Base );
fill( testPoly(:,1), testPoly(:,2), 'b' )
[testPoly,testBase2] = displaceLinkPoly( link2Poly, 3*pi/4 - pi/2.5, testBase2, [0 0] );
fill( testPoly(:,1), testPoly(:,2), 'b' )

[testPoly,testBase2] = displaceLinkPoly( link1Poly, pi/4, link1Base, link2Base );
fill( testPoly(:,1), testPoly(:,2), 'g' )
[testPoly,testBase2] = displaceLinkPoly( link2Poly, pi/4 + pi/2.5, testBase2, [0 0] );
fill( testPoly(:,1), testPoly(:,2), 'g' )
hold off
axis([-2 2 -1 3]);
grid on;
xlabel('x');
ylabel('y');
axis square


for i=1:length(h)
 %   print(h(i), '-depsc', sprintf('../report/figures/plot%i.eps',i));
end