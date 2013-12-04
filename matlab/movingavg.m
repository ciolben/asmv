function [ out ] = movingavg( ws, data )
%MOVINGAVG Summary of this function goes here
%   Detailed explanation goes here

    %beginning
    beginning = floor(ws / 2);
    data = data';
    n = size(data, 2);
    ending = n - beginning + 1;
    out = [];
    
    %begin
    for i = 1:beginning
        out = [out sum(data(1:i * 2 - 1))/(i * 2 - 1)];
    end
    
    %middle
    fullavg = filter(ones(1, ws), ws, data);
    out = [out fullavg(2 * beginning + 1:n)];

    %end
    for i = ending:n
        out = [out sum(data(i - (n - i):n))/(2 * (n - i) + 1)];
    end
    out = out';
end

%clf; hold on; plot(data, 'Color', 'blue'); plot(movingavg(ws-1, movingavg(ws, data)), 'Color', 'red'); hold off;
