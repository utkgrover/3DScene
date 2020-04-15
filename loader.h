#ifndef LOADER_H
#define LOADER_H

#include<iostream>
#include<string>
#include<vector>
#include<GL/glut.h>

typedef struct object{
    std::string name;
    std::vector<std::vector<int>> faceVertex;
    std::string material;
}object;


class Loader{
private:
    std::vector<std::vector<GLfloat>> vertex;
    std::vector<object> loadedObject;
public:
    Loader(std::string path);
    // Loader(){std::cout<<"wrong way to declare the class\n";x=1;}
    object getObj(int index);
    int numOfObjects();
    std::vector<std::vector<GLfloat>> getVertex();
};

#endif