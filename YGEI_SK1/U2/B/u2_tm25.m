clc; clear; format long g;

image = imread('TM25_sk1.jpg');
% subplot(2,2,1)
% imshow(image)
% title('Původní obrázek')

%% Změna barevných pásem a předzpracování - nebylo potřeba

% % obr v šede
% im_gray = im2gray(image);
% % subplot(2,2,1)
% % imshow(im_gray)
% % title('Obráz v šedé')
% 
% contrasted_im_gray = histeq(im_gray,32);
% % imshow(contrasted_im_gray)
% 
% 
% % rozklad na RGB
% R = image(:,:,1);
% G = image(:,:,2);
% B = image(:,:,3);
% 
% % figure('Name','R')
% % imshow(R)
% % figure('Name','G')
% % imshow(G)
% % figure('Name','B')
% % imshow(B)
% 
% HSV = uint8(255*(rgb2hsv(image)));
% %LAB = (rgb2lab(image));

%% Segmentace obrázku, k = 8 (nejlepší výsledek)
[L,Centers] = imsegkmeans(image,8);
% imshow(L,[])
% Zvýrazněná pouze plocha lesů, na originálním obrázku
B = labeloverlay(image,double(L).*(double(L==7)), "Transparency",0);
%B = labeloverlay(image,L);
imshow(B)
title("Segmentovaný obrázek - lesy")
%savefig('segmented.fig')

%%
% Vytvoření a uložení pouze plochy lesů z původního obrázku
only_lesy = image.*(uint8(L==7));
only_lesy(only_lesy==0) = 255;
imshow(only_lesy)

save('lesy_imsegkmeans.mat','only_lesy','-mat')


%%
%maskedImage2(maskedImage2==0) = 255;
%imshow(maskedImage2)

% Uložení plochy lesů z obrázku vytvořeného GraphCutem
lesy_graphcut = imread('lesy_graphcut.png');
imshow(lesy_graphcut)

save('lesy_graphcut.mat','lesy_graphcut','-mat')




