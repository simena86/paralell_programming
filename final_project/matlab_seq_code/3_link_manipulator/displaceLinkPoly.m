function [linkPoly, nextLinkBase] = displaceLinkPoly( linkPolyRef, linkAngle,linkBase, nextLinkBaseRef )

linkPoly = zeros(length(linkPolyRef),2);

% Making the 2D rotation matrix
Rotation_matrix = [cos(linkAngle), -sin(linkAngle) ; sin(linkAngle), cos(linkAngle)];

% Rotate and translate every vertices of the polygon
for i =1:length(linkPolyRef);
    x = [linkPolyRef(i,1) ; linkPolyRef(i,2)];   
    % Rotation
    linkPoly(i,:) = Rotation_matrix * x;
    %translation
    linkPoly(i,1) = linkPoly(i,1) + linkBase(1);
    linkPoly(i,2) = linkPoly(i,2) + linkBase(2); 
    
end

% Do the rotiation and translation for the next link base
x = [nextLinkBaseRef(1) ; nextLinkBaseRef(2)];
nextLinkBase = Rotation_matrix * x;
nextLinkBase(1) = nextLinkBase(1) + linkBase(1);
nextLinkBase(2) = nextLinkBase(2) + linkBase(2);

end