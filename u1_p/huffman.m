function [Y_encoded, V, C]=huffman(Y)
% Y_decoded = vektor (double) s vektorem Y přepsaným pomocí Huffmanova
% kódování
% V = seřazený vektor hodnot nacházejících se ve vektoru Y
% C = vektor svým pořadím odpovídající V s kódy pro hodnoty z Y

%% Huffmannovo kódování

% input: sekvence hodnot
% output: strom, který tvoří nové hodnoty pro znaky, v závislosti na jejich
% četnosti 

%Y = [172 126 126 126 126 126 126 126 126 195 195 21 21 21 21];

values = unique(Y);
%counts = tabulate(Y);
counts = histcounts(Y, [values, max(values)+1]);

%probs = counts(:,3);
%values = num2cell(counts(:,1));
[probs, idx] = sort(counts);
hodnoty = values(idx);
values = num2cell(values(idx));

% codes = cell(size(values));
% codes(:) = {''}; % Inicializace prázdných řetězců pro kódy
codes = num2cell(repmat("", size(values))); % prázdná buňka pro kódy

while length(probs) > 1
    % create two nodes with the smallest probalities and their summed
    % probability
    new_probs = probs(1) + probs(2);
    new_value = {[values{1}, values{2}]};

 % Aktualizace kódů (přiřaď 0 a 1 všem listům)
    for i = 1:length(values{1})
        codes{1}{i} = strcat('1', codes{1}{i});
    end
    for i = 1:length(values{2})
        codes{2}{i} = strcat('0', codes{2}{i});
    end

    % Actualize list
    probs = [new_probs, probs(3:end)];
    values = [new_value, values(3:end)];

    % Sloučíme kódy ze dvou listů do jednoho
    codes = [{[codes{1}, codes{2}]}, codes(3:end)];

    % sort in respect to probabilities
    [probs,idx] = sort(probs);
    values = values(idx);

    % Aktualizace hodnot a kódů
    codes = codes(idx);
end

for i = 1:length(Y)
    for j = 1:length(values{1})
        if Y(i)==values{1}(j)
            Y_encoded(i) = codes{1}(j);
        end
    end
end

Y_encoded = str2double(Y_encoded);
V = cell2mat(values);
C = str2double(codes{1});


end
