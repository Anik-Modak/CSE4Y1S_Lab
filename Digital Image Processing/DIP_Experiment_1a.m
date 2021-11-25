clc;
close all;

originalimage = imread("cameraman.jpg");
img = rgb2gray(originalimage);
img = imresize(img, [512 512]);

[row, column] = size(img);

number_of_image = 8;
plot_dim = ceil(sqrt(number_of_image));

%% Decrease spatial resolution by half every time
for i = 1 : number_of_image
    
    tmp = imresize(img, [row column]);
    subplot(plot_dim, plot_dim, i);
    imshow(tmp);
    
    title(strcat(int2str(row), 'X', int2str(column)));
    axis on;
    
    row = row/2;
    column = column/2;
end
