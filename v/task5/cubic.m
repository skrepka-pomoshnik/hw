A = -10
B = 10
H = 2
F = @(t) 1/(t^2+1) %runge function
X = (A:H:B)'
Y = arrayfun(F,X)

function [a,b,c,d] = scubic(x,y)
    n = length(x);
    h = zeros(n-1,1);
    for j = 1:n-1
        h(j) = x(j+1) - x(j);
    end

    H = zeros(n);
    H(1,1)= 1;
    H(n,n) = 1;

    for i = 2:n-1
        H(i,i-1) = h(i-1);
        H(i,i) = 2*(h(i-1)+h(i));
        H(i,i+1) = h(i);
    end

    B = zeros(n,1);

    for i = 2:n-1
        B(i) = (3/h(i))*(y(i+1)-y(i)) - (3/h(i-1))*(y(i)-y(i-1));
    end

    b = H\B;

    c = zeros(n-1,1);
    for i = 1:n-1
        c(i) = (1/h(i))*(y(i+1)-y(i)) - (1/3*h(i))*(2*b(i)+b(i+1));
    end

    a = zeros(n-1,1);
    for i = 1:n-1
        a(i) = (1/(3*h(i))) * (b(i+1)-b(i));
    end
    d = y

end

%plotting all at one graph
[a,b,c,d] = scubic(X,Y)
grid on
hold on
for i = 1:length(X)-1
    Fs = @(x) d(i) + c(i).*(x-X(i)) + b(i).*(x-X(i)).^2 + a(i).*(x-X(i)).^3
    Xs = linspace(X(i),X(i+1))
    plot(Xs,Fs(Xs))
end
