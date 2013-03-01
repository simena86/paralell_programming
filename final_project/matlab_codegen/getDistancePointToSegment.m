function dist = getDistancePointToSegment(q, p1, p2)
% Computes the distance from a point to a line segment.
% Function requires point to test q = [x,y] and two
% points to define the segment, p1 = [x1,y1] and p2 = [x2,y2].

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Intro to Robotics, ME170A/ECE181A, Spring 2009
% Joey Durham
% April 1, 2009
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

q_x = q(1);
q_y = q(2);
[a,b,c] = getLineThroughTwoPoints(p1,p2);
dist = 0;

% First, find the orthogonal projection of q onto the line
p_x = (b^2*q_x - a*b*q_y -a*c)/sqrt(a^2 + b^2);
p_y = (-a*b*q_x + a^2*q_y -b*c)/sqrt(a^2 + b^2);

% If projection is on the line segment, then distance is from q to p.
% Otherwise, it's the shorter of the distances from the endpoints
% of the segment.
bOnX = p_x >= min(p1(1),p2(1)) && p_x <= max(p1(1),p2(1));
bOnY = p_y >= min(p1(2),p2(2)) && p_y <= max(p1(2),p2(2));

if bOnX && bOnY
    dist = sqrt((q_x-p_x)^2 + (q_y-p_y)^2);
else
    dist1 = sqrt((q_x-p1(1))^2 + (q_y-p1(2))^2);
    dist2 = sqrt((q_x-p2(1))^2 + (q_y-p2(2))^2);
    dist = min(dist1,dist2);
end

% Uncomment the following lines to display debug plot
% figure;
% hold on
% plot(q_x,q_y,'ok');
% plot(p_x,p_y,'or');
% plot([p1(1),p2(1)],[p1(2),p2(2)],'-ob');
% axis([min([q_x,p1(1),p2(1)])-1, max([q_x,p1(1),p2(1)])+1, min([q_y,p1(2),p2(2)])-1, max([q_y,p1(2),p2(2)])+1]);
% axis square
% hold off;