clear all
close all
clc

% this script is plotting vs n

% First we plot the totale thing

%%
% Paralell efficiency vs n


% n = [10,15,20,25,30,35,40,45,50,55];
n = [15,20,25,30,35,40,45,50,55];
p8 = 8;
p16 = 16;


%p=8
%run_times_n_8 = [ 0.00093,0.00825,0.04948,0.18875,0.52159,1.39290,3.11647,7.13247,15.52397,28.75429];


run_times_n_8 = [	0.03116,	0.137743,	0.443438	,1.281424	,3.181954	,7.50003	,14.691187	,28.072558	,49.815521];
run_times_n_1 = [0.190401	,0.942674	,3.441077	,10.029809	,24.935827	,54.889046	,111.097107	,208.242789	,368.418783];
run_times_n_16 = [0.023344	,0.076406	,0.244682	,0.663206	,1.622798	,3.79863	,7.819164	,14.093173	,25.22];



h(10)=figure(10);
hold on; grid on;
plot(n,run_times_n_1, '-or');
plot(n,run_times_n_8, '-ob');
plot(n,run_times_n_16, '-og');
legend('p=1','p=8','p=16','Location','Best');
xlabel('n');
ylabel('time');
title('Totale running times vs n');
%%
%


pe8 = run_times_n_1./(p8.*run_times_n_8);
pe16 = run_times_n_1./(p16.*run_times_n_16);


h(11)=figure(11);
hold on; grid on;
plot(n,pe8, '-ob');
plot(n,pe16, '-or');
xlabel('n');
ylabel('Paralell efficiency');
title('Paralell efficiency vs n (whole program)');
legend('p=8','p=16','Location','Best');

%%

% plotting the sampling time

% Paralell efficiency vs n



p8 = 8;
p16 = 16;


%p=8
%run_times_n_8 = [ 0.00093,0.00825,0.04948,0.18875,0.52159,1.39290,3.11647,7.13247,15.52397,28.75429];

run_times_n_1 = [0.034675,	0.082417	,0.161021	,0.279251	,0.448	,0.670897	,0.952543	,1.320307	,1.742765];
run_times_n_8 = [	0.008055,	0.016545	,0.022748	,0.04352	,0.066294	,0.097265	,0.133225	,0.185375	,0.246335];
run_times_n_16 = [0.008977,	0.012298,	0.021309	,0.027734	,0.042801	,0.064563	,0.079617	,0.119901	,0.147009];



h(12)=figure(12);
hold on; grid on;
plot(n,run_times_n_1, '-or');
plot(n,run_times_n_8, '-ob');
plot(n,run_times_n_16, '-og');
legend('p=1','p=8','p=16','Location','Best');

xlabel('n');
ylabel('time');
title('Sampling running times vs n');
%%
%


pe8 = run_times_n_1./(p8.*run_times_n_8);
pe16 = run_times_n_1./(p16.*run_times_n_16);


h(13)=figure(13);
hold on; grid on;
plot(n,pe8, '-ob');
plot(n,pe16, '-or');
xlabel('n');
ylabel('Paralell efficiency');
title('Paralell efficiency vs n (sampling), p=8 and p=16');
legend('p=8','p=16','Location','Best');



%%
for i=1:3
    print(h(i+9), '-depsc', sprintf('plot%i.eps',i+9));
end
