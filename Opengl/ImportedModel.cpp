#include <fstream>
#include <sstream>
#include <glm\glm.hpp>
#include "ImportedModel.h"

using namespace std;


// Constructor for ImportedModel
ImportedModel::ImportedModel() {}

// Constructor for ImportedModel that loads a model from an OBJ file
ImportedModel::ImportedModel(const char *filePath) {
	ModelImporter modelImporter = ModelImporter();
	modelImporter.parseOBJ(filePath);
	numVertices = modelImporter.getNumVertices();
	vector<float> verts = modelImporter.getVertices();
	vector<float> tcs = modelImporter.getTextureCoordinates();
	vector<float> normals = modelImporter.getNormals();

	for (int i = 0; i < numVertices; i++) {
		vertices.push_back(glm::vec3(verts[i*3], verts[i*3+1], verts[i*3+2]));
		texCoords.push_back(glm::vec2(tcs[i*2], tcs[i*2+1]));
		normalVecs.push_back(glm::vec3(normals[i*3], normals[i*3+1], normals[i*3+2]));
	}
}
// Get the number of vertices in the ImportedModel
int ImportedModel::getNumVertices() { return numVertices; }
// Get the vertices of the ImportedModel
vector<glm::vec3> ImportedModel::getVertices() { return vertices; }
// Get the texture coordinates of the ImportedModel
vector<glm::vec2> ImportedModel::getTextureCoords() { return texCoords; }
// Get the normals of the ImportedModel
vector<glm::vec3> ImportedModel::getNormals() { return normalVecs; }


// Constructor for ModelImporter
ModelImporter::ModelImporter() {}


// Parse an OBJ file and extract its data
void ModelImporter::parseOBJ(const char *filePath) {
	float x, y, z;
	string content;
	ifstream fileStream(filePath, ios::in);
	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		if (line.compare(0, 2, "v ") == 0) {
			stringstream ss(line.erase(0, 1));
			ss >> x; ss >> y; ss >> z;
			vertVals.push_back(x);
			vertVals.push_back(y);
			vertVals.push_back(z);
		}
		if (line.compare(0, 2, "vt") == 0) {
			stringstream ss(line.erase(0, 2));
			ss >> x; ss >> y;
			stVals.push_back(x);
			stVals.push_back(y);
		}
		if (line.compare(0, 2, "vn") == 0) {
			stringstream ss(line.erase(0, 2));
			ss >> x; ss >> y; ss >> z;
			normVals.push_back(x);
			normVals.push_back(y);
			normVals.push_back(z);
		}
		if (line.compare(0, 2, "f ") == 0) {
			string oneCorner, v, t, n;
			stringstream ss(line.erase(0, 2));
			for (int i = 0; i < 3; i++) {
				getline(ss, oneCorner, ' ');
				stringstream oneCornerSS(oneCorner);
				getline(oneCornerSS, v, '/');
				getline(oneCornerSS, t, '/');
				getline(oneCornerSS, n, '/');

				int vertRef = (stoi(v) - 1) * 3;
				int tcRef = (stoi(t) - 1) * 2;
				int normRef = (stoi(n) - 1) * 3;

				triangleVerts.push_back(vertVals[vertRef]);
				triangleVerts.push_back(vertVals[vertRef + 1]);
				triangleVerts.push_back(vertVals[vertRef + 2]);

				textureCoords.push_back(stVals[tcRef]);
				textureCoords.push_back(stVals[tcRef + 1]);

				normals.push_back(normVals[normRef]);
				normals.push_back(normVals[normRef + 1]);
				normals.push_back(normVals[normRef + 2]);
			}
		}
	}
}
// Get the number of vertices in the parsed model
int ModelImporter::getNumVertices() { return (triangleVerts.size()/3); }
// Get the vertices of the parsed model
vector<float> ModelImporter::getVertices() { return triangleVerts; }
// Get the texture coordinates of the parsed model
vector<float> ModelImporter::getTextureCoordinates() { return textureCoords; }
// Get the normals of the parsed model
vector<float> ModelImporter::getNormals() { return normals; }