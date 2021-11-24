clc;
close all;
clear all;

originalimage = imread('cameraman.jpg');
img = rgb2gray(originalimage);
img = imresize(img, [512 512]);
img = imnoise(img,'gaussian');

D0 = 150;
[rows, columns] = size(img);
fimg = fftshift(fft2(img));
[u, v] = meshgrid(-(rows/2) : ((rows/2)-1), -(columns/2) : ((columns/2)-1));
D = sqrt(u.^2 + v.^2); 

bwlf = 1./ (1.+ ((D./ D0).^(2*4)));
foutput_img = fimg .* bwlf;
tmp_img = ifft2(foutput_img);
butter_img = mat2gray(abs(tmp_img));   

glf = exp(-((D.*D)./(2.*D0.^2)));
foutput_img = fimg .* glf;
tmp_img = ifft2(foutput_img);
gaussian_img = mat2gray(abs(tmp_img)); 

%%Plot Images
subplot(2, 2, 1);
imshow(img);
title('gaussian noise Image');

subplot(2, 2, 2);
imshow(butter_img);
title('Butterworth filtered image');

subplot(2, 2, 3)
imshow(gaussian_img);
title('Gaussian filtered image');

subplot(2, 2, 4)
imshow(imabsdiff(gaussian_img, butter_img).*200);
title('Difference image');