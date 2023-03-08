%UI
function UI()
     %initial point
    pointInitialX = 0;
    pointInitialY = 0;
    
    currentPosX = pointInitialX;
    currentPosY = pointInitialY;

    %end point
    endpointX = 0;
    endpointY = 0;

    exploredNodesX = [];%<SM:REF>
    exploredNodesY = [];%<SM:REF>


    %Create node map 
    xrand = (rand(1,500)*1000);%<SM:RANDGEN>
    yrand = (rand(1,500)*1000);%<SM:RANDGEN>

    f = uifigure('name','Shortest Path');%<SM:NEWFUN> 
    set(f,'Position',[100 50 1000 700])%<SM:NEWFUN> 
    
    gl = uigridlayout(f,[2,2]);%<SM:NEWFUN>
    gl.RowHeight = {'1x',30};%<SM:NEWFUN>
    gl.ColumnWidth = {'1x','2x'};%<SM:NEWFUN>
    
    p = uipanel(gl,'Title','Path Configuration');%<SM:NEWFUN>
    
    grid2 = uigridlayout(p,[3 2]);%<SM:NEWFUN>
    grid2.RowHeight = {22,22,22};%<SM:NEWFUN>
    grid2.ColumnWidth = {80,'1x'};%<SM:NEWFUN>
    
    %Path Density
    pDlabel = uilabel(grid2);%<SM:NEWFUN>
    pDlabel.HorizontalAlignment = 'right';%<SM:NEWFUN>
    pDlabel.Text = 'Path Density';%<SM:NEWFUN>

    promptPD = uieditfield(grid2);%<SM:NEWFUN>
    
    %Initial Point 
    pIXlabel = uilabel(grid2);%<SM:NEWFUN>
    pIXlabel.HorizontalAlignment = 'right';%<SM:NEWFUN>
    pIXlabel.Text = 'Initial Point (X)';%<SM:NEWFUN>

    promptIX = uieditfield(grid2);%<SM:NEWFUN>
    
    %Initial Point Y
    pIXlabel = uilabel(grid2);%<SM:NEWFUN>
    pIXlabel.HorizontalAlignment = 'right';%<SM:NEWFUN>
    pIXlabel.Text = 'Initial Point (Y)';%<SM:NEWFUN>

    promptIY = uieditfield(grid2);%<SM:NEWFUN>
    
    %Final Point X
    pFXlabel = uilabel(grid2);%<SM:NEWFUN>
    pFXlabel.HorizontalAlignment = 'right';%<SM:NEWFUN>
    pFXlabel.Text = 'Final Point (X)';%<SM:NEWFUN>

    promptFX = uieditfield(grid2);%<SM:NEWFUN>
    
    %Final Point Y
    pFYlabel = uilabel(grid2);%<SM:NEWFUN>
    pFYlabel.HorizontalAlignment = 'right';%<SM:NEWFUN>
    pFYlabel.Text = 'Final Point (Y)';%<SM:NEWFUN>

    promptFY = uieditfield(grid2);%<SM:NEWFUN>
   
    cbx = uicheckbox(grid2, 'Text','Show units in output',...%<SM:NEWFUN>
                  'Value', 0,...
                  'Position',[50 50 102 15],...
                  'FontSize',13,...
                  'WordWrap','on');
              
    cbx2 = uicheckbox(grid2, 'Text','Show nodes instead of path        (Will not trace route between the chosen nodes)',...%<SM:NEWFUN>
                  'Value', 0,...
                  'Position',[50 50 102 15],...
                  'FontSize',13,...
                  'WordWrap','on');
              
    cbx3 = uicheckbox(grid2, 'Text','Show visualizati-on in new window',...%<SM:NEWFUN>
                  'Value', 1,...
                  'Position',[50 50 102 15],...
                  'FontSize',13,...
                  'WordWrap','on');
     
    cbx4 = uicheckbox(grid2, 'Text','Optimize Performance (Computation will take a shorter time period)',...
                  'Value', 0,...
                  'Position',[50 50 102 15],...
                  'FontSize',13,...
                  'WordWrap','on');
              
    hlink = uihyperlink(grid2);%<SM:NEWFUN>
    hlink.Text = 'Learn more about path planning algorithms';%<SM:NEWFUN>
    hlink.WordWrap = 'on';%<SM:NEWFUN>
    %Motion planning From Wikipedia, the free encyclopedia
    hlink.URL = 'https://en.wikipedia.org/wiki/Motion_planning';%<SM:NEWFUN>
    
    pl = uiaxes(gl); %<SM:PLOT>
    pl.Layout.Row = 1;%<SM:NEWFUN>
    pl.Layout.Column = 2;%<SM:NEWFUN>
    plot(pl,xrand,yrand,'.');%<SM:PLOT> 
    title(pl,'Node Map');

    % Create and lay out button
    btn = uibutton(gl);%<SM:NEWFUN>
    btn.Layout.Row = 2;%<SM:NEWFUN>
    btn.Layout.Column = 1;%<SM:NEWFUN>
    btn.Text = 'Run Simulation';%<SM:NEWFUN>
    % Assign button callback function
    btn.ButtonPushedFcn = {@plotButtonPushed,currentPosX,currentPosY,xrand,yrand,exploredNodesX,exploredNodesY,promptIX,promptIY,promptFX,promptFY,promptPD,cbx,cbx2,cbx3,cbx4};%<SM:NEWFUN>
        
    % Create and lay out button
    btn2 = uibutton(gl);%<SM:NEWFUN>
    btn2.Layout.Row = 2;%<SM:NEWFUN>
    btn2.Layout.Column = 2;%<SM:NEWFUN>
    btn2.Text = 'Export Data to File';%<SM:NEWFUN>
    btn2.ButtonPushedFcn = {@ExportProcess,xrand,yrand,cbx};%<SM:NEWFUN>
    
    btn3 = uibutton(grid2);%<SM:NEWFUN>
    btn3.Text = 'View Program Description';%<SM:NEWFUN>
    btn3.ButtonPushedFcn = @Instructions_Description;%<SM:NEWFUN>
    
    Instructions_Description();%<SM:PDF_CALL>

end