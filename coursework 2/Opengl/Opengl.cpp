#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <windows.h>
using namespace std;


#include "Sphere.h"
#include "Utils.h"
#include "ImportedModel.h"	


#define USE_UTIL  
#define ROOM_L  100  // room width
#define ROOM_HIGH  (ROOM_L/4) // room height


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


#define numVAOs 1 
#define numVBOs_obj	3 

Utils util = Utils();
float cameraX, cameraY, cameraZ;
float objLocX, objLocY, objLocZ;
GLuint renderingProgram;  // shader program

GLuint vao[numVAOs];
GLuint vbo_obj_sofa[1]; // vbo of obj



GLuint mvLoc, projLoc; 
int width, height;
int opendoor=0; // flag of open door
float aspect;
float tf;
glm::mat4 pMat, vMat, tMat, rMat, sMat,mMat, mvMat; // mat to shader

// Textures
GLuint brickTexture, floor_color_Texture, floor_stone_Texture,wood_Texture, door_Texture, light_Wood_Texture;
GLuint nameTexture, blackTexture, tvTexture;


// load obj model
ImportedModel myModel_sofa("obj/1/Tables_Chairs.obj");

bool changeTvTexutre = false; // flag of change tv texture


void display_obj(glm::mat4 &mvMat, ImportedModel *pModel, GLuint *pVBO_obj, int nSize, GLuint aTexture);
float toRadians(float degrees) { return (degrees * 2.0f * 3.14159f) / 360.0f; }

// init obj vao vbo 
void setupVertices_obj(ImportedModel &myModel, GLuint *vbo_obj,int nSize) {
std::vector<glm::vec3> vert = myModel.getVertices();
std::vector<glm::vec2> tex = myModel.getTextureCoords();
std::vector<glm::vec3> norm = myModel.getNormals();

std::vector<float> pvalues;
std::vector<float> tvalues;
std::vector<float> nvalues;

for (int i = 0; i < myModel.getNumVertices(); i++) {
	if (nSize >= 1) {
		pvalues.push_back((vert[i]).x);
		pvalues.push_back((vert[i]).y);
		pvalues.push_back((vert[i]).z);
	}
	if (nSize >= 2) {
		tvalues.push_back((tex[i]).s);
		tvalues.push_back((tex[i]).t);
	}
	if (nSize >= 3) {
		nvalues.push_back((norm[i]).x);
		nvalues.push_back((norm[i]).y);
		nvalues.push_back((norm[i]).z);
	}
}



	if (nSize >= 1) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo_obj[0]);
		glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, &pvalues[0], GL_STATIC_DRAW);
	}
	if (nSize >= 2) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo_obj[1]);
		glBufferData(GL_ARRAY_BUFFER, tvalues.size() * 4, &tvalues[0], GL_STATIC_DRAW);
	}
	if (nSize >= 3) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo_obj[2]);
		glBufferData(GL_ARRAY_BUFFER, nvalues.size() * 4, &nvalues[0], GL_STATIC_DRAW);
	}
}


// init cube vao vbo
unsigned int cubeVAO;
unsigned int VBO[3];
void setupVertice_Cube() {
	float  vertexPositions[] = {
		-0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f,  0.5f, -0.5f, 0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f, 0.5f, -0.5f,  0.5f, 0.5f,  0.5f,  0.5f, 0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f, 0.5f,  0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f,  0.5f, 0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f,  0.5f, 0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f, 0.5f,  0.5f, -0.5f, 0.5f,  0.5f,  0.5f, 0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f,
	};

	float textureCoordinates[] = {
			0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	float textureCoordinates1[] = {
		0.0f, 0.0f, 4.0f, 0.0f, 4.0f, 4.0f, 4.0f, 4.0f, 0.0f, 4.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 4.0f, 0.0f, 4.0f, 4.0f, 4.0f, 4.0f, 0.0f, 4.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 4.0f, 0.0f, 4.0f, 4.0f, 4.0f, 4.0f, 0.0f, 4.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 4.0f, 0.0f, 4.0f, 4.0f, 4.0f, 4.0f, 0.0f, 4.0f, 0.0f, 0.0f,
		0.0f, 4.0f, 4.0f, 4.0f, 4.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 4.0f,
		0.0f, 4.0f, 4.0f, 4.0f, 4.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 4.0f
	};

	glGenBuffers(3, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates), textureCoordinates, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates1), textureCoordinates1, GL_STATIC_DRAW);

	
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);



}



