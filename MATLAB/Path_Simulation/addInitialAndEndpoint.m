function [updatedXrand,updatedYrand] = addInitialAndEndpoint(promptIX,promptIY,promptFX,promptFY,xrand,yrand)%<SM:PDF>%<SM:PDF_PARAM> 
    %If initial and endpoint nodes arent in current map, add
    %Search for initial and endpoints
    tempX = xrand;%<SM:REF> 
    tempY = yrand;%<SM:REF> 
    initX = find(xrand == promptIX,1);%<SM:RANDUSE>%<SM:REF>%<SM:ROP>   
    if(isempty(initX) == 1)%<SM:IF> %<SM:ROP>  
        %Add to node map 
        tempX = [tempX,promptIX];%<SM:RANDUSE> %<SM:REF> 
    end
    initY = find(yrand == promptIY,1);%<SM:RANDUSE>%<SM:ROP>   
    if(isempty(initY) == 1)%<SM:IF> %<SM:ROP>  
        %Add to node map
        tempY = [tempY,promptIY];%<SM:RANDUSE> %<SM:REF> 
    end
    endX = find(xrand == promptFX,1);%<SM:RANDUSE> %<SM:ROP>   
    if(isempty(endX) == 1)%<SM:IF> %<SM:ROP>  
        %Add to node map
        tempX = [tempX,promptFX];%<SM:RANDUSE> %<SM:REF> 
    end
    endY = find(yrand == promptFY,1);%<SM:RANDUSE>%<SM:ROP>   
    if(isempty(endY) == 1)%<SM:IF>%<SM:ROP>  
        %Add to node map
        tempY = [tempY,promptFY];%<SM:RANDUSE> %<SM:REF> 
    end
    updatedXrand = tempX;%<SM:PDF_RETURN> 
    updatedYrand = tempY;%<SM:PDF_RETURN> 
end