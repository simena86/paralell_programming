clear all
close all
clc




%%
% runtimes vs p
n = 40;
p = [1,	2	,3	,4	,5	,6	,7	,8	,10	,12	,16	,20	,26	,32	,40	,50	,64];
run_times_tot = [54.979953,	27.457603	,18.421665	,13.789829	,11.061219	,9.313183	,8.029002	,7.023167	,5.709573	,4.755729	,3.597782	,2.904370	,2.269197	,1.975175	,1.605897	,1.297975	,1.012298];
run_times_sampling = [0.666704,	0.33628	,0.22772	,0.173505	,0.140272	,0.122115	,0.104067	,0.096887	,0.079547	,0.0729	,0.061942	,0.058173	,0.056877	,0.069046	,0.064668	,0.058054	,0.056982];

h(1)=figure(1);
hold on; grid on;
plot(p,run_times_tot, '-ob');
xlabel('p');
ylabel('time');
title('totale tuntime vs p, n=40');

%%
% Speedup
pe = run_times_tot(1)./(run_times_tot);

h(2)=figure(2);
hold on; grid on;
plot(p,pe, '-ob');
xlabel('nprocs');
ylabel('speedup');
title('Speedup vs nprocs (totale program), n=40');


%%
% Speedup
pe = run_times_tot(1)./(p.*run_times_tot);

h(3)=figure(3);
hold on; grid on;
plot(p,pe, '-ob');
xlabel('nprocs');
ylabel('Paralell efficiency');
title('Paralell efficiency vs nprocs (totale program), n=40');


%%

% Plotting the sampling times

h(4)=figure(4);
hold on; grid on;
plot(p,run_times_sampling, '-ob');
xlabel('nprocs');
ylabel('time');
title('Sampling runtime vs nprocs, n=40');

%%
% Speedup
pe = run_times_sampling(1)./(run_times_sampling);

h(5)=figure(5);
hold on; grid on;
plot(p,pe, '-ob');
xlabel('nprocs');
ylabel('speedup');
title('Speedup vs nprocs (sampling), n=40');


%%
% Speedup
pe = run_times_sampling(1)./(p.*run_times_sampling);

h(6)=figure(6);
hold on; grid on;
plot(p,pe, '-ob');
xlabel('nprocs');
ylabel('Paralell efficiency');
title('Paralell efficiency vs nprocs (sampling), n=40');


%%
for i=1:length(h)
    print(h(i), '-depsc', sprintf('plot%i.eps',i));
end