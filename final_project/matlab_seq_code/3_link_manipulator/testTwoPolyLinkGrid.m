close all
clc
clear all
%% Intialize polygons

% Obstacles and links are modeled as polygons
clear all
Poly1 = [-0.6,0.3;-0.4,-0.4;0.7,-0.3;0.6,0.4;0.2,0.3;-0.296057,0.596997];
Poly2 = [-0.8,-0.4;-0.1,-0.1;0.9,-0.4;0.3,0.2;0.102922,0.598169;-0.3,0.4];
%Poly3 = [-0.8,-0.4;-0.1,-0.1;0.9,-0.4;0.3,0.2;0.102922,0.598169;-0.3,0.4];
Poly3 = [-0.6,0.3;-0.4,-0.4;0.7,-0.3;0.6,0.4;0.2,0.3;-0.296057,0.596997];

Poly1 = Poly1 + ones(size(Poly1))*[1.4 0; 0 .7];
Poly2 = Poly2 + ones(size(Poly2))*[-1.5 0; 0 1.6];
Poly3 = Poly3 + ones(size(Poly2))*[-1.5 0; 0 -1.4];

ObstacleList = {Poly1, Poly2, Poly3};

% link1Poly = [-.1,-.2; 1.1,-.2; 1.1,.2; -.1,.2];
% link2Poly = [-.1,-.1; 1.7,-.1; 1.7,.1; -.1,.1];
link1Poly = [-.1,-.2; .5,-.3; 1.1,-.2; 1.1,.1; .5,.3; -.1,.1];
link2Poly = [-.1,-.1; .5,-.2; 1.7,-.1; 1.7,.05; .5,.2; -.1,.05];
link3Poly = [-.1,-.1; .5,-.2; 1.7,-.1; 1.7,.05; .5,.2; -.1,.05];


link1Base = [0,0];  % In absolute coordinates
link2Base = [1,0];  % In relative coordinates, should be inside link1Poly
link3Base = [1.7,0];


%% Generate sample points

%numSamples = 30;
numSamples = 15;
angleSamples = linspace( -pi, pi - (2*pi)/numSamples, numSamples );
%angleSamples = linspace( -pi, pi, numSamples );
sampleList = [];
for angle3 = angleSamples
    for angle2 = angleSamples
        for angle1 = angleSamples
            sampleList = [sampleList; angle1, angle2, angle3];
        end
    end
end

%% Determine which sample points are in free config space

disp('Computing Free Configuration Space for 2-link manipulator')
tic
freeCSpacePoints = computeTwoPolyLinkFreePoints( sampleList, link1Base, link1Poly, link2Base, link2Poly, link3Base, link3Poly, ObstacleList );
toc

%% Plot freeCSpacePoints for testing

figure;
%axis( [-pi pi -pi pi] )
axis( [-pi pi -pi pi -pi pi] )
axis square
grid on
hold on
xlabel('alpha')
ylabel('beta')
zlabel('gamma')
for j = 1:size(freeCSpacePoints,1)

    alpha = freeCSpacePoints(j,1);
    beta = freeCSpacePoints(j,2);
    gamma = freeCSpacePoints(j,3);
    %plot( alpha, beta, '.b', 'LineWidth', 2 );
    plot3( alpha, beta, gamma, '.r', 'LineWidth', 2 );

end
hold off

%% Compute adjacency look-up table suitable for doing BFS

connectRadius = (2.2*pi)/(numSamples-1);
%connectRadius = 2.5*(2.2*pi)/(numSamples-1);

disp('Computing Adjacency Table')
tic
adjTable = computeAdjTableForFreeCSpacePoints( freeCSpacePoints, connectRadius );
toc

%% Plot connections between vertices

figure;
%axis( [-pi pi -pi pi] )
axis( [-pi pi -pi pi -pi pi] )
axis square
hold on
for j = 1:size(freeCSpacePoints,1)

    alpha = freeCSpacePoints(j,1);
    beta = freeCSpacePoints(j,2);
    gamma = freeCSpacePoints(j,3);
    plot3( alpha, beta, gamma, '.r', 'LineWidth', 2 );

