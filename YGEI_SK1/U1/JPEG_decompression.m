function [] = JPEG_decompression(Y_t,CB_t,CR_t)


%%
% JPEG decompression
for i = 1:8:m-7
    for j = 1:8:n-7

        % Create sub-matrices
        Ys = Y_t(i:i+7,j:j+7);
        CBs = CB_t(i:i+7,j:j+7);
        CRs = CR_t(i:i+7,j:j+7);


        % Apply IDCT and DeQuantisate
        Y_idct = my_idct(Ys.*Qc);
        CB_idct = my_idct(CBs.*Qy);
        CR_idct = my_idct(CRs.*Qy);

        % Overwriting tiles with compressed ones

        Y(i:i+7,j:j+7) = Y_idct; CB(i:i+7,j:j+7) = CB_idct; CR(i:i+7,j:j+7) = CR_idct;

    end
end


%%
% Conversion back to RGB

Rd = Y + 1.4020*(CR-128);
Gd = Y - 0.3441*(CB-128) - 0.7141*(CB-128);
Bd = Y + 1.7720*(CB-128) - 0.001*(CB-128);

% convert to uint8
Rd = uint8(Rd); Gd = uint8(Gd); Bd = uint8(Bd);

% Show the decompressed image

Ras_decomp(:,:,1) = Rd; Ras_decomp(:,:,2) = Gd; Ras_decomp(:,:,3) = Bd;

imshow(Ras_decomp)

%%


%%
% define inverse DCT function

function Rt = my_idct(R)
    Rt=R;
    % Output raster: rows
    for x=0:7

        % Output raster: columns
        for y=0:7

            F = 0;
            % Input raster: rows
            for u=0:7
                if u==0
                    Cu = sqrt(2)/2;
                else
                    Cu = 1;
                end
                % Input raster: columns
                for v=0:7
                        if v==0
                            Cv = sqrt(2)/2;
                        else
                            Cv = 1;
                        end

                    F = F + (1/4)*Cu*Cv*(R(u+1,v+1)*cos((2*x+1)*u*pi/16)*cos((2*y+1)*v*pi/16));

                end
            end

            % Output raster
            Rt(x+1,y+1) = F;

        end

    end

end



end