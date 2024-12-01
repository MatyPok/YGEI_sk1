clc; clear; close all; format long g

figure(1)
[x,y] = getpts;
M = [x,y];
save body.mat M