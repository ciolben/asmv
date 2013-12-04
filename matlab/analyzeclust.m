function analyzeclust( name )
%ANALYZECLUST Summary of this function goes here
%   Detailed explanation goes here

    % create clusters.txt
    root = strcat(name, 'motionData/clusters/');
    fid = fopen( strcat(root, 'clusters.txt'), 'w+' );
    if fid == -1
        disp 'error open file clusters.txt';
        return
    end
    
    folder = dir(root);
    n = length(folder);

    try
        for i = 1:n
            filename = [root 'wflow' num2str(i) '.yml.gz.clust' ];
            if exist(filename, 'file')
                content = fileread(filename);
                if isempty(content) == 0
                    fwrite(fid, content);
                end
            end
        end
    catch err
        fclose(fid);
        rethrow(err);
    end
    
    % load points
    fclose(fid);
    fid = fopen( strcat(root, 'clusters.txt'), 'r' );
    data = fscanf(fid, '%f');
    fclose(fid);
    
    if isempty(data)
        disp 'Empty array';
        return;
    end
    
    % compute plot
    ws = 10; %window size
    fps = 24; %larger window size
    
    %h = pdf('Normal', -floor(ws/2):floor(ws/2),0,1);
    h = figure;
    %set(gcf,'Visible', 'off'); 
    hold on;
    plot(data, 'Color', 'blue');
    plot(movingavg(ws-1, movingavg(ws, data)), 'Color', 'red');
    plot(movingavg(fps, movingavg(fps, data)), 'Color', 'green');
    hold off;
    
    %save plot and data
    print(h, '-dpng', strcat(root, name, '.png'));
    save(strcat(root, name, '.mat'), 'data');
    
end