end

for j = 1:size(freeCSpacePoints,1)

    alpha1 = freeCSpacePoints(j,1);
    beta1 = freeCSpacePoints(j,2);
    gamma1 = freeCSpacePoints(j,3);

    for k = 1:size(adjTable{j},1)
        idx2 = adjTable{j}(k,1);
        alpha2 = freeCSpacePoints(idx2,1);
        beta2 = freeCSpacePoints(idx2,2);
        gamma2 = freeCSpacePoints(idx2,3);

        if( max(abs(freeCSpacePoints(j,:) - freeCSpacePoints(idx2,:))) < 1.1*connectRadius )
            
            plot3( [alpha1 alpha2], [beta1 beta2], [gamma1 gamma2], '-b', 'LineWidth', 1 );
        end
    end

end
hold off

%% Plot some test output

testPoints = randperm(size(freeCSpacePoints,1));



    startIdx = testPoints(2-1);
    goalIdx = testPoints(2);

    disp('Finding BFS path')
    tic
    cSpacePath = computeBFSPath(startIdx, goalIdx, adjTable);
    toc

    disp('Ploting results')
    % tic
    figure;
    axis( [-pi pi -pi pi -pi pi] )
    axis square
    hold on

    % Plot the free configuration points
    for j = 1:size(freeCSpacePoints,1)
        
        alpha = freeCSpacePoints(j,1);
        beta = freeCSpacePoints(j,2);
        gamma = freeCSpacePoints(j,3);
        plot3( alpha, beta, gamma, '.b', 'LineWidth', 2 );
        
    end

    % Plot the path produced by BFS through the free configuration space
    for row = 1:size(cSpacePath,1)
        edge = cSpacePath(row,:);
        
        v1 = edge(1);
        v2 = edge(2);
        
        plot3( [freeCSpacePoints(v1,1); freeCSpacePoints(v2,1)], [freeCSpacePoints(v1,2); freeCSpacePoints(v2,2)], [freeCSpacePoints(v1,3); freeCSpacePoints(v2,3)], 'or', 'LineWidth', 2 )
          
        if( max(abs(freeCSpacePoints(v1,:) - freeCSpacePoints(v2,:))) < 1.1*connectRadius )
            % Only draw segments  which don't wrap around toroidal config space
            plot3( [freeCSpacePoints(v1,1); freeCSpacePoints(v2,1)], [freeCSpacePoints(v1,2); freeCSpacePoints(v2,2)], [freeCSpacePoints(v1,3); freeCSpacePoints(v2,3)], '-r', 'LineWidth', 1 )
        end
        
    end

    % Plot the start and goal vertexes
    plot3( freeCSpacePoints(startIdx,1), freeCSpacePoints(startIdx,2), freeCSpacePoints(startIdx,3), 'og', 'LineWidth', 5 )
    plot3( freeCSpacePoints(goalIdx,1), freeCSpacePoints(goalIdx,2), freeCSpacePoints(goalIdx,3), 'or', 'LineWidth', 5 )
    %toc
    hold off
    
    % Plot the start and goal configurations in the workspace with obstacles
    figure
    hold on
    for i = 1:length(ObstacleList)
        obs = ObstacleList{i};
        fill(obs(:,1),obs(:,2),'k')
    end
    [startLink1,newLink2Base] = displaceLinkPoly( link1Poly, freeCSpacePoints(startIdx,1), link1Base, link2Base );
    [startLink2,newLink3Base] = displaceLinkPoly( link2Poly, freeCSpacePoints(startIdx,1) + freeCSpacePoints(startIdx,2), newLink2Base, link3Base );
    startLink3 = displaceLinkPoly( link3Poly, freeCSpacePoints(startIdx,1) + freeCSpacePoints(startIdx,2) + freeCSpacePoints(startIdx,3), newLink3Base, [0,0] );
    fill( startLink1(:,1), startLink1(:,2), 'g' )
    fill( startLink2(:,1), startLink2(:,2), 'g' )
    fill( startLink3(:,1), startLink3(:,2), 'g' )

    [goalLink1,newLink2Base] = displaceLinkPoly( link1Poly, freeCSpacePoints(goalIdx,1), link1Base, link2Base );
    [goalLink2,newLink3Base] = displaceLinkPoly( link2Poly, freeCSpacePoints(goalIdx,1) + freeCSpacePoints(goalIdx,2), newLink2Base, link3Base );
    goalLink3 = displaceLinkPoly( link3Poly, freeCSpacePoints(goalIdx,1) + freeCSpacePoints(goalIdx,2) + freeCSpacePoints(goalIdx,3), newLink3Base, [0,0] );
    fill( goalLink1(:,1), goalLink1(:,2), 'r' )
    fill( goalLink2(:,1), goalLink2(:,2), 'r' )
    fill( goalLink3(:,1), goalLink3(:,2), 'r' )

    axis([-3 3 -3 3 -3 3])
    axis square
    hold off



