clc;
close all;
clear all;

originalimage = imread('cameraman.jpg');
img = rgb2gray(originalimage);
img = imresize(img, [512 512]);

[rows, columns] = size(img);
prompt = 'What is the intensity value? ';
enhancement = input(prompt);

prompt = 'What is the range? ';
left = input(prompt);
right = input('');

tmp_img = uint16(img);

for i = 1 : rows
    for j = 1 : columns
        if left <= img(i,j) && img(i,j) <= right
            tmp_img(i,j) = img(i,j) + enhancement;           
        end
    end
end

%% Normalization
_min = min(tmp_img(:));
_max = max(tmp_img(:));
normalized_img = double(tmp_img - _min)./double(_max-_min);
output_img = uint8(normalized_img*255);

%% Ploat Images 
subplot(2,2,1);
imshow(img);
title('Original Image');

subplot(2,2,2);
imhist(img);
title('Original Image Hist');

subplot(2,2,3);
imshow(output_img);
title('Range intensity enhancement');

subplot(2,2,4);
imhist(output_img);
title('Output Image Hist');