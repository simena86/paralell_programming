function xyzfinal = nbody(n)
% NBODY : Simulate n-body problem
%
% xyzfinal = nbody(n)
%
% We simulate Newton's equations of motion in steps of dt seconds,
% drawing a picture after every time step.
%
% n = 0 simulates the solar system (sun and 9 planets)
% n > 0 generates n bodies at random to simulate

% John R. Gilbert, January 2010, last updated 22 Jan 2013

if nargin == 0 || n == 0
    n = 10;
    [mass,xyz,vxyz] = gen_nbody; % generate the solar system
else
    [mass,xyz,vxyz] = gen_nbody(n); % generate random initial data
           % mass(i)     = mass of i-th body (kg)
           % xyz(i,1:3)  = initial position of i-th body (m in x,y,z)
           % vxyz(i,1:3) = initial velocity of i-th body (m/s in x,y,z)
end;
                          
G = 6.674e-11;             % gravitational constant, m^3 kg^-1 s^-2
week = 60 * 60 * 24 * 7;   % one week, in seconds
dt = 1 * week;             % size of a time step
steps = 500;               % number of time steps to simulate    
pix = 1;                   % 1 to draw pictures, 0 not to

if pix > 0, clf reset; plot_pix(xyz,0); end;

for s = 1:steps
    axyz = zeros(n,3);   % acceleration of each body at this time step
    for i = 1:n
        for j = 1:n
            dxyz = xyz(i,:) - xyz(j,:);  % (x,y,z) vector from body j to i
            r = norm(dxyz);              % distance between bodies i and j
            if r == 0, continue, end;    % no force on a body from itself
            f = G * mass(i) * mass(j) / r^2;  % force as a scalar
            fxyz = f * dxyz/r;                % force as a vector
            axyz(i,:) = axyz(i,:) - fxyz / mass(i);  % update to acceleration
        end;
    end;
    vxyz = vxyz + dt * axyz;    % update to velocity
    xyz = xyz + dt * vxyz;      % update to position
    if pix > 0, plot_pix(xyz,s); end;
end;
xyzfinal = xyz;
end



function plot_pix(v,t)
view = [1 0 0 ; 0 1 0]; % projection matrix for 2D pictures
dim = 1e13;
plot(v(:,1),v(:,2),'r.');
hold on;
plot(v(1,1),v(1,2),'y*');
axis([-dim dim -dim dim]);
axis square
title(sprintf('step %d',t));
hold off
shg;
pause(.02);
end
