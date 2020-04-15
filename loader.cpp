#include "loader.h"
#include<iostream>
#include<cstring>
#include<cstdio>

Loader::Loader(std::string pathobj,std::string pathmtl){

    FILE *fp = fopen(&pathobj[0],"r"); 
    if(fp == NULL){std::cout<<"cant open the file :"<<pathobj<<std::endl;}

    object currentObject;

    vertex.push_back({0,0,0});
    while(1){
        char lineHeader[128];
        int res = fscanf(fp, "%s", lineHeader);
        if (res == EOF){
            loadedObject.push_back(currentObject);
            break;
        }
        
        if(strcmp( lineHeader, "o" ) == 0){
            loadedObject.push_back(currentObject);//push the object into the loadedObjects vector
            currentObject = object();//clear currentObject
            char dump[1000];
            fscanf(fp, "%s", dump ); 
            currentObject.name = std::string(dump);

        }else if(strcmp( lineHeader, "v" ) == 0 ){
            float x,y,z;
            fscanf(fp, "%f %f %f\n", &x, &y, &z );
            vertex.push_back({x,y,z});

        }else if(strcmp( lineHeader, "f" ) == 0){
            int vert[4],uv[4],normal[4];
            fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",&vert[0],&uv[0],&normal[0],&vert[1],&uv[1],&normal[1],&vert[2],&uv[2],&normal[2],&vert[3],&uv[3],&normal[3]);
            currentObject.faceVertex.push_back({vert[0],vert[1],vert[2],vert[3]});
            //std::cout<<"pushed back a face"<<std::endl;

        }else if(strcmp( lineHeader, "usemtl" ) == 0){
            char dump[1000];
            fscanf(fp, "%s", dump ); 
            currentObject.material = std::string(dump);

        }
        
    }
    fclose(fp);

    std::cout<<"finished reading faces\n";

    fp = fopen(&pathmtl[0],"r"); 
    if(fp == NULL){std::cout<<"cant open the file :"<<pathmtl<<std::endl;}

    std::string temp;
    while(1){
        char lineHeader[128];
        int res = fscanf(fp, "%s", lineHeader);

        if (res == EOF){break;}

        if(strcmp( lineHeader, "newmtl" ) == 0){
            char dump[1000];
            fscanf(fp, "%s", dump ); 
            temp = std::string(dump);

        }else if(strcmp( lineHeader, "Kd" ) == 0 ){
            float x,y,z;
            fscanf(fp, "%f %f %f\n", &x, &y, &z );
            value.insert(std::pair<std::string,std::vector<GLfloat>>(temp,{x,y,z}));

        }
    }
    fclose(fp);
}

object Loader::getObj(int index){
    return loadedObject[index];
}

int Loader::numOfObjects(){
    return loadedObject.size();
}

std::vector<std::vector<GLfloat>> Loader::getVertex(){
    return vertex;
}

std::vector<GLfloat> Loader::getValue(std::string s){
    return value[s];
}