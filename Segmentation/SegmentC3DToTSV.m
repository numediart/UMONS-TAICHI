%This code requires the MoCap Toolbox installed on your computer.
%The MoCap Toolbox is available at: 
% https://www.jyu.fi/hytk/fi/laitokset/mutku/en/research/materials/mocaptoolbox



%Move C3D and Lab files in same folder as this script 
%(or change code according to file paths)
tic;

filenames = dir('*.lab');

%Check labels
test = checklabels(filenames);
if test
    error('Correct your label files before segmenting!');
end

mkdir('segmented');

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
    
    %%% Parse labels
    [index, label] = parselab([filename '.lab']);
    
    %%% Parse C3D data
    mytrack = mcread([filename '.c3d']);
    
    %%% Initialize parameters
    nseg = size(index,1);
    nframes = size(mytrack.data, 1);
    segment = mytrack;
    freq = mytrack.freq;
    index = round(index*freq);%convert index to frames (not seconds)
    
    gesturetypes = {'ex1','ex2','ex3','ex4','ex5l','ex5r','tech1l','tech1r','tech2l',...
        'tech2r','tech3l','tech3r','tech4l','tech4r','tech5l','tech5r','tech6l','tech6r'...
        ,'tech7l','tech7r','tech8l','tech8r'};
    newgesturetypes = {'G01D01','G02D01','G03D01','G04D01','G05D01','G05D02',...
        'G06D01','G06D02','G07D01','G07D02','G08D01','G08D02',...
        'G09D01','G09D02','G10D01','G10D02','G11D01','G11D02',...
        'G12D01','G12D02','G13D01','G13D02'};
    samplecounts = zeros(length(gesturetypes),1);
    
    %%% Extract segment data
        for s=1:nseg
                        
            if s<nseg
                segment.data = mytrack.data( index(s):index(s+1)-1, :);
            else
                segment.data = mytrack.data( index(s):end, :);
            end
            
            segment.nFrames = size(segment.data,1);
            
            %check label
            labeltype = find(ismember(gesturetypes,label{s}));
            
            if isempty(labeltype) && label{s}~='_'
                error(['Unkown label "' label{s} '" in file ' filename ...
                    '. Use CheckLabels.m and correct manually you label files before using this script']);
            end
            
            if ~isempty(labeltype)
                
                samplecounts(labeltype) = samplecounts(labeltype) + 1;
                segname = [filename newgesturetypes{labeltype} sprintf('S%02d',samplecounts(labeltype))];
                fname = segname;
                
                %save segment
                segment.filename = fname;
                segmentpath = 'segmented';
                mcwritetsv2(segment,segmentpath);
            end           
            
        end
end

fclose('all');
toc;

%% Visualization Example (Requires the MoCap Toolbox extension, 
%available at:
% https://github.com/titsitits/MocapRecovery/tree/master/MoCapToolboxExtension
close all;
filename = dir(['segmented/P01T03C02G13D01S01.tsv']);
disp(filename(1).name);
tmptrack = mcread([filename(1).folder '\' filename(1).name]);
p = mcinitanimpar;
%p.conn = mcautomaticbones2(tmptrack);
mc3dplot(tmptrack,p);
