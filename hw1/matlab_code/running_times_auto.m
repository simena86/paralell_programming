clc;clear all;close all
%--------------------------
%
% plot running times automatically
% by Simen Andresen
%
%--------------------------



rtimes=csvread('../code/running_times_1');

n_values=rtimes(:,1);
running_t=rtimes(:,2);
flops_per_second=rtimes(:,3);

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
%axis([0,2200,-10^10 6*10^11]);




rtimes_2=csvread('../code/running_times_2');
rtimes_3=csvread('../code/running_times_3');


running_t_fastest=rtimes_2(:,2);
flops_fastest=rtimes_2(:,3);

running_t_slowest=rtimes_3(:,2);
flops_slowest=rtimes_3(:,3);



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
%axis([0,2200,-10^10 2*10^12]);

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
%axis([0,2200,-10^10 4*10^11]);



for i = 1:length(h)
    print(h(i), '-depsc',sprintf('../report/figures/plot2%i',i));
end