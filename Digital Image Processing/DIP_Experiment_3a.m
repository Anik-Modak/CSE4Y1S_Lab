clc;
close all;
clear all;

originalimage = imread('cameraman.jpg');
img = rgb2gray(originalimage);
image = imresize(img, [512 512]);

subplot(2,2,1);
imshow(image);
title('input image');

image_noise=imnoise(image,'salt & pepper',0.02);
subplot(2,2,2);
imshow(image_noise);
title('noise image');

median_image = medfilt2(image_noise,[5,5]);
subplot(2,2,3);
imshow(median_image);
title('after median image');

averagef = fspecial('average',[3,3]);
spatial_image = imfilter(image_noise,averagef);
subplot(2,2,4);
imshow(spatial_image);
title('after average partial filter');