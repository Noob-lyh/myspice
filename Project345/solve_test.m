clc       % cmd window
clear     % workspace
close all % figure
format long

% generate/load a random matrix for test..
% G = rand(11,11);
% for i = 1:11
%     G(i,i) = G(i,i) * 20;
% end
G = load('rand11.mat');     % G is posdef, cond(G) = 18.5927
G = G.G(1:5,1:5);
n = size(G,1);
b = (1:n)';
method = 0;
max_it = 100;
eps = 1E-9;

[x, t, it, res] = solve(G, b, method, max_it, eps);
if(method ~= 0)
    plot(1:it, res(1:it));
else
    res = norm(G*x-b);
end