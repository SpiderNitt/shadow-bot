%% Link Properties of the System
front_link_length = 170;
rear_link_length = 265;
wheel_diameter = 75;

world_offset_x = 40;
world_offset_y = 0;

angle_rear_ground = 15 * pi/180; % initial degree to radian
angle_front_ground = asin(rear_link_length/front_link_length*sin(angle_rear_ground));

world_offset = [world_offset_x,world_offset_y,1]';
%% Calculation
t1 = homogenous_tansformation(rotation_matrix(angle_rear_ground),[world_offset_x,world_offset_y + wheel_diameter/2]);
t2 = homogenous_tansformation(rotation_matrix(-(angle_front_ground + angle_rear_ground + 5*pi/180)),[front_link_length,0]);
%% Positions of the links
rear_link_end_position = t1 * [rear_link_length,0,1]';  % Same as rear link start position
front_link_end_position = t1 * t2 *[front_link_length,0,1]';
%% Draw links
hold on;
dummy_theta = 0:pi/100:2*pi;

% Front wheel (movable)
front_wheel = plot(wheel_diameter/2 * cos(dummy_theta) + front_link_end_position(1),wheel_diameter/2 *sin(dummy_theta) + world_offset(2),'Color','r');

% Rear wheel
rear_wheel = plot(wheel_diameter/2 * cos(dummy_theta) + world_offset(1),wheel_diameter/2 *sin(dummy_theta) + world_offset(2) ,'Color','b');

% Front Link
front_link = plot([rear_link_end_position(1),front_link_end_position(1)],[rear_link_end_position(2),front_link_end_position(2)],'Color','y','LineWidth',2);

% Rear Link
rear_link = plot([world_offset(1),rear_link_end_position(1)],[world_offset(2),rear_link_end_position(2)],'Color','g','LineWidth',2);


% Ground
ground = plot([0,front_link_end_position(1) + 60],[-wheel_diameter/2,-wheel_diameter/2],'LineWidth',2,'Color','black');

legend('Front Wheel','Rear Wheel','Front Link','Rear Link','Ground');

hold off;

% %% Animate the suspension
% for i = angle_front_ground + 1 : 60
%     i = 30 * pi/180; % initial degree to radian
%     j = asin(front_link_length/rear_link_length*sin(i))
% 
%     world_offset = [world_offset_x,world_offset_y,1]';
%     t1 = homogenous_tansformation(rotation_matrix(angle_front_ground),[world_offset_x,world_offset_y + wheel_diameter/2]);
%     t2 = homogenous_tansformation(rotation_matrix(-(angle_front_ground + angle_rear_ground +9*pi/180)),[front_link_length,0]);
%     front_link_end_position = t1 * [front_link_length,0,1]';  % Same as rear link start position
%     rear_link_end_position = t1 * t2 *[rear_link_length,0,1]';
%     hold on;
%     dummy_theta = 0:pi/100:2*pi;
%     % Front wheel (movable)
%     front_link = plot(wheel_diameter/2 * cos(dummy_theta) + world_offset(1),wheel_diameter/2 *sin(dummy_theta) + world_offset(2),'Color','r');
% 
%     % Rear wheel
%     rear_wheel = plot(wheel_diameter/2 * cos(dummy_theta) + rear_link_end_position(1),wheel_diameter/2 *sin(dummy_theta) + rear_link_end_position(2),'Color','b');
% 
%     % Front Link
%     front_link = plot([world_offset(1),front_link_end_position(1)],[world_offset(2),front_link_end_position(2)],'Color','y','LineWidth',2);
% 
%     % Rear Link
%     rear_link = plot([front_link_end_position(1),rear_link_end_position(1)],[front_link_end_position(2),rear_link_end_position(2)],'Color','g','LineWidth',2);
% 
%     hold off;
%     pause(0.1);
% end

%% Roation Matrix function
function y = rotation_matrix(angle)
    y = [cos(angle) -sin(angle);sin(angle) cos(angle)];
end

%% Homogenous transformation
function y = homogenous_tansformation(rot_matrix,translation_vector)
    y = [rot_matrix,translation_vector';0 0 1];
end
