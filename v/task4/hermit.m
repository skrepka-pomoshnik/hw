INPUT = [0,5,-7,10;1,-4,-13,NaN;2,-61,-127,NaN;3,-862,NaN,NaN]
%INPUT = [-1,-17,33,NaN;0,-4,3,-8;2,10,NaN,NaN]
%NaN is a missing value
MULT = zeros(1,size(INPUT,1))
X = []
Y = []

for i=1:size(INPUT,1)
    m = -1
    for j=1:size(INPUT,2)
        if !isnan(INPUT(i,j)) 
            m++
        endif
    endfor
    MULT(i) = m
endfor

%todo: rewrite this using octave indexing
for i=1:size(INPUT,1)
    for j=1:MULT(i)
        X = [X;INPUT(i,1)]
        Y = [Y;INPUT(i,2)]
    endfor
endfor

N = sum(MULT)
D = zeros(N,N-1)
D = [X Y D]

for i=1:N+1
    for j=1:N-i
        if D(j+i,1)!=D(j,1) %if not multiple
            D(j,i+2) = (D(j+1,i+1)-D(j,i+1))/(D(j+i,1)-D(j,1))
        else
            D(j,i+2) = INPUT(find(INPUT(:,1)==D(j,1)),i+2)/factorial(i)
        endif
    endfor
endfor

function p = interhermite(x,D)
    p = D(1,2)
    for i=3:size(D,2)
            pn = 1
        for j=1:i-2
            pn=pn*(x-D(j,1))
        endfor
        p+=D(1,i)*pn
    endfor
end

%check
Y2 = zeros(1,size(INPUT,1))
for i=1:size(INPUT,1)
    Y2(i)=interhermite(INPUT(i,1),D)
endfor
