clc;
close all;
clear all; 

originalimage = imread('fingerprint.png'); 
img = rgb2gray(originalimage);
I = imresize(img,[512,512]);
 
subplot(2, 3, 1), 
imshow(I*255); 
title('Original image');

%Structuring Elements
se = strel('rectangle',[3,3]); 
  
% Dilated Image  
dilate = imdilate(I, se); 
subplot(2, 3, 2),  
imshow(dilate*255); 
title('Dilated image'); 
  
% Eroded image 
erode = imerode(I, se); 
subplot(2, 3, 3),  
imshow(erode*255); 
title('Eroded image'); 