%% Produce movie for particular configurations

% Find path between two particular points in c-space.  First, need to find
% closest sampled points.

startPoint = [0, 0, 0];
goalPoint = [1.5, -1.5, -1];

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

filename = '3-linkMovieb.avi';
delete(filename);
movieObj = avifile('3-linkMovieb.avi');
movieObj.Quality = 100;
% If you have trouble playing the movie, try changing the compression type,
% see help avifile for more info.
movieObj.Compression = 'None';
movieObj.Fps = 10.0;

set(fig,'DoubleBuffer','on');
set(gca,'xlim',[-2 2],'ylim',[-2 2],...
    'nextplot','replace','Visible','off');

for row = 1:size(cSpacePath,1)
    edge = cSpacePath(row,:);
    
    v1 = edge(1);
    v2 = edge(2);
    
    alpha1 = freeCSpacePoints(v1,1);
    alpha2 = freeCSpacePoints(v2,1);
    
    beta1 = freeCSpacePoints(v1,2);
    beta2 = freeCSpacePoints(v2,2);

    gamma1 = freeCSpacePoints(v1,3);
    gamma2 = freeCSpacePoints(v2,3);

    
    
    
    [drawLink1,newLink2Base] = displaceLinkPoly( link1Poly, alpha1, link1Base, link2Base );
    [drawLink2,newLink3Base] = displaceLinkPoly( link2Poly, alpha1 + beta1, newLink2Base, link3Base );
    drawLink3 = displaceLinkPoly( link3Poly, alpha1 + beta1 + gamma1, newLink3Base, [0,0] );
    fill( drawLink1(:,1), drawLink1(:,2), 'g' )
    hold on
    fill( drawLink2(:,1), drawLink2(:,2), 'y' )
    fill( drawLink3(:,1), drawLink3(:,2), 'g' )

    for i = 1:length(ObstacleList)
        obs = ObstacleList{i};
        fill(obs(:,1),obs(:,2),'r')
    end

    hold off
    axis([-3 3 -3 3])
    axis square
    frame = getframe(gca);
    movieObj = addframe(movieObj,frame);
    
    [drawLink1,newLink2Base] = displaceLinkPoly( link1Poly, alpha2, link1Base, link2Base );
    [drawLink2,newLink3Base] = displaceLinkPoly( link2Poly, alpha2 + beta2, newLink2Base, link3Base );
    drawLink3 = displaceLinkPoly( link3Poly, alpha2 + beta2 + gamma2, newLink3Base, [0,0] );
    fill( drawLink1(:,1), drawLink1(:,2), 'g' )
    hold on
    fill( drawLink2(:,1), drawLink2(:,2), 'y' )
    fill( drawLink3(:,1), drawLink3(:,2), 'g' )
    
    for i = 1:length(ObstacleList)
        obs = ObstacleList{i};
        fill(obs(:,1),obs(:,2),'r')
    end
    
    hold off
    axis([-3 3 -3 3])
    axis square
    frame = getframe(gca);
    movieObj = addframe(movieObj,frame);
    
    
end

movieObj = close(movieObj);
