* Example spicets

Is1 N_in1 N_in4   2M
Is2 N_in2 N_in4		5M
Vs3 N_in2 N_in3 	2.5
L1		0		N_in1		0.5
Cl		0		N_in2		2
R1	N_in1 N_in2		3K
R2	N_in3	N_in4		1.8K
R3	N_in4		0			10K

.PROBE  V(n_in2) V(n_in4)
.end