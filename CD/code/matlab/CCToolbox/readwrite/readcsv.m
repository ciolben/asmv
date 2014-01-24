function [ data ] = readcsv( filename )
%READCSV Read csv with encoded cell array
%   Cell array must be matrices of nx2
h = fopen(filename);
if h == -1
    disp('error');
else
    %try to determine nb of line to preallocate struct
    %# Get file size.
    fseek(h, 0, 'eof');
    fileSize = ftell(h);
    frewind(h);
    %# Read the whole file.
    data = fread(h, fileSize, 'uint8');
    %# Count number of line-feeds and increase by one.
    numLines = sum(data == 10) + 1;
    frewind(h);

    %preallocate output
    data = cell(numLines, 1);
    
    %convert lines
    line = fgets(h);
    i = 1;
    while ischar(line)
        v = textscan(line, '%f', 'delimiter', ',');
        v = v{1}; %stocked in a cell array
        for x = 1:2:length(v)
            data{i} = [data{i};v(x:x+1)'];
        end;
        line = fgets(h);
        i = i + 1;
    end;
    fclose(h);
end;
end

