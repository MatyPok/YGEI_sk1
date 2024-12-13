clc; clear; format long g; close all

% Parametry
N = 50;  % Počet bodů
a = 1.5; % Parametr pro transformaci
b = round(rand(1,2)*10); % Náhodné posunutí pro shluky

% Generování bodů
A = randn(N,2);  % Vygenerování N bodů s normálním rozdělením
B = A .* a + b;  % Transformace bodů A
C = A - b .* [-1, 1];  % Další transformace bodů A

% Vizualizace dat
figure(3)
hold on
scatter(A(:,1), A(:,2), 'filled') % Body A
scatter(B(:,1), B(:,2), 'filled') % Body B
scatter(C(:,1), C(:,2), 'filled') % Body C
grid on
M = [A; B; C]; % Sjednocení všech bodů do jedné matice
title('Vygenerované shluky')
save('data.mat', 'M')  % Uložení dat do souboru