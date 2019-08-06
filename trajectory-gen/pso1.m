clc;
clear;
close all;

%% Problem Definiton

%%In this problem we try to generate trajectories based on cubic
%%splines.The cubic splines require a set of waypoints and a set of time
%%stamps during which they have to be traversed through.The waypoints are
%%generated from path planning algorithms and the time stamps are to
%%determined based on the physical limitations of acceleration and
%%velocities of our bot.This trajectory generation aims to generate a set
%%of optimal time intervals which helps us to construct the required cubic
%%spline.Since the optimization problem here is highly convex and non
%%linear in case of cubic splines,we employ a method called particle swarm optimization to help us
%%achieve our objective.

problem.CostFunction = @(x,params,A,V) Sphere(x,params,A,V);  % Cost Function
problem.nVar = 7;       % Number of Unknown (Decision) Variables
problem.VarMin =  0.1;  % Lower Bound of Decision Variables
problem.VarMax =  2;   % Upper Bound of Decision Variables

%% Parameters of Particle Swarm Optimizer

params.MaxIt = 150;        % Maximum Number of Iterations
params.nPop = 50;           % Population Size (Swarm Size)
params.w = 1;               % Intertia Coefficient
params.wdamp = 0.99;        % Damping Ratio of Inertia Coefficient
params.c1 = 2;              % Personal Acceleration Coefficient
params.c2 = 2;              % Social Acceleration Coefficient
params.ShowIterInfo = true; % Flag for Showing Iteration Informatin

%%Spline characteristic conditions

params.A_max = 20;        %Set Max. allowed acceleration
params.V_max = 10;        %Set Max. allowed velocity

%% Calling Particle Swarm Optimizer

y = [0 2 5 4 8 10 9 14]; %1D Waypoints to be traversed through. 
x = [0 2 4 6 8 10 12 14]; %1D Waypoints to be traversed through.

out_y = PSO(problem, params,y);
BestSol_y = out_y.BestSol.Position %Best Solution of time intervals needed

out_x = PSO(problem, params,x);
BestSol_x = out_x.BestSol.Position %Best Solution of time intervals needed

t_stamps_x = init_time_stamps(BestSol_x);
t_stamps_y = init_time_stamps(BestSol_y);

for i=1:1:7
    BestSol(i) = max(BestSol_x(i),BestSol_y(i));
end

t_stamps = init_time_stamps(BestSol);

tt = 0:0.2:abs(t_stamps(8)+1);

spline_final_trajectory_y = spline(t_stamps,y,tt);
spline_final_trajectory_x = spline(t_stamps,x,tt);

%% Results
plot3(t_stamps,y,x,'o',tt,spline_final_trajectory_y,spline_final_trajectory_x);
grid on;
xlabel('Time');
Ylabel('X');
Zlabel('Y');


