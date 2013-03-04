function freeConfigs = computeTwoPolyLinkFreePoints( sampleList, link1BaseRef,link1PolyRef, link2BaseRef, link2PolyRef, link3BaseRef, link3PolyRef, ObstacleList )

k = 1;

for i=1:length(sampleList)
    collision = false; 
    % Set the manipulator in the given configuration given by (alpha,beta)
    % in sampleList
    
    [tempPoly1,tempBase2] = displaceLinkPoly( link1PolyRef, sampleList(i,1), link1BaseRef, link2BaseRef )
    [tempPoly2,tempBase3] = displaceLinkPoly( link2PolyRef, sampleList(i,1)+sampleList(i,2),tempBase2 , link3BaseRef)
    [tempPoly3,not_used] = displaceLinkPoly( link3PolyRef,  sampleList(i,1)+sampleList(i,2)+sampleList(i,3),tempBase3 , [0 0])  
    
    for j=1:length(ObstacleList)
        % Check if the manipulator collide with any obstacle in the given
        % configuration
        if (checkCollisionBetweenPolygons( tempPoly1,ObstacleList{j}) == true || checkCollisionBetweenPolygons( tempPoly2,ObstacleList{j}) == true || checkCollisionBetweenPolygons( tempPoly3,ObstacleList{j}) == true)
            collision = true;
            break;
        end
    end
    if (collision == false)
        % If no collision, add the given sampleList set to freeConfigs
        freeConfigs(k,:) = sampleList(i,:);
        k=k+1;
    end
end
end