F = @(t) 1/(t^2+13)
A = 0
B = 1
STEPS = 1
EXACT = atan(B/sqrt(13))/sqrt(13) - atan(A/sqrt(13))/sqrt(13)

%left rectangle
function integral = left(f, a, b, n)
    h = (b-a)/n;
    result = 0
    for i = 0:(n-1)
        result = result + f((a) + i*h);
    end
    integral = h*result;
end

%right rectangle
function integral = right(f, a, b, n)
    h = (b-a)/n;
    result = 0
    for i = 0:(n-1)
        result = result + f((b) - i*h);
    end
    integral = h*result;
end

%trapezodial method
function integral = trapezoidal(f, a, b, n)
    h = (b-a)/n;
    result = 0.5*f(a) + 0.5*f(b);
    for i = 1:(n-1)
        result = result + f(a + i*h);
    end
    integral = h*result;
end

%midpoint triangles
function integral = midpoint(f, a, b, n)
    h = (b-a)/n;
    result = 0;
    for i = 0:(n-1)
        result = result + f((a + h/2) + i*h);
    end
    integral = h*result;
end

%parabolic method
function integral = simpson(f, a, b, n)
    h = (b-a)/(2*n);
    result = f(a)+f(b);
    for i = 1:(2*n-1)
        if mod(i,2) == 0
            result = result + 2*f(a + i*h);
            else
                result = result + 4*f(a + i*h);
            endif
        end
        integral = result*h/3;
end

%compute everything
left(F,A,B,STEPS)
trapezoidal(F,A,B,STEPS)
simpson(F,A,B,STEPS)
EXACT-left(F,A,B,STEPS)
EXACT-trapezoidal(F,A,B,STEPS)
EXACT-simpson(F,A,B,STEPS)

%trapezoidal(F,0,1,3)
%EXACT-trapezoidal(F,0,1,3)
%simpson(F,0,1,3)
%EXACT-simpson(F,0,1,10)
