function showPlotAS(checkboxValue,array)%<SM:PDF>%<SM:PDF_PARAM>
    if checkboxValue == 0%<SM:IF> %<SM:ROP>  
        figure(2)%<SM:PLOT>
        plot(array);%<SM:PLOT>
    else %<SM:IF>
        figure(2)%<SM:PLOT>
        plot(array,'.');%<SM:PLOT>   
    end
end