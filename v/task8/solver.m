%x' = cos(1.75 t + x) + 1.25 (t − x), x(0) = 0.
dx = @(x,t) cos(1.75*t+x)+1.25*(t-x)
A = 0
B = 1
H = 0.1
N = (B-A)/h

%bare euler
function [sol, time] = euler1(f, y_0, h, T)
    N_t = floor(T/h);
    u = zeros(N_t+1, 1);
    t = linspace(0, N_t*h, length(u));
    u(1) = y_0;
        for n = 1:N_t
        u(n+1) = u(n) + h*f(u(n), t(n));
        end
    sol = u;
    time = t;
end

%euler-cauchey
function [sol, time] = euler2(f, y_0, h, T)
    N_t = floor(T/h);
    u = zeros(N_t+1, 1);
    u1 = u;
    t = linspace(0, N_t*h, length(u));
    u(1) = y_0;
        for n = 1:N_t
        u1(n+1) = u(n) + h*f(u(n), t(n));
        u(n+1) = u(n) + (h/2)*(f(u(n), t(n))+f(u1(n+1), t(n+1)));
        end
    sol = u;
    time = t;
end

%enhanced euler
function [sol, time] = euler3(f, y_0, h, T)
    N_t = floor(T/h);
    u = zeros(N_t+1, 1);
    u1 = zeros(N_t+1, 1);
    t = linspace(0, N_t*h, length(u));
    t1 = t+(h/2)
    u(1) = y_0;
        for n = 1:N_t
            u1(n+1) = u(n) + (h/2)*f(u(n), t(n));
            u(n+1) = u(n) + (h)*(f(u1(n+1), t(n+1)));
        end
    sol = u;
    time = t;
end

%runge-kutte of order 4
function [sol, time] = ruk4(f, y_0, h, T)
end

%solve equations 
y_math = lsode(dx,0,(0:H:1))
y_h = euler1(dx,0,H,0.5)
y_h2 = euler1(dx,0,H/2,0.5)
y_rev = euler3(dx,0,H,0.5)

%print the table to compare
for i=1:6
    fprintf("%f|%f|%f|%f|%f\n",y_math(i),y_h(i),y_h2(2*i-1),y_rev(i),y_rev(i)-y_math(i))
endfor
