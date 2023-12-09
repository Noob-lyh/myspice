function [x, t, it, res] = solve(A, b, method, max_it, eps)

tic;

    [n,~] = size(A);        % size of A
    x = zeros(n,1);         % initialize x to 0
    it = 1;                 % iterate times
    res = zeros(max_it,1);  % store residule info
    
    if norm(b) == 0
        t = toc;
        res(1) = 0;
        return;
    end
    
    % direct, use matlab
    if (method == 0)    
        x = A \ b;
    end
    
    % iterative, Jacobi & G-S & SOR
    % A = M - N   --->  M^(-1)Ax = M^(-1)b
    % x(k+1) = M^(-1)N x(k) + M^(-1)b
    %        =    G    x(k) +    f
    
    if (method == 1)    % Jacobi    
        M = diag(diag(A));  % M = D
        N = M - A;          % N = -L_wodiag -U_wodiag
        G = M \ N;
        f = M \ b;
        while it < max_it
            x = G * x + f;
            res(it) = norm(A * x - b);
            if res(it) < eps
                break;
            else
                it = it + 1;
            end
        end
    end
    
    if (method == 2) % G-S
        M = tril(A);        % M = L_widiag = D - (-L_wodiag)
        N = M - A;          % N = (-U_wodiag)
        G = M \ N;
        f = M \ b;
        while it < max_it
            x = G * x + f;
            res(it) = norm(A * x - b);
            if res(it) < eps
                break;
            else
                it = it + 1;
            end
        end
    end
    
    if (method == 3) % SOR
        w = 1;    % w > 0 && w != 0
        M = diag(diag(A))./w - tril(A,-1);  % M = D/w - (-L_wodiag)
        N = M - A;                          % N = (-U_wodiag) + (1/w - 1)D
        G = M \ N;
        f = M \ b;
        while it < max_it
            x = G * x + f;
            res(it) = norm(A * x - b);
            if res(it) < eps
                break;
            else
                it = it + 1;
            end
        end
    end 

    % iterative, GCR
    
    if (method == 4) % GCR
        r = b - A * x;
        p = zeros(n, max_it);
        Ap = zeros(n, max_it);
        ApTAp = zeros(1, max_it);
        p(:,1) = r;
        Ap(:,1) = A * p(:,1);
        ApTAp(1) = sum(Ap(:,1).*Ap(:,1));
        while it < max_it
            alpha = dot(r,Ap(:,it)) / ApTAp(it);
            x = x + alpha * p(:,it);
            r = r - alpha * Ap(:,it);
            p(:,it+1) = r;
            for i = 1 : it
                p(:,it+1) = p(:,it+1) - ...
                    (dot(A*r, Ap(:,i)) / ApTAp(i)) * p(:,i);
            end  
            Ap(:,it+1) = A * p(:,it+1);
            ApTAp(it+1) = sum(Ap(:,it+1).*Ap(:,it+1));
            res(it) = norm(A * x - b);
            if norm(r) < eps
                break;
            else
                it = it + 1;
            end
        end
    end

t = toc;

end