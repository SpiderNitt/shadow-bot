function init_t_array = init_time_stamps(x)

init_t_array = zeros(1,8);
k = 2;
while(k <= 8)
            z = 1;
            while(z<k)
               init_t_array(k) = init_t_array(k) + x(z); %Initialising time stamps
               z = z + 1;
            end
            k = k +1;
end

end