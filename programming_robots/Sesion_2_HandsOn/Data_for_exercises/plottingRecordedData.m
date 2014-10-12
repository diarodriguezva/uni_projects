%% init
close all

a = load('/logs/log_PTP_movement.log');
b = load('/logs/log_LIN_movement.log');
sum_a = zeros(size(a));
sum_b = zeros(size(b));
for i=2:length(a)
    sum_a(i,:) = sum_a(i-1,:)+a(i,:);
end

for i=2:length(b)
    sum_b(i,:) = sum_b(i-1,:)+b(i,:);
end

%% relative
figure
hold on;
title('RELATIVE TRANSLATIONAL DISTANCE');

plot(a(:,1),a(:,2));
plot(b(:,1),b(:,2),'r');
legend('PTP','LIN','Location', 'SouthEast');

figure
hold on;
title('RELATIVE ROTATIONAL DISTANCE');
plot(a(:,1),a(:,3));
plot(b(:,1),b(:,3),'r');
legend('PTP','LIN','Location', 'SouthEast');

figure
hold on;
title('RELATIVE JOINT SPACE DISTANCE');
plot(a(:,1),a(:,4));
plot(b(:,1),b(:,4),'r');
legend('PTP','LIN','Location', 'SouthEast');

%% absolute
figure
hold on;
title('ABSOLUTE TRANSLATIONAL DISTANCE');

plot(sum_a(:,1),sum_a(:,2));
plot(sum_b(:,1),sum_b(:,2),'r');
legend('PTP','LIN','Location', 'SouthEast');

figure
hold on;
title('ABSOLUTE ROTATIONAL DISTANCE');
plot(sum_a(:,1),sum_a(:,3));
plot(sum_b(:,1),sum_b(:,3),'r');
legend('PTP','LIN','Location', 'SouthEast');

figure
hold on;
title('ABSOLUTE JOINT SPACE DISTANCE');
plot(sum_a(:,1),sum_a(:,4));
plot(sum_b(:,1),sum_b(:,4),'r');
legend('PTP','LIN','Location', 'SouthEast');