function AdjTable = computeAdjTableForFreeCSpacePoints( freeCSpacePoints,maxAdjRadius )

% this function will have the time complexity of O(n^2)
num_points = size(freeCSpacePoints,1);
AdjTable{num_points} = [];

for i = 1:num_points
    x = freeCSpacePoints(i,1);
    y = freeCSpacePoints(i,2);
    z = freeCSpacePoints(i,3);
    for j = i+1:num_points  % +1 because we don't want to connect to our self

        x_j = freeCSpacePoints(j,1);
        y_j = freeCSpacePoints(j,2);
        z_j = freeCSpacePoints(j,3);

        % Calkulate the distance in x-direction
        dist_x = abs(x_j - x);
        % If the distance is longer than pi, we know that the distanse is 
        % shorter going through the torus
        if(dist_x > pi)
            % Calculate the distance through the torus
            dist_x = min(abs(pi-x_j),abs(-pi-x_j)) + min(abs(pi-x),abs(-pi-x));
        end

        % Do the same for in y-direction
        dist_y = abs(y_j - y);
        if(dist_y > pi)
            dist_y = min(abs(pi-y_j),abs(-pi-y_j)) + min(abs(pi-y),abs(-pi-y));
        end

        % Do the same for in z-direction
        dist_z = abs(z_j - z);
        if(dist_z > pi)
            dist_z = min(abs(pi-z_j),abs(-pi-z_j)) + min(abs(pi-z),abs(-pi-z));
        end

        % Calculate the total distance
        dist_ = sqrt(dist_x^2 + dist_y^2 + dist_z^2);

        if (dist_ < maxAdjRadius)
            AdjTable{i} = [AdjTable{i} ; j];
            AdjTable{j} = [AdjTable{j} ; i];
        end
    end
end