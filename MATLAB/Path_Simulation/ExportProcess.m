function ExportProcess(src,event,xrand,yrand,cbx)%<SM:PDF> %<SM:PDF_PARAM>
    cbx_conv = cbx.Value;%<SM:NEWFUN>
    currentfolder = pwd;%<SM:NEWFUN>
    newFolder = "ShortestPath_output";
    if ~exist(newFolder, 'dir')%<SM:NEWFUN>%<SM:IF>
        mkdir(newFolder);%<SM:NEWFUN>
    end
    baseFileName = 'Path_output_generated.xlsx';
    fullFileName = fullfile(newFolder, baseFileName);%<SM:NEWFUN>
    XMap = reshape(xrand,[],1);%<SM:NEWFUN>%<SM:AUG>
    YMap = reshape(yrand,[],1);%<SM:NEWFUN>%<SM:AUG>
    %Description
    text = "This is the output of the Shortest Path matlab program.The first column holds the x values of the map and the second column holds the y values of the map.";
    writematrix(text,baseFileName,'Sheet','Sheet1','Range','D2');%<SM:WRITE>  
    %Get path
    path = [];%<SM:REF> 
    T = table(XMap,YMap);%<SM:NEWFUN>
    writetable(T,baseFileName);%<SM:NEWFUN>%<SM:WRITE>  
    movefile Path_output_generated.xlsx ShortestPath_output%<SM:NEWFUN>
    exportDescription();%<SM:PDF_CALL> 
end