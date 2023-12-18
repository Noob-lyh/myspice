* diff_amp

R1 VDD out1 80k
R2 VDD out2 80k

M1 out1 in1 p NMOS L=0.8u W=80u
M2 out2 in2 p NMOS L=0.8u W=80u

Iss p 0 20u

VDD VDD 0 3.3
Vin1 in1 0 1.65
Vin2 in2 0 sin(1.65 1m 1e2)

.probe V(out1) V(out2)

.op

.tran 1m 0.2

.end
