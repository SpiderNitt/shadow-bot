clc;
clear all;

%%Bot Parameters

AB = 0.265;
AD = 0.110;
BC = 0.170;
BE = 0.080;

M_bot = 1.75;
M_link = 0.22;

theta = 0.785; %%45 degrees
J_axis = M_bot*((AB)^2)/3 + M_link*((AB)^2 + ((BC)^2)/3 + (AB)*(BC)*cos(theta));
T = 0;

AC = (AB^2 + BC^2 - 2*(AB)*(BC)*cos(3.14 - theta))^0.5;
AE = (AB^2 + BE^2 - 2*(AB)*(BE)*cos(3.14 - theta))^0.5;

phi = asin(BC*sin(theta)/AC);
del = phi - asin(BE*sin(theta)/AE);

v_A = 0.1; %m/s Initial value

%%Slope Parameter

g = 9.8;
beta = 1.046; %%60 degrees
mu_fr = 0.35;

del_t = 0.0005;

i = 1;
alpha(1)= 0;
V(1) = 0;

zoomed_axes_x = zeros(5,200);
zoomed_axes_y = zeros(5,200);
labels_x = zeros(1,5);
labels_y = zeros(1,5);

for j = 1:1:5
    
while(alpha(i) < beta)
    
alpha_dot = v_A * sin(beta)*cos(alpha(i))/(AC*cos(beta - alpha(i)));
alpha_dot_dot = - (alpha_dot)^2 * sin (beta) * (sec(alpha(i)))^2/(cos(beta) + sin(beta)*tan(alpha(i))) ;

Nfr(i) = (M_bot*g*AD*cos(alpha(i) + phi) + M_link*g*AE*cos(del + alpha(i)) + T*AD + J_axis*alpha_dot_dot)/(AC*(cos(beta - alpha(i)) - mu_fr*sin(beta-alpha(i))));

alpha(i+1) = 0.0001 + alpha(i);
delta(i+1) = alpha(i+1)*57.3;
V(i+1) = V(i) + del_t;
i = i+1 ;

end
Nfr(i) = Nfr(i-1);
%v_A = v_A + 0.2; 
T = T + 5;%% Thrust varies by 5 Newton
alpha(1) = 0;
V(1) = 0;
i=1;
    
plot(delta,Nfr,'LineWidth',2.5);
title('Normal Force variation with $\delta$','Interpreter','Latex');
xlabel('Delta ($^{\circ}$)','Interpreter','Latex');
ylabel('Contact Force on the Front Link (N)');
zoomed_axes_y(j,:) = Nfr(1:200);
zoomed_axes_x(j,:) = delta(1:200);
grid on;
hold on
end

legend('0','5','10','15','20','Location','NorthEast');
[hleg,att] = legend('show');
title(hleg,'Thrust (N)');

labels_x = zeros(1,5);
labels_y = zeros(1,5);

axes('Position',[0.35 0.59 0.25 .3]); 
for i= 1:5
    plot(zoomed_axes_x(i,:),zoomed_axes_y(i,:));
    grid on;
    hold on;
    labels_y(i) = zoomed_axes_y(i,1);
    labels_x(i) = zoomed_axes_x(i,1);
end

text(labels_x + 0.1,labels_y,string(labels_y));

