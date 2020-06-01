%secant method handle
function runsecant()
    f = @(x) x^2 - 20*sin(x);
    eps = 1e-9;
    x0 = 5; x1 = x0 - 1;
    [solution,err] = secant(f, x0, x1, eps);
    if err > 0   % Solution found
        fprintf('Iterations: %d\n', 2 + err);
        fprintf('Solution: %f\n', solution)
    else
        fprintf('Fail.\n')
    end
end

%secand method
function [solution,err] = secant(f, x0, x1, eps)
    f_x0 = f(x0);
    f_x1 = f(x1);
    it = 0;
    while abs(f_x1) > eps && it < 100
            denominator = (f_x1 - f_x0)/(x1 - x0);
            x = x1 - (f_x1)/denominator;
        x0 = x1;
        x1 = x;
        f_x0 = f_x1;
        f_x1 = f(x1);
        it = it + 1;
    end
    if abs(f_x1) > eps
        it = -1;
    end
    solution = x1;
    err = it;
end


%iteration method handle
function runiterations()
    f = @(x) x^2 - 20*sin(x);
    eps = 1e-9;
    x0 = 5;
    lambda = 25
    [solution,err] = iterate(f, x0, eps, lambda);
        fprintf('Iterations: %d\n', 1 + err);
        fprintf('Solution: %f\n', solution);
end

%iteration method, WARNING: is unstable 
function [solution,err] = iterate(f, x0, eps, lambda)
    phi = @(x) x - f(x)/lambda;
    it = 0;
    while abs(f(x0)) > eps && it < 100
        it=it+1
        x0 = phi(x0)
    end
        solution = x0;
        err = it;
end
