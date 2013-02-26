close all; clc; clear all

% Intialize polygons
% Obstacles and links are modeled as polygons
figure

Poly1(:,1)=[-2.3960 -2.3847  -2.2543    -2.1181   -1.9594   -1.7836   -1.6928   -1.6021   -1.4603   -1.2448   -1.0860   -1.0123   -0.9442   -0.9442   -1.0406 ...
    -1.0633   -1.1257   -1.1257   -1.2278   -1.2391   -1.3696   -1.3696   -1.4773   -1.4943   -1.6361   -1.7268   -1.5340   -1.4603   -1.3809   -1.3242   -1.2448...
       -1.1994   -1.1484   -1.0974   -1.0406   -0.9612   -0.9159   -0.9045   -0.9216   -1.0180   -1.0803   -1.2618   -1.4206   -1.6588   -1.8686   -1.8800   -1.8800  -2.0388   -2.2429   -2.4074];


Poly1(:,2)=[ -0.1965     0.3584    0.8671    1.1908    1.2139    1.1445    1.0058    0.9249    0.8208    0.8208    0.8208    0.7746    0.5896    0.3699    0.4509    0.3468...    
    0.4393    0.3006    0.4277    0.1734    0.3353    0.0925    0.2543    0.0809    0.1156   -0.0925   -0.1040   -0.0578   -0.1618    0.0462   -0.0578    0.0925...
       -0.0694    0.1734    0.0462    0.2312    0.1156   -0.0231   -0.1387   -0.1387   -0.2775   -0.3931   -0.3931   -0.4509   -0.4509   -0.7052   -1.0867   -1.0867   -1.0983   -1.0983];

   
Poly2(:,1)=[ 2.3409     2.5227    2.6136    2.2500    1.7955    1.5682   1.6136    2.0530    1.8864    1.8106    1.5985    1.1288    0.9015    0.7197    0.7803    0.9318...
    1.0985    1.2500    1.3409    1.4167    1.5682    1.7348    1.6742    1.6742    1.2348   1.2197    1.6136    2.0833    2.3106    2.4924    2.2500    2.1742    2.3712];

Poly2(:,2)=[   0.1917    0.6709    1.0927    1.4952    1.3994    0.9585    0.3642    0.0767   -0.5176   -0.9201   -0.6134   -0.0767    0.1725   -0.0767   -0.4026   -0.4026   -0.3450...
       -0.4792   -0.7859   -1.0160   -1.0927   -1.5144   -2.3003   -2.6454   -2.5304   -2.7987   -2.7412   -2.7412   -2.7412   -2.6645   -2.1470   -1.4952   -0.6518];
   
Poly1(:,2)=Poly1(:,2)+1;
Poly1(:,1)=Poly1(:,1)-0.1;
Poly2(:,1)=Poly2(:,1)+0.1;   
i=1;
axis([-3 3 -3 3]);         
hold off;
% [q(1), q(2)] = ginput(1); % get a point
% axis([-3 3 -3 3]);
% while(1)  
%     [x10(i),x20(i)] = ginput(1);   
%     if(x10(i) > 2.5 && x20(i) > 2.5)  
%        break;              
%     end
%     fill(x10,x20, 'b');
%     hold on
%     fill(Poly1(:,1), Poly1(:,2), 'g');
%     fill(Poly2(:,1), Poly2(:,2), 'g');
%     
%     hold off
%     axis([-3 3 -3 3]); 
%     i=i+1;
% end
% hold on;
% P=zeros(i-1,2);
% P(:,1)=x10(1:end-1);
% P(:,2)=x20(1:end-1);

link1Poly=[ 
    -0.4773 ,   0.4792;
   -0.7803 ,   0.0958;
    0.1288  ,  0.1342 ;
    0.12018  , 0.1192;
    0.12018    0.3067];

link2Poly=[
     -0.2348 ,   0.3067;
   -0.6439   , 0.0383;
   -0.7197 ,  -0.3642;
   -0.2955 ,   0.0383;
    0.1439 ,  -0.1342;
    0.52500 ,  -0.2492;
    0.0379 ,   0.2109;
    ];

link1Poly(:,1)=link1Poly(:,1)+0.45;
link2Poly(:,1)=link2Poly(:,1)+0.64;
link2Poly(:,2)=link2Poly(:,2)+0.25;

hold on;
    fill(Poly1(:,1), Poly1(:,2), 'g');
    fill(Poly2(:,1), Poly2(:,2), 'g');
    fill(link1Poly(:,1),link1Poly(:,2), 'r');
    fill(link2Poly(:,1),link2Poly(:,2), 'r');
    grid on



link1Base = [0,0];  % In absolute coordinates
link2Base = [0.55,0.2];  % In relative coordinates, should be inside link1Poly

