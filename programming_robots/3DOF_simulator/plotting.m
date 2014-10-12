close all

% % Plots of q
% figure
% plot(results_q.time,results_q.data(1,:),'b')
% hold on
% plot(results_q.time,results_q.data(2,:),'g')
% hold on
% plot(results_q.time,results_q.data(3,:),'r')
% title('Joint Positions Q')
% legend('q1','q2','q3')
% 
% % Plots of q_dot
% figure 
% plot(results_q_dot.time,results_q_dot.data(1,:),'b')
% hold on
% plot(results_q_dot.time,results_q_dot.data(2,:),'g')
% hold on
% plot(results_q_dot.time,results_q_dot.data(3,:),'r')
% title('Joint Velocities Q dot')
% legend('qdot1','qdot2','qdot3')
% 
% % Plots of tau
% figure 
% plot(results_tau.time,results_tau.data(1,:),'b')
% hold on
% plot(results_tau.time,results_tau.data(2,:),'g')
% hold on
% plot(results_tau.time,results_tau.data(3,:),'r')
% title('Torques')
% legend('tau1','tau2','tau3')
% 
% % Plots of x_pose
% figure 
% plot(results_x.time,results_x.data(1,:),'b')
% title('Pose')
% hold on
% plot(results_x.time,results_x.data(2,:),'g')
% legend('x','y')

% Plots of observer
figure 
plot(results_observer.time,results_observer.data(1,:),'b')
hold on
% plot(results_observer.time,results_observer.data(2,:),'b')
% hold on
% plot(results_observer.time,results_observer.data(3,:),'r')
title('Observer - Torques')
% legend('obs-tau1','obs-tau2','obs-tau3')
legend('obs-tau1')

% Plots of noisy
figure 
plot(results_noisy_q.time,results_noisy_q.data(1,:),'b')
hold on
title('Noisy signal q')

% Plots of observer
figure 
plot(results_noisy_q_dot.time,results_noisy_q_dot.data(1,:),'b')
hold on
title('Noisy signal q-dot')
