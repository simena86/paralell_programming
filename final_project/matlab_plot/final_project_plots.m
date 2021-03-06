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
% Paralell efficiency  vs n


% n = [10,15,20,25,30,35,40,45,50,55];
n = [10,15,20,25,30,35,40,45];
p = 8;


%p=8
%run_times_n_8 =  [ 0.00093,0.00825,0.04948,0.18875,0.52159,1.39290,3.11647,7.13247,15.52397,28.75429];
run_times_n_8 =  [ 0.00093,0.00825,0.04948,0.18875,0.52159,1.39290,3.11647,7.13247];

h(4)=figure(4);
hold on; grid on;
plot(n,run_times_n_8, '-ob', 'MarkerSize',20);
xlabel('n');
ylabel('Paralell efficiency');
title('Paralell efficiency vs p, n=50');
%%
%

% n = [10,15,20,25,30,35,40,45,50,55];
n = [10,15,20,25,30,35,40,45];
p = 8;

%p=1
run_times_n_1 = [0.00692,0.07450,0.42361,1.60599,4.71198,11.92388,26.56231,54.05625];
%p=8
%run_times_n_8 =  [ 0.00093,0.00825,0.04948,0.18875,0.52159,1.39290,3.11647,7.13247,15.52397,28.75429];
run_times_n_8 = [0.00093,0.00825,0.04948,0.18875,0.52159,1.39290,3.11647,7.13247];
pe = run_times_n_1./(p.*run_times_n_8);


h(5)=figure(5);
hold on; grid on;
plot(n,pe, '-ob', 'MarkerSize',20);
xlabel('n');
ylabel('Paralell efficiency');
title('Paralell efficiency vs n, p=8');

%%
for i=1:length(h)
    print(h(i), '-depsc', sprintf('plot%i.eps',i));
end


