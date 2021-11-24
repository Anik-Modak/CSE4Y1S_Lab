clc;
close all;
clear all;

originalimage = imread('cameraman.jpg');
img = rgb2gray(originalimage);
img = imresize(img, [512 512]);
img = imnoise(img,'gaussian');

D0=10;
[rows columns] = size(img);
fimg = fftshift(fft2(img));

fimg1 = fftshift(fft2(ori_img));

[u v] = meshgrid(-(rows/2) : ((rows/2)-1), -(columns/2) : ((columns/2)-1));
D = sqrt(u.^2 + v.^2);

ghf = 1.-exp(-((D.*D)./(2.*D0.^2)));
foutput_img = fimg .* ghf;
tmp_img = ifft2(foutput_img);
gaussian_hf_img = mat2gray(abs(tmp_img)); 

foutput_img_ori = fimg1 .* ghf;
tmp_img_ori = ifft2(foutput_img_ori);
gaussian_hf_img_ori = mat2gray(abs(tmp_img_ori));   

idhf = D > D0;
foutput_img = fimg .* idhf;
tmp_img = ifft2(foutput_img);
ideal_hf_img = mat2gray(abs(tmp_img));

idhf = D > D0;
foutput_img_ori = fimg1 .* idhf;
tmp_img_ori = ifft2(foutput_img_ori);
ideal_hf_img_ori = mat2gray(abs(tmp_img_ori));

%%Plot Images    
subplot(2,3,1);
imshow(ori_img);
title('original Image');
    
subplot(2,3,2);
imshow(gaussian_hf_img_ori);
title('Gaussian High Pass Image');

subplot(2,3,3);
imshow(ideal_hf_img_ori);
title('Ideal High Pass Image');

subplot(2,3,4);
imshow(img);
title('noisy original Image');
    
subplot(2,3,5);
imshow(gaussian_hf_img);
title('noisy Gaussian High Pass Image');

subplot(2,3,6);
imshow(ideal_hf_img);
title('noisy Ideal High Pass Image');