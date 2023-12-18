* an invertor

M1 out in VDD PMOS W=10u L=2u
M2 out in 0 NMOS W=3u L=2u

VDD VDD 0 1.8

Vin in 0 pulse(0 1.8 10e-9 1.5e-9 1.5e-9 4e-9 3e-8)

.probe V(out)

.tran 1e-11 10e-8

.end

 