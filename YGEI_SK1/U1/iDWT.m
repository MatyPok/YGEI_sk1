function [A] = iDWT(LL, LH, HL, HH)
    % Inverzni diskrétní vlnková transformace (IDWT) pro Haarovu vlnku
    % Vstup: LL, LH, HL, HH 
    % Výstup: A - rekonstruovaná matice

    %% zpetne rozsireni matice na puvodni velikost, nejpre radky
    L = zeros(size(LL, 1) * 2, size(LL, 2)); % Zvětšíme počet řádků
    H = zeros(size(HL, 1) * 2, size(HL, 2));

    % LL/LH do lichých a sudých řádků
    L(1:2:end, :) = LL; % Liché řádky dostanou LL
    L(2:2:end, :) = LH; % Sudé řádky dostanou LH

    % HL/HH do lichých a sudých řádků
    H(1:2:end, :) = HL; % Liché řádky dostanou HL
    H(2:2:end, :) = HH; % Sudé řádky dostanou HH

    %% ted sloupce
    A = zeros(size(L, 1), size(L, 2) * 2); % Zvětšíme počet sloupců
    A(:, 1:2:end) = L; 
    A(:, 2:2:end) = H; 
    %% slozeni obrazu
    [r, s] = size(A);
    vystup = zeros(r, s);

    for i = 1:2:r-1
        for j = 1:2:s-1
            % Rekonstrukce původních hodnot
            vystup(i, j) = (A(i, j) + A(i, j + 1) + A(i + 1, j) + A(i + 1, j + 1)) / 2;
            vystup(i, j + 1) = (A(i, j) - A(i, j + 1) + A(i + 1, j) - A(i + 1, j + 1)) / 2;
            vystup(i + 1, j) = (A(i, j) + A(i, j + 1) - A(i + 1, j) + A(i + 1, j + 1)) / 2;
            vystup(i + 1, j + 1) = (A(i, j) - A(i, j + 1) - A(i + 1, j) + A(i + 1, j + 1)) / 2;
        end
    end
    A = vystup; 
end
