clc; clear; close all; format long g
n = 200;

% Generování dat s vysokou variabilitou v první ose (x) a malou v druhé (y)
x = 2 * rand(n,1); % x bude náhodné číslo mezi 0 a 1
y = 3 * x + 0.75 * randn(n, 1); % y je lineárně závislé na x, ale s přidaným šumem

sada1 = [x,y];
save sada1.mat sada1

% Vytvoření grafu
figure(1)
scatter(x,y, 'filled')
grid on
title('Generovani bodu 1]')

%%

q = 0.75*randn(n,1)-2;
w = 0.75*randn(n,1);
sada2 = [q,w];
save sada2.mat sada2

figure(2)
scatter(q,w,'filled')
grid on
title('Generovani bodu 2]')

%%
