function [LL, LH, HL, HH] = DWT(obraz)

    % Diskretni vlnkova transformace pro 2D obraz
    % Pouziti Haarovy vlnky

    %% Filtry (Haarova vlna)
    low = [1/sqrt(2), 1/sqrt(2)];   % Low-pass filtr
    high = [1/sqrt(2), -1/sqrt(2)]; % High-pass filtr

    %% Filtrace radku
    L = conv2(obraz, low', 'same');  % Low-pass filtr na radky
    H = conv2(obraz, high', 'same'); % High-pass filtr na radky

    %% vezmu kazdy druhy radek
    L = L(1:2:end, :); % Zachovat každý druhý řádek
    H = H(1:2:end, :); % Zachovat každý druhý řádek

    %% Filtrace sloupcu
    LL = conv2(L, low, 'same');  % Low-pass filtr na sloupce
    LH = conv2(L, high, 'same'); % High-pass filtr na sloupce
    HL = conv2(H, low, 'same');  % Low-pass filtr na sloupce
    HH = conv2(H, high, 'same'); % High-pass filtr na sloupce

    %% kazdy druhy sloupec
    LL = LL(:, 1:2:end);
    LH = LH(:, 1:2:end);
    HL = HL(:, 1:2:end);
    HH = HH(:, 1:2:end);
end
