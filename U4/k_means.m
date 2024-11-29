clc; clear; format long g;

%%

M = load('data.mat');

M = cell2mat(struct2cell(M));

N = length(M);

x = M(:,1); y = M(:,2);
% figure(1)
% plot(x,y,'.')

%%

% Pocet shluku:
n = input('Pocet shluku: ');

%

min_M = min(min(M))*0.9;
max_M = max(max(M))*0.9;

t_x = mean(x); t_y = mean(y);

xs = linspace(min_M, max_M, n)';
ys = xs;
xs = xs + t_x; ys = ys + t_y;

S = [xs,ys];

% figure(2)
% plot(x,y,'.',xs,ys,'o')



%%
% kdy jsem spoko
podminka = 0.1;
dS = 1;
while any(dS > podminka) % dokud nejsem spoko
    L = zeros(N,1);
    d2 = zeros(n,1);
    
    xs = S(:,1); ys = S(:,2);
    
    % vzdalenost kazdeho bodu od kazdeho stredu
    for i = 1:N
        for j = 1:n
            d2(j) = ( x(i) - S(j,1) )^2 + ( y(i) - S(j,2) )^2;
        end
        [d_min,L(i)]=min(d2);
    end
    
    % posunut stredu S do teziste sveho shluku
    
   nove_S = zeros(n,2); 
    for j = 1:n
        k = find(L==j);
        nove_S(j,:) = mean(M(k,:));
    end
    
    % velikost posunu stredu
    dS = ( nove_S(:,1) - S(:,1) ).^2 + ( nove_S(:,2) - S(:,2) ).^2;
    
    S = nove_S;
    

end

hold on
scatter(x,y,[],L,'filled')
scatter(S(:,1),S(:,2),'r')
hold off





















