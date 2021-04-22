# FEUP_PROG
EIC0012 Programação - MIEIC

Project1:
- Menu 3 opções:
    1) Exit
    2) Rules
    3) Play
        if 2):
          Number of the maze: XX
          Create a file MAZE_XX.TXT
          Loop till the file is found or the input is 0 -> show the initial menu
          
- ShowTheMaze:
  H = player alive; h = player dead
  R = robot alive; r = robot dead
  * = eletrical fence;
 
- AskThePlayer:
        Q  W  E
        A POS D
        Z  X  C
   if S the player stays in his current position
   Impossible to move to cells occupied by destroyed robots, ask for a new movement
   Ctrl-z in windows to leave, Ctrl-D in linux to leave
   
 - UpdateThePosition




 - IfPlayerSurvives
    Ask name
    Update list of winners
    Stored in MAZE_XX_WINNERS.txt
    Store the time
