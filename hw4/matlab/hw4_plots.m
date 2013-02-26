clear all
close all

%%
% fixed num of cores = 4


size_of_array = [1e5,1e6,1e7,1e8];

run_time_1_core_rec = [0.003,0.027000,0.368000,3.333000]; %time on one core
run_time_1_core_loop = [0.004000,0.042000,0.521000,4.873000];
run_time_1_core_hyperobject = [0.003000,0.029000,0.288000,2.983000];

run_times_4_cores_rec = [0.001000,0.006000,0.088000,0.813000];
run_times_4_cores_loop = [0.001000,0.013000,0.151000,1.462000];
run_times_4_cores_hyperobject = [0.001000,0.007000,0.072000,0.717000];

speedup_rec = run_time_1_core_rec./run_times_4_cores_rec;
speedup_loop = run_time_1_core_loop./run_times_4_cores_loop;
speedup_hyperobject = run_time_1_core_hyperobject./run_times_4_cores_hyperobject;

h(1)=figure(1);
hold on; grid on;

plot(log10(size_of_array),speedup_rec, '-ob');
plot(log10(size_of_array),speedup_loop, '-og');
plot(log10(size_of_array),speedup_hyperobject, '-ok');
xlabel('Input size (log10)');
ylabel('Speedup');
title('Different input sizes with 4 cores');
legend('rec','loop','hyperobject', 'Location','Best');


%%

%clear all


size_of_array = 1e6;
nproc = [1,2,3,4,5,6,7,8];
runtimes_rec = [0.027000,0.013000,0.008000,0.006000,0.005000,0.004000,0.004000,0.003000];
runtimes_loop = [0.042000,0.023000,0.016000,0.013000,0.011000,0.010000,0.009000,0.008000];
runtimes_hyperobject = [0.029000,0.014000,0.010000,0.007000,0.006000,0.005000,0.004000,0.004000];

speedup_rec = runtimes_rec(1)./runtimes_rec;
speedup_loop = runtimes_loop(1)./runtimes_loop;
speedup_hyperobject = runtimes_hyperobject(1)./runtimes_hyperobject;


h(2)=figure(2);
grid on; hold on;
plot(nproc,speedup_rec, '-ob');
plot(nproc,speedup_loop, '-og');
plot(nproc,speedup_hyperobject, '-ok');
xlabel('Num cores');
ylabel('Speedup');
title('Different number of cores with fixed input size = 10^6');
legend('rec','loop','hyperobject', 'Location','Best');


for i=1:length(h)
    print(h(i), '-depsc', sprintf('plot%i.eps',i));
end






