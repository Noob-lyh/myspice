clc       % cmd window
clear     % workspace
close all % figure
format long



% step 0: MNA
%
%       C_x * X¡¤ + G_x * X = B * U
%       Y = L^T * X
%
%       C_x = C in workspace = | C 0 |
%                              | 0 L |
%       G_x = G in workspace = |   G    E |
%                              | -E^T   0 |



% step 1: stamp
FILE = 1;
cd ./Benchmark
if(FILE == 1)
    stamp rlc_s3_pulse.sp
    data = read_data('rlc_s3_pulse.lis');
    T = 0.02;
end
if(FILE == 2)
    stamp rlc_s3_sin.sp
    data = read_data('rlc_s3_sin.lis');
    T = 0.02;
end
if(FILE == 3)
    stamp bus8bit8seg_pulse.sp
    data = read_data('bus8bit8seg_pulse.lis');
    T = 1E-9;
end
if(FILE == 4)
    stamp bus32seg16_pulse.sp
    data = read_data('bus32seg16_pulse.lis');
    T = 1E-9;
end
steps = 100;
interval = T/steps;
cd ..


% step 1x: generate/load a random matrix for test..
% G = rand(11,11);
% for i = 1:11
%     G(i,i) = G(i,i) * 20;
% end
% G = load('rand11.mat');     % G is posdef, cond(G) = 18.5927
% G = G.G;


% step 2: setup

% solve setting
method1 = 0;    % dc
method2 = 0;    % trans
max_iter = 100;
eps = 1E-6;

% get SRC and set BU
SRC_t = getsrcv(SRC, interval*(1:steps));
BU_t = B * SRC_t;

% allocate x and output
X_t = zeros(size(B,1), steps);
output_t = zeros(size(LT,1), steps);



% step 3: solve G_x X_0 = B U_0 to get X_0 (DC analysis)
[X_t(:,1), t, it, res] = solve(G, BU_t(:,1), method1, max_iter, eps);
output_t(:,1) = LT * X_t(:,1);
% plot(1:it, res(1:it));



% setp 4: solve ODE using TR method (transient analysis)
A1 = C - (interval/2) * G;
A2 = C + (interval/2) * G;
for step = 2 : steps
    b = A1*X_t(:,step-1) + 0.5*interval*(BU_t(:,step-1)+BU_t(:,step));
    [X_t(:,step), t, it, res] = solve(A2, b, method2, max_iter, eps);
    output_t(:,step) = LT * X_t(:,step);
end


% step 5: compare with HSPICE result
fig_num = size(data,2) - 1;
fig_size = ceil(sqrt(fig_num));
for i = 1 : fig_num
    subplot(fig_size, fig_size, i);
    plot(interval*(1:steps), output_t(i,:), 'r');
    hold on;
    plot(data(:,1),data(:,i+1), 'g');
    hold off;
    xlabel(num2str(i));
%     legend('my', 'hspice');
end
% xlabel('time / s');
% ylabel('value / ?');
