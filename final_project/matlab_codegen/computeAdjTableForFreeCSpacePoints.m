function AdjTable = computeAdjTableForFreeCSpacePoints( freeCSpacePoints,maxAdjRadius )
% function AdjTable = computeAdjTableForFreeCSpacePoints( freeCSpacePoints,maxAdjRadius )

    AdjTable=cell(size(freeCSpacePoints,1));
    fc=mod(freeCSpacePoints,2*pi);
    for i=1:size(freeCSpacePoints,1)
        for j=i+1:size(freeCSpacePoints,1)
            % find closest distance on a 2-torus
            dca=fc(i,1)-fc(j,1);
            dcb=fc(i,2)-fc(j,2);
            dcca=2*pi-fc(i,1)+fc(j,1);
            dccb=2*pi-fc(i,2)+fc(j,2);
            alpha= min(dca,dcca);
            beta= min(dcb,dccb);
            if(sqrt(alpha.^2 + beta.^2)<=maxAdjRadius)
                AdjTable{i}=[AdjTable{i},j];
                AdjTable{j}=[AdjTable{j},i];
            end
        end
       AdjTable{i}=AdjTable{i}'; 
    end
end