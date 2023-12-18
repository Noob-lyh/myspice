clc
clear
close all

% M1 out in VDD PMOS W=10u L=2u
% M2 out in 0   NMOS W=3u  L=2u
% VDD VDD 0 1.8

% parameter of NMOS
un = 350e-4;            % (m^2)/(V*s)
Coxn = 6.9e-3;          % F/(m^2)
Vthn = 0.7; 
lamdan = 0.1; 
Wn = 3e-6;
Ln = 2e-6;

% parameter of PMOS
up = 100e-4; 
Coxp = 6.9e-3; 
Vthp = -0.8; 
lamdap = -0.2; 
Wp = 10e-6;
Lp = 2e-6;

% parameter of circuit
Vdd = 1.8;

% symbolic valuables
syms Vout_s Vin_s;
Id_n_line = 0.5 * un * Coxn * Wn/Ln * (2*(Vin_s-Vthn)*Vout_s - Vout_s^2)                 * (1 + lamdan * Vout_s);
Id_n_sat  = 0.5 * un * Coxn * Wn/Ln * (Vin_s-Vthn)^2                                     * (1 + lamdan * Vout_s);
Id_p_line = 0.5 * up * Coxp * Wp/Lp * (2*(Vin_s-Vdd-Vthp)*(Vout_s-Vdd) - (Vout_s-Vdd)^2) * (1 - lamdap * (Vdd-Vout_s));
Id_p_sat  = 0.5 * up * Coxp * Wp/Lp * (Vin_s-Vdd-Vthp)^2                                 * (1 - lamdap * (Vdd-Vout_s));

% F and J in symbolic form
f = piecewise(...
    Vin_s < Vthn,                           0 - Id_p_line, ...
    Vthn <= Vin_s < Vout_s + Vthp,          Id_n_sat - Id_p_line, ...
    Vout_s + Vthp <= Vin_s < Vout_s + Vthn, Id_n_sat - Id_p_sat, ...
    Vout_s + Vthn <= Vin_s < Vdd + Vthp,    Id_n_line - Id_p_sat, ...
    Vdd + Vthp <= Vin_s,                    Id_n_line - 0 ...
    );
j = diff(f, Vout_s);


% .tran 1e-11 10e-8
T = 1e-7;
dt = 1e-11;
N = ceil(T/dt);

% iteration settings
max_iter = 5;          
max_error = 1e-12;  

% result space
Vin = zeros(1,N+1); 
Vout = zeros(1,N+2);
num_nt_iters = zeros(N+1,1);  

% iteration
tic;
Vout(:,1) = 1.8; 
for k = 1 : N+1
    Vin(k) = src_pulse((k-1)*dt); 
    iter = 0;      
    while iter < max_iter
        F = subs(f, [Vout_s;Vin_s], [Vout(:,k);Vin(k)]);
        if (norm(F) < max_error)
            break;
        end
        J = subs(j, [Vout_s;Vin_s], [Vout(:,k);Vin(k)]);  
        Vout(:,k) = Vout(:,k) - J \ F;
        iter = iter + 1;             
    end
    num_nt_iters(k) = iter;
    Vout(:,k+1) = Vout(:,k);    % next Vout  
end
toc;


% plotting
subplot(3,1,1);
plot(0:dt:N*dt, Vin);
xlabel('t(s)');
ylabel('Vin(V)');
    
subplot(3,1,2);
plot(0:dt:N*dt, Vout(1:N+1));
xlabel('t(s)');
ylabel('Vout(V)');
    
subplot(3,1,3);
plot(0:1:N, num_nt_iters);
xlabel('K');
ylabel('Iters');


% Vin in 0 pulse(0 1.8 10e-9 1.5e-9 1.5e-9 4e-9 3e-8)
function [Vin] = src_pulse(t)

v1 = 0;
v2 = 1.8;
td = 10e-9;
tr = 1.5e-9;
tf = 1.5e-9;
pw = 4e-9;
per = 3e-8;
t = rem(t, per);
    
if t <= td
    Vin = v1;
elseif t <= td + tr
    Vin = v1 + (v2 - v1) / tr * (t - td);
elseif t <= td + tr + pw
    Vin = v2;
elseif t <= td + tr + pw + tf
    Vin = v2 - (v2 - v1) / tf * (t - td - tr - pw);
else
    Vin = v1;
end

end