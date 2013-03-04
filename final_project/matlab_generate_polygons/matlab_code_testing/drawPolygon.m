

clc
figure(1)
clf
axis([-3 3 -3 3]);
axis square
hold on;
grid on;
fill(Poly1(:,1),Poly1(:,2),'g');
fill(Poly2(:,1),Poly2(:,2),'g');
fill(link1Base(1)+link1Poly(:,1),link1Base(2)+link1Poly(:,2),'c');
fill(link2Base(1)+link2Poly(:,1),link2Base(2)+link2Poly(:,2),'r');

aaa=-2.7;
bbb=-2.2;
ccc= 2.1;

[r_out1,b2] = displaceLinkPoly( link1Poly, aaa,link1Base, link2Base );
[r_out2,b3] = displaceLinkPoly( link2Poly, aaa+bbb,b2, link3Base );
[r_out3,b4] = displaceLinkPoly( link3Poly, aaa+bbb+ccc,b3, [1,0] );

% 
fill(r_out1(:,1),r_out1(:,2),'r');
fill(r_out2(:,1),r_out2(:,2),'b');
fill(r_out3(:,1),r_out3(:,2),'y');


hold off






%%