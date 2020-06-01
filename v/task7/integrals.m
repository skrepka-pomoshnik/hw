F = @(t) sqrt(t)*cos(t)
F_p = @(t) cos(t)
A = 0
B = 1
EXACT = quad(F,A,B)

%simpson method
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

%gauss for 2,3,4,5 nodes, precomputed
function integral = gauss2(f, a, b, n)
%to do: compute legende roots on the fly
G2 = [-sqrt(1/3),sqrt(1/3)]
G3 = [-sqrt(3/5),0,sqrt(3/5)]
WG3 = [5/9,8/9,5/9]
G4 = [-sqrt(3/7 + sqrt(6/5)*2/7),-sqrt(3/7 - sqrt(6/5)*2/7),sqrt(3/7 - sqrt(6/5)*2/7),sqrt(3/7 + sqrt(6/5)*2/7)]
WG4 = [(18-sqrt(30))/36,(18+sqrt(30))/36,(18+sqrt(30))/36,(18-sqrt(30))/36]
G5 = [-sqrt(5+2*sqrt(10/7))/3,-sqrt(5-2*sqrt(10/7))/3,0,sqrt(5-2*sqrt(10/7))/3,sqrt(5+2*sqrt(10/7))/3]
WG5 = [(322-13*sqrt(70))/900,(322+13*sqrt(70))/900,128/225,(322+13*sqrt(70))/900,(322-13*sqrt(70))/900]
    I1 = 0.5*b - 0.5*a
    I2 = 0.5*b + 0.5*a
    g = @(t) f(I1*t+I2)
    switch (n)
        case 2
            integral = I1*(g(G2(1))+g(G2(2)));
        case 3
            integral = 0
            for i=1:n
                integral+=WG3(i)*g(G3(i))
            endfor
                integral = integral * I1
        case 4
            integral = 0
            for i=1:n
                integral+=WG4(i)*g(G4(i))
            endfor
                integral = integral * I1
        case 5
            integral = 0
            for i=1:n
                integral+=WG5(i)*g(G5(i))
            endfor
                integral = integral * I1
            otherwise
                integral = -666;
    endswitch
end


%pre computed newtonkotess
function integral = newtonkot(f, a, b, n)
    Bi = [1/2,1/3,3/8,2/45,5/288]
    Ai = [1,1,0,0,0,0;1,4,1,0,0,0;1,3,3,1,0,0;7,32,12,32,7,0;19,75,50,50,75,19]
    h = (b-a)/n
    integral = 0
    for i=1:(n+1)
        integral+=f(a+h*(i-1))*Ai(n,i)
    endfor
        integral = h*Bi(n)*integral
end


% integrating with weight = sqrt
function integral = weightintegral(fp,a,b)
X = [0;0.5;1]
wk = @(xk) 1/(3*xk^2 -3*xk+0.5)
A1 = wk(X(1))*quad(@(x) sqrt(x)*(x-0.5)*(x-1),a,b) 
A2 = wk(X(2))*quad(@(x)sqrt(x)*(x)*(x-1),a,b) 
A3 = wk(X(3))*quad(@(x)sqrt(x)*(x-0.5)*(x),a,b) 
integral = fp(X(1))*A1+fp(X(2))*A2+fp(X(3))*A3
end

%gaussian formula for 1,t,t^2,t3: derivation and evaluation
function integral = tipagauss(fp,a,b) 
p0 = @(t) sqrt(t)
p1 = @(t) sqrt(t)*t
p2 = @(t) sqrt(t)*t^2
p3 = @(t) sqrt(t)*t^3
m0 = quad(p0,a,b)
m1 = quad(p1,a,b)
m2 = quad(p2,a,b)
m3 = quad(p3,a,b)
a1 = (m0*m3-m2*m1)/(m1^2-m0*m2)
a2 = (m2^2-m3*m1)/(m1^2-m0*m2)
X = roots([1,a1,a2])
A1 = (m1-X(2)*m0)/(X(1)-X(2))
A2 = (m1-X(1)*m0)/(X(2)-X(1))
integral = fp(X(1))*A1+fp(X(2))*A2
end

%print the table
fprintf("%d/0\n%d/%d\n%d/%d\n%d/%d\n%d/%d\n"
,EXACT
,simpson(F,A,B,3)
,simpson(F,A,B,3)-EXACT
,weightintegral(F_p,A,B)
,weightintegral(F_p,A,B)-EXACT
,gauss2(F,A,B,2)
,gauss2(F,A,B,2)-EXACT
,tipagauss(F_p,A,B)
,tipagauss(F_p,A,B)-EXACT)
