function [Y_encoded, code_table]=huffman(Y)
% Y_decoded = vector (double) s vektorem Y přepsaným pomocí Huffmanova
% kódování
% code_table = seřazený vektor hodnot nacházejících se ve vektoru Y a vektor svým pořadím odpovídající V s kódy pro hodnoty z Y

%% Huffmannovo kódování

% input: sekvence hodnot
% output: strom, který tvoří nové hodnoty pro znaky, v závislosti na jejich
% četnosti 

%Y = [172 126 126 126 126 126 126 126 126 195 195 21 21 21 21];

% nalezení unikátních hodnot v Y
values = unique(Y);
%counts = tabulate(Y);

% absolutní četnosti unikátních hodnot
counts = histcounts(Y, [values, max(values)+1]);

%probs = counts(:,3);
%values = num2cell(counts(:,1));

% seřazení podle četností
[probs, idx] = sort(counts);
hodnoty = values(idx);
values = num2cell(values(idx));

% codes = cell(size(values));
% codes(:) = {''}; % Inicializace prázdných řetězců pro kódy
codes = num2cell(repmat("", size(values))); % prázdná buňka pro kódy

% dokud se ve vektoru četností nachází hodnoty
while length(probs) > 1
    % vytvoření dvou uzlů o nejmenší čenosti a jejich kombinovaná četnost
    new_probs = probs(1) + probs(2);
    new_value = {[values{1}, values{2}]};

 % Aktualizace kódů (přiřaď 0 a 1 všem listům)
    for i = 1:length(values{1})
        codes{1}{i} = strcat('1', codes{1}{i});
    end
    for i = 1:length(values{2})
        codes{2}{i} = strcat('0', codes{2}{i});
    end

    % aktualizace listu
    probs = [new_probs, probs(3:end)];
    values = [new_value, values(3:end)];

    % Sloučíme kódy ze dvou listů do jednoho
    codes = [{[codes{1}, codes{2}]}, codes(3:end)];

    % opět seřadíme podle četností
    [probs,idx] = sort(probs);
    values = values(idx);

    % Aktualizace hodnot a kódů
    codes = codes(idx);
    codes;
end

% Přepsaní vektoru Y do Huffmannova kódu
for i = 1:length(Y) % Prohledávání hodnot Y
    for j = 1:length(values{1}) % Ke každé hodnotě z vektoru Y prohledáváme odpovídající ve values
        if Y(i)==values{1}(j) % pokud nalezneme odpovídající hodnotu,
            Y_encoded(i) = codes{1}(j); % přidělíme jí kód
        end
    end
end

%Y_encoded = str2double(Y_encoded);
V = cell2mat(values);
%C = str2double(codes{1});
code_table = [V;codes{1}]; % návrat tabulky s klíčemi, pro následné dekódování


end
