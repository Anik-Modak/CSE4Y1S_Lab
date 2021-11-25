clc;
close all;

originalimage = imread("cameraman.jpg");
img = rgb2gray(originalimage);
img = imresize(img, [512 512]);

[row, column] = size(img);
grayLevels = 8;
plot_dim = ceil(sqrt(grayLevels));

subplot(plot_dim, plot_dim, 1);
imshow(im2double(img));
title(strcat('Intensity Level : ',int2str(grayLevels)));

%% Decrease it intensity level resolution by one bit
tmp_img = double(zeros([row column]));
for i = 1 : grayLevels-1
    tmp = 0;
    for j = 1 : row
        for k = 1 : column
            tmp = floor(img(j,k)/(2^i));
            tmp_img(j,k) = tmp/(2^grayLevels/2^i);
        end
    end
    subplot(plot_dim, plot_dim, i+1);
    imshow(tmp_img);
    title(strcat('Intensity Level : ',int2str(grayLevels-i)));
end