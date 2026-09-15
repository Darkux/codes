clc;
clear variables;
close all;

I = imread('lena.jpg');
Igray = rgb2gray(I);
CR = I(:,:,1) * 1.5; 
CV = I(:,:,2) * 0.8; 
CA = I(:,:,3) * 0.2;
figure(1)
subplot(121);imshow(I);title('ORIGINAL')
subplot(122);imshow(Igray);title('Esacala grises')
figure(2)
subplot(221);imshow(Igray);title('Esacala grises')
subplot(222);imshow(CR);title('Esacala ROJO')
subplot(223);imshow(CV);title('Esacala VERDE')
subplot(224);imshow(CA);title('Esacala AZUL')
Rojo = I;Rojo(:,:,2) = 0;Rojo(:,:,3) = 0;
verde = I;verde(:,:,1) = 0;verde(:,:,3) = 0;
azul = I;azul(:,:,1) = 0;azul(:,:,2) = 0;
figure(3)
subplot(221);imshow(I);title('ORIGINAL')
subplot(222);imshow(Rojo);title('ROJO')
subplot(223);imshow(verde);title('VERDE')
subplot(224);imshow(azul);title('AZUL')
figure(4)
espDI=fliplr(I);
espAB=flipud(I);
Girar=imrotate(I, 45);
subplot(221);imshow(I);title('ORIGINAL')
subplot(222);imshow(espDI);title('Espejo')
subplot(223);imshow(espAB);title('Ariva')
subplot(224);imshow(Girar);title('Griro')
  

