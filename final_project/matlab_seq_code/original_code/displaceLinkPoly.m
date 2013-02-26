function [linkPoly, nextLinkBase] = displaceLinkPoly( linkPolyRef, linkAngle,linkBase, nextLinkBaseRef )
% function [linkPoly, nextLinkBase] = displaceLinkPoly( linkPolyRef, linklinkAngle,linkBase, nextLinkBaseRef )
% this function rotates a polygon of a robot manipulator by linklinkAngle and
% translated by linkBase

% Rotation matrix
R=[cos(linkAngle), -sin(linkAngle); sin(linkAngle), cos(linkAngle)];

% Rotate polygon and endpoint
linkPoly=(R*linkPolyRef')';
nextLinkBase=(R*nextLinkBaseRef')';

% Translate polygon
linkPoly(:,1)=linkPoly(:,1) + linkBase(1);
linkPoly(:,2)=linkPoly(:,2) + linkBase(2);
nextLinkBase(1)=nextLinkBase(1)+linkBase(1);
nextLinkBase(2)=nextLinkBase(2)+linkBase(2);


end
