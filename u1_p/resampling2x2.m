function [B] = resampling2x2(A)
% A = matice, kterou chceme prevzorkovat
% B = prevzorkovana matice
% prevozorkovani probiha pomoci submatic 2*2 pixelu
%podminkou je, aby matice mela sudy pocet sloupcu a radku

[r, s] = size(A);
B = ones(r,s);
for i = 1:2:r-1 % radky

    for j = 1:2:s-1 % sloupce

        A_sub = A(i:i+1,j:j+1);
        prumer = mean(mean(A_sub)); % vypocet prumerne hodnoty submatice
        pom = ones(size(A_sub,1),size(A_sub,2))*prumer; % vytvoreni pomocne submatice, ktera ma vsude prumernou hodnotu
        B(i:i+1,j:j+1) = pom; % prevzorkovani podle vysledku submatice

    end


end


end