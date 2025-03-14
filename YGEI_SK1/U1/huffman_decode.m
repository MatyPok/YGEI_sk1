function [Y] = huffman_decode(Y_encoded, code_table)

V = code_table(1,:);
C = code_table(2,:);

values = mat2cell(V,1);
codes = mat2cell(C,1);

Y_encoded = string(Y_encoded);


% prohledávání zadaného vektoru a tabulky s klíči pro dekódování
for i = 1:length(Y_encoded)
    for j = 1:length(codes{1})
        if Y_encoded(i)==codes{1}(j) % pokud v klíči nalezneme kód shodující se se zadaným, přidělíme mu hodnotu z klíče
            Y(i) = values{1}(j);
        end
    end
end

%Y_encoded = str2double(Y_encoded);

%C = str2double(codes{1});

% návrat dekódovaného vektoru
Y = str2double(Y);







end
