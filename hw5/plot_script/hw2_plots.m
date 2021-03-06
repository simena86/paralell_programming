clear all
close all
clc

% For all plots we have 1000 iterations
iter = 1000;
% CUPS (Cells Updated Per Second) = iter * n² / s
%%
% CUPS vs n
n = [500,1000,1500,2000,2500,3000,3500,4000,4500];
% Fixed num of processors
run_times_n =  [736.344000, 2143.160000, 4241.789000, 6952.073000, 10366.296000, 14284.383000, 18805.925000, 24001.320000, 29590.858000]./1000;

CUPS = (iter * n.^2) ./ run_times_n;

h(1)=figure(1);
hold on; grid on;
plot(n,CUPS, '-ob');
xlabel('n');
ylabel('CUPS');
title('CUPS vs n, p=8');

%%
% CUPS vs p, n=2000
p = [1,2,3,4,5,6,7,8];
n = 2000;
run_times_p =  [44799.198000, 23497.478000, 16062.110000, 12540.451000, 9948.694000, 8607.739000, 7668.280000, 6967.520000]./1000;

CUPS = (iter * n.^2) ./ run_times_p;

h(2)=figure(2);
hold on; grid on;
plot(p,CUPS, '-ob');
xlabel('p');
ylabel('CUPS');
title('CUPS vs p, n=2000');

%%
% Paralell efficiency (t_1/p*t_p) vs n

n = [500,1000,1500,2000,2500,3000,3500,4000,4500];
t_1 = [4908.951000, 14024.559000, 27309.618000, 44778.765000, 66433.730000, 92272.367000, 122299.665000, 156510.376000, 194942.282000]./1000;
p = 8;
paralell_efficience = t_1 ./ (p .* run_times_n);

h(3)=figure(3);
hold on; grid on;
plot(n,paralell_efficience, '-ob');
xlabel('n');
ylabel('Paralell efficiency');
title('Paralell efficiency vs n, p=8');

%%
% Paralell efficiency (t_1/p*t_p) vs p

t_1 = run_times_p(1);
p = [1,2,3,4,5,6,7,8];
paralell_efficience = t_1 ./ (p .* run_times_p);

h(4)=figure(4);
hold on; grid on;
plot(p,paralell_efficience, '-ob');
xlabel('n');
ylabel('Paralell efficiency');
title('Paralell efficiency vs p, n=2000');

%%
for i=1:length(h)
    print(h(i), '-depsc', sprintf('plot%i.eps',i));
end


