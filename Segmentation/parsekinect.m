function [frames, data] = parsekinect(filepath)

fileID = fopen(filepath);
formatspec = ['%f' repmat(' %f %f %f',1,25) ];%timestamp and 25 3D locations
tmp = textscan(fileID, formatspec);
frames = tmp{1};
data = cell2mat(tmp);
data = data(:,2:end);
fclose(fileID);

end