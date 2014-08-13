%Simple Matlab template to plot result from gepda.

thread_count = [1 2 4 8 16];
run_time_machine1 = [0.7844 0.7298 0.3674 0.2187 0.1420];
run_time_machine2 = [2.3255 2.1528 1.0880 0.6437 0.4109];
run_time_machine3 = [3.8042 3.5152 1.7829 1.0361 0.6365];

idx=size(thread_count);
for i=0:idx(2)-1
    speedup_machine1(i+1) = run_time_machine1(1)/run_time_machine1(i+1);
    speedup_machine2(i+1) = run_time_machine2(1)/run_time_machine2(i+1);
    speedup_machine3(i+1) = run_time_machine3(1)/run_time_machine3(i+1);
end

subplot(1,2,1)
hold on
plot(thread_count,run_time_machine1,'k.-')
plot(thread_count,run_time_machine2,'b.-')
plot(thread_count,run_time_machine3,'c.-')
xlabel('thread count'); ylabel('run time (s)')
legend('machine 1', 'machine 2', 'machine 3')
hold off
subplot(1,2,2)
hold on
plot(thread_count(2:5),speedup_machine1(2:5),'k.-')
plot(thread_count(2:5),speedup_machine2(2:5),'b.-')
plot(thread_count(2:5),speedup_machine3(2:5),'c.-')
xlabel('thread count'); ylabel('speedup')
legend('machine 1', 'machine 2', 'machine 3')
hold off