ObstacleList = {Poly1, Poly2};





%% Generate sample points

numSamples = 30;
angleSamples = linspace( -pi, pi - (2*pi)/numSamples, numSamples );
%angleSamples = linspace( -pi, pi, numSamples );
sampleList = [];
for angle2 = angleSamples
    for angle1 = angleSamples
        sampleList = [sampleList; angle1, angle2];
    end
end

plot(sampleList(:,1), sampleList(:,2), '.r');
%% Determine which sample points are in free config space

disp('Computing Free Configuration Space for 2-link manipulator')
tic
freeCSpacePoints = computeTwoPolyLinkFreePoints( sampleList, link1Base, link1Poly, link2Base, link2Poly, ObstacleList );
toc

%% Plot freeCSpacePoints for testing

figure;
axis( [-pi pi -pi pi] )
axis square
hold on
for j = 1:size(freeCSpacePoints,1)

    alpha = freeCSpacePoints(j,1);
    beta = freeCSpacePoints(j,2);
    plot( alpha, beta, '.b', 'LineWidth', 2 );

end
hold off

%% Compute adjacency look-up table suitable for doing BFS

connectRadius = (2.2*pi)/(numSamples-1);

disp('Computing Adjacency Table')
tic
adjTable = computeAdjTableForFreeCSpacePoints( freeCSpacePoints, connectRadius );
toc

%% Plot connections between vertices

figure;
axis( [-pi pi -pi pi] )
axis square
hold on
for j = 1:size(freeCSpacePoints,1)

    alpha = freeCSpacePoints(j,1);
    beta = freeCSpacePoints(j,2);
    plot( alpha, beta, '.b', 'LineWidth', 2 );

end

for j = 1:size(freeCSpacePoints,1)

    alpha1 = freeCSpacePoints(j,1);
    beta1 = freeCSpacePoints(j,2);

    for k = 1:size(adjTable{j},1)
        idx2 = adjTable{j}(k,1);
        alpha2 = freeCSpacePoints(idx2,1);
        beta2 = freeCSpacePoints(idx2,2);

        if( max(abs(freeCSpacePoints(j,:) - freeCSpacePoints(idx2,:))) < 1.1*connectRadius )

            plot( [alpha1 alpha2], [beta1 beta2], '-b', 'LineWidth', 1 );
        end
    end

end
hold off

%% Plot some test output

close all;
testPoints = randperm(size(freeCSpacePoints,1));

for i = 1:3

    startIdx = testPoints(2*i-1);
    goalIdx = testPoints(2*i);

    disp('Finding BFS path')
    tic
    cSpacePath = computeBFSPath(startIdx, goalIdx, adjTable);
    toc

    disp('Ploting results')
    % tic
    h((i-1)*2+1)=figure((i-1)*2+1);
    axis( [-pi pi -pi pi] )
    axis square
    hold on

    % Plot the free configuration points
    for j = 1:size(freeCSpacePoints,1)
        
        alpha = freeCSpacePoints(j,1);
        beta = freeCSpacePoints(j,2);
        plot( alpha, beta, '.b', 'LineWidth', 2 );
        
    end
    xlabel('alpha');
    ylabel('beta');
    % Plot the path produced by BFS through the free configuration space
    for row = 1:size(cSpacePath,1)
        edge = cSpacePath(row,:);
        
        v1 = edge(1);
        v2 = edge(2);
        
        plot( [freeCSpacePoints(v1,1); freeCSpacePoints(v2,1)], [freeCSpacePoints(v1,2); freeCSpacePoints(v2,2)], 'or', 'LineWidth', 2 )
          
        if( max(abs(freeCSpacePoints(v1,:) - freeCSpacePoints(v2,:))) < 1.1*connectRadius )
            % Only draw segments  which don't wrap around toroidal config space
            plot( [freeCSpacePoints(v1,1); freeCSpacePoints(v2,1)], [freeCSpacePoints(v1,2); freeCSpacePoints(v2,2)], '-r', 'LineWidth', 1 )
        end
        
    end

    % Plot the start and goal vertexes
    plot( freeCSpacePoints(startIdx,1), freeCSpacePoints(startIdx,2), 'og', 'LineWidth', 5 )
    plot( freeCSpacePoints(goalIdx,1), freeCSpacePoints(goalIdx,2), 'or', 'LineWidth', 5 )
    %toc
    hold off
    
    % Plot the start and goal configurations in the workspace with obstacles
    h((i-1)*2+2)=figure((i-1)*2+2);
    hold on
    for i = 1:length(ObstacleList)
        obs = ObstacleList{i};
        fill(obs(:,1),obs(:,2),'k')
    end
    [startLink1,newLink2Base] = displaceLinkPoly( link1Poly, freeCSpacePoints(startIdx,1), link1Base, link2Base );
    startLink2 = displaceLinkPoly( link2Poly, freeCSpacePoints(startIdx,1) + freeCSpacePoints(startIdx,2), newLink2Base, [0,0] );
    fill( startLink1(:,1), startLink1(:,2), 'g' )
    fill( startLink2(:,1), startLink2(:,2), 'g' )

    [goalLink1,newLink2Base] = displaceLinkPoly( link1Poly, freeCSpacePoints(goalIdx,1), link1Base, link2Base );
    goalLink2 = displaceLinkPoly( link2Poly, freeCSpacePoints(goalIdx,1) + freeCSpacePoints(goalIdx,2), newLink2Base, [0,0] );
    fill( goalLink1(:,1), goalLink1(:,2), 'r' )
    fill( goalLink2(:,1), goalLink2(:,2), 'r' )
    xlabel('x');
    ylabel('y');
    axis([-3 3 -3 3])
    axis square
    hold off

