function z = Sphere(x,params,A,V)
    
    %Cost Function Definition.This has to be minimized
    if(A < params.A_max && V < params.V_max) %Condition for solution feasibility
    z = sum(x);
    
    else %If the solution is not feasible
    z = inf;
    end

end
