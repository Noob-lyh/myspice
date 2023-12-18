function src_t = getsrcv(SRC, t)

% SRC   : cell structure
% t     : time steps
% src_t : the values of input sources in those time steps

src_num = length(SRC);
value_num = length(t);
src_t = zeros(src_num, value_num);

for i = 1 : src_num
    
    %pulse source
    if strcmp(SRC{i,1}{1,1},'pulse')
        
        para_num = length(SRC{i,1});
        Tstep = 0.001;  %default time step
        
        v1 = SRC{i,1}{2,1};
        v2 = SRC{i,1}{3,1};
        td = 0;
        tr = Tstep;
        tf = Tstep;
        pw = Tstep;
        per = Tstep;
        %0 1 0.05ns 0.05ns 0.05ns 0.30ns 0.50ns
        if para_num > 3
            td = SRC{i,1}{4,1};
        end
        
        if para_num > 4
            tr = SRC{i,1}{5,1};     
        end
        
        if para_num > 5
            tf = SRC{i,1}{6,1};  
        end
        
        if para_num > 6
            pw = SRC{i,1}{7,1};
        end
        
        if para_num > 7
            per = SRC{i,1}{8,1};
        end
        
        t0 = rem(t, per);
        for j = 1 : value_num
            if t0(j) <= td      % 0~0.05ns, before rise
                src_t(i,j) = v1;
            elseif t0(j) <= (td + tr)   % 0.05~0.10ns, rising
                src_t(i,j) = (v2 - v1)*(t0(j) - td)/tr + v1;
            elseif t0(j) <= td + tr + pw    % 0.10~0.40ns, flat
            	src_t(i,j) = v2;
            elseif t0(j) <= td + tr + pw + tf   % 0.40~0.45ns, fall
                src_t(i,j) = (v2 - v1)*(td + tr + pw + tf - t0(j))/tf + v1;
            else    % 0.45ns ~ ?, flat
                src_t(i,j) = v1;
            end
        end
    
    %sin source
    elseif strcmp(SRC{i,1}{1,1},'sin')
        
        para_num = length(SRC{i,1});
        Tstop = 0.1;% default time step
        
        v0 = SRC{i,1}{2,1};     % 0
        va = SRC{i,1}{3,1};     % 3
        freq = 1/Tstop;
        tds = 0;
        theta = 0;
        phi = 0;
        
        if para_num > 3
            freq = SRC{i,1}{4,1};   % 200
        end
        
        if para_num > 4
            tds = SRC{i,1}{5,1};    % 0
        end
        
        if para_num > 5
            theta = SRC{i,1}{6,1};  
        end
        
        if para_num > 6
            phi = SRC{i,1}{7,1};
        end
        
        per = 1/freq;
        ts = rem(t,per);
        for j = 1 : value_num
            if ts(j) <= tds
                src_t(i,j) = v0 + ...
                    va * sin(2*pi*phi/360);
            else
                src_t(i,j) = v0 + ...
                    va * sin(2*pi*(freq*(ts(j)-tds) + phi/360)) * ...
                    exp(-1*(ts(j)-tds)*theta);
                % 3*sin(2*pi*200*ts(j))
            end
        end
        
    end

end