function [ret1,ret2] = errorChecks(promptIX,promptIY,promptFX,promptFY,pathD,xrand)%<SM:PDF_CALL>%<SM:PDF_PARAM> 
    returned1 = 1;
    returned2 = 1;
    %Error check path points fields
    %Checks to make sure value is less than map size and if field is blank
    if pathD > 1000%<SM:IF> %<SM:ROP>  
        returned1 = 0;
    end
    if isempty(promptIX) || promptIX > pathD%<SM:IF>%<SM:BOP> %<SM:ROP>  
        returned1 = 0;
    end
    if isempty(promptIY) || promptIY > pathD%<SM:IF>%<SM:BOP> %<SM:ROP>  
        returned1 = 0;
    end
    if isempty(promptFX) || promptFX > pathD%<SM:IF>%<SM:BOP> %<SM:ROP>  
        returned1 = 0;
    end
    if isempty(promptFY) || promptFY > pathD%<SM:IF>%<SM:BOP>  %<SM:ROP>  
        returned1 = 0;
    end
    %Error check path density field
    %Checks t omake sure user selected node density is less than 1000 nodes
    %and field is not left blank
    if isempty(pathD) || promptFY > 1000%<SM:IF>%<SM:BOP>  %<SM:ROP>  
        returned2 = 0;
    end
    ret1 = returned1;%<SM:PDF_RETURN>
    ret2 = returned2;%<SM:PDF_RETURN>
end
