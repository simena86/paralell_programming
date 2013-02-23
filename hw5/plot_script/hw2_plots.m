clear all
close all
clc

% For all plots we have 1000 iterations
iter = 1000;
% CUPS (Cells Updated Per Second) = iter * n² / s
%%
% CUPS vs n

n = [100,200,400,800,1500];
% Fixed num of processors
run_times_n =  [6,5,4,3,2];

CUPS = (iter * n.^2) ./ run_times_n;


h(1)=figure(1);
hold on; grid on;

plot(n,CUPS, '-ob');
xlabel('n');
ylabel('CUPS');
title('CUPS vs n');

%%
% CUPS vs p

p = [1,2,3,4,5,6,7,8];
n = 10000;
run_times_p =  [8,7,6,5,4,3,2,1];

CUPS = (iter * n.^2) ./ run_times_p;


h(2)=figure(2);
hold on; grid on;

plot(p,CUPS, '-ob');
xlabel('p');
ylabel('CUPS');
title('CUPS vs p');

%%
% Paralell efficiency (t_1/p*t_p) vs n

n = [100,200,400,800,1500];
t_1 = 8;
p = 8;
paralell_efficience = t_1 ./ (p .* run_times_n);

h(3)=figure(3);
hold on; grid on;

plot(n,paralell_efficience, '-ob');
xlabel('n');
ylabel('Paralell efficiency');
title('Paralell efficiency vs n');

%%
% Paralell efficiency (t_1/p*t_p) vs p

t_1 = 8;
p = [1,2,3,4,5,6,7,8];
paralell_efficience = t_1 ./ (p .* run_times_p);

h(4)=figure(4);
hold on; grid on;

plot(p,paralell_efficience, '-ob');
xlabel('n');
ylabel('Paralell efficiency');
title('Paralell efficiency vs p');

%%
for i=1:length(h)
    print(h(i), '-depsc', sprintf('plot%i.eps',i));
end


