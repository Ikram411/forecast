clear all;
close all;
clc;

file = fopen('data\in.csv','r');
X = fscanf(file, '%d');
M = X(1);
p = X(2);
D = X(3);
q = X(4);
X = X(5:end);
N = length(X);

A = arima(p,D,q); 
A = estimate(A, X, 'print', false);
[Y YMSE] = forecast(A, M, 'Y0', X);

fclose(file);
file = fopen('data\out.csv','w');
fprintf(file, '%f\n', Y);
fclose(file);

