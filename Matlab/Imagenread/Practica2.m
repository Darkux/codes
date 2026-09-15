clc;clear variables; close all;
I = imread('coins.png');
T = graythresh(I);
BIN = imbinarize(I,T);
BIN2 = imfill(BIN,'holes');
[L m] = bwlabel(BIN2);
figure(1);
subplot(221);imshow(I);title('Imagen original')
subplot(222);imshow(BIN);title('Imagen binarizada')
subplot(223);imshow(BIN2);title('Imagen binarizada')

% Propiedad de region
PROP = regionprops(L,'all');

SUMA =0;
figure(2);imshow(I);hold on;

for n =1: size(PROP,1)
    cent = PROP(n).Centroid;
    x= cent(1); y= cent(2);
    
    if PROP(n).Area>2000
        text(x-10,y,'5 c')
        SUMA =SUMA+5;
    else
        text(x-10,y,'10 c')
        SUMA =SUMA+10;
    end
    
end

hold off
title(['Toltal De Money= ',num2str(SUMA),'centavos'])