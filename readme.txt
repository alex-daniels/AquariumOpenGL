A small 'aquarium' in opengl to test lighting and texture mapping. 
***********************
To compile and run: bash script.sh

OR compile as:
g++ main.cpp DisplayClass.h AnimalsClass.h SceneryClass.h CameraClass.h -framework OpenGL -framework GLUT

run as:
./a.out
***********************

*NOTES*
Textures included in /assets

*CONTROLS*
x -> Decrease x (towards -x)
X -> Increase x (towards +x)
y -> Decrease y (towards -y)
Y -> Increase y (towards +y)
z -> Decrease z (towards -z)
Z -> Increase z (towards +z)
c -> Reset the current view (valid on Z, Y, X views, see below)

*RIGHT CLICK OPTIONS*
Z: Looking down the Z-axis **FLYBY WORKS**
Y: Looking down the Y-axis **FLYBY WORKS**
X: Looking down the X-axis **FLYBY WORKS**

Hit C to stop flyby and resume static camera.

Offset1: Offset view of Z axis
Offset2: Offset view of Z axis opposite Offset1
Offset3: Offset view of Z axis
Offset4: Offset view of Z axis opposite Offset3
Custom: Enter-> (CameraX, CameraY, CameraZ, lookX, lookY, lookZ) coordinates via command line
Follow: Follow a single fish.
Exit: Exits the program OR hit 'esc'


