%input: k lambda b1 bn
F = @(x) sin(x)
k = 3 %order of diff
lambda = 0 %1 = first node

function res = differ(f,d,bn,l) %diff f d times in point h*l
    h = bn(2)-bn(1)
    v = bn-h*l
    n = length(v)
    b = zeros(n,1)
    b(d+1) = factorial(d)

    A = []
        for i=1:n
            temp = zeros(1,n)
                for j=1:n
                    temp(j) = v(j)^(i-1)
                endfor
            A = [A;temp]   
            endfor
    c = linsolve(A,b)
    res = dot(c,arrayfun(f,bn))
end

%calculate table
R = []
for n=1:5
 H = 10^(-n)
 Bn = [0:H:10*H]
 Fnumdiff=differ(F,k,Bn,lambda)
 Fdiff = -cos(lambda*H)
 R = [R; Fnumdiff,abs(Fnumdiff-Fdiff)]
endfor
