clc; clear; format long g; close all

N = 100; % Počet bodů v každém shluku

a = 1.25; % Koeficient pro škálování druhého shluku
b = round(rand(1,3) * 10); % Náhodný vektor pro škálování třetího shluku

% Generování dat
A = randn(N,3); % První shluk
B = A .* a + b; % Druhý shluk (škálovaný)
C = A - b .* [-1, 1, 1]; % Třetí shluk (škálovaný a invertovaný v ose x)

% Správné vykreslení pomocí scatter3
figure;
scatter3(A(:,1), A(:,2), A(:,3), 'filled'); hold on; % Shluk A
scatter3(B(:,1), B(:,2), B(:,3),  'filled'); % Shluk B
scatter3(C(:,1), C(:,2), C(:,3),  'filled'); % Shluk C
title('3D Data');
% xlabel('X'); ylabel('Y'); zlabel('Z');
% legend('Shluk A', 'Shluk B', 'Shluk C' );
title('Vygenerované 3D shluky')
grid on;
hold off;


% plot3(A(:,1),A(:,2),A(:,3),'.',B(:,1),B(:,2),B(:,3),'.',C(:,1),C(:,2),C(:,3),'.')

% Spojení dat do jedné matice
M = [A; B; C];

% Uložení do souboru
save('data3D.mat', 'M');
