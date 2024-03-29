#ifndef _WRITE_PLY_
#define _WRITE_PLY_

#include "math.h"

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>

void writePLY(const std::vector<float>& vertices, const std::vector<float>& normals, const std::string& fileName) {
    std::ofstream plyFile(fileName);

    if (!plyFile.is_open()) {
        std::cout<< "Unable to open file";
        return;
    }

    plyFile << "ply\n";
    plyFile << "format ascii 1.0\n";
    plyFile << "element vertex " << vertices.size() / 3 << "\n";
    plyFile << "property float x\n";
    plyFile << "property float y\n";
    plyFile << "property float z\n";
    plyFile << "property float nx\n";
    plyFile << "property float ny\n";
    plyFile << "property float nz\n";
    plyFile << "element face " << vertices.size() / 9 << "\n";
    plyFile << "property list uchar int vertex_index\n";
    plyFile << "end_header\n";

    // Write vertices and normals
    for (size_t i = 0; i < vertices.size(); i += 3) {
        plyFile << vertices[i] << " " << vertices[i + 1] << " " << vertices[i + 2] << " ";
        plyFile << normals[i] << " " << normals[i + 1] << " " << normals[i + 2] << "\n";
    }

    // Write faces
    for (size_t i = 0; i < vertices.size() / 9; ++i) {
        plyFile << "3 " << (i * 3) << " " << (i * 3 + 1) << " " << (i * 3 + 2) << "\n";
    }

    plyFile.close();
}

#endif