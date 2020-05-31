# 3DScene

Rendering 3D objects in OpenGL from the given wavefront file

## Getting Started

### Prerequisites

Run the following commands to install libraries on ubuntu 

```
sudo apt install freeglut3-dev libglew-dev
```

### Installing

git clone the repo into the desired folder

```
git clone https://github.com/utkgrover/3DScene.git
```

to run :

```
make main
```

to delete the object files

```
make clean
```

## Controls

Translation controls :
* a,d to move in x axis
* w,s to move in y axis
* q,e to move in z axis

Rotation controls :
* i,k to rotate about y axis
* j,l to rotate about y axis
* u,o to rotate about z axis

Other:
* c,v to change the sensitivity of the controls
* x to quit
