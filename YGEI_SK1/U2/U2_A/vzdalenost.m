function [d] = vzdalenost(A,B)

for i = 1:size(A,1)
    d = sqrt((A(i,1) - B(i,1))^2 + (A(i,2) - B(i,2))^2);

end

end