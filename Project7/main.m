clear;
clc;
close all;


cd ./Benchmark
FILE = 1;
if(FILE == 1)
    stamp RLC_s3.sp
    %output_hspice = read_data('rlc_s3_pulse.lis');
    T = 0.02;
end
if(FILE == 2)
    stamp bus8bit8seg.sp
    %output_hspice = read_data('bus8bit8seg_pulse.lis');
    T = 1E-9;
end
if(FILE == 3)
    stamp bus32seg16.sp
    %output_hspice = read_data('bus32seg16_pulse.lis');
    T = 1E-9;
end
steps = 100;
interval = T/steps;
cd ..

T_start = 0;
T_end = 1e-7;
dt = 1e-9;
%T_end = hspice_data(size(hspice_data,1),1);
%dt = hspice_data(2,1) - hspice_data(1,1);
N = floor( (T_end-T_start)/dt ) + 1;

%cycle: the cycle number of the waveform
%error_limited: the limited error to stop iteration
%iter_max: the maximum steps of Newton_method to stop iteration
cycle = 5;
error_limited = 1e-9;
iter_max = 50;

%begin to iterate
tic;
[ X_T, Xerror, Herror, index ] = newton( C, G, B, LT, SRC, T_start, T_end / cycle, floor(N / cycle), error_limited, iter_max );
[results, src_value, ~] = BE(C, G, B, LT, SRC, T_start, T_end, N, X_T);
toc;

%compute the error
% [error , max_error ,MSE] = calc_error(hspice_data,results);

%store data
% result_file = strcat(result_filename,'.mat');
% save( result_file, 'hspice_data','results','src_value','N','error','max_error','MSE','index','X_T','Xerror','Herror','-mat');

%display the figures and print results
% load(result_file,'-mat');
% disp(result_file);
fprintf('Initial value = %lf\n', X_T);
fprintf('Iteration number of Newton = %d\n', index);
fprintf('Error of X = %lf\n', Xerror);
fprintf('Error of H = %lf\n', Herror);
% fprintf('Maximum error (absolute) = %lf\n', max_error);
% fprintf('MSE = %lf\n', MSE);

% subplot(2,2,1);
% plot(results(:,1),src_value(:,:),'b');
% title('Fig.1: input signal waveform','FontSize',14);
% xlabel('t(s)','FontSize',14);
% ylabel('Voltage(V)','FontSize',14);
% 
% subplot(2,2,2);
% plot(results(:,1),results(:,2),'r');
% title('Fig.2: output of Back Euler simuation','FontSize',14);
% xlabel('t(s)','FontSize',14);
% ylabel('Voltage(V)','FontSize',14);
% 
% subplot(2,2,3);
% plot(results(:,1),results(:,2),'b--');
% hold on;
% plot(hspice_data(:,1),hspice_data(:,2),'r');
% title('Fig.3: comparison between simulation and spice result','FontSize',14);
% xlabel('t(s)','FontSize',14);
% ylabel('Voltage(V)','FontSize',14);
% legend('Back Euler simuation','hspice result');
% 
% subplot(2,2,4);
% plot(error(:,1),error(:,2),'c');
% title('Fig.4: absolute error distribution','FontSize',14);
% xlabel('t(s)','FontSize',14);
% ylabel('Voltage(V)','FontSize',14);