clc;
close all;
clear all; 

originalimage = imread('fingerprint.png'); 
img = rgb2gray(originalimage);
I = imresize(img,[512,512]);
   
subplot(2, 2, 1),  
imshow(I); 
title('Original image'); 
  
% Dilated Image 
se = strel('rectangle',[5,5]);
erode = imerode(I, se); 

% Boundary extraction  
output = I-erode;
subplot(2, 2, 2),  
imshow(output); 
title('Boundary of the image'); 