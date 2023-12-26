clc
clear
close all


% R1 VDD out1 80k
% R2 VDD out2 80k
% M1 out1 in1 p NMOS L=0.8u W=80u
% M2 out2 in2 p NMOS L=0.8u W=80u
% Iss p 0 20u
% VDD VDD 0 3.3


% parameter of NMOS
un = 350e-4; 
Coxn = 6.9e-3; 
Wn = 80e-6;
Ln = 0.8e-6;
Vthn = 0.7; 
lamdan = 0.1; 

% parameter of circuit
Vdd = 3.3;
Iss = 20e-6;
Vin1 = 1.65;
R1 = 80e3;
R2 = 80e3;


% symbolic valuables
syms Vout1 Vout2 Vss Vin2_s;   % Vin1 is fixed, Vss = Vp
Vout_s = [Vout1; Vout2; Vss];

% KCL at p, output1 and output2
f1 = Iss - (Vdd-Vout1) / R1 - (Vdd-Vout2) / R2; 
f2 = (Vdd-Vout1) / R1 - 0.5 * un * Coxn * Wn/Ln * (Vin1  -Vss-Vthn)^2 * (1 + lamdan * (Vout1-Vss));
f3 = (Vdd-Vout2) / R2 - 0.5 * un * Coxn * Wn/Ln * (Vin2_s-Vss-Vthn)^2 * (1 + lamdan * (Vout2-Vss));

% F and J in symbolic form
f = [f1; f2; f3];   % f = I(Vout1, Vout2, Vss) = I(Vout_s)= 0
j = jacobian(f, Vout_s); 


% .tran 1m 0.2
T = 0.2;
dt = 1e-3;
N = T/dt;

% iteration settings
max_iter = 5;           
max_error = 1e-12;

% result space
Vin = zeros(1,N+1);
Vout = zeros(3,N+2);        
num_nt_iters = zeros(N+1,1);

% iteration
tic;
Vout(:,1) = [2.5,2.5,0];  
for k = 1:N+1
    Vin(k) = src_sin((k-1)*dt);
    iter = 0;
    while iter < max_iter
        F = subs(f, [Vout_s;Vin2_s], [Vout(:,k);Vin(k)]);
        if (norm(F) < max_error)
            break;
        end
        J = subs(j, [Vout_s;Vin2_s], [Vout(:,k);Vin(k)]);
        Vout(:,k) = Vout(:,k) - J \ F;
        iter = iter + 1;             
    end
    num_nt_iters(k) = iter;
    Vout(:,k+1) = Vout(:,k);  % as next Vout start point
end
toc;


% plotting
subplot(2,2,1);
plot(0:dt:N*dt, Vin);
xlabel('t(s)');
ylabel('Vin(V)');

subplot(2,2,2);
plot(0:1:N, num_nt_iters);
xlabel('K');
ylabel('Iters');
    
subplot(2,2,3);
plot(0:dt:N*dt, Vout(1, 1:N+1));
xlabel('t(s)');
ylabel('Vout1(V)');
    
subplot(2,2,4);
plot(0:dt:N*dt, Vout(2, 1:N+1));
xlabel('t(s)');
ylabel('Vout2(V)');


% Vin2 in2 0 sin(1.65 1m 1e2)
function [Vin] = src_sin(t)

v0 = 1.65;
va = 1e-3;
freq = 1e2;
tds = 0;
theta = 0;
phi = 0;

if t <= tds
    Vin = v0 + va * sin(2*pi*phi/360);
else
    Vin = v0 + va * sin(2*pi*(freq*(t-tds) + phi/360)) * exp(-1*(t-tds)*theta);
end

end