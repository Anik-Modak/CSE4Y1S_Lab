clc;
close all;
clear all;

originalimage = imread('cameraman.jpg');
img = rgb2gray(originalimage);
img = imresize(img, [512 512]);

dimg = im2double(img);
[rows, columns] = size(dimg);

%converting image to double 

mask_dim = 5; % mask dimention should be always odd
loop_n = floor(mask_dim/2);

% average mask
mask = ones(mask_dim, mask_dim)*(1.0/(mask_dim*mask_dim));

% padding each dimention by replicating last values
padded_img = padarray( dimg,[mask_dim mask_dim],'replicate');

% Geometric mean filter operation
gmean_img = zeros(rows, columns);
for i = (mask_dim + 1) : (rows + mask_dim)
    for j = (mask_dim + 1) : (columns + mask_dim)
        sum = 0.0;
        for ii = -loop_n : loop_n
            for jj = -loop_n : loop_n
                sum = sum + log(double(padded_img(i+ii, j+jj)));
            end
        end
        %disp(sum)
        gmean_img(i-mask_dim, j-mask_dim) = sum;
    end
end

gmean_img = exp(gmean_img).^(1.0/(mask_dim*mask_dim));
maxx = max(gmean_img(:));

imshow(uint8(normalize_image(gmean_img, 0, 255)));
m = n = 5;
g = double(img) ; 
f = exp ( imfilter ( log(g) , ones (m, n ) , ' replicate ' ) ).^(1/m*n); 

imshow(uint8(normalize_image(f, 0, 255)));

%Median Filter 
median_img = img;

% loop through image locations
for i = (mask_dim + 1) : (rows + mask_dim)
    for j = (mask_dim + 1) : (columns + mask_dim)
        
        sum = 0.0;
        im = 0;
        md_array = zeros(1,mask_dim*mask_dim);
        
        % loop for mask 
        for ii = -loop_n : loop_n
            for jj = -loop_n : loop_n
                im = im + 1;
                md_array(1,im) = padded_img(i+ii, j+jj);
            end
        end
        median_img(i-mask_dim, j-mask_dim) = (median(md_array));
    end
end


%%Plot Images
subplot(2, 2, 1)
imshow(img);
title('Original Image');

subplot(2,2,2)
imshow(uint8(avg_img));
title('Average Image');

subplot(2,2,3)
imshow(uint8(median_img));
title('Median Image');