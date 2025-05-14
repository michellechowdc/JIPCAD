#include <stdio.h>
#include <math.h>
// Given list of vertices describing a polygon, first compute the centroid of the polygon

float* compute_centroid(float vertices[][3], int num_vertices) {
    // Compute location of centroid given list of vertices of a polygon
    static float centroid[3] = {0, 0, 0};

    // sum magnitude of the coordinates in each direction: x, y, z
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < 3; j++) {
            centroid[j] += vertices[i][j];
        }
    }

    // then divide by the number of vertices
    for (int i = 0; i < 3; i++) {
        centroid[i] /= num_vertices;
    }

    return centroid;
}

float* cross_product(float v1[3], float v2[3]) {
    // Compute the cross product of 2 vectors, v1 and v2
    static float result[3];
    result[0] = v1[1] * v2[2] - v1[2] * v2[1];
    result[1] = v1[2] * v2[0] - v1[0] * v2[2];
    result[2] = v1[0] * v2[1] - v1[1] * v2[0];

    return result;
}

float compute_angle(float v1[3], float v2[3]) {
    float dot_product = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
    float magnitude_v1 = sqrt(v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2]);
    float magnitude_v2 = sqrt(v2[0] * v2[0] + v2[1] * v2[1] + v2[2] * v2[2]);

    float cos_angle = dot_product / (magnitude_v1 * magnitude_v2);
    float angle = acos(cos_angle);

    return angle;
}

int main() {
    // ex. start with convex polygon, begin counterclockwise traversal from vertex bx
    float vertices[5][3] = {
        {2, 0, 0},
        {0, 2, 0},
        {-2, 0, 0},
        {0, -2, 0},
        {0.5, 0.5, 0}
    };
    int num_vertices = sizeof(vertices) / sizeof(vertices[0]);

    float* polygon_centroid = compute_centroid(vertices, num_vertices);
    // printf("Centroid: (%f, %f, %f)\n", centroid[0], centroid[1], centroid[2]);

    // compute the normal vector of each star-triangle formed by the centroid and 2 polygon vertices
    // and weigh it by it's angle relative to the centroid to get the angle-weighted normal vector
    float angle_weighted_norm[3] = {0, 0, 0};
    float* normal_vectors[num_vertices];

    for (int i = 0; i < num_vertices; i++) {
        // form 2 vectors from centroid to vertices
        int next_vertex = (i + 1) % num_vertices; // if i is last vertex, next vertex is the first vertex
        float v1[3] = {vertices[i][0] - polygon_centroid[0], vertices[i][1] - polygon_centroid[1], vertices[i][2] - polygon_centroid[2]};
        float v2[3] = {vertices[next_vertex][0] - polygon_centroid[0], vertices[next_vertex][1] - polygon_centroid[1], vertices[next_vertex][2] - polygon_centroid[2]};
        
        // compute normal vector of star-triangle
        // not normalizing this vector means it is weighted by it's area
        float* normal = cross_product(v1, v2);
        
        normal_vectors[i] = normal;
        printf("Area Weighted Normal of Vertex %d: (%f, %f, %f)\n", i, normal[0], normal[1], normal[2]);
    }

    return 0;
}