// init obj vao vbo
void setupVertices(void) {
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(1, vbo_obj_sofa);
	setupVertices_obj(myModel_sofa, vbo_obj_sofa, 3);
}




void init(GLFWwindow* window) {
	renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl"); // load shader
	
	objLocX = 0.0f; objLocY = 0.0f; objLocZ = 0.0f;

	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
	
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 32.0f;	

	// load textures
	floor_color_Texture = Utils::loadTexture("img/floor_color.jpg");
	wood_Texture = Utils::loadTexture("img/wood3.jpg");
	door_Texture = Utils::loadTexture("img/door.jpg");	

	light_Wood_Texture= Utils::loadTexture("img/light_Wood.jpg");
	floor_stone_Texture = Utils::loadTexture("img/3Dxy_Img_2.jpg");
	nameTexture = Utils::loadTexture("img/name.jpg");
	blackTexture = Utils::loadTexture("img/black.jpg");
	tvTexture = Utils::loadTexture("img/tv.jpg");  

	// set vao vbo
	setupVertices();
	setupVertice_Cube();
}

// display obj
void display_obj(glm::mat4 &mvMat, ImportedModel *pModel, GLuint *pVBO_obj,int nSize,GLuint aTexture)
{
	if (1) {
		if (0) {
			mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
			projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

			vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
			mMat = glm::translate(glm::mat4(1.0f), glm::vec3(objLocX, objLocY, objLocZ));

			mMat = glm::rotate(mMat, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			mMat = glm::rotate(mMat, toRadians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			mMat = glm::rotate(mMat, toRadians(35.0f), glm::vec3(0.0f, 0.0f, 1.0f));

			mvMat = vMat * mMat;
		}
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	}
	int idx = 0;
	if (idx < nSize) {
		glBindBuffer(GL_ARRAY_BUFFER, pVBO_obj[idx]);
		glVertexAttribPointer(idx, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(idx);
		idx++;
	}

	if (idx < nSize) {
		if (0) { //not use tx
			glBindBuffer(GL_ARRAY_BUFFER, pVBO_obj[idx]);
			glVertexAttribPointer(idx, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(idx);
		}
		idx++;
	}

	if (aTexture != 0xff) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, aTexture);
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, pModel->getNumVertices());
}


float doorAngle = 0; // door angel(-90 - 0)
float deltaTime = 0.0f;
float lastFrame = 0.0f;
void display(GLFWwindow* window, double currentTime) {

	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;


	glClearColor(0.0, 0.0, 0.0, 1.0); // background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(renderingProgram);

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");  // view * model matrix
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix"); // projection matrix

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ)); // lookat matrix (cam pos)

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));//apply project matrix [pMat] to [proj_matrix] in shader


	glEnable(GL_DEPTH_TEST); // enable depth test
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);





	if (opendoor) { // if flag opendoor doorAngle decrease util -89, == rotate -89.f
		doorAngle -= deltaTime * 50;
		if (doorAngle < -89) doorAngle = -89;
	}
	else {
		doorAngle += deltaTime * 50;
		if (doorAngle > 0) doorAngle = 0;
	}



	// behind
	{
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glm::mat4 model = glm::mat4(1.f);
		model = model * glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -ROOM_L * 0.5));
		model = model * glm::scale(glm::mat4(1.f), glm::vec3(ROOM_L, ROOM_HIGH, 0.001));
		mvMat = vMat * model;
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, wood_Texture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}


	// front
	{
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glm::mat4 model = glm::mat4(1.f);
		model = model * glm::translate(glm::mat4(1.f), glm::vec3(0, 0, ROOM_L * 0.5));
		model = model * glm::scale(glm::mat4(1.f), glm::vec3(ROOM_L, ROOM_HIGH, 0.001));
		mvMat = vMat * model;
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, wood_Texture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}

	// left 
	{
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glm::mat4 model = glm::mat4(1.f);
		model = model * glm::translate(glm::mat4(1.f), glm::vec3(-ROOM_L * 0.5, 0, 0));
		model = model * glm::scale(glm::mat4(1.f), glm::vec3(0.001, ROOM_HIGH, ROOM_L));
		mvMat = vMat * model;
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, wood_Texture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}


	// right 
	{
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glm::mat4 model = glm::mat4(1.f);
		model = model * glm::translate(glm::mat4(1.f), glm::vec3(ROOM_L * 0.5, 0, ROOM_L * 0.05));
		model = model * glm::scale(glm::mat4(1.f), glm::vec3(2, ROOM_HIGH, ROOM_L * 0.9));
		mvMat = vMat * model;
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, wood_Texture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}


	// door 
	{
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glm::mat4 model = glm::mat4(1.f);
		model = model * glm::translate(glm::mat4(1.f), glm::vec3(ROOM_L * 0.5, 0, ROOM_L * -0.45));
		model = model * glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -ROOM_L * 0.05));
		model = model * glm::rotate(glm::mat4(1.f), glm::radians(doorAngle), glm::vec3(0, 1, 0));
		model = model * glm::translate(glm::mat4(1.f), glm::vec3(0, 0, ROOM_L * 0.05));
		model = model * glm::scale(glm::mat4(1.f), glm::vec3(2, ROOM_HIGH, ROOM_L * 0.1));
		mvMat = vMat * model;
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, door_Texture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}

	// bottom 
	{
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glm::mat4 model = glm::mat4(1.f);
		model = model * glm::translate(glm::mat4(1.f), glm::vec3(0, -ROOM_HIGH * 0.5, 0));
		model = model * glm::scale(glm::mat4(1.f), glm::vec3(ROOM_L, 0.001, ROOM_L));
		mvMat = vMat * model;
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, floor_stone_Texture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}


	// top 
	{
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glm::mat4 model = glm::mat4(1.f);
		model = model * glm::translate(glm::mat4(1.f), glm::vec3(0, ROOM_HIGH * 0.5, 0));
		model = model * glm::scale(glm::mat4(1.f), glm::vec3(ROOM_L, 0.001, ROOM_L));
		mvMat = vMat * model;
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, floor_color_Texture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}


	// tv
	{
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glm::mat4 model = glm::mat4(1.f);
		model = model * glm::translate(glm::mat4(1.f), glm::vec3(-ROOM_L * 0.497, 0, 0));
		model = model * glm::scale(glm::mat4(1.f), glm::vec3(0.6, ROOM_HIGH * 0.4, ROOM_L * 0.16));
		mvMat = vMat * model;
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, blackTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}

	// tv photo
	{
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glm::mat4 model = glm::mat4(1.f);
		model = model * glm::translate(glm::mat4(1.f), glm::vec3(-ROOM_L * 0.497 + 0.31, 0, 0));
		model = model * glm::scale(glm::mat4(1.f), glm::vec3(0.001, ROOM_HIGH * 0.38, ROOM_L * 0.15));
		mvMat = vMat * model;
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));

		glActiveTexture(GL_TEXTURE0);
		if(changeTvTexutre)
			glBindTexture(GL_TEXTURE_2D, nameTexture);
		else {
			glBindTexture(GL_TEXTURE_2D, tvTexture);
		}
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}



	// display obj
	glBindVertexArray(vao[0]);
	tMat = glm::mat4(1.0f);
	float fscale = 2 + fabs(20 * sin(tf)); //test for scale
	rMat = glm::rotate(glm::mat4(1.0f), 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	sMat = glm::scale(rMat, glm::vec3(fscale, fscale, fscale));
	rMat = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));	//tf
	mMat = tMat * rMat;
	mvMat = vMat * mMat;
	sMat = glm::scale(glm::mat4(1.0f), glm::vec3(2, 2, 2));
	glm::mat4 mT =glm::translate(mvMat, glm::vec3(0,-13,0));//mvMat drop to floor
	mvMat = mT * sMat;
	display_obj(mvMat, &myModel_sofa,vbo_obj_sofa,3, light_Wood_Texture);
}





void window_size_callback(GLFWwindow* win, int newWidth, int newHeight) {
	aspect = (float)newWidth / (float)newHeight;
	glViewport(0, 0, newWidth, newHeight);
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}




const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and configure
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MyOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSwapInterval(1);
	init(window);
	
	// render loop
	// renderingProgram
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}



void processInput(GLFWwindow *window)
{

	int step = 1;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraX -= step;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraX += step;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraZ -= step;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraZ += step;
	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		cameraY -= step;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		cameraY += step;
	}


	// name texutre 
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		changeTvTexutre = true;
	}

	// tv texture
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		changeTvTexutre = false;
	}

	// open door
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
		opendoor = true;
	}

	// close door
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		opendoor = false;
	}



	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		tf = 0;
		changeTvTexutre = false;
		opendoor = false;
		cameraX = 0.0f; cameraY = 0.0f; cameraZ = 32.0f;
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
