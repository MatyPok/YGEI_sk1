function [Y_t,CB_t,CR_t] = JPEG_compression(Raster,compression_factor)


%clc; clear; format long g;
%%
% load images as matrices (load does not work, imread() needed)
%pic1 = imread("Image1.bmp");
pic2 = imread(Raster);

%%
% Compression factor
if nargin==2
    q = compression_factor;
else
    q = 25;
end

%%
% divide pistures into RGB parts
%R1=pic1(:,:,1); G1=pic1(:,:,2); B1=pic1(:,:,3);
R=double(pic2(:,:,1)); G=double(pic2(:,:,2)); B=double(pic2(:,:,3));

%%
% transformation to YCC
% Y1 = 0.2990*R1 + 0.5870*G1 + 0.1140*B1;
% CB1 = -0.1687*R1 - 0.3313*G1 + 0.*B1 + 128;
% CR1 = 0.5*R1 - 0.4187*G1 - 0.0813*B1 + 128;

Y = 0.2990*R + 0.5870*G + 0.1140*B;
CB = -0.1687*R - 0.3313*G + 0.5*B + 128;
CR = 0.5*R - 0.4187*G - 0.0813*B + 128;


%%
% quantization matrix

Qy = [16    11    10    16    24    40    51    61
      12    12    14    19    26    58    60    55
      14    13    16    24    40    57    69    56
      14    17    22    29    51    87    80    62
      18    22    37    56    68   109   103    77
      24    35    55    64    81   104   113    92
      49    64    78    87   103   121   120   101
      72    92    95    98   112   100   103    99 ];

% Update Qy according to q 
Qy = 50*Qy/q;

% chrominance matrix

Qc = [17   18   24   47   99   99   99   99
      18   21   26   66   99   99   99   99
      24   26   56   99   99   99   99   99
      47   66   99   99   99   99   99   99
      99   99   99   99   99   99   99   99
      99   99   99   99   99   99   99   99
      99   99   99   99   99   99   99   99
      99   99   99   99   99   99   99   99];

% Update Qc according to q
Qc = 50*Qc/q;

%%
% Process input raster by sub-matrices

[m,n] = size(R);

for i = 1:8:m-7
    for j = 1:8:n-7

        % Create sub-matrices
        Ys = Y(i:i+7,j:j+7);
        CBs = CB(i:i+7,j:j+7);
        CRs = CR(i:i+7,j:j+7);

        % Apply DCT
        Y_dct = my_dct(Ys);
        CB_dct = my_dct(CBs);
        CR_dct = my_dct(CRs);

        % Quantisation
        Y_Q = Y_dct./Qc;
        CB_Q = CB_dct./Qy;
        CR_Q = CR_dct./Qy;

        % Y_Q = Y_dct;
        % CB_Q = CB_dct;
        % CR_Q = CR_dct;


        % Round (int)
        
        Y_Qr = round(Y_Q); CB_Qr = round(CB_Q); CR_Qr = round(CR_Q);

        % Overwriting tiles with compresseds ones

        Y_t(i:i+7,j:j+7) = Y_Qr; CB_t(i:i+7,j:j+7) = CB_Qr; CR_t(i:i+7,j:j+7) = CR_Qr;
        
    end
end


%%
% define DCT function

function Rt = my_dct(R)
    Rt=R;
    % Output raster: rows
    for u=0:7
        if u==0
            Cu = sqrt(2)/2;
        else
            Cu = 1;
        end

        % Output raster: columns
        for v=0:7
    
            if v==0
                Cv = sqrt(2)/2;
            else
                Cv = 1;
            end

            F = 0;
            % Input raster: rows
            for x=0:7
                % Input raster: columns
                for y=0:7
                    F = F + (1/4)*Cu*Cv*(R(x+1,y+1)*cos((2*x+1)*u*pi/16)*cos((2*y+1)*v*pi/16));
                end
            end

            % Output raster
            Rt(u+1,v+1) = F;

        end

    end

end




end