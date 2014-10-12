% m3dof_simulation Parameter file

eg = [0 1 0];

m1 = 3; % Mass link 1 
m2 = 3; % Mass link 2
m3 = 3; % Mass link 3
l1 = 1/3; % Lenght link 1
l2 = 1/3; % Lenght link 2
l3 = 1/3; % Lenght link 3
mx1 = m1*l1/2 ; % Mass moment first order 1
mx2 = m2*l2/2 ; % Mass moment first order 2
mx3 = m3*l3/2 ; % Mass moment first order 3
I1 = 4/12*m1*l1^2; %Mass moment of Inertia 1
I2 = 4/12*m2*l2^2; %Mass moment of Inertia 2
I3 = 4/12*m3*l3^2; %Mass moment of Inertia 3