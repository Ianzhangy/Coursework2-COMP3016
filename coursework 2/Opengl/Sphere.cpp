#include <cmath>
#include <vector>
#include <iostream>
#include <glm\glm.hpp>
#include "Sphere.h"
using namespace std;

Box3D::Box3D() {
	init(1);
}

Box3D::Box3D(int scale) {
	init(scale);
}

void Box3D::init(int scale) {
    numVertices = 0;

    // Initially, no vertices exist, so the loop for adding tangents does not execute
    for (int i = 0; i < numVertices; i++) {
        tangents.push_back(glm::vec3());
    }

    numVertices = 4; // Setting the number of vertices to 4 (for a square)
    // Define vertices of a square
    float vertices0[] = {
        // x, y, z
        -0.25f, -0.25f, 0.0f, // Vertex 0, bottom left corner
        0.25f, -0.25f, 0.0f,  // Vertex 1, bottom right corner
        0.25f,  0.25f, 0.0f,  // Vertex 2, top right corner
        -0.25f,  0.25f, 0.0f, // Vertex 3, top left corner
    };
    // Scale and store the vertices
    for (int i = 0; i < numVertices; i++) {
        vertices0[i] *= 4 * scale;
        vertices.push_back(glm::vec3(vertices0[0 + i * 3], vertices0[1 + i * 3], vertices0[2 + i * 3]));
        normals.push_back(glm::vec3(0, 0, 1)); // Normal vector facing up
    }

    // Texture coordinates for each vertex
    float tx_1[] = {
        0.0f, 0.0f, 0.0f, // Texture coordinate for Vertex 0
        1.0f, 0.0f, 0.0f, // Texture coordinate for Vertex 1
        1.0f, 1.0f, 0.0f, // Texture coordinate for Vertex 2
        0.0f, 1.0f, 0.0f, // Texture coordinate for Vertex 3
    };
    for (int i = 0; i < numVertices; i++) {
        texCoords.push_back(glm::vec2(tx_1[0 + i * 3], tx_1[1 + i * 3]));
    }

    // Indices define two triangles that make up the square
    int indices0[] = {
        0, 1, 3, // Indices for the first triangle
        1, 2, 3  // Indices for the second triangle
    };
    numIndices = 6; // Setting the number of indices (6 for two triangles)
    for (int i = 0; i < numIndices; i++) {
        indices.push_back(indices0[i]);
    }
}


Sphere::Sphere() {
	init(48);
}

Sphere::Sphere(int prec) {
	init(prec);
}

void Sphere::init(int prec) {
	numVertices = (prec + 1) * (prec + 1);
	numIndices = prec * prec * 6;
	for (int i = 0; i < numVertices; i++) { vertices.push_back(glm::vec3()); }
	for (int i = 0; i < numVertices; i++) { texCoords.push_back(glm::vec2()); }
	for (int i = 0; i < numVertices; i++) { normals.push_back(glm::vec3()); }
	for (int i = 0; i < numVertices; i++) { tangents.push_back(glm::vec3()); }
	for (int i = 0; i < numIndices; i++) { indices.push_back(0); }

	// calculate triangle vertices
	for (int i = 0; i <= prec; i++) {
		for (int j = 0; j <= prec; j++) {
			float y = (float)cos(toRadians(180.0f - i * 180.0f / prec));
			float x = -(float)cos(toRadians(j*360.0f / prec))*(float)abs(cos(asin(y)));
			float z = (float)sin(toRadians(j*360.0f / (float)(prec)))*(float)abs(cos(asin(y)));
			vertices[i*(prec + 1) + j] = glm::vec3(x, y, z);
			texCoords[i*(prec + 1) + j] = glm::vec2(((float)j / prec), ((float)i / prec));
			normals[i*(prec + 1) + j] = glm::vec3(x, y, z);

			// calculate tangent vector
			if (((x == 0) && (y == 1) && (z == 0)) || ((x == 0) && (y == -1) && (z == 0))) {
				tangents[i*(prec + 1) + j] = glm::vec3(0.0f, 0.0f, -1.0f);
			}
			else {
				tangents[i*(prec + 1) + j] = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(x, y, z));
			}
		}
	}
	// calculate triangle indices
	for (int i = 0; i<prec; i++) {
		for (int j = 0; j<prec; j++) {
			indices[6 * (i*prec + j) + 0] = i*(prec + 1) + j;
			indices[6 * (i*prec + j) + 1] = i*(prec + 1) + j + 1;
			indices[6 * (i*prec + j) + 2] = (i + 1)*(prec + 1) + j;
			indices[6 * (i*prec + j) + 3] = i*(prec + 1) + j + 1;
			indices[6 * (i*prec + j) + 4] = (i + 1)*(prec + 1) + j + 1;
			indices[6 * (i*prec + j) + 5] = (i + 1)*(prec + 1) + j;
		}
	}
}

float Obj3D::toRadians(float degrees) { return (degrees * 2.0f * 3.14159f) / 360.0f; }

int Obj3D::getNumVertices() { return numVertices; }
int Obj3D::getNumIndices() { return numIndices; }
vector<int> Obj3D::getIndices() { return indices; }
vector<glm::vec3> Obj3D::getVertices() { return vertices; }
vector<glm::vec2> Obj3D::getTexCoords() { return texCoords; }
vector<glm::vec3> Obj3D::getNormals() { return normals; }
vector<glm::vec3> Obj3D::getTangents() { return tangents; }