function Rt = myDCT_inv(R)
Rt = R;

for x = 0:7

    for y = 0:7
        F = 0;
        for u = 0:7
    % nastavovani hodnot pro C(u)
             if u == 0
                Cu = sqrt(2)/2;
            else
                Cu = 1;
             end
        
   

         %vysledny rastr: sloupce
            for v = 0:7
                % nastavovani hodnot pro  C(v)
                if v == 0
                   Cv = sqrt(2)/2;
                else
                   Cv = 1;
                end
                % ted ten hnusnej predpis funkce
                F = F + 1/4*Cu*Cv*(R(u+1,v+1)*cos((2*x + 1)*u*pi/16)*cos((2*y+1)*v*pi/16));   %R(x+1,y+1) uprava pro indexovani v matlabu
            end
        end
        Rt(x+1,y+1) = F;
    end
end
     
end