function A = inv_zig_zag(a,m,n)


%% Normální zig zag pro vytvoření vektorů s indexy
x = round(rand(m,n).*10);
%x = [1 2 3 4; 5 6 7 8; 9 10 11 12; 13 14 15 16];
[m,n] = size(x);
y = [];    % This will store the zigzagged values
k = [];    % This will store the (i, j) indices of the elements in zigzag order

% First element
y(end+1) = x(1,1);
k(end+1, :) = [1, 1];  % Store the index of X(1,1) as [i, j]
j = 1; i = 1;
change_dir = 0;

while length(y) < m * n

    if change_dir == 0
        j = j + 1;
    elseif change_dir >= 1
        i = i + 1;
    end

    % If we are at the end of the matrix, save the last element and break the loop
    if length(y) == m * n - 1
        y(end+1) = x(i,j);
        k(end+1, :) = [i, j];  % Store the (i, j) index
        break;
    end 

    if j == n
        change_dir = change_dir + 1;
    end

    % Moving alongside a sub-diagonal in SW direction
    sub_array = x(i:j, i:j);
    sub_array = fliplr(sub_array);
    diag_elements = diag(sub_array);

    % Append the diagonal elements to Y
    y(end+1:end+length(diag_elements)) = diag_elements;

    % Find and append the corresponding (i, j) indices to k
    for d = 1:length(diag_elements)
        row = i + d - 1;
        col = j - d + 1;
        k(end+1, :) = [row, col];  % Store the (i, j) index
    end

    if change_dir <= 1
        i = j;
        j = 1;
    elseif change_dir > 1
        j = i;
        i = m;
    end

    % Changing direction
    if change_dir == 0
        i = i + 1;
    elseif change_dir >= 1
        j = j + 1;
    end

    if length(y) == m * n - 1
        y(end+1) = x(i,j);
        k(end+1, :) = [i, j];  % Store the (i, j) index
        break;
    end

    if i == m
        change_dir = change_dir + 1;
    end

    % Moving alongside a sub-diagonal in NE direction
    sub_array = x(j:i, j:i);
    sub_array = flipud(sub_array);
    diag_elements = diag(sub_array);

    % Append the diagonal elements to Y
    y(end+1:end+length(diag_elements)) = diag_elements;

    % Find and append the corresponding (i, j) indices to k
    for d = 1:length(diag_elements)
        row = i - d + 1;
        col = j + d - 1;
        k(end+1, :) = [row, col];  % Store the (i, j) index
    end

    if change_dir <= 1
        j = i;
        i = 1;
    elseif change_dir > 1
        i = j;
        j = n;
    end

end

%%
% Vytvoření matice z vektoru hodnot a matice indexů

A = zeros(m,n);
for l = 1:length(k)
    A(k(l,1),k(l,2))=a(l);
end



end