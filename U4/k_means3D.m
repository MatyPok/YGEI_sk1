clc; clear; format long g; 

%% Načtení dat
% M = load('body.mat'); % shluky ziskane z funkce gen_points_figure
 M = load('data3D.mat'); % shluky ziskane z funkce gen_points_randn3D
M = cell2mat(struct2cell(M));
N = length(M);
x = M(:,1); y = M(:,2); z = M(:,3) ;

%% Počet shluků
n = input('Pocet shluku: ');

% 1. Výpočet diagonální přímky
min_point = [min(x), min(y),  min(z)]; % Bod s minimálními souřadnicemi
max_point = [max(x), max(y), max(z)]; % Bod s maximálními souřadnicemi

% 2. Rozmístění počátečních středů podél přímky
xs = linspace(min_point(1), max_point(1), n)'; % Rovnoměrně mezi min(x) a max(x)
ys = linspace(min_point(2), max_point(2), n)'; % Rovnoměrně mezi min(y) a max(y)
zs = linspace(min_point(3), max_point(3), n)'; % Rovnoměrně mezi min(z) a max(z)

S = [xs, ys, zs]; % Počáteční středy

% Zobrazení dat a počátečních středů
figure(2);
scatter3(x, y,z, 'filled'); hold on;
plot3([min_point(1), max_point(1)], [min_point(2), max_point(2)], [min_point(3), max_point(3)], 'r-', 'LineWidth', 1.5); % Diagonální přímka
scatter3(S(:,1), S(:,2),S(:,3), 100, 'g*'); % Počáteční středy
title('Počáteční rozmístění středů');
hold off;

%% Algoritmus k-means
podminka = 0.01; % Tolerance
dS = 1;
maxIter = 100; % Maximální počet iterací
iter = 0;

while any(dS > podminka) && iter < maxIter
    iter = iter + 1;
    L = zeros(N, 1);
    d2 = zeros(n, 1);
    
    % Přiřazení bodů k nejbližšímu středu
    for i = 1:N
        for j = 1:n
            d2(j) = (x(i) - S(j,1))^2 + (y(i) - S(j,2))^2 + (z(i) - S(j,3))^2;
        end
        [~, L(i)] = min(d2);
    end
    
    % Přepočet center shluků
    nove_S = zeros(n, 3);
    for j = 1:n
        k = find(L == j);
        if isempty(k)
            nove_S(j,:) = S(j,:); % Pokud je shluk prázdný
        else
            nove_S(j,:) = mean(M(k,:));
        end
    end
    
    % Vzdálenost posunu středu
    dS = sqrt((nove_S(:,1) - S(:,1)).^2 + (nove_S(:,2) - S(:,2)).^2 + (nove_S(:,3) - S(:,3)).^2);
    S = nove_S;
end

%% Vizualizace
figure(3);
grid on;
scatter3(x, y,z, [], L,'filled'); hold on;
scatter3(S(:,1), S(:,2), S(:,3), 100, 'r*'); % Středy shluků
title('Výsledek clusterizace');
xlabel('X'); ylabel('Y'); zlabel('Z');

