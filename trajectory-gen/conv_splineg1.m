function a_v = splineg1(init_array,y_1)

%init_array = zeros(1,8);
%y_1 = [0 2 4 6 8 10 12 14]; %1D Waypoints to be traversed through. 
yy_1 = spline(init_array,[0,y_1,0]); %Generates the spline

[breaks,coef,L,order,dim] = unmkpp(yy_1);

k = 1;
for it = 2:1:8
   for d = 0:0.01:round(init_array(it)-init_array(it-1))
       v_t(k) = abs(3*coef(it-1)*d^2 + 2*coef(it+6)*d + coef(it+13));
       a_t(k) = abs(6*coef(it-1)*d + 2*coef(it+6)); 
       j_t(k) = abs(6*coef(it-1));
       k = k + 1;
   end
end
A_max = max(a_t);
V_max = max(v_t);

a_v.A = A_max;
a_v.V = V_max;

disp(A_max);
disp(V_max);
end