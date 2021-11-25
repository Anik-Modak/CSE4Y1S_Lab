clc;
close all;
clear all; 

originalimage = imread('fingerprint.png'); 
img = rgb2gray(originalimage);
I = imresize(img,[512,512]);
   
subplot(2, 3, 1),  
imshow(I); 
title('Original image'); 
  
%Structuring Elements
se = strel('rectangle',[20,20]); 

%Opening
opening  = imopen(I, se); 
subplot(2, 3, 2),  
imshow(opening); 
title('Opened image'); 
  
%Closeing
closing  = imclose(I, se); 
subplot(2, 3, 3),  
imshow(closing); 
title('Closed image'); 