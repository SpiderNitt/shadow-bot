function out = PSO(problem, params ,y)

    %% Problem Definiton

    CostFunction = problem.CostFunction;  % Cost Function

    nVar = problem.nVar;        % Number of Unknown (Decision) Variables

    VarSize = [1 nVar];         % Matrix Size of Decision Variables

    VarMin = problem.VarMin;	% Lower Bound of Decision Variables
    VarMax = problem.VarMax;    % Upper Bound of Decision Variables


    %% Parameters of PSO

    MaxIt = params.MaxIt;   % Maximum Number of Iterations

    nPop = params.nPop;     % Population Size (Swarm Size)

    w = params.w;           % Intertia Coefficient
    wdamp = params.wdamp;   % Damping Ratio of Inertia Coefficient
    c1 = params.c1;         % Personal Acceleration Coefficient
    c2 = params.c2;         % Social Acceleration Coefficient
    A_max = params.A_max;   % Maximum Velocity
    V_max = params.V_max;   % Maxium Acceleration

    % The Flag for Showing Iteration Information
    ShowIterInfo = params.ShowIterInfo;    

    MaxVelocity = 0.1*(VarMax-VarMin);
    MinVelocity = -MaxVelocity;
    
    %% Initialization

    % The Particle Template
    empty_particle.Position = [];
    empty_particle.Velocity = [];
    empty_particle.Cost = [];
    empty_particle.Best.Position = [];
    empty_particle.Best.Cost = [];

    % Create Population Array
    particle = repmat(empty_particle, nPop, 1);
    
    % Initialize Global Best
    GlobalBest.Cost = inf;
    
    % Initialize Population Members
    
    
    for i=1:1:nPop

        disp('Enter');
        % Generate Random Solution
        particle(i).Position = zeros(VarSize);
        
        particle(i).Position = unifrnd(VarMin, VarMax, VarSize);
        
        init_array_size = [1 (nVar+1)];
        init_array = zeros(init_array_size);
        
        init_array = init_time_stamps(particle(i).Position);
        
        %disp(init_array);
        
        acc_vel = conv_splineg1(init_array,y); %Returns the max. velocity and max. acceleration of the spline generated
        %disp(acc_vel);
        
        %Initialising the particle positions to feasible solution points
        while((acc_vel.A > params.A_max)||(acc_vel.V > params.V_max))
            particle(i).Position = unifrnd(VarMin, VarMax, VarSize);%Initialises time intervals between successive waypoints
            init_array = init_time_stamps(particle(i).Position);%Initialises Linear Time stamps
            acc_vel = conv_splineg1(init_array,y); %Returns the max. velocity and max. acceleration of the spline generated
        end
            
            
        % Initialize Velocity
        particle(i).Velocity = zeros(VarSize);

        % Evaluation
        particle(i).Cost = CostFunction(particle(i).Position,params,acc_vel.A,acc_vel.V);

        % Update the Personal Best
        particle(i).Best.Position = particle(i).Position;
        particle(i).Best.Cost = particle(i).Cost;

        % Update Global Best
        if (particle(i).Best.Cost < GlobalBest.Cost)
            GlobalBest = particle(i).Best;
        end

        disp('Done Initialising');
    end

    % Array to Hold Best Cost Value on Each Iteration
    BestCosts = zeros(MaxIt, 1);
    %% Main Loop of PSO

    for it=1:MaxIt
    
        for i=1:nPop
            
            % Update Velocity
            particle(i).Velocity = w*particle(i).Velocity ...
                + c1*rand(VarSize).*(particle(i).Best.Position - particle(i).Position) ...
                + c2*rand(VarSize).*(GlobalBest.Position - particle(i).Position);

            % Apply Velocity Limits
            particle(i).Velocity = max(particle(i).Velocity, MinVelocity);
            particle(i).Velocity = min(particle(i).Velocity, MaxVelocity);
            
            % Update Position
            particle(i).Position = particle(i).Position + particle(i).Velocity;
            
            % Apply Lower and Upper Bound Limits
            particle(i).Position = max(particle(i).Position, VarMin);
            particle(i).Position = min(particle(i).Position, VarMax);
            
            init_array = init_time_stamps(particle(i).Position); %Update Time Stamps
        
            acc_vel = conv_splineg1(init_array,y); %Finding max acceleration and velocity for this spline

            % Evaluation
            disp('Eval');
            particle(i).Cost = CostFunction(particle(i).Position,params,acc_vel.A,acc_vel.V);
            disp(particle(i).Cost);
            % Update Personal Best
            if particle(i).Cost < particle(i).Best.Cost

                particle(i).Best.Position = particle(i).Position;
                particle(i).Best.Cost = particle(i).Cost;

                % Update Global Best
                if particle(i).Best.Cost < GlobalBest.Cost
                    GlobalBest = particle(i).Best;
                end            
            end
            
           

        end

        % Store the Best Cost Value
        BestCosts(it) = GlobalBest.Cost;

        % Display Iteration Information
        if ShowIterInfo
            disp(['Iteration ' num2str(it) ': Best Cost = ' num2str(BestCosts(it))]);
        end

        % Damping Inertia Coefficient
        w = w * wdamp;

    end
    
    out.pop = particle;
    out.BestSol = GlobalBest;
    out.BestCosts = BestCosts;
    
end