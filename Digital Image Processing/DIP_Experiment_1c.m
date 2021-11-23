clc;
close all;

originalimage = imread('cameraman.jpg');
resizedimage = imresize(originalimage, [512 512]);
img = resizedimage;
subplot(3, 1, 1);
imshow(img);
title('Grayscale Image');

subplot(3, 1, 2);
imhist(img);
title('Histogram');

%% Threshold operation
threshold = input('Enter Threshhold value: ');
output_img = img;
[rows, columns] = size(img);

for i = 1 : rows
    for j = 1 : columns
        if img(i,j) >= threshold
            output_img(i,j) = 255;
        else
            output_img(i,j) = 0;
        end
    end
end

%% Plot images imhist(output_img)
subplot(3, 1, 3);
imshow(output_img);
title('After Thresholding the Image');