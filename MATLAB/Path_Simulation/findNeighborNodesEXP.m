function [CLSa,CLSb] = findNeighborNodesEXP(pointX,pointY,xrand,yrand,visitedArray,no_of_neighbors)%<SM:PDF> %<SM:PDF_PARAM>
    closestNode = [];%<SM:REF> 
    dists = [];%<SM:REF> 
    recurred = 0;
    for i = 1: length(xrand)%<SM:FOR> 
        temp = findDistanceBetweenNodes(pointX,pointY,xrand(i),yrand(i));%<SM:PDF_CALL> 
        dists = [dists,temp];%<SM:REF> 
    end
    %Find the closest distances and add to array
    closestList = [];%<SM:REF>
    for j = 1:no_of_neighbors%<SM:FOR> 
        Vals = sort(dists);%<SM:SORT> 
        closestList = [closestList,Vals(j)];%<SM:REF> 
    end
    %Fin the indexes of the closest distances and add to separate array
    closestListIndxs = [];%<SM:REF>
    for j = 1:no_of_neighbors%<SM:FOR> 
        indxs = find(dists == closestList(j),1);%<SM:REF> %<SM:ROP>  
        closestListIndxs = [closestListIndxs,indxs];%<SM:REF> 
    end
    returnedX = [];%<SM:REF>
    returnedY = [];%<SM:REF>
    for j = 1:length(closestList)%<SM:FOR> 
        if visitedArray(closestListIndxs(j)) ~= 1%<SM:REF> %<SM:IF> %<SM:ROP>  
            returnedX = [returnedX,xrand(closestListIndxs(j))];%<SM:REF> 
            returnedY = [returnedY,yrand(closestListIndxs(j))];%<SM:REF> 
        end
    end
    if isempty(returnedX)%<SM:IF>
        if no_of_neighbors > 10%<SM:IF>%<SM:NEST> %<SM:ROP>  
            CLSa = 0;%<SM:PDF_RETURN> 
            CLSb = 0;%<SM:PDF_RETURN> 
        else
            [val1,val2] = findNeighborNodesEXP(pointX,pointY,xrand,yrand,visitedArray,no_of_neighbors+1);%<SM:PDF_CALL> 
            CLSa = val1;%<SM:PDF_RETURN> 
            CLSb = val2;%<SM:PDF_RETURN> 
        end
    else
        CLSa = returnedX;%<SM:RANDUSE> %<SM:REF> %<SM:PDF_RETURN> 
        CLSb = returnedY;%<SM:RANDUSE> %<SM:REF> %<SM:PDF_RETURN> 
    end
    
end