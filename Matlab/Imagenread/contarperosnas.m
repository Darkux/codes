clc;clear variables; close all;
I = imread('Familia.jpg');

figure(1);imshow(I);title('Deteccion rostros')

%caras
Face = vision.CascadeObjectDetector();
Caja = step(Face, I);
for j =1:size(Caja,1)
    rectangle('Position',Caja(j,:),'edgecolor','b');
end
hold off
%nariz
figure(2);imshow(I);title('Deteccion nariz')
NARIZ = vision.CascadeObjectDetector('Nose', 'MergeThreshold',16);
Caja2 = step(NARIZ, I);
for j =1:size(Caja2,1)
    rectangle('Position',Caja2(j,:),'edgecolor','y');
end
hold off