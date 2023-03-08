function [indX,indY] = Path2(xrandUPD,yrandUPD,promptIX,promptIY,exploredNodesX,exploredNodesY,cbx2)%<SM:PDF_CALL>%<SM:PDF_PARAM>
     % First, we initialize the algorithm as follows:
    % We set the starting node.
    startX = promptIX;
    startY = promptIY;
    % We set the distances between the starting node and all other cities to infinity, except for the distance between the starting node and itself, which we set to 0.
    distances(1:length(xrandUPD)) = Inf;%<SM:REF> 
    visitedNodes(1:length(xrandUPD)) = 0;%<SM:REF>
    nextNode = 0;
    currentPosX = promptIX;
    currentPosY = promptIY;
    followingNode = 0;
    
    indexEnd = 502;
    promptFX = exploredNodesX;
    promptFY = exploredNodesY;
    indxsX = []; %<SM:REF>
    indxsY = [];%<SM:REF>
    count = 1;
    while count <= length(xrandUPD)%<SM:WHILE>%<SM:ROP>  
        % We choose the node with the smallest value as the “current node” and visit all of its neighboring nodes. As we visit each neighbor, we update their tentative distance from the starting node.
        mindistance = Inf;
        for h = 1:length(xrandUPD)%<SM:FOR> 
            this_dist = findDistanceBetweenNodes(currentPosX,currentPosY,xrandUPD(h),yrandUPD(h));%<SM:PDF_CALL>
            if this_dist < mindistance & visitedNodes(h)~= 1 %<SM:IF>%<SM:BOP> %<SM:ROP>   
                mindistance = this_dist;
                nextNode = h;
            end
        end
        [CLSa,CLSb] = findNeighborNodesEXP(xrandUPD(nextNode),yrandUPD(nextNode),xrandUPD,yrandUPD,visitedNodes,3);%<SM:PDF_CALL>
        if CLSa == 0 %<SM:IF> %<SM:ROP>  
            count = length(xrandUPD) + 1;%<SM:RTOTAL>
        else
            costs = [];%<SM:REF>
            for p = 1:length(CLSa)%<SM:FOR> 
                %G is the distance between the current node and the start node.
                g = findDistanceBetweenNodes(CLSa(p),CLSb(p),startX,startY);%<SM:PDF_CALL>
                %H is the heuristic — estimated distance from the current node to the end node.
                h = findDistanceBetweenNodes(CLSa(p),CLSb(p),promptFX,promptFY);%<SM:PDF_CALL>
                %F is the total cost of the node.
                f = g + h;%<SM:RTOTAL>
                costs = [costs,f];%<SM:REF>
            end
            leastCost = min(costs);%<SM:REF>
            leastCostIndex = find(costs == leastCost,1);%<SM:REF> %<SM:ROP>  
            loc = findPairInMap(CLSa(leastCostIndex),CLSb(leastCostIndex),xrandUPD,yrandUPD);%<SM:PDF_CALL>
            distances(count) = mindistance;%<SM:REF>
            visitedNodes(loc) = 1;%<SM:REF>
            indxsX = [indxsX,xrandUPD(loc)];%<SM:REF>
            indxsY = [indxsY,yrandUPD(loc)];%<SM:REF>
            currentPosX = xrandUPD(loc);%<SM:REF>
            currentPosY = yrandUPD(loc);%<SM:REF>
            followingNode = find(xrandUPD == CLSa(leastCostIndex),1);%<SM:REF> %<SM:ROP>  
            count = count + 1;%<SM:RTOTAL>
        end
          
    end
    showPlotAS(cbx2,indxsX);%<SM:PDF_CALL>
    indX = indxsX; %<SM:PDF_RETURN> 
    indY = indxsY; %<SM:PDF_RETURN> 
end