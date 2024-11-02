%%
clc; clear; format compact; close all

MM = imread('MMC08_sk1.jpg');
figure(1)
subplot(2,2,1);
imshow(MM, [])
axis on
title('Původní mapa')


%% vzorek pro hledani
vzorek = imcrop(MM, [1434 3840 36 76]);
[r_vzorek, s_vzorek] = size(vzorek,1:2);
subplot(2,2,2)
imshow(vzorek)
axis on
title('Vzorek pro vyhledávání')

%% zmena barev
[m, n, barevne_pasy] = size(MM);
MM_gray = double(im2gray(MM));
vzorek_gray = double(im2gray(vzorek));
%% korelace
corelation_channel_output = 1;
korelace_vystup = normxcorr2(vzorek_gray, MM_gray); % vystupni matice ma vetsi 
% rozmer, protoze korelace bere v potaz vsechny moznosti zasazeni vzorku. 
% Pro nalazeni vzorku podle korelace musim vyslednou matici korelace_vystup
% upravit na spravnou velikost, aby vyhledavani fungovalo spravne a ja si
% ukladala spravne indexy.
subplot(2,2,3)
imshow(korelace_vystup);
axis on

%%
korelace = 0.7;
[r,s] = find(abs(korelace_vystup) >= korelace);
nalezeno = [r,s];
pocet = size(nalezeno,1);


%%
subplot(2,2,4)
hold on
imshow(MM, [])
for i = 1:size(nalezeno,1)
    rectangle('Position',[nalezeno(i,1)-s_vzorek, nalezeno(i,2)-r_vzorek, s_vzorek, r_vzorek],'EdgeColor','g')
end
axis on
% imrect()


% Bylo by dobre i nejake predzpracovani obrazu. pohrat si s barevnymi
% kanaly (rgb2hsv, im2hsv uprednostnil by spis hsl, im2lab)
% normxcorr2