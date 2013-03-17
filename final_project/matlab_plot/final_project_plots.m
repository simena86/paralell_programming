clear all
close all
clc


% Output of runtimes of the function comupteAdjtable. n = 50
% 
%  p: 1, time: 100.46644 
%  p: 2, time: 49.23119 
%  p: 3, time: 32.93524 
%  p: 4, time: 23.78315 
%  p: 6, time: 17.37631 
%  p: 8, time: 13.42576 
%  p: 10, time: 11.01912 
%  p: 12, time: 11.26837 
%  p: 16, time: 8.53925
%  p: 20, time: 5.61935 
%  p: 32, time: 3.59269 
%  p: 64, time: 1.90838  

%%
% runtimes vs p

p = [1,2,3,4,6,8,10,12,16,20,32,64];
n = 50;
run_times_p =  [100.46644,49.23119,32.93524,23.78315,17.37631,13.42576,11.01912,11.26837,8.53925,5.61935,3.59269,1.90838];

h(1)=figure(1);
hold on; grid on;
plot(p,run_times_p, '-ob','MarkerSize',20);
xlabel('p');
ylabel('time');
title('runtime vs p, n=50');

%%
% Speedup
p = [1,2,3,4,6,8,10,12,16,20,32,64];
n = 50;
run_times_p =  [100.46644,49.23119,32.93524,23.78315,17.37631,13.42576,11.01912,11.26837,8.53925,5.61935,3.59269,1.90838];
pe = run_times_p(1)./(run_times_p);

h(2)=figure(2);
hold on; grid on;
plot(p,pe, '-ob', 'MarkerSize',20);
xlabel('p');
ylabel('speedup');
title('Speedup vs p, n=50');


%%
% Speedup
p = [1,2,3,4,6,8,10,12,16,20,32,64];
n = 50;
run_times_p =  [100.46644,49.23119,32.93524,23.78315,17.37631,13.42576,11.01912,11.26837,8.53925,5.61935,3.59269,1.90838];
pe = run_times_p(1)./(p.*run_times_p);

h(3)=figure(3);
hold on; grid on;
plot(p,pe, '-ob', 'MarkerSize',20);
xlabel('p');
ylabel('Paralell efficiency');
title('Paralell efficiency vs p, n=50');


%%
for i=1:length(h)
    print(h(i), '-depsc', sprintf('plot%i.eps',i));
end


