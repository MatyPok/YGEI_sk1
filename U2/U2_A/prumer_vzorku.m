function [a] = prumer_vzorku(pocet)
% funkce, ktera nacte pozadovany pocet vzorku do bunkoveho pole. Vzorky
% jsou zprumerovany a vysledkem je jeden zprumerovany vzorek s o velikosti
% prvniho vzorku

pom = cell(pocet,1);


for i = 1:pocet
    soubor = ['vzor' num2str(i) '.jpg']; % generování názvu souboru
    pom{i,1} = imread(soubor); % Načti obrázek a ulož ho do buňkového pole
end

% sjednoceni velikosti podle prvniho vzorku
pom_size = size(pom{1});
for i = 1:pocet
    pom{i} = imresize(pom{i}, pom_size(1:2));
end

% prumerovani
a = zeros(pom_size(1:2));
for i = 1:pocet
    a = a + double(pom{i});
end

a = uint8(a/pocet);

out = a;

end