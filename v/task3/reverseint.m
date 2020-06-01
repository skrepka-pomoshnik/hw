%input
F = @(x) e^x
F_1 = @(x) log(x)
X = [-0.3,-0.2,-0.1,0,0.1,0.3]
Y = arrayfun(F,X)
x_i = 0.2
y_i = 0.8
EPS = 10^(-7)
x_e = F_1(0.8)


%lagrange interpolation
function f = lagrangepoly(xi, yi)
%too good to not to be stolen
  n = length(xi);
  f = zeros(1, n);
  Ilog = logical(eye(n));
  for i = 1:n
    Pi = poly(xi(~Ilog(i,:)));
    Pi = Pi ./ polyval(Pi, xi(Ilog(i,:)));
    Pi = Pi .* yi(Ilog(i,:));
    f = f + Pi;
  endfor
end

%secant method for solving f(x)=0
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

%find interpolation for f
Pf = lagrangepoly(X,Y)

%poly = y
G = @(x) polyval(Pf,x)-y_i

x0 = -1; x1 = 0;
x_iter = secant(G, x0, x1, eps);

%find interpolation for f-1
Pf_1 = lagrangepoly(Y,X)
x_m = polyval(Pf_1,y_i)
