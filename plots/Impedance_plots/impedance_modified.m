% plot(oneT, oneP); grid on; hold on;
% plot(sixT, sixP); grid on; hold on;
% plot(sevenT, sevenP); grid on;hold on;
% plot(eightT, eightP); grid on; hold off;

plot(eightT, eightP); grid on; hold on;
plot(sevenT, sevenP); grid on;hold on;
plot(sixT, sixP); grid on; hold on;
plot(oneT, oneP); grid on; hold off;

title('Modified Dynamics');
xlabel('Time (s)');
ylabel('Angular Position (rad)');
xlim([0 0.6]);

% legend('0','5','10','15','20','Location','NorthWest');
legend('0.70,0.60','0.75,0.65','0.85,0.75','0.90,0.80','Location','NorthEast');
[hleg,att] = legend('show');
title(hleg,'K_d ,  B_d');

%Legend:
%Kd= 0.90; Bd= 0.80; (%for one)
%Kd= 0.85; Bd= 0.75; (%for six)
%Kd= 0.75; Bd= 0.65; (%for seven)
%Kd= 0.70; Bd= 0.60; (%for eight)