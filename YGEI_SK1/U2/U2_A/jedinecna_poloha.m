function [Q] = jedinecna_poloha(A, okoli)
    % VSTUP:
    %   A = matice, ve které budeme vyhledávat unikátní pozici pro opakující se jev
    %   okoli = jaké okolí chce zohlednit
    % VYSTUP:
    %   Q = matice, kde se zachovala jedinečná poloha

    % Nejprve seřadím body podle prvního sloupce
    A = sortrows(A,1);
    
    
    Q = A(1,:);
   
    for i = 2:size(A,1)
        % aktuální bod z A
        pom = A(i, :);
        
        % Spočítám vzdálenost mezi aktualni a všemi body v Q
        vzd = sqrt(sum((Q - pom).^2, 2));
        
        % Pokud žádná vzdálenost není menší než zadané okolí, přidáme bod do Q
        if all(vzd > okoli)
            Q = [Q; pom]; 
        end
    end
end
