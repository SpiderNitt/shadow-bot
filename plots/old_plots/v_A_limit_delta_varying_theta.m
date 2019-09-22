clc;
clear all;

%%Bot Parameters

AB = 0.265;
AD = 0.110;
BC = 0.170;
BE = 0.080;

M_bot = 1.75;
M_link = 0.22;

theta = 1.57; %%90 degrees initially
J_axis = M_bot*((AB)^2)/3 + M_link*((AB)^2 + ((BC)^2)/3 + (AB)*(BC)*cos(theta));
T = 0;

AC = (AB^2 + BC^2 - 2*(AB)*(BC)*cos(3.14 - theta))^0.5;
AE = (AB^2 + BE^2 - 2*(AB)*(BE)*cos(3.14 - theta))^0.5;

phi = asin(BC*sin(theta)/AC);
del = phi - asin(BE*sin(theta)/AE);

v_A = 0.15; %m/s

%%Slope Parameter

g = 9.8;
beta = 1.046; %%60 degrees
mu_fr = 0.35;

del_t = 0.0005;

i = 1;
alpha(1)= 0;

zoomed_axes_x = zeros(6,200);
zoomed_axes_y = zeros(6,200);
labels_x = zeros(1,6);
labels_y = zeros(1,6);

for j = 1:1:6
    
while(alpha(i) < (0.98*beta))
    
alpha_dot = v_A * sin(beta)/(AC*cos(beta - alpha(i)));
alpha_dot_dot = - (alpha_dot)^2 * tan(beta - alpha(i));

F(i) = (((cos(beta - alpha(i)))^2)*(AC^2)*(M_bot*g*AD*cos(alpha(i) + phi) + M_link*g*AE*cos(del + alpha(i)) + T*AD )/((sin (beta))^2 * J_axis * tan(beta -alpha(i))))^0.5;

alpha(i+1) =  0.0001 + alpha(i);
delta(i+1) = alpha(i+1)*57.3;
i = i+1 ;
end

F(i) = F(i-1);
theta = theta - 0.2616 ; %%Each plot decreases theta by 15 degrees for each plot
AC = (AB^2 + BC^2 - 2*(AB)*(BC)*cos(3.14 - theta))^0.5;
AE = (AB^2 + BE^2 - 2*(AB)*(BE)*cos(3.14 - theta))^0.5;
J_axis = M_bot*((AB)^2)/3 + M_link*((AB)^2 + ((BC)^2)/3 + (AB)*(BC)*cos(theta));

alpha(1) = 0;
delta(1) = 0;

i=1;

title('V_A limit');
plot(delta,F,'LineWidth',1);
xlabel('$Delta$ ($^{\circ}$)','Interpreter','Latex');
ylabel('V_{limit}  (m/s)');

zoomed_axes_x(j,:) = delta(1:200);
zoomed_axes_y(j,:) = F(1:200);

grid on;
hold on
end

legend('90','75','60','45','30','15','Location','NorthWest');
[hleg,att] = legend('show');
title(hleg,'$\theta ^{\circ}$','Interpreter','latex');

zoomed_axes = axes('Position',[0.48 0.6 0.25 .3]); 
hold on

for i = 1 : 5
    plot(zoomed_axes_x(i,:),zoomed_axes_y(i,:));
    labels_x(i) = zoomed_axes_x(i,1);
    labels_y(i) = zoomed_axes_y(i,1);
end

text(labels_x,labels_y + 0.03,string(labels_y));
axis tight;