end

for k=1:length(h)
   % print(h(k), '-depsc',sprintf('../report/figures/plotbfs%i',k));
end

%% Produce movie for particular configurations

% Find path between two particular points in c-space.  First, need to find
% closest sampled points.

startPoint = [-pi/2-0.3, 0];
goalPoint = [pi/2, .3];

startVertex = 1;
bestStartDist = 2*pi;
goalVertex = 1;
bestGoalDist = 2*pi;

for i = 1:size(freeCSpacePoints,1)
    if( angDist( startPoint, freeCSpacePoints(i,:) ) < bestStartDist )
        startVertex = i;
        bestStartDist = angDist( startPoint, freeCSpacePoints(startVertex,:) );
    elseif( angDist( goalPoint, freeCSpacePoints(i,:) ) < bestGoalDist )
        goalVertex = i;
        bestGoalDist = angDist( goalPoint, freeCSpacePoints(goalVertex,:) );
    end
end

disp('Finding BFS path')
tic
cSpacePath = computeBFSPath(startVertex, goalVertex, adjTable);
toc

fig=figure;

filename = '2-linkMovieb.avi';
delete(filename);
movieObj = avifile('2-linkMovieb.avi');
movieObj.Quality = 20;
% If you have trouble playing the movie, try changing the compression type,
% see help avifile for more info.
movieObj.Compression = 'None';
movieObj.Fps = 10.0;

set(fig,'DoubleBuffer','on');
set(gca,'xlim',[-2 2],'ylim',[-2 2],...
    'nextplot','replace','Visible','off');

for row = 1:(size(cSpacePath,1)-3)
    edge = cSpacePath(row,:);
    
    v1 = edge(1);
    v2 = edge(2);
    
    alpha1 = freeCSpacePoints(v1,1);
    alpha2 = freeCSpacePoints(v2,1);
    
    beta1 = freeCSpacePoints(v1,2);
    beta2 = freeCSpacePoints(v2,2);
    
    
    [drawLink1,newLink2Base] = displaceLinkPoly( link1Poly, alpha1, link1Base, link2Base );
    drawLink2 = displaceLinkPoly( link2Poly, alpha1 + beta1, newLink2Base, [0,0] );
    h1=fill( drawLink1(:,1), drawLink1(:,2), 'r' );
    hold on
    h2=fill( drawLink2(:,1), drawLink2(:,2), 'b' );
    set(h1,'facealpha',0.5);
    set(h2,'facealpha',0.6);
    for i = 1:length(ObstacleList)
        obs = ObstacleList{i};
        fill(obs(:,1),obs(:,2),'g')
    end

    hold off
    axis([-3 3 -3 3])
    axis square
    frame = getframe(gca);
    movieObj = addframe(movieObj,frame);
    
    [drawLink1,newLink2Base] = displaceLinkPoly( link1Poly, alpha2, link1Base, link2Base );
    drawLink2 = displaceLinkPoly( link2Poly, alpha2 + beta2, newLink2Base, [0,0] );
    h1=fill( drawLink1(:,1), drawLink1(:,2), 'r' );
    hold on
    h2=fill( drawLink2(:,1), drawLink2(:,2), 'b' );
    set(h1,'facealpha',0.5);
    set(h2,'facealpha',0.6);
    
    for i = 1:length(ObstacleList)
        obs = ObstacleList{i};
        fill(obs(:,1),obs(:,2),'g')
    end
    
    hold off
    axis([-3 3 -3 3])
    axis square
    frame = getframe(gca);
    movieObj = addframe(movieObj,frame);
    f = getframe;
    imwrite(f.cdata, sprintf('./video/%04d.png',row));
end

movieObj = close(movieObj);