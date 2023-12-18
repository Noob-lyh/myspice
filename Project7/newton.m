function [ X_T, Xerror, Herror, index ] = newton( C, G, B, LT, SRC, T_start, T_end, L, error_limited, iter_max )

X_size = size(G, 1);
X_zero = zeros(X_size, 1);
Xerror = inf;
Herror = inf;
delta = (T_end - T_start) / L; % delta_t = T / L
dfai = ( inv(C + delta * G) * C )^L; % dfai = (C(C+delta_t*G)^-1)^L
J = dfai - eye(X_size); % Jacobi Matrix = dfai - I
index = 0;

while ( Xerror > error_limited || Herror > error_limited) && index < iter_max
    %get the result calculated by Back Euler method
    [~, ~, X_T] = BE(C, G, B, LT, SRC, T_start, T_end, L, X_zero);
    
    H = X_T - X_zero;
    
    X_next = X_zero - J \ H;
    
    Xerror = norm(X_next - X_zero);
    Herror = norm(H);
    
    X_zero = X_next;

    index = index + 1;

end