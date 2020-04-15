#ifndef LOADER_H
#define LOADER_H

#include<iostream>
#include<string>
#include<vector>
#include<map>
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
    std::map<std::string,std::vector<GLfloat>> value;
public:
    Loader(std::string pathobj,std::string pathmtl);
    // Loader(){std::cout<<"wrong way to declare the class\n";x=1;}
    object getObj(int index);
    int numOfObjects();
    std::vector<std::vector<GLfloat>> getVertex();
    std::vector<GLfloat> getValue(std::string);
};

#endif