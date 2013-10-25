function [warpI2,I]=warpinterp(i2,vx,vy,t)
% warp i1 according to flow field in vx vy
[M,N]=size(i2);
[x,y]=meshgrid(1:N,1:M);
warpI2=interp2(x,y,i2,x+vx*t,y+vy*t,'bicubic');
%warpI2=interp2(x,y,i2,x+vx,y+vy);
I=find(isnan(warpI2));
warpI2(I)=zeros(size(I));