function ret = checklabels(filenames)

ret = 0;

if iscell(filenames)
    nfiles = size(filenames,2);
elseif isstruct(filenames)
    nfiles = size(filenames,1);
else
    nfiles = 1;
end

for f = 1:nfiles
    
    %%% Load file
    if iscell(filenames)
        filename = filenames{f}(1:end-4);
    elseif isstruct(filenames)
        filename = filenames(f).name(1:end-4);
    else
        filename = filenames(1:end-4);
    end
    
    %disp(['Checking file: ' filename]);
    
    %%% Parse labels
    [index, label] = parselab([filename '.lab']);
    
    %%% Initialize parameters
    nseg = size(index,1);
    
    %%% Extract segment data
    for i=1:nseg
        
        %check label
        switch label{i}
            case 'ex1'
                labs = 'g1';
            case 'ex2'
                labs = 'g2';
            case 'ex3'
                labs = 'g3';
            case 'ex4'
                labs = 'g4';
            case 'ex5l'
                labs = 'g5_sl';
            case 'ex5r'
                labs = 'g5_sr';
            case 'tech1l'
                labs = 'g6_sl';
            case 'tech1r'
                labs = 'g6_sr';
            case 'tech2l'
                labs = 'g7_sl';
            case 'tech2r'
                labs = 'g7_sr';
            case 'tech3l'
                labs = 'g8_sl';
            case 'tech3r'
                labs = 'g8_sr';
            case 'tech4l'
                labs = 'g9_sl';
            case 'tech4r'
                labs = 'g9_sr';
            case 'tech5l'
                labs = 'g10_sl';
            case 'tech5r'
                labs = 'g10_sr';
            case 'tech6l'
                labs = 'g11_sl';
            case 'tech6r'
                labs = 'g11_sr';
            case 'tech7l'
                labs = 'g12_sl';
            case 'tech7r'
                labs = 'g12_sr';
            case 'tech8l'
                labs = 'g13_sl';
            case 'tech8r'
                labs = 'g13_sr';
            case '_'
                labs = 'rest';
            otherwise
                warning(['Unkown label "' label{i} '" in file ' filename]);
                ret = 1;
        end
        
    end
    
end

fclose('all');

end