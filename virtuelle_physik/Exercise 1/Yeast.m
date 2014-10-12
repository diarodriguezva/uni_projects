%% yeast
V = 1;
s0 = 2;
p0 = 1e-6;

Cf = 50;
R = 10;
S = 15;
Tref = 300;

h = 0.01;
n = 1;

p(n) = p0;
s(n) = s0;

t = 0;

T = 310;

while t<=10
    p(n+1) = p(n)+p(n)*((R+2*S)*s(n)-2*S*s0)*h;
    s(n+1) = s(n)-(s(n)*p(n)*Cf*(T/Tref)/V)*h;
    t = t+h;
    n = n+1;
end

a = (s0 - s);

plot(a,'r')
hold on
grid on
plot(s)

figure
grid on
plot(p)