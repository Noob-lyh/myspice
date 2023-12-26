clear;
clc;
close all;

% read file
cd ./Benchmark
FILE = 1;
if(FILE == 1)
    stamp RLC_s3.sp
    output_hspice = read_data('RLC_s3.lis');
    T = 0.02; 
    dt = 0.000004;
    circle = 0.005;
end
if(FILE == 2)
    stamp bus8bit8seg.sp
    output_hspice = read_data('bus8bit8seg.lis');
    T = 1e-9;
    dt = 1e-12;
    circle = 5e-11;
end
if(FILE == 3)
    stamp bus32seg16.sp
    output_hspice = read_data('bus32seg16.lis');
    T = 0.02; 
    dt = 0.000004;
    circle = 0.005;
end
cd ..

% settings
n = size(G, 1);
N = round(T/dt);
error_limited = 1e-9;
iter_max = 50;

% get src values
for i = 1 : length(SRC) % can't read in phase?
    SRC{i,1}{5,1} = 0;
    SRC{i,1}{6,1} = 0;
    SRC{i,1}{7,1} = 90; % cos(200*pi*t) or cos(20G*pi*t)
end
SRC_Value = getsrcv(SRC, dt*(1:N));

%begin to iterate
tic;
L = round(circle/dt);
M = C + dt * G;
J = (M\C)^L - eye(n);
x = zeros(n, N+1);  % x_it
Xerror = inf;
Herror = inf;
iter = 0;
% calculate inital value for steady solution
while (Xerror > error_limited || Herror > error_limited) && iter < iter_max
    for i = 1 : L   % x_it(0) + BE iteration -> x_it(T)
        b = C * x(:, i) + dt * B * SRC_Value(:,i); 
        x(:,i + 1) = M \ b;
    end   
    H = x(:, L+1) - x(:, 1);
    Herror = norm(H);               % x_it(T) - x_it(0)
    x_diff = J\H;
    Xerror = norm(x_diff);          % x_it+1(0) - x_it(0)
    x(:, 1) = x(:, 1) - x_diff;
    iter = iter + 1;
end
% calculate steady solution
output_shooting = zeros(N+1, size(LT,1)+1);    
for i = 1 : N
    b = C * x(:, i) + dt * B * SRC_Value(:,i); 
    x(:,i + 1) = M \ b;
    output_shooting(i+1, :) = [i*dt, (LT*x(:,i + 1))'];
end
% calculate error
error = output_hspice(2:end, 2) - output_shooting(2:end, 2);
MSE = sum(error.^2)/length(error);
toc;

% ploting
subplot(3,1,1);
plot((0:N-1)*dt, SRC_Value);
xlabel('t / s');
ylabel('Vin / V');

subplot(3,1,2);
plot((1:N)*dt, output_shooting(2:end, 2), 'r');
hold on;
plot((1:N)*dt, output_hspice(2:end, 2), 'g');
xlabel('t / s');
ylabel('Vout_1(shooting-hspice) / V)');

subplot(3,1,3);
plot((1:N)*dt, error);
xlabel('t / s');
ylabel('Verror_1 / V');

fprintf('MSE of output 1 is: %f\n', MSE);