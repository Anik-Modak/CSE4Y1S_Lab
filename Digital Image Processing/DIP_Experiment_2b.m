clc;
close all;
clear all;

originalimage = imread('cameraman.jpg');
img = rgb2gray(originalimage);
img = imresize(img, [512 512]);

double_img = im2double(img);
[rows, columns] = size(img);

power_img = zeros(rows, columns);
ilog_img = zeros(rows, columns);

L = 8; % intensity level
c = (L - 1)/log(L) ;
factor = input('value of gamma : ');

for i = 1 : rows
    for j = 1 : columns
        power_img(i,j) = c*double_img(i,j)^factor;
        %log_img(i,j) = c*log(1.0 + double_img(i,j));
        ilog_img(i,j) = exp(double_img(i,j)).^(1/c) - 1; %inverse log
    end
end

%difference
new = imabsdiff(power_img, ilog_img);

%% Ploat Images 
subplot(4,2,1);
imshow(img);
title('Original Image');

subplot(4,2,2);
imhist(img);
title('Original img Hist');

subplot(4,2,3);
imshow(power_img);
title('PowerLaw Transformed Image');

subplot(4,2,4);
imhist(power_img);
title('PowerLaw Hist');

subplot(4,2,5);
imshow(ilog_img);
title('Inverse Log Transformed Hist');

subplot(4,2,6);
imhist(ilog_img);
title('Inverse Log Transformed Image');

subplot(4,2,7);
imshow(new);
title('Difference between two Images');

subplot(4,2,8);
imhist(new);
title('Differentiation Hist');