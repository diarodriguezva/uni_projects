#!/usr/bin/env python3


#Setting the parameters
V = 1  #volume of fermentation vessel
s0 = 0.2 #inital concentration of sugar 
p0 = 1e-6 #initial population of yeast [m3]

C_f = 50 #feeding Coefficient [1/day]
R = 10 #reproductivity [1/day]
S = 15 #sensitivity w.r.t. alcohol [1/day]
T_ref = 300 #reference temperature [K]

h = 0.01 #time-step of forward Euler integration


#Setting the initial values
p = p0
s = s0
a = s0 - s;
time = 0


#Setting the input-value
T = 310


#perform time-integration
while time < 10:
    dp_dt = p*((R+S)*s - S*s0)
    ds_dt = -s*p*C_f*(T/T_ref)*1/V
    p += h*dp_dt
    s += h*ds_dt
    a = s0-s
    time += h
    print(time,"\t",p,"\t",s,"\t",a)
