clc;
close all
clear all

a=csvread('cilkview.out');

rec=zeros(size(a,1)/3,2);
loop=zeros(size(a,1)/3,2);
hyper=zeros(size(a,1)/3,2);

for i=0:size(a,1)/3-1
    rec(i+1,:)=a(i*3+1,:);
    loop(i+1,:)=a(i*3+2,:);
    hyper(i+1,:)=a(i*3+3,:);
end

h(1)=figure(1);
plot(rec(:,1), rec(:,2));
hold on;
plot(loop(:,1), loop(:,2),'-r');
%plot(hyper(:,1), hyper(:,2), 'k');
legend('Recursive', 'Loop','Location','Best');
xlabel('Coarsness');
ylabel('time [s]');
grid on;

for i=1:length(h)
    print(h(i), '-depsc', sprintf('../report/figures/plot2%i.eps',i));
end


