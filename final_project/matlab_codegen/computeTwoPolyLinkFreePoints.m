function freeConfigs = computeTwoPolyLinkFreePoints( sampleList, link1BaseRef,link1PolyRef, link2BaseRef, link2PolyRef, ObstacleList )
% function freeConfigs = computeTwoPolyLinkFreePoints( sampleList, link1BaseRef,link1PolyRef, link2BaseRef, link2PolyRef, ObstacleList )
% this function 
    freeConfigs=[];
    collision=0;
    for i = 1:size(sampleList,1)
       alpha=sampleList(i,1); 
       beta=sampleList(i,2); 
       [poly1, base2]=displaceLinkPoly(link1PolyRef,alpha,link1BaseRef,link2BaseRef);
       [poly2, dummy]=displaceLinkPoly(link2PolyRef,alpha+beta,base2,[0 0]);
       for k = 1:length(ObstacleList)
           if (checkCollisionBetweenPolygons(poly1,ObstacleList{k}) || checkCollisionBetweenPolygons(poly2,ObstacleList{k}))
                collision=1;
           else
               noCollision=0;
           end
        end
        if collision ==0
            freeConfigs(size(freeConfigs,1)+1,:)=[alpha, beta];
        end
        collision=0;
    end
end


