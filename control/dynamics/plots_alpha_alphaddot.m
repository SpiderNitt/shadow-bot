syms v_com phi l_eff y(t) z(t);

%% alpha from alpha dot equation is y
initial_condition = y(0) == 0;
y = dsolve(diff(y,t) == v_com/(l_eff*sin(y+phi)),initial_condition);

% Subsitutte the values for the variables
y = subs(y,[v_com,phi,l_eff],[10,pi/6,15]);
%% To plot the required y vs time
% Plot only after substituting values
time_input = linspace(0,100,1000);
figure;
plot(time_input,subs(y,t,time_input));
title('Alpha vs time from alpha-dot');
xlabel('Time (seconds)');
ylabel('Angle Alpha (radians)');

%% alpha from alpha ddot equation is z
z = dsolve(diff(z,t,2) == (-v_com*v_com*cos(phi+z))/(l_eff*l_eff*(sin(phi+z))^3));
time_input = linspace(0,100,1000);

% Subsitutte the values for the variables
z = subs(z,[v_com,phi,l_eff],[10,pi/6,15])
%% To plot the required z vs time
% Plot only after substituting values
figure;
plot(time_input,subs(z,t,time_input));
title('Alpha vs time from alpha-ddot');
xlabel('Time (seconds)');
ylabel('Angle Alpha (radians)');

