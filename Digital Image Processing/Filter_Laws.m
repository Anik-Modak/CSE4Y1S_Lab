%Geometric Mean Filter

f(x,y) = g(s,t)^1/mn

%Hermonic Mean Filter

f(x,y) = mn/(1/g(s,t))

%Ideal Low-pass filter

H(u,v) = { 1 if D(u,v) <= D0
           0 otherwise}
           

%ButterWorth Low-pass filter

H(u,v) = 1/(1+(D(u,v)/D0)^2n)


%Gaussain Low-pass filter

H(u,v) = e^(-D(u,v)^2/(2D0^2))


%Ideal High-pass filter

H(u,v) = { 0 if D(u,v) <= D0
           1 otherwise}
           

%ButterWorth High-pass filter

H(u,v) = 1/(1+(D0/D(u,v))^2n)


%Gaussain High-pass filter

H(u,v) = 1 - e^(-D(u,v)^2/(2D0^2))

%Where D0 is cutoff frequency

