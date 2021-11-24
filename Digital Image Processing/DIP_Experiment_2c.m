clc;
close all;
clear all;

originalimage = imread('cameraman.jpg');
img = rgb2gray(originalimage);
img = imresize(img, [512 512]);

%% difference between orginal and the image obtained by last three bits
[rows, columns] = size(img);
mask = 224; %3bit mask

three_msb_img = bitand(img, mask);

difference_image = imabsdiff(img, three_msb_img);

%% Plot Images
subplot(3,1,1);
imshow(img);
title('Original Image');

subplot(3,1,2);
imshow(three_msb_img);
title('Three MSB image');

subplot(3,1,3);
imshow(difference_image);
title('Difference Image');