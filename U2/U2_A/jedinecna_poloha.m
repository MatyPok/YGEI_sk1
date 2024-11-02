function  [Q] = jedinecna_poloha(A,okoli)
% VSTUP:
%   A = matice, ve ktere budeme vyhledavat unikatni pozici pro opakujici se
%   jev
%   okoli = jake okoli chce zohlednit
% VYSTUP:
%   Q = matice, kde se zachovala jedinecna poloha
%
% vypocet je realizovan pomoci vzdalenosti dvou sousednich bodu.

A = sortrows(A,1);

r = size(A,1);
Q = A(1,:);

for i = 1:r-1
    if vzdalenost(A(i,:), A(i+1,:)) > okoli
        Q = cat(1,Q,A(i+1,:));
    end
end
end