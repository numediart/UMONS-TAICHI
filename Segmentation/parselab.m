function [index, label] = parselab(filepath)

fileID = fopen(filepath);
tmp = textscan(fileID, '%f %s');
index = tmp{1};
label = tmp{2};
fclose(fileID);

end