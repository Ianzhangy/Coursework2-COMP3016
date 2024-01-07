#include <cmath>
#include <vector>
#include <glm\glm.hpp>
using namespace std;

class Obj3D
{
public:
	Obj3D() {};
	int numVertices;
	int numIndices;
	vector<int> indices;
	vector<glm::vec3> vertices;
	vector<glm::vec2> texCoords;
	vector<glm::vec3> normals;
	vector<glm::vec3> tangents;

public:

	float toRadians(float degrees);
	int getNumVertices();
	int getNumIndices();
	vector<int> getIndices();
	vector<glm::vec3> getVertices();
	vector<glm::vec2> getTexCoords();
	vector<glm::vec3> getNormals();
	vector<glm::vec3> getTangents();
};


class Sphere:public Obj3D
{

public:
	Sphere();
	Sphere(int prec);
	

public:
	void init(int);
};


class Box3D :public Obj3D
{

public:
	Box3D();
	Box3D(int scale);


public:
	void init(int);
};