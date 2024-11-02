function Y=zig_zag(X)
    %X = [1 2 3 4; 5 6 7 8; 9 10 11 12; 13 14 15 16];

    [m,n]=size(X);
    Y = [];

    Y(end+1)=X(1,1);
    j = 1; i = 1;
    change_dir = 0;

    while length(Y) < m*n

        if change_dir == 0
            j = j + 1;
        elseif change_dir >= 1
            i = i + 1;
        end

        % if we are at the end of matrix, we save the last element in Y and
        % break the cycle
        if length(Y) == m*n - 1
            Y(end+1) = X(i,j);
            break
        end 

        if j == n
            change_dir = change_dir + 1;
        end

        % moving alongside a sub-diagonal in SW direction
        % creating sub array
        sub_array = X(i:j,i:j);
        % fliping it right to left
        sub_array = fliplr(sub_array);

        Y(end+1:end+length(sub_array)) = diag(sub_array);

        if change_dir <= 1
            i = j;
            j = 1;
        elseif change_dir > 1
            j = i;
            i = m ;
        end

        % changing direction

        if change_dir == 0
            i = i + 1;
        elseif change_dir >= 1
            j = j + 1;
        end

        % if we are at the end of matrix, we save the last element in Y and
        % break the cycle
        if length(Y) == m*n - 1
            Y(end+1) = X(i,j);
            break
        end 


        if i == m
            change_dir = change_dir + 1;
        end

        % moving alongside a sub-diagonal in NE direction
        % creating sub array
        sub_array = X(j:i,j:i);
        % fliping it tight to left
        sub_array = flipud(sub_array);
           
        Y(end+1:end+length(sub_array)) = diag(sub_array);

        if change_dir <= 1
            j = i;
            i = 1;
        elseif change_dir > 1
            i = j;
            j = n;
        end

    end

end