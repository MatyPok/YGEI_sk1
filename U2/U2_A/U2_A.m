%%
clc; clear; format compact; close all

% NACTETE OBRAZ
im = imread('MMC08_sk1.jpg');

% ZADEJTE KORELACNI KOEFICIENT
korelace = 0.7;

% ZADEJTE POCET VZORKU
pocet_vzorku = 5;

%
% prumerovani vzorku
avg_vzor = prumer_vzorku(pocet_vzorku); % je potreba mit vzorky uz vybrane a ulozene pod konkretnim nazvem - viz. funkce.

%% PREDZPRACOVANI OBRAZU
im_YCBCR = rgb2ycbcr(im);
im_YCBCR = im_YCBCR(:,:,1);
im_YCBCR = imgaussfilt(im_YCBCR, 2);
im_post = im_YCBCR;
vzorekYCBCR = rgb2ycbcr(avg_vzor);
vzorekYCBCR = vzorekYCBCR(:,:,1);
vzorekYCBCR = imgaussfilt(vzorekYCBCR, 2);
vzorek_post = vzorekYCBCR;

%% 
[vyska_vzorek, sirka_vzorek] = size(avg_vzor,1:2);
subplot(2,2,2)
imshow(avg_vzor)
axis on
title('Vzorek pro vyhledávání')

%% korelace
corelation_channel_output = 1;
korelace_vystup = normxcorr2(vzorek_post, im_post); % vystupni matice ma vetsi 
% rozmer, protoze korelace bere v potaz vsechny moznosti zasazeni vzorku. 
% Pro nalazeni vzorku podle korelace musim vyslednou matici korelace_vystup
% upravit na spravnou velikost, aby vyhledavani fungovalo spravne a ja si
% ukladala spravne indexy.

%% porovnani s korelacnim koeficientem
[r,s] = find(abs(korelace_vystup) >= korelace);
nalezeno = [r,s];

%%
% mam vicenasobne opakovani, ktere chci profiltrovat a nechat jen jedinecnou polohu 
nalezeno = sortrows(nalezeno,1); 
nalezeno = jedinecna_poloha(nalezeno,sirka_vzorek);
pocet = size(nalezeno,1);

%% 
% vytvoreni grafickeho okna a zobrazeni puvodniho obrazu.
figure(1)
subplot(2,2,1);
imshow(im, [])
axis on
title('Původní mapa')

subplot(2,2,2)
imshow(avg_vzor)
axis on
title('Vzorek pro vyhledávání')

subplot(2,2,3)
imshow(korelace_vystup);
axis on

subplot(2,2,4)
hold on
imshow(im, [])
for i = 1:size(nalezeno,1)
    rectangle('Position', [nalezeno(i,2)-sirka_vzorek, nalezeno(i,1)-vyska_vzorek, sirka_vzorek, vyska_vzorek],'EdgeColor','m', 'LineWidth',1)
end
axis on
title('Identifikované vzory v mapě',['počet nalezených vzorů = ', num2str(pocet)])

%%
figure(2)
hold on
imshow(im, [])
for i = 1:size(nalezeno,1)
    rectangle('Position', [nalezeno(i,2)-sirka_vzorek, nalezeno(i,1)-vyska_vzorek, sirka_vzorek, vyska_vzorek],'EdgeColor','m', 'LineWidth',1)
end
axis on
title('Identifikované vzory v mapě',['počet nalezených vzorů = ', num2str(pocet)])



%% pixelove souradnice obci s kostelem
pixel_sourad = [nalezeno(:,2)-sirka_vzorek, nalezeno(:,1)-vyska_vzorek, nalezeno(:,2)+sirka_vzorek, nalezeno(:,1)+vyska_vzorek];
