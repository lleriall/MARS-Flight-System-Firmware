function found = findPairInMap(xVal,yVal,xrand,yrand)%<SM:PDF>%<SM:PDF_PARAM>  
    trueX = 1;
    search1 = find(xrand == xVal);%<SM:REF> %<SM:ROP>   
    if isempty(search1)%<SM:IF>
        trueX = 0;
    end
    search2= find(yrand == yVal);%<SM:REF> %<SM:ROP>   
    if isempty(search2)%<SM:IF>
        trueX = 0;
    else
        if search1 ~= search2%<SM:IF> %<SM:NEST>%<SM:ROP>  
            trueX = 0;
        end
    end
    if trueX == 1%<SM:IF> %<SM:ROP>  
        found = search1;
    else
         found = -1;%<SM:PDF_RETURN>
    end
end
