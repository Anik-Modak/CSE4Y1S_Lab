clc;
close all;
clear all;

originalimage = imread('cameraman.jpg');
img = rgb2gray(originalimage);
img = imresize(img, [512 512]);
img = imnoise(img,'gaussian');

D0 = 10; 
n = 15;
plot_dim = ceil(sqrt(n));


subplot(plot_dim, plot_dim, 1);
imshow(img);
title('Original Image');    

[rows columns] = size(img);
fimg = fftshift(fft2(img));
[u v] = meshgrid(-(rows/2) : ((rows/2)-1), -(columns/2) : ((columns/2)-1));
D = sqrt(u.^2 + v.^2);

for i = 1 : n 
    idlf = D < D0;

    foutput_img = fimg .* idlf;
    tmp_img = ifft2(foutput_img);
    idlf_img = mat2gray(abs(tmp_img));
    
    subplot(plot_dim, plot_dim, i+1);
    imshow(idlf_img);
    title(strcat('IDLF img when D0 =  ' , int2str(D0)));
    
    D0 = D0 + 5;
end