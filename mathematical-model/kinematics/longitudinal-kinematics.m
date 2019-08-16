% Forward Kinematics:

% (ALL DIMENSIONS IN mm)

body = 265;
arm = 170;

% measure of radius
rearWheel = 110/2;
frontWheel = 75/2;

toRad = 180/pi;
theta = 0.01;
alpha = 0;

% "delta" is difference between the radius of front and rear wheels.
delta = rearWheel - frontWheel;


% assuming origin as rear-wheel-contact

%___________A__o__THETA________
%_____________/_\______________
%____(body)__/___\_(arm)_______
%___________/_____\____________
%__________/)ALPHA_\_B_________
%-(0,0)O--o---------o--(x, 0)--
%##############################

for theta=0:pi/20:0.65*pi
    % body * sin(alpha) = arm * sin(theta - alpha)
    c = arm^2 + body^2 - 2*arm*body*cos(pi - theta);
    x = sqrt(c - delta^2);
    alpha = atan(sin(theta)/((body/arm) + cos(theta))) - atan(delta/x);

    % cosine rule
    Ax = body*cos(alpha);
    Ay = rearWheel + body*sin(alpha);

    % plotter:
    %for .GIF
    %thisFigure = figure;
    %thisAxes = axes('Parent',thisFigure)
    
    % front wheel
    circle(x, frontWheel, frontWheel, 'k');

    % arms
    plot([-100, 500],[0, 0], 'k-', 'LineWidth',1); hold on;
    plot([0, Ax],[rearWheel, Ay], 'bo-', 'LineWidth',20); hold on;
    plot([Ax, x],[Ay, frontWheel], 'ro-', 'LineWidth',10); hold on;

    % rear wheel
    circle(0, rearWheel, rearWheel, 'k');
    hold off;
    axis equal;
    
    % for .GIF
    %fname = sprintf('filename(%d).png', theta);
    %saveas(thisFigure,fname)
    
    pause(0.1)
end

function circles = circle(x, y, radius, color)
    angle = 0:pi/50:2*pi;
    X = radius * cos(angle) + x;
    Y = radius * sin(angle) + y;
    circles = plot(X, Y);
    fill(X, Y, color);
    hold on
end
