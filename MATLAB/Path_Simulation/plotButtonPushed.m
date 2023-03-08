function finalPath = plotButtonPushed(src,event,currentPosX,currentPosY,xrand,yrand,exploredNodesX,exploredNodesY,promptIX,promptIY,promptFX,promptFY,pathD,cbx,cbx2,cbx3,cbx4)%<SM:PDF>%<SM:PDF_PARAM>
%     Convert
    promptIX_conv = str2num(promptIX.Value);%<SM:STRING> %<SM:NEWFUN> 
    promptIY_conv = str2num(promptIY.Value);%<SM:STRING> %<SM:NEWFUN> 
    promptFX_conv = str2num(promptFX.Value);%<SM:STRING> %<SM:NEWFUN> 
    promptFY_conv = str2num(promptFY.Value);%<SM:STRING> %<SM:NEWFUN> 
    promptPathDensity = str2num(pathD.Value);%<SM:STRING> %<SM:NEWFUN> 
    cbx2_conv = cbx2.Value;%<SM:NEWFUN> 
    cbx4_conv = cbx4.Value;%<SM:NEWFUN> 
    
    %Verify edit fields have been populated, if not dialog box
    [ret1,ret2] = errorChecks(promptIX_conv,promptIY_conv,promptFX_conv,promptFY_conv,promptPathDensity,xrand);%<SM:PDF> 
    if ret1 == 0 || ret2 == 0 %<SM:IF>%<SM:BOP> %<SM:ROP>       
        dialogBox();%<SM:PDF> 
        
    else %<SM:IF>   
        %Check if initial and final points are in map, if not append to map
        [xrandUPD,yrandUPD] = addInitialAndEndpoint(promptIX_conv,promptIY_conv,promptFX_conv,promptFY_conv,xrand,yrand); %<SM:PDF_CALL>  
        %Use checkbox input to determine algorithm to be used 
        if cbx4_conv == 0 %<SM:IF>%<SM:NEST>  %<SM:ROP>  
            [indX,indY] = Path2(xrandUPD,yrandUPD,promptIX_conv,promptIY_conv,promptFX_conv,promptFY_conv,cbx2_conv); %<SM:PDF_CALL> 
        else %<SM:IF>
            %Path finds the shortest route and returns vector with final path
            %points
            [distancesR,visitedNodesR,indexEndR] = Path(xrandUPD,yrandUPD,promptIX_conv,promptIY_conv,exploredNodesX,exploredNodesY,cbx2_conv); %<SM:PDF_CALL>  
        end
    end 
end  