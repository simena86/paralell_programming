function path= computeBug1Path( start, goal, PolyList )
% Computes the path a Bug would follow until it hits an obstacle.
% Function requires start and goal point as well as a cell array of
% polygonal obstacles and returns an ordered list of all of the points 
% visited by the bug along its path. Note that each polygon is 
% defined by a n x 2 array of counterclockwise points.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Intro to Robotics, ME170A/ECE181A, Spring 2009
% Joey Durham
% April 25, 2010
% modified to bug1path by Simen Andresen, Sprint 2013
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% tolerances
circumStartTolerance=0.02;
circumLeaveStartTolerance=50;
maxStepSize = 0.02;

% Initialize the path variable 
path = start;

% loop until goal reached or no path exists
while( true )
    
    distToGoal = dist( path(end,:), goal );
    % Has bug reached goal location?
    if( distToGoal < maxStepSize )
        break
    end
    
    distToClosestObstacle = distToGoal + maxStepSize;
    closestPolygon = [];
    
    % Loop through each polygonal obstacle in the list to find the closest
    % one to the Bug's current position.
    for i = 1:length(PolyList)
        distToObstacle = computeDistancePointToPolygon(path(end,:), PolyList{i});
        if( distToObstacle < distToClosestObstacle )
            distToClosestObstacle = distToObstacle;
            closestPolygon = PolyList{i};
        end
    end
    
    % Is bug inside polygon?
    if( length(closestPolygon) > 0 && inpolygon(path(end,1), path(end,2), closestPolygon(:,1), closestPolygon(:,2)) )
        disp('Error - bug entered polygon')
        break
    end
    
    % Limit the length of a step the Bug will take based on proximity to
    % obstacles, goal so that it does not over shoot and enter an obstacle
    % or pass the goal location.
    stepSize = min( [maxStepSize, distToClosestObstacle/5, distToGoal] );
    
    % Has bug hit an obstacle?
    if( distToClosestObstacle < maxStepSize )
        
        %---- circumnavigation ----%
        circumPath=[newPoint];
        circumStart=newPoint;
        closestPoint=newPoint;
        while(1)
            
            % get one step of circum navigation
            [u_x u_y] = computeTangentVectorToPolygon(circumPath(end,:), closestPolygon);
            step=stepSize*[u_x u_y];
            newPoint=circumPath(end,:) + step;
            circumPath=[circumPath;newPoint];
            
            % check for closest point
            if dist(newPoint, goal) < dist(closestPoint,goal)
                closestPoint=newPoint;
                closestIndex=size(circumPath,1);
            end
                           
            % check if back at start point
            if(size(circumPath,1) > circumLeaveStartTolerance && dist(newPoint,circumStart) < circumStartTolerance)
                break;
            end
        end
        
        % Update Path
        path=[path ; circumPath(1:end,:) ; circumPath(1:closestIndex,:)];
        d1=computeDistancePointToPolygon(path(end,:),closestPolygon);
        
        % check if one can move towards goal from closest point on polygon
        u_x = (goal(1) - path(end,1))/distToGoal;
        u_y = (goal(2) - path(end,2))/distToGoal;
        step = stepSize*[u_x, u_y];
        stepFromPolygon = path(end,:) + step;
        d2=computeDistancePointToPolygon(stepFromPolygon,closestPolygon);
        if (d1 > d2)
            disp('No path from start to goal exists');
            return;
        end
        %---- end circumnavigation ----%
        
    else
        % Step towards goal along unit vector u between current point and goal
        u_x = (goal(1) - path(end,1))/distToGoal;
        u_y = (goal(2) - path(end,2))/distToGoal;

        % Add new step to end of the path
        step = stepSize*[u_x, u_y];
        newPoint = path(end,:) + step;
        path = [path; newPoint];
    end
    
      
end


