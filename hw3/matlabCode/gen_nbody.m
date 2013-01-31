function [mass,xyz,vxyz] = gen_nbody(n)
% GEN_NBODY : Generate dataset for nbody simulation
%
% [mass,xyz,vxyz] = gen_nbody(n);
%
% Output is a three arrays of initial values for n-body simulation.
%    mass : n-by-1 array of masses in kg
%    xyz  : n-by-3 array of positions in m
%    vxyz : n-by-3 array of velocities in m/sec
% If input argument n is omitted, generate the 10-body solar system.
%
% John R. Gilbert  18 Jan 2010

if nargin == 0
    n = 10;
    % sun mercury venus earth mars, jupiter saturn neptune uranus pluto
    earth = 4;
    earthspeed = 29800;  % m/s
    
    mass = [1.99e30; 3.30e23; 4.87e24; 5.97e24; 6.42e23; ...
        1.90e27; 5.69e26; 1.02e26; 8.68e25; 1.31e22]; 
    dist = [0; 5.8e10; 1.08e11; 1.50e11; 2.28e11; ...
        7.78e11; 1.43e12; 2.87e12; 4.50e12; 5.91e12];
    
    theta = 2*pi*rand(10,1); % start at random position in 2D orbit
    xyz = [dist.*cos(theta) dist.*sin(theta) zeros(10,1)];
    
    speed = earthspeed * (dist(earth) ./ dist).^.5;
    speed(1) = 0;
    direction = [-xyz(:,2) xyz(:,1) zeros(10,1)];
    direction = diag(1./sqrt(sum(direction.^2,2))) * direction;
    direction(1,:) = [0 0 0];
    vxyz = diag(speed) * direction;
    vxyz(1,:) = [0 0 0];
else  % generate n bodies with random masses and positions, zero velocity
    mass = 1e30*ones(n,1);    % masses up to about 1/2 solar mass
    i=0;
    for proc=0:1
        for j=0:2
             xyz(proc+1,j+1)=proc*1000 + i*j  + 10*j + 10*i;
        end
    end
    
    vxyz = zeros(n,3);          % initial velocities all zero
    disp('init states');
    disp([xyz(1,1), xyz(1,2),xyz(1,3),vxyz(1,1), vxyz(1,2),vxyz(1,3)]);
end;
