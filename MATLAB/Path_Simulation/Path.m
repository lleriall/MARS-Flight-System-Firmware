function [distancesR,visitedNodesR,indexEndR] = Path(xrand,yrand,promptIX,promptIY,exploredNodesX,exploredNodesY,cbx2)%<SM:PDF>%<SM:PDF_PARAM> 
    count = 1;
    expNodesXCopy = 0;
    expNodesYCopy = 0;
     % First, we initialize the algorithm as follows:
    % We set the starting node.
    startX = promptIX;
    startY = promptIY;
    % We set the distances between the starting node and all other cities to infinity, except for the distance between the starting node and itself, which we set to 0.
    distances(1:length(xrand)) = Inf;%<SM:REF> 
    visitedNodes(1:length(xrand)) = 0;%<SM:REF>
    
    % After that, we iteratively execute the following steps:
    % We choose the node with the smallest value as the “current node” and visit all of its neighboring nodes. As we visit each neighbor, we update their tentative distance from the starting node.
    % Once we visit all of the current node’s neighbors and update their distances, we mark the current node as “visited.” Marking a node as “visited” means that we’ve arrived at its final cost.
    % We go back to step one. The algorithm loops until it visits all the nodes in the graph. 
    % The algorithm loops until it visits all the nodes in the graph. 

    currentDistance = 0;
    nextNode = 0;
    currentPosX = promptIX;
    currentPosY = promptIY;

    indexEnd = 502;
    indxs = []; %<SM:REF> 
    while count <= length(xrand)%<SM:WHILE> %<SM:ROP>   
        % We choose the node with the smallest value as the “current node” and visit all of its neighboring nodes. As we visit each neighbor, we update their tentative distance from the starting node.
       mindistance = Inf;
        for h = 1:length(xrand) %<SM:FOR> 
            this_dist = findDistanceBetweenNodes(currentPosX,currentPosY,xrand(h),yrand(h));%<SM:PDF_CALL>
            if this_dist < mindistance & visitedNodes(h)~= 1 %<SM:IF>%<SM:BOP> %<SM:ROP>   
                mindistance = this_dist;
                nextNode = h;
            end
        end
        distances(count) = mindistance;%<SM:REF>
        visitedNodes(nextNode) = 1;%<SM:REF>
        indxs = [indxs,nextNode];%<SM:REF>
        currentPosX = xrand(nextNode);%<SM:REF>
        currentPosY = yrand(nextNode);%<SM:REF>

        count = count + 1;%<SM:RTOTAL>  

    end
    showPlotAS(cbx2,indxs);%<SM:PDF_CALL>
    %Return values
    distancesR = distances;
    visitedNodesR = visitedNodes;
    indexEndR = indxs;
end
