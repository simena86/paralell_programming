clc;clear all;close all;
%-------------------------------------------------
%   plot running times of sequential program
%
%-------------------------------------------------


n_values=[128,256,512,1024,1400,2048];
running_t=[0.00001,0.000062,0.999873,12.99, 32 ,115.22];
flops_per_second=[5.174e+11,5.45e+11,2.68e+8,1.78949e+8, 1.715e+8,1.44369e+8];



h(1)=figure(1);
plot(n_values, running_t, '-or');
grid on;    
xlabel('n - matrix dimension');
ylabel('time [s]');

h(2)=figure(2);
plot(n_values, flops_per_second, '-or');
grid on;    
xlabel('flops per second');
ylabel('time [s]');
axis([0,2200,-10^10 6*10^11]);




%% task 2
%
%
% i k j     512:3           1024 : 28
% k j i     512:0.00213     1024 : 2.99
% k i j     512:3.02        1024 : 27.99
% j k i     512:0.000182    1024 : 1.9999
% j i k     512: 0.999      1024 : 13.1
%


running_t_fastest=[0.000005,0.000026,0.000203,1.999638,4.000095,13.000045];
flops_fastest=[8.79609e+11,1.3153e+12,1.32459e+12,1.07394e+9,1.37197e+9,1.32152e+9 ];
running_t_slowest=[0.000012,0.000133, 3.000328,27.999786,79.000325,268.999434];
flops_slowest=[3.59024e+11,2.51767e+11,8.94687e+7,7.66964e+7,6.94681e+7,6.38658e+7]





h(3)=figure(3);
plot(n_values, running_t_fastest, '-or');
grid on;    
title('Running times for fastest order of nested loops');
xlabel('n - matrix dimension');
ylabel('time [s]');

h(4)=figure(4);
plot(n_values, flops_fastest, '-or');
title('Flops per second for fastest order of nested loops');
grid on;    
xlabel('flops per second');
ylabel('time [s]');
axis([0,2200,-10^10 2*10^12]);

h(5)=figure(5);
plot(n_values, running_t_slowest, '-or');
title('Running times for slowest order of nested loops');
grid on;    
xlabel('n - matrix dimension');
ylabel('time [s]');

h(6)=figure(6);
plot(n_values, flops_slowest, '-or');
title('Flops per second for slowest order of nested loops');
grid on;    
xlabel('flops per second');
ylabel('time [s]');
axis([0,2200,-10^10 4*10^11]);



for i = 1:length(h)
    print(h(i), '-depsc',sprintf('../report/figures/plot%i',i));
    i
end


