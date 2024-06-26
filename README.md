# KUbeDescrambler
INFO: C++ algorithm for solving a rubiks cube. Takes input via the format shown bellow where each character represents a color: 
   www      
   www      
   www      
rrrbbboooggg
rrrbbboooggg
rrrbbboooggg
   yyy      
   yyy      
   yyy  

Moves required for a solve are ouptutted in the form of a list. The definitions of moves are as follows:
f - rotate front face clockwise
f' - rotate front face counter-clockwise
r - rotate right face clockwise
r' - rotate right face counter-clockwise
l - rotate left face clockwise
l' - rotate left face counter-clockwise
u - rotate upper face clockwise
u' - rotate upper face counter-clockwise
b - rotate back face clockwise
b' - rotate back face counter-clockwise
d - rotate down face clockwise
d' - rotate down face counter-clockwise

Compiling/Running
  - compiled using g++ via makeFile
  - run target is outputted as "main"
