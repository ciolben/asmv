function warpI2=warpFLColorinterp(im1,im2,vx,vy,t)
if isfloat(im1)~=1
    im1=im2double(im1);
end
if isfloat(im2)~=1
    im2=im2double(im2);
end
if exist('vy')~=1
    vy=vx(:,:,2);
    vx=vx(:,:,1);
end
nChannels=size(im1,3);
for i=1:nChannels
    [im,isNan]=warpFLinterp(im2(:,:,i),vx,vy,t);
    temp=im1(:,:,i);
    %im(isNan)=temp(isNan);
    warpI2(:,:,i)=im;
end