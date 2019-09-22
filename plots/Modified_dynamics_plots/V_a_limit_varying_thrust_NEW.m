clc;
clear all;

%%Bot Parameters

AB = 0.265;
AD = 0.110;
BC = 0.170;
BE = 0.080;

M_bot = 1.75;
M_link = 0.22;

theta = 0.78; %%45 degrees initially
J_axis = M_bot*((AB)^2)/3 + M_link*((AB)^2 + ((BC)^2)/3 + (AB)*(BC)*cos(theta));
T = 8;%%0 Thrust Initially

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

zoomed_axes_x = zeros(4,200);
zoomed_axes_y = zeros(45,200);
labels_x = zeros(1,4);
labels_y = zeros(1,4);

for j = 1:1:4
    
while(alpha(i) < (0.98*beta))
    
alpha_dot = v_A * sin(beta)*cos(alpha(i))/(AC*cos(beta - alpha(i)));
alpha_dot_dot = - (alpha_dot)^2 * sin (beta) * (sec(alpha(i)))^2/(cos(beta) + sin(beta)*tan(alpha(i))) ;

G = (M_bot*g*AD*cos(alpha(i) + phi) + M_link*g*AE*cos(del + alpha(i)) + T*AD );

F(i) = (G * ((cos(beta - alpha(i)))^3) * (AC)^2 /(((sin(beta))^3 )* cos(alpha(i)) * J_axis))^0.5;
%F(i) = (((cos(beta - alpha(i)))^2)*(AC^2)*(M_bot*g*AD*cos(alpha(i) + phi) + M_link*g*AE*cos(del + alpha(i)) + T*AD )/((sin (beta))^2 * J_axis * tan(beta -alpha(i))))^0.5;

alpha(i+1) =  0.0001 + alpha(i);
delta(i+1) = alpha(i+1)*57.3;
i = i+1 ;
end

F(i) = F(i-1);
T= T + 8 ; %%Each plot increases thrust by 5 Newtons
AC = (AB^2 + BC^2 - 2*(AB)*(BC)*cos(3.14 - theta))^0.5;
AE = (AB^2 + BE^2 - 2*(AB)*(BE)*cos(3.14 - theta))^0.5;
J_axis = M_bot*((AB)^2)/3 + M_link*((AB)^2 + ((BC)^2)/3 + (AB)*(BC)*cos(theta));

alpha(1) = 0;
delta(1) = 0;

i=1;

plot(delta,F,'LineWidth',1);
title('(V_A)_{max}');
xlabel('$Delta$ ($^{\circ}$)','Interpreter','Latex');
ylabel('V_{limit} (m/s)');

zoomed_axes_x(j,:) = delta(1:200);
zoomed_axes_y(j,:) = F(1:200);

grid on;
hold on
end

legend('8','16','24','32','Location','SouthEast');
[hleg,att] = legend('show');
% set(hleg,'position',[0.19 0.70 0.02 0.1])
title(hleg,'$T$ $(N)$','Interpreter','latex');
axis tight;

% yticks([0 1.09 1.21 1.31 1.41 1.5 2 2.5 3 3.5 4 4.5 5 5.5]);

zoomed_axes = axes('Position',[0.20 0.62 0.2 .25]); 
hold on
ylim([-1 5]);

for i = 1 : 4
    plot(zoomed_axes_x(i,:),zoomed_axes_y(i,:));
    labels_x(i) = zoomed_axes_x(i,1);
    labels_y(i) = zoomed_axes_y(i,1);
%     yline(zoomed_axes_y(i,1),'--');
%     text(zoomed_axes_x(i,1) + 10 * i,zoomed_axes_y(i,1) + 0.03,string(zoomed_axes_y(i,1)));
end

% yticks([0 1.09 1.21 1.31 1.41 1.5 2 2.5 3 3.5 4 4.5 5 5.5]);
text(labels_x + 0.07,labels_y + 0.04,string(labels_y));

axis tight;
