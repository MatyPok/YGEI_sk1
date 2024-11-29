clc; clear; format long g;

N = 50;

a = 1.5;
b = round(rand(1,2)*10);

A = randn(N,2);
B = A.*a + b;
C = A - b.*[-1,1];


plot(A(:,1),A(:,2),'.',B(:,1),B(:,2),'.',C(:,1),C(:,2),'.')

M=[A;B;C];

save('data.mat','M')