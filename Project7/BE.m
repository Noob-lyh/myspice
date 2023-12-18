function [output_value, SRC_Value, X_T] = BE(C, G, B, LT, SRC, T_start, T_end, N, X0)

delta_T = (T_end - T_start) / N; % T/N
tn = 0; % t0
X_num = size(G, 1); % set the X_num as the maximum steps of GCR

SRC_Value = zeros(N + 1, length(SRC));
output_value = zeros(N + 1, size(LT, 1) + 1);
output_value(1, 1) = tn;

src_point = getsrcv(SRC, tn); % get U(t0)
SRC_Value(1,:) = src_point';
x = zeros(X_num, N + 1);

%get the initial value by solving GX0=BU(0) 
x(:,1) = X0; % the initial value of x, x(t0)
output_value(1,2:end) = (LT * x(:,1))';

%solve the equation: (C + G * delta_T) * x(tn+1) = Cx(tn) + delta_T*BU(tn+1)
M = C + delta_T .* G; % M = C + G * delta_T
for i = 1:1:N
    tn = tn + delta_T; % tn+1 = (n+1) * delta_T
    output_value(i + 1, 1) = tn;
    src_point = getsrcv(SRC, tn); % get U(tn+1)
    SRC_Value(i + 1,:) = src_point';
    b = C * x(:,i) + delta_T .* (B * src_point); % b = Cx(tn) + delta_T*BU(tn+1)
    x(:,i + 1) = M \ b;
    output_value(i + 1,2:end) = (LT * x(:,i + 1))';
end

X_T = x(:, N+1);