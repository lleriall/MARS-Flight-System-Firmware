function [CLSa,CLSb] = findNeighborNodes(pointX,pointY,xrand,yrand)%<SM:PDF> %<SM:PDF_PARAM>
    closestNode = [];%<SM:REF> 
    dists = [];%<SM:REF> 
    for i = 1: length(xrand)%<SM:FOR> 
        temp = findDistanceBetweenNodes(pointX,pointY,xrand(i),yrand(i));%<SM:PDF_RETURN> 
        dists = [dists,temp];%<SM:REF> 
    end
    closest = min(dists);%<SM:REF> 
    closestindX = find(dists == closest,1);%<SM:REF>%<SM:ROP>  
    %Return the point
    CLSa = xrand(closestindX);%<SM:RANDUSE> %<SM:REF> 
    CLSb = yrand(closestindX);%<SM:RANDUSE> %<SM:REF> 
    
end