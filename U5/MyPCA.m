clc; clear; close all; format long g

%% nacteni dat
% Načítání datových souborů "sada1.mat" a "sada2.mat"
% Předpokládáme, že soubory obsahují proměnné 'sada1' a 'sada2' obsahující matice dat
sada1 = load('sada1.mat');
sada1 = sada1.sada1;  % Extrakce datové sady 1
sada2 = load('sada2.mat');
sada2 = sada2.sada2;  % Extrakce datové sady 2

%% kovariancni matice
% Odstranění průměru z dat (centrování)
var1 = sada1 - mean(sada1);
var2 = sada2 - mean(sada2);

% Výpočet směrodatné odchylky pro obě sady
smodch1 = std(var1');
smodch2 = std(var2');

% Výpočet kovariančních matic pro obě sady
Kov1 = cov(var1);
Kov2 = cov(var2);

%% korelacni matice
% Výpočet korelačních matic pro obě sady
Kor1 = corrcoef(var1);
Kor2 = corrcoef(var2);

%% vlastni cisla
% Výpočet vlastních čísel a vlastních vektorů kovariančních matic
[V1, D1] = eig(Kov1);  % Vlastní čísla a vektory pro kovarianční matici sady 1
[V2, D2] = eig(Kov2);  % Vlastní čísla a vektory pro kovarianční matici sady 2

%% vlastni cisla kovariancni matice
% Seřazení vlastních čísel v sestupném pořadí
[D1_sorted, idx1] = sort(diag(D1), 'descend');  % Seřazení pro sadu 1
[D2_sorted, idx2] = sort(diag(D2), 'descend');  % Seřazení pro sadu 2
DKov1 = D1(idx1, idx1);  % Seřazená vlastní čísla pro sadu 1
DKov2 = D2(idx2, idx2);  % Seřazená vlastní čísla pro sadu 2

%% vlastni vektory kovariancni matice
% Seřazení vlastních vektorů podle vlastních čísel
VKov1 = V1(:, idx1);  % Seřazené vlastní vektory pro sadu 1
VKov2 = V2(:, idx2);  % Seřazené vlastní vektory pro sadu 2



%% rozptyl * vlastni vektor kovariancni matice
% Vynásobení dat centrováním s vlastními vektory kovarianční matice
varVKov1 = var1 * VKov1;  % Vynásobení sady 1 vlastními vektory
varVKov2 = var2 * VKov2;  % Vynásobení sady 2 vlastními vektory

%% smer vlastniho vektoru
% Výpočet směrů vlastních vektorů pro obě sady
% Směr 1. a 2. vlastního vektoru pro sadu 1
smer11 = VKov1(2,1) / VKov1(1,1);
smer12 = VKov1(2,2) / VKov1(1,2);

% Směr 1. a 2. vlastního vektoru pro sadu 2
smer21 = VKov2(2,1) / VKov2(1,1);
smer22 = VKov2(2,2) / VKov2(1,2);

%% pro osy hlavnich komponent
% Projekce dat na hlavní komponenty pro obě sady
hlk1 = var1 * VKov1;  % Projekce sady 1
hlk2 = var2 * VKov2;  % Projekce sady 2

%% podil variance vysvetleny jednotlivymi hlavnimi komponentami
% Procentuální podíl vysvětlené variance pro první a druhou komponentu

% Sada 1
explained_var1 = D1_sorted / sum(D1_sorted) * 100;

% Podmínka pro sadu 1: První hlavní komponenta musí vysvětlit více než 70 % variance
if explained_var1(1) > 70
    disp('Podmínka pro sadu 1 splněna: První hlavní komponenta vysvětluje více než 70 % variance.');
else
    disp('Podmínka pro sadu 1 NENÍ splněna: První hlavní komponenta nevysvětluje více než 70 % variance.');
end

% Sada 2
explained_var2 = D2_sorted / sum(D2_sorted) * 100;
disp('Podíl variance vysvětlený jednotlivými hlavními komponentami (sada2):');
disp(explained_var2);

% Podmínka pro sadu 2: Rozdíl mezi první a druhou komponentou musí být menší než 10 %
diff_var2 = abs(explained_var2(1) - explained_var2(2));
if diff_var2 < 10
    disp('Podmínka pro sadu 2 splněna: Rozdíl mezi první a druhou komponentou je menší než 10 %.');
else
    disp('Podmínka pro sadu 2 NENÍ splněna: Rozdíl mezi první a druhou komponentou je větší než 10 %.');
end

%% Vizualizace
% Graf původních dat pro obě sady

% ---------------------------------------------
figure(1)
subplot(1,2,1)
hold on
scatter(sada1(:,1), sada1(:,2))
grid on
title('Rozptyl původních dat - sada 1')
xlabel('X')
ylabel('Y')

subplot(1,2,2)
scatter(sada2(:,1), sada2(:,2))
grid on
title('Rozptyl původních dat - sada 2')
xlabel('X')
ylabel('Y')

% ---------------------------------------------
% Směry hlavních komponent pro obě sady
figure(2)
subplot(1,2,1)
hold on
plot(var1(:,1), var1(:,2), 'r*')
line([min(var1(:,1)), max(var1(:,1))], [min(var1(:,1))*smer11, max(var1(:,1))*smer11], 'color', 'b')
line([min(var1(:,1)), max(var1(:,1))], [min(var1(:,1))*smer12, max(var1(:,1))*smer12], 'color', 'g')
legend('Vstupní data', 'Směr 1. vektoru', 'Směr 2. vektoru','Location','best')
grid on
title('Směry hlavních komponent - sada 1')
xlabel('X')
ylabel('Y')

subplot(1,2,2)
hold on
plot(var2(:,1), var2(:,2), 'r*')
line([min(var2(:,1)), max(var2(:,1))], [min(var2(:,1))*smer21, max(var2(:,1))*smer21], 'color', 'b')
line([min(var2(:,1)), max(var2(:,1))], [min(var2(:,1))*smer22, max(var2(:,1))*smer22], 'color', 'g')
legend('Vstupní data', 'Směr 1. vektoru', 'Směr 2. vektoru','Location','best')
grid on
title('Směry hlavních komponent - sada 2')
xlabel('X')
ylabel('Y')

% -----------------------------------------
% Projekce do os hlavních komponent
figure(3)
title('Zobrazení v osách hlavních komponent')
subplot(1,2,1)
hold on
scatter(hlk1(:,1), hlk1(:,2), 'r*')
grid on
title('Data v osách hlavních komponent - sada 1')
xlabel('1. hlavní komponenta')
ylabel('2. hlavní komponenta')

subplot(1,2,2)
hold on
scatter(hlk2(:,1), hlk2(:,2), 'r*')
grid on
title('Data v osách hlavních komponent - sada 2')
xlabel('1. hlavní komponenta')
ylabel('2. hlavní komponenta')

% -----------------------------------------------
% Podíl vysvětlené variance
figure(4);
subplot(1,2,1)
bar(explained_var1);
title('Podíl vysvětlené variance - sada 1');
xlabel('Hlavní komponenty');
ylabel('Podíl vysvětlené variance (%)');
grid on;

subplot(1,2,2)
bar(explained_var2);
title('Podíl vysvětlené variance - sada 2');
xlabel('Hlavní komponenty');
ylabel('Podíl vysvětlené variance (%)');
grid on;


%% numericke vystupy

disp('Vlastní čísla pro kovarianční matici sady 1:');
disp(D1_sorted);
disp('Vlastní vektory pro kovarianční matici sady 1:');
disp(VKov1);
disp('Podíl variance vysvětlený jednotlivými hlavními komponentami (sada1):');
disp(explained_var1);
% Podmínka pro sadu 1: První hlavní komponenta musí vysvětlit více než 70 % variance
if explained_var1(1) > 70
    disp('Podmínka pro sadu 1 splněna: První hlavní komponenta vysvětluje více než 70 % variance.');
else
    disp('Podmínka pro sadu 1 NENÍ splněna: První hlavní komponenta nevysvětluje více než 70 % variance.');
end

disp('===========================================================================================================================')
disp('Vlastní čísla pro kovarianční matici sady 2:');
disp(D2_sorted);
disp('Vlastní vektory pro kovarianční matici sady 2:');
disp(VKov2);
disp('Podíl variance vysvětlený jednotlivými hlavními komponentami (sada2):');
disp(explained_var2);

% Podmínka pro sadu 2: Rozdíl mezi první a druhou komponentou musí být menší než 10 %
diff_var2 = abs(explained_var2(1) - explained_var2(2));
if diff_var2 < 10
    disp('Podmínka pro sadu 2 splněna: Rozdíl mezi první a druhou komponentou je menší než 10 %.');
else
    disp('Podmínka pro sadu 2 NENÍ splněna: Rozdíl mezi první a druhou komponentou je větší než 10 %.');
end
