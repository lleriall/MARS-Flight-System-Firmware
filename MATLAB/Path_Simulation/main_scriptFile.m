% -------------------------------------------
%{
Program Number: 
Program Purpose: Path Simulation
 
Created By: Nyameaama Gambrah 
Created On: 24, 02, 2022
Last Modified On: 27, 03, 2022

Credit to: Nyameaama Gambrah
By submitting this program with my name,
I affirm that the creation and modification
of this program is primarily my own work.

This project takes input through a GUI to select two nodes. 
(An origin and a destination). The shortest path is then calculated
through the nodes and a visualization is outputted.

SOURCES USED
- https://www.mathworks.com/help/matlab/ref/uicontrol.html
- https://www.mathworks.com/help/matlab/ref/uifigure.html
- https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
- https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
- http://theory.stanford.edu/~amitp/GameProgramming/AStarComparison.html

%}

%Maintenance Functions
clc 
clear
close all

%Main Function Call
UI();%<SM:PDF_CALL>