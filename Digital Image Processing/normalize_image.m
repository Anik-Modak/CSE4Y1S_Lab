function [normalized_img] = normalize_image(img, new_min, new_max) 
    % return double image
    
    tmp_img = double(img);
    old_min = min(tmp_img(:));
    old_max = max(tmp_img(:));

    normalized_img = (tmp_img - old_min).*((new_max-new_min)/(old_max-old_min)) + new_min;
    
end