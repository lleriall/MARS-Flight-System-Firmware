function result = findDistanceBetweenNodes(currentPosX,currentPosY,filteredX,filteredY)%<SM:PDF> %<SM:PDF_PARAM> 
      %Use pythagoras to find distance between nodes
     dist = [];%<SM:REF> 
     pythagoras = sqrt(power((filteredX - currentPosX),2) + power((filteredY - currentPosY),2));%<SM:RTOTAL>  
     if pythagoras ~= 0 %<SM:IF> %<SM:ROP>  
         dist = [dist,pythagoras];%<SM:REF> 
     end
    result = dist;%<SM:PDF_RETURN>
end