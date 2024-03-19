#ifndef _CALC_NORMALS_
#define _CALC_NORMALS_

#include "math.h"

#include <vector>
#include <cmath>

std::vector<float> crossProduct(const std::vector<float>& v1, const std::vector<float>& v2) {
    std::vector<float> result(3);
    result[0] = v1[1] * v2[2] - v1[2] * v2[1];
    result[1] = v1[2] * v2[0] - v1[0] * v2[2];
    result[2] = v1[0] * v2[1] - v1[1] * v2[0];
    return result;
}

void normalize(std::vector<float>& vec) {
    float magnitude = std::sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
    if (magnitude != 0) {
        vec[0] /= magnitude;
        vec[1] /= magnitude;
        vec[2] /= magnitude;
    }
}

std::vector<float> compute_normals(const std::vector<float>& vertices) {
    std::vector<float> normals;

    for (int i = 0; i < vertices.size(); i += 9) {
        std::vector<float> v1 = {vertices[i], vertices[i + 1], vertices[i + 2]};
        std::vector<float> v2 = {vertices[i + 3], vertices[i + 4], vertices[i + 5]};
        std::vector<float> v3 = {vertices[i + 6], vertices[i + 7], vertices[i + 8]};

        std::vector<float> edge1 = {v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]};
        std::vector<float> edge2 = {v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2]};

        std::vector<float> normal = crossProduct(edge1, edge2);

        normalize(normal);

        for (int j = 0; j < 3; ++j) {
            normals.push_back(normal[0]);
            normals.push_back(normal[1]);
            normals.push_back(normal[2]);
        }
    }

    return normals;
}

#endif
