function writekinect(path, filename, data, frames)

fid = fopen( fullfile(path,[filename '.txt']), 'w' );
for k=1:size(data,1)
    fprintf(fid,'%d',frames(k));
    fprintf(fid, ' %.4f', data(k,:));
    fprintf(fid, '\n');
end

fclose(fid);

end