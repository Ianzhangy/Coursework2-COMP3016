#include <vector>
using namespace std;

class ImportedModel
{
private:
	int numVertices;
	vector<glm::vec3> vertices;
	vector<glm::vec2> texCoords;
	vector<glm::vec3> normalVecs;
public:
	ImportedModel();
	ImportedModel(const char *filePath);
	int getNumVertices();
	vector<glm::vec3> getVertices();
	vector<glm::vec2> getTextureCoords();
	vector<glm::vec3> getNormals();
};

class ModelImporter
{
private:
	vector<float> vertVals;
	vector<float> triangleVerts;
	vector<float> textureCoords;
	vector<float> stVals;
	vector<float> normals;
	vector<float> normVals;
public:
	ModelImporter();
	void parseOBJ(const char *filePath);
	int getNumVertices();
	vector<float> getVertices();
	vector<float> getTextureCoordinates();
	vector<float> getNormals();
};