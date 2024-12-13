% Načtení dat z uloženého souboru
clc; clear; format long g; close all
M = load('data.mat');  % Načtení dat
M = cell2mat(struct2cell(M));  % Převod na matici
N = length(M);  % Počet bodů
x = M(:,1);  % X-ová souřadnice
y = M(:,2);  % Y-ová souřadnice

% Počet shluků
n = input('Pocet shluku: ');  % Zadání počtu shluků uživatelem

%% 1. Výpočet diagonální přímky
min_point = [min(x), min(y)];  % Minimální bod
max_point = [max(x), max(y)];  % Maximální bod

%% 2. Umístění počátečních středů
xs = linspace(min_point(1), max_point(1), n+2)';  % X-ové souřadnice pro středy
ys = linspace(min_point(2), max_point(2), n+2)';  % Y-ové souřadnice pro středy
S = [xs(2:end-1), ys(2:end-1)];  % Počáteční středy

%% Zobrazení počátečních středů
figure;
scatter(x, y, 'filled'); hold on;
plot([min_point(1), max_point(1)], [min_point(2), max_point(2)], 'r-', 'LineWidth', 1.5); % Diagonální přímka
scatter(S(:,1), S(:,2), 100, 'g+');  % Počáteční středy
grid on
title('Počáteční rozmístění středů');
hold off;

%% Clusterizace
podminka = 0.01;  % Tolerance pro změnu středu
dS = 1;  % Počáteční posun středů
maxIter = 100;  % Maximální počet iterací
iter = 0;  % Počítadlo iterací

while any(dS > podminka) && iter < maxIter
    iter = iter + 1;
    L = zeros(N, 1);  % Přiřazení bodů k shlukům
    d2 = zeros(n, 1);  % Vzdálenosti od středů
    
    % Přiřazení bodů k nejbližšímu středu
    for i = 1:N
        for j = 1:n
            d2(j) = (x(i) - S(j,1))^2 + (y(i) - S(j,2))^2;
        end
        [~, L(i)] = min(d2);  % Přiřadí bod k nejbližšímu středu
    end
    
    % Přepočet nových středů
    nove_S = zeros(n, 2);  % Matice pro nové středy
    for j = 1:n
        k = find(L == j);  % Indexy bodů přiřazených ke středu j
        if isempty(k)
            nove_S(j,:) = S(j,:);  % Pokud je shluk prázdný, zůstává původní střed
        else
            nove_S(j,:) = mean(M(k,:));  % Nový střed je průměr bodů v shluku
        end
    end
    
    % Vzdálenost mezi starými a novými středy
    dS = sqrt((nove_S(:,1) - S(:,1)).^2 + (nove_S(:,2) - S(:,2)).^2);
    S = nove_S;  % Aktualizace středů
end

%% Použití kmeans funkce
[idx, C] = kmeans(M, n);  % Výpočet shluků pomocí funkce kmeans

%% Vizualizace výsledků
figure;
subplot(1,2,1)
grid on
hold on;
scatter(x, y, [], L, 'filled'); % Body barevně podle shluku
scatter(S(:,1), S(:,2), 100, 'r+'); % Středy shluků
title('Výsledek clusterizace');
hold off;

subplot(1,2,2)
gscatter(M(:,1), M(:,2), idx, 'bgm');  % Vizualizace výsledků kmeans
hold on
plot(C(:,1), C(:,2), 'r+');  % Středy shluků
legend off
grid on
title('Použití funkce kmeans');