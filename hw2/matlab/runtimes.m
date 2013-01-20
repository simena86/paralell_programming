clc;close all;
%-----------------------------
%
%   plot of execution time
%
%-----------------------------


run_t = [ 25.67,12.95,6.47,3.41,1.97];
processors=[1,2,4,8,16];

para_eff=zeros(1,length(run_t));
for i=1:length(run_t)
    para_eff(i)=run_t(1)/(processors(i)*run_t(i));
end

h(1)=figure(1);
plot(processors, run_t, '-or');
grid on;
xlabel('n processors');
ylabel('Execution Time [s]');

h(2)=figure(2);
plot(processors, para_eff, '-or');
grid on;
xlabel('n processors');
ylabel('Parallel efficiency');



for i=1:length(h)
    print(h(i), '-depsc', sprintf('../report/figures/plot%i.eps',i));
end

avg=0
for i=1:(length(run_t)-1)
    avg=avg+run_t(i)./run_t(i+1);
end

avg=avg/4