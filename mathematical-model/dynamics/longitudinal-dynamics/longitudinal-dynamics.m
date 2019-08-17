% (ALL DIMENSIONS IN m)

b = 0.265; %body
a = 0.170; %arm

mBody = 10; %body
mArm = 5; %arm

% measure of radius
rearWheel = 0.110/2;
frontWheel = 0.075/2;

% "delta" is difference between the radius of front and rear wheels.
delta = rearWheel - frontWheel;

toRad = 180/pi;
g = 9.810; % g-constant

q1 = 0;
q2 = 0;

%input torque:
Tou = [0; 0];

q1d = 0;
q2d = 0;
qd = [q1d; q2d];

% By lagrangian formulation,
% Tou = Mqdd + C(qd, q) + G + J'.Fext

%___________A__o__q2___________
%_____________/_\______________
%_______(b)__/___\_(a)_________
%________q1_/_____\____________
%_________|/_______\_B_________
%-(0,0)O--o---------o--(x, y)--
%##############################

% Mass-matrix (M):
m11 = mBody*b^2 + mArm*(b^2 + 2*b*a*cos(q2)+a^2);
m12 = mArm*(b*a*cos(q2) + a^2);
m21 = mArm*(b*a*cos(q2) + a^2);
m22 = mArm*a^2;

M = [m11 m12; m21 m22]

% Coriolis matrix (C):
c11 = -mArm*b*a*sin(q2)*(2*q1d*q2d + q2d^2);
c21 = -mArm*b*a*q1d*q2d*sin(q2);

Cqdot = [c11; c21]
% G matrix:
g11 = -(mBody + mArm)*b*g*sin(q1) - mArm*g*a*sin(q1 + q2);
g21 = -mArm*g*a*sin(q1 + q2);

G = [g11; g21]

% Jacobian matrix (J);
j11 = -b*sin(q1) - a*sin(q1 + q2);
j12 = -a*sin(q1 + q2);
j21 = b*cos(q1) + a*cos(q1 + q2);
j22 = a*cos(q1 + q2);

J = [j11 j12; j21 j22]

% external force on the front wheel
Fext = [1; 1]; 

qdd = inv(M) * (Tou - J'*Fext - C - G)
