clc; clear; format long g
%% 
% Tento skript slouží pro kompresi pomocí DWT. Ve skriptu jsou volány dvě funkce: DWT a iDWT.
%%

% nacteni rastru
ras1 = imread('image_papousek.jpg'); % nacte se jako RGB
% ras1 = imread('geodetka.jpeg');
% imshow(ras1);

% ziskani RGB slozek
R = double(ras1(:,:,1));
G = double(ras1(:,:,2));
B = double(ras1(:,:,3));

%% transformace RGB to YCbCr

Y = 0.2990 * R + 0.5870 * G + 0.1140 * B;
CB = - 0.1687 * R - 0.3313 * G + 0.5000*B + 128;
CR = 0.5000 * R - 0.4187 * G - 0.0813*B + 128;
[m,n] = size(Y);
%% transfomace intevalu 0,255 na -255,255
%roztahujeme interval
Y_ = 2*Y-255;
CB_ = 2*CB - 255;
CR_ = 2*CR - 255;



%% komprese dwt
 % aplikace me funkce diskretni vlnkove transformace
[Y_LLt, Y_LHt, Y_HLt, Y_HHt] = DWT(Y);
Y_LLt_n = mat2gray(Y_LLt); % Převede matici LL do rozsahu 0-1
Y_LHt_n = mat2gray(Y_LHt); % Převede matici LL do rozsahu 0-1
Y_HLt_n = mat2gray(Y_HLt); % Převede matici LL do rozsahu 0-1
Y_HHt_n = mat2gray(Y_HHt); % Převede matici LL do rozsahu 0-1
[CBs_LLt, CBs_LHt, CBs_HLt, CBs_HHt] = DWT(CB);
[CRs_LLt, CRs_LHt, CRs_HLt, CRs_HHt] = DWT(CR);


%% kvantizace
% kvantizace je v teto kompresi vynechána, protože obraz nebyl dělen na submatice

%% dekomprese
  Y_idwt = iDWT(Y_LLt, Y_LHt, Y_HLt, Y_HHt);
CBs_idwt = iDWT(CBs_LLt, CBs_LHt, CBs_HLt, CBs_HHt);
CRs_idwt = iDWT(CRs_LLt, CRs_LHt, CRs_HLt, CRs_HHt);


% Rekonstrukce YCbCr do RGB
Rd = Y_idwt + 1.4020 * (CRs_idwt - 128);
Gd = Y_idwt - 0.344136 * (CBs_idwt - 128) - 0.714136 * (CRs_idwt - 128);
Bd = Y_idwt + 1.7720 * (CBs_idwt - 128);


% Sestavte obraz zpět
ras_dekompress(:,:,1) = uint8(Rd);
ras_dekompress(:,:,2) = uint8(Gd);
ras_dekompress(:,:,3) = uint8(Bd);

imshow(ras_dekompress)
% imwrite(ras_dekompress,'image_papousek_DWT.jpg')


%% ZHODNOCENI JPG komprese pomoci metriky
% vypocet strednich chyb
dR = R - Rd(1:size(R,1), 1:1:size(R,2));
dG = G - Gd(1:size(G,1), 1:1:size(G,2));
dB = B - Bd(1:size(B,1), 1:1:size(B,2));

dR2 = dR.^2; 
dG2 = dG.^2; 
dB2 = dB.^2; 

sigR  = sqrt(sum(sum(dR2))/(m*n));
sigG = sqrt(sum(sum(dG2))/(m*n));
sigB = sqrt(sum(sum(dB2))/(m*n));
