clc; clear; format long g

% nacteni rastru
ras1 = imread("image_papousek_gray.jpg"); % nacte se jako RGB

%imshow(ras1);

% ziskani RGB slozek
R = double(ras1(:,:,1));
G = double(ras1(:,:,2));
B = double(ras1(:,:,3));

%% transformace RGB to YCbCr

Y = 0.2990 * R + 0.5870 * G + 0.1140 * B;
CB = - 0.1687 * R - 0.3313 * G + 0.5000*B + 128;
CR = 0.5000 * R - 0.4187 * G - 0.0813*B + 128;



%% transfomace intevalu 0,255 na -255,255
%roztahujeme interval
Y_ = 2*Y-255;
CB_ = 2*CB - 255;
CR_ = 2*CR - 255;

%% diskretni kosinova transformace
% aplikuje se na submatice 8x8
% jako bonus muzeme udelat fast furierovu transformaci
% clen DC ma nejvetsi vliv pri zpetne dekompresi. 

% nejprve potrebujeme kvantizacni matice
Qy = [16 11 10 16 24 40 51 61
      12 12 14 19 26 58 60 55
      14 13 16 24 40 87 69 56
      14 17 22 29 51 87 80 62
      18 22 37 26 68 109 103 77
      24 35 55 64 81 104 113 92
      49 64 78 87 103 121 120 101
      72 92 95 98 112 100 103 99];

Qc = [17 18 24 47 66 99 99 99
      18 21 26 66 99 99 99 99
      24 26 56 99 99 99 99 99
      47 69 99 99 99 99 99 99
      99 99 99 99 99 99 99 99
      99 99 99 99 99 99 99 99
      99 99 99 99 99 99 99 99
      99 99 99 99 99 99 99 99];

% update kvantizacnich matic podle q
q = 70;
Qc = (50*Qc)/q;
Qy = (50*Qy)/q;



%% Process input raster by sub-matrixes
[m,n] = size(Y);
for i = 1:8:m-7
    for j = 1:8:n-7
        % tvorba submatice pro jednotlive chrominacni slozky. Nepotrebujeme
        % je ukladat, budeme pracovt v cyklu s aktualni submatici
        Ys  =  Y(i:i+7,j:j+7);
        CBs = CB(i:i+7,j:j+7);
        CRs = CR(i:i+7,j:j+7);

        % prevzorkovani
        Ys  = resampling2x2(Ys );
        CBs = resampling2x2(CBs);
        CRs = resampling2x2(CRs);


        % aplikace nasi funkce Diskretni cosinovy transformace
        Ydct = myDCT(Ys);
        CBdct = myDCT(CBs);
        CRdct = myDCT(CRs);

        % aplikace kvantizacni matice, kvantizujeme
        % submatice
        Yq = Ydct./Qc;
        CBq = CBdct./Qy;
        CRq = CRdct./Qy;

        % zaokrouhleni
        Yqr  = round(Yq);
        CBqr = round(CBq);
        CRqr = round(CRq);     

        YT(i:i+7,j:j+7) = Yqr ;
        CBT(i:i+7,j:j+7) = CBqr;
        CRT(i:i+7,j:j+7) = CRqr;

    end

end


%% dekomprese
% [m,n] = size(YT);
for i = 1:8:m-7
    for j = 1:8:n-7

        
        % tvorba submatice pro jednotlive chrominacni slozky. Nepotrebujeme
        % si je nekam ukladat, budeme pracovt v cyklu s aktualni submatici
        Ys =  YT(i:i+7,j:j+7);
        CBs = CBT(i:i+7,j:j+7);
        CRs = CRT(i:i+7,j:j+7);

        %  dekvantizace
        Ysd = Ys.*Qc;
        CBd = CBs.*Qy;
        CRqd = CRs.*Qy;

        % aplikace nasi funkce inverzni Diskretni cosinovy transformace
        Yidct =  myDCT_inv(Ysd );
        CBidct = myDCT_inv(CBd );
        CRidct = myDCT_inv(CRqd);

        %  dekvantizace


        % overwrite tule with the compressed one
        Y(i:i+7,j:j+7) = Yidct ;
        CB(i:i+7,j:j+7)= CBidct;
        CR(i:i+7,j:j+7)= CRidct;
    end
end


%% YCBC TO RGB
Rd = Y+ 0 + 1.4020*(CR - 128);
Gd = Y - 0.3441*(CB - 128)  - 0.7141*(CR - 128);
Bd = Y + 1.7720*(CB - 128) - 0.0001*(CR - 128);

%% convert double to uint8
Ri = uint8(Rd);
Gi = uint8(Gd);
Bi = uint8(Bd);

%% slozeni rastru
ras_dekompress(:,:,1) = Ri;
ras_dekompress(:,:,2) = Gi;
ras_dekompress(:,:,3) = Bi;
imshow(ras_dekompress)
% imwrite(ras_dekompress,'image_papousek_gray_DCT10.jpg')
%% ZHODNOCENI JPG komprese pomoci metriky
% vypocet strednich chyb
dR = R - Rd;
dG = G - Gd;
dB = B - Bd;

dR2 = dR.^2; 
dG2 = dG.^2; 
dB2 = dB.^2; 

sigR  = sqrt(sum(sum(dR2))/(m*n));
sigG = sqrt(sum(sum(dG2))/(m*n));
sigB = sqrt(sum(sum(dB2))/(m*n));

