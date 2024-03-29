#ifndef _MARCHING_CUBES_H_
#define _MARCHING_CUBES_H_

#include "math.h"
#include "vector"
#include "TriTable.hpp"

#define FRONT_TOP_LEFT 128
#define FRONT_TOP_RIGHT 64
#define TOP_RIGHT 32
#define TOP_LEFT 16
#define FRONT_BOTTOM_LEFT 8
#define FRONT_BOTTOM_RIGHT 4
#define BOTTOM_RIGHT 2
#define BOTTOM_LEFT 1

const std::vector<int> bitValues = {1, 2, 4, 8, 16, 32, 64, 128};

int marching_cubes(float (*f)(float, float, float), float isovalue, float stepsize, float x, float y, float z, std::vector<float>& vertices){
    bool tl, tr, br, bl, fbl, fbr, ftl, ftr;
    std::vector<bool> cases = {(*f)(x, y, z) < isovalue,
                                (*f)(x + stepsize, y, z) < isovalue,
                                (*f)(x + stepsize, y, z + stepsize) < isovalue,
                                (*f)(x, y, z + stepsize) < isovalue,
                                (*f)(x, y + stepsize, z) < isovalue,
                                (*f)(x + stepsize, y + stepsize, z) < isovalue,
                                (*f)(x + stepsize, y + stepsize, z + stepsize) < isovalue,
                                (*f)(x, y + stepsize, z + stepsize) < isovalue};
    int curCase = 0;
    for (int i = 0; i < cases.size(); i++){
        if(cases[i]){
            curCase |= bitValues[i];
        }
    }
    int count = 0;
    int *verts = marching_cubes_lut[curCase];
    for (int i = 0; i < 16; i++){
        if(verts[i] != -1){
            vertices.push_back(x + stepsize * vertTable[verts[i]][0]);
            vertices.push_back(y + stepsize * vertTable[verts[i]][1]);
            vertices.push_back(z + stepsize * vertTable[verts[i]][2]);
            count++;
        }
    }
    return count;
}

#endif
