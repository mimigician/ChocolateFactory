//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "sphere.h"
#include "cube.h"
#include "stb_image.h"

#include <iostream>
#include <stdlib.h>
#include<windows.h> 

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
//void sideWall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void frontWall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void roof(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void ladder(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);

void table(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void mixer(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void oven(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void shelf(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
//void boxShelf(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void bench(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void roomTable(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void fan(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void stick(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void soap_container(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void stairs(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void cart(unsigned int& cubeVAO, Sphere sphere, Shader& lightingShader, glm::mat4 alTogether);

void boxShelf(Cube cube, Cube cube2, Shader& lightingShaderWithTexture, glm::mat4 alTogether);
void rackChocolates(Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether);
void floor(Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether);
void sideWall(Cube cube, Cube cube2, Shader& lightingShaderWithTexture, glm::mat4 alTogether);
void machineChocolates(Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether);
void bathroom_wall(Cube cube, Cube cube1, Cube cube2, Cube cube3, Cube cube4, Cube cube5, Cube cube6, Cube cube7, Shader& lightingShaderWithTexture, glm::mat4 alTogether);
void roomWall(Cube cube, Cube cube2,Shader& lightingShaderWithTexture, glm::mat4 alTogether);

void cocoa_bean(Sphere sphere, Shader& lightingShader, glm::mat4 alTogether);

//void drawCurveObj(unsigned int& bezierVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b, float s);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
void drawCurveObj(unsigned int& bezierVAO_, Shader& lightingShader, glm::mat4 model,  float r, float g, float b, float shine);


long long nCr(int n, int r);
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L);
unsigned int hollowBezier(GLfloat ctrlpoints[], int L, vector <float>& coordinates,
    vector <float>& normals,
    vector <int>& indices,
    vector <float>& vertices);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

//for curves
vector <float> cntrlPoints = {
-0.8200, 1.6350, 5.1000,
-0.8050, 1.4000, 5.1000,
-0.7600, 1.2750, 5.1000,
-0.6600, 1.1750, 5.1000,
-0.5850, 1.1100, 5.1000,
-0.4550, 1.0400, 5.1000,
-0.3250, 0.9950, 5.1000,
-0.2200, 0.9650, 5.1000,
-0.0950, 0.9700, 5.1000,
};

vector <float> lampPoints = {
-0.1400, 1.6450, 5.1000,
-0.3850, 1.6350, 5.1000,
-0.5350, 1.2250, 5.1000,
-0.6600, 0.9500, 5.1000,
-0.2800, 0.9200, 5.1000,
};

vector <float> cylinderPoints = {
-0.4250, 1.9950, 5.1000,
-0.4250, 0.2900, 5.1000,
};

vector <float> chimneyHeadPoints = {
-0.3900, 1.5450, 5.1000,
-0.6300, 1.2150, 5.1000,
};

vector <float> chimneyPoints = {
-0.2400, 2.1150, 5.1000,
-0.4100, 0.6600, 5.1000,
};

vector <float> coordinates;
vector <float> normals;
vector <int> indices;
vector <float> vertices;

vector <float> lampCoordinates;
vector <float> lampNormals;
vector <int> lampIndices;
vector <float> lampVertices;

vector <float> cylinderCoordinates;
vector <float> cylinderNormals;
vector <int> cylinderIndices;
vector <float> cylinderVertices;

vector <float> chimneyHeadCoordinates;
vector <float> chimneyHeadNormals;
vector <int> chimneyHeadIndices;
vector <float> chimneyHeadVertices;

vector <float> chimneyCoordinates;
vector <float> chimneyNormals;
vector <int> chimneyIndices;
vector <float> chimneyVertices;

class point
{
public:
    point()
    {
        x = 0;
        y = 0;
    }
    int x;
    int y;
} clkpt[2];

const double pi = 3.14159265389;
const int nt = 40;
const int ntheta = 20;

bool loadBezierCurvePoints = true;
bool showHollowBezier = true;
bool lineMode = false;
unsigned int bezierVAO;
unsigned int bezierVAO2;
unsigned int bezierVAO3;
unsigned int bezierVAO4;
unsigned int bezierVAO5;

// modelling transform
float rotateAngleFan_Y = 0.0;
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

float r = 0.0f;
float beltTranslate = 0.01f;
float beltGateTranslate = 0.003f;
float beltSpeed = 0.0f;
float beltGate = 0.0f;
float chocolateSpeed = 0.0f;
float bowlSpeed = 0.0f;
float cocoaSpeed = 0.0f;
float cocoaTranslate = 0.004f;
float bowlTranslate = 0.15f;
float mixerSpeed = 0.0f;
float bathDoorSpeed = 0.0f;
float bathDoorTranslate = 1.0f;
float mainDoorSpeed = 0.0f;
float mainDoorTranslate = 1.0f;

bool fanSwitch = false;
bool beltSwitch = false;
bool bowlSwitch = false;
bool mixerSwitch = false;
bool bathDoorSwitch = false;
bool mainDoorSwitch = false;

bool flagForGate = false;
bool cocoaFall = false;
bool uncutBarFlag = false;

// camera
Camera camera(glm::vec3(2.0f, 1.1f, 11.2f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);


// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(-1.00f,  1.9f,  0.0f),
    glm::vec3(2.0f,  1.9f,  0.0f),
    glm::vec3(4.0f,  1.9f,  0.0f)
};

glm::vec3 directionalLightDirection = -glm::vec3(3.0f, 6.0f, 9.0f);

glm::vec3 spotLightPosition = glm::vec3(0.0f, 1.9f, 0.0f);
glm::vec3 spotLightDirection = glm::vec3(0.0f, -1.0f, 0.0f);

PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position 
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);

DirectionalLight directionallight(

    directionalLightDirection.x, directionalLightDirection.y, directionalLightDirection.z,  // direction
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f        // specular
);

SpotLight spotlight(

    spotLightPosition.x, spotLightPosition.y, spotLightPosition.z,  // position
    spotLightDirection.x, spotLightDirection.y, spotLightDirection.z, // direction
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(21.5f))
);


// light settings
bool pointLightOn = true;
bool directionalLightOn = true;
bool spotLightOn = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;


// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

//rotate
bool isRotate = false;
float fanSpeed = 5.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);



    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    

    Sphere sphere = Sphere();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");

    // Floor texture
    string diffuseMapPath = "floor 3.jpg";
    string specularMapPath = "floor_spec.png";

    string specularMapPath3 = "black_specular.jpg";


    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // Packet chocolate texture
    string diffuseMapPath2 = "mimi.jpg";
    string specularMapPath2 = "white.png";

    unsigned int diffMap2 = loadTexture(diffuseMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap2 = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube2 = Cube(diffMap2, specMap2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // Hand sign texture
    string diffuseMapPath3 = "hand_sign.png";
    unsigned int diffMap3 = loadTexture(diffuseMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap3 = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube sign_cube = Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // Chocolate bar texture
    string diffuseMapPath4 = "chocolate.jpg";
    unsigned int diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap4 = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube choco_bar_cube = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // Bathroom wall texture
    diffuseMapPath4 = "bathroom_wall.jpg";
    diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap4 = loadTexture(specularMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube bathroom_wall_cube = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // Toilet pan texture
    string diffuseMapPath5 = "ss.png";
    unsigned int diffMap5 = loadTexture(diffuseMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap5 = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube toilet_cube = Cube(diffMap5, specMap5, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // Bathroom floor texture
    diffuseMapPath4 = "bathroom_floor.png";
    diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap4 = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube bathroom_floor_cube = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // Basin texture
    diffuseMapPath4 = "basin.png";
    diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap4 = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube basin_cube = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // Mirror texture
    diffuseMapPath4 = "mirror.png";
    diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap4 = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube mirror_cube = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // Tap texture
    diffuseMapPath4 = "basin_tap.jpg";
    diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap4 = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube tap_cube = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // soap texture
    diffuseMapPath4 = "soap.png";
    diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap4 = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube soap_cube = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // bath door texture
    diffuseMapPath4 = "door.png";
    diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap4 = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube bath_door_cube = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // wall texture
    diffuseMapPath4 = "wall2.jpg";
    diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap4 = loadTexture(specularMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube wall_cube = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // door texture
    diffuseMapPath4 = "door2.png";
    diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap4 = loadTexture(specularMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube room_door_cube = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // cardboard texture
    diffuseMapPath4 = "cardboard.png";
    diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap4 = loadTexture(specularMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cardboard_cube = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // cardboard texture
    diffuseMapPath4 = "metal.png";
    diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap4 = loadTexture(specularMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube metal_cube = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // main gate texture
    diffuseMapPath4 = "maingate.png";
    diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap4 = loadTexture(specularMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube main_gate_cube = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //curve vao,vbo,veo creation by hallowBazier
    bezierVAO = hollowBezier(cntrlPoints.data(), ((unsigned int)cntrlPoints.size() / 3) - 1, coordinates, normals, indices, vertices);
    loadBezierCurvePoints = false;
    showHollowBezier = true;

    bezierVAO2 = hollowBezier(lampPoints.data(), ((unsigned int)lampPoints.size() / 3) - 1, lampCoordinates, lampNormals, lampIndices, lampVertices);
    loadBezierCurvePoints = false;
    showHollowBezier = true;

    bezierVAO3 = hollowBezier(cylinderPoints.data(), ((unsigned int)cylinderPoints.size() / 3) - 1, cylinderCoordinates, cylinderNormals, cylinderIndices, cylinderVertices);
    loadBezierCurvePoints = false;
    showHollowBezier = true;

    bezierVAO4 = hollowBezier(chimneyHeadPoints.data(), ((unsigned int)chimneyHeadPoints.size() / 3) - 1, chimneyHeadCoordinates, chimneyHeadNormals, chimneyHeadIndices, chimneyHeadVertices);
    loadBezierCurvePoints = false;
    showHollowBezier = true;

    bezierVAO5 = hollowBezier(chimneyPoints.data(), ((unsigned int)chimneyPoints.size() / 3) - 1, chimneyCoordinates, chimneyNormals, chimneyIndices, chimneyVertices);
    loadBezierCurvePoints = false;
    showHollowBezier = true;

    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        pointlight2.setUpPointLight(lightingShader);

        // set up directional and spot lights
        directionallight.setUpDirectionalLight(lightingShader);
        spotlight.setUpSpotLight(lightingShader);

        
        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        //lightingShaderWithTexture.setMat4("view", view);
        lightingShader.setMat4("view", view);

        // Modelling Transformation for texture
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 0.0f, -4.0f));







        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);

        //glBindVertexArray(cubeVAO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        //sideWall(cubeVAO, lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(9.2f, translate_Y, translate_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        //sideWall(cubeVAO, lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        //frontWall(cubeVAO, lightingShader, model);
        roof(cubeVAO, lightingShader, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.5f, 0.5f, -.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        table(cubeVAO, lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.65f, translate_Y, -2.4f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        mixer(cubeVAO, lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.5f, translate_Y, -3.8f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        oven(cubeVAO, lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5f, 0.1, -3.8f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        shelf(cubeVAO, lightingShader, model);

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.2f, 0.1, -2.0f)); //5.5 3.8
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        bench(cubeVAO, lightingShader, model);

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.0, 5.0f)); //5.5 3.8
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        //stairs(cubeVAO, lightingShader, model);

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.0, 7.0f)); //5.5 3.8
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        //cart(cubeVAO, sphere, lightingShader, model);

        //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.2f, 0.1, -1.8f)); //7.2 -2
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        roomTable(cubeVAO, lightingShader, model);

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, 0.08f, -2.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        stick(cubeVAO, lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.00f, 0.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        soap_container(cubeVAO, lightingShader, model);

        for (float i = 0.0f; i <= 1.5f; i += 1.5f) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(2.12f + i, 0.00f, -3.1f));
            rotateZMatrix = glm::rotate(identityMatrix, glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
            ladder(cubeVAO, lightingShader, model);
        }
        


        //-------------------------------------------
        // Bezier curves

        lightingShader.use();

        // Bowl
        if (bowlSwitch == true && bowlSpeed <= 40.0f)
        {
            bowlSpeed += bowlTranslate;
            if (bowlSpeed >= 40.0f) {
                cocoaFall = true;
            }

        }
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.f, 0.85f, -2.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z + bowlSpeed), glm::vec3(0.0f, 0.0f, 1.0f)); //
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
        glm::mat4 model_for_half_sphere = translateMatrix * rotateZMatrix * rotateXMatrix * rotateYMatrix *  scaleMatrix;

        //drawCurveObj(bezierVAO, lightingShader, model_for_pointlight, 1.0f, 1.0f, 1.0f, 1.0f);
        drawCurveObj(bezierVAO, lightingShader, model_for_half_sphere, 0.67f, 0.66f, 0.68f, 2.0f);

        //point light 1
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(pointLightPositions[0].x + 0.05f, pointLightPositions[0].y - 0.065, pointLightPositions[0].z + 0.05f) );
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
        glm::mat4 model_for_pointLight = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        drawCurveObj(bezierVAO2, lightingShader, model_for_pointLight, 1.0f, 1.0f, 1.0f, 32.0f);

        //point light 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(pointLightPositions[1].x + 0.05f, pointLightPositions[1].y - 0.065, pointLightPositions[1].z + 0.05f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
        model_for_pointLight = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        drawCurveObj(bezierVAO2, lightingShader, model_for_pointLight, 1.0f, 1.0f, 1.0f, 32.0f);

        //spotlight
        translateMatrix = glm::translate(identityMatrix, glm::vec3(spotLightPosition.x + 0.05f, spotLightPosition.y - 0.075, spotLightPosition.z + 0.05f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
        model_for_pointLight = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        drawCurveObj(bezierVAO2, lightingShader, model_for_pointLight, 1.0f, 1.0f, 1.0f, 32.0f);

        //Big Chimney
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.8f, 0.7f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 2.0f, 1.0f));
        model_for_pointLight = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        drawCurveObj(bezierVAO5, lightingShader, model_for_pointLight, 1.0f, 1.0f, 1.0f, 32.0f);


        // --------------------CHIMNEY-------------------------
        //cylinder
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.6f, 1.6f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.2f, 0.4f));
        model_for_pointLight = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        drawCurveObj(bezierVAO3, lightingShader, model_for_pointLight, 1.0f, 1.0f, 1.0f, 32.0f);
        //chimney head
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.6f, 1.38f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.2f, 0.4f));
        model_for_pointLight = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        drawCurveObj(bezierVAO4, lightingShader, model_for_pointLight, 1.0f, 1.0f, 1.0f, 32.0f);

        for (float i = 0.0f; i <= 1.5f; i += 1.5f) {
            //gallon cylinder
            translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f + i, 0.0f, -3.0f));
            //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.f), glm::vec3(1.0f, 0.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.f, 0.5f, 1.0f));
            model_for_pointLight = translateMatrix * scaleMatrix;
            drawCurveObj(bezierVAO3, lightingShader, model_for_pointLight, 0.67f, 0.66f, 0.68f, 2.0f);

            // gallon head
            translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f + i, 1.8f, -3.0f));
            rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
            rotateZMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.51f, 0.51f, 0.51f));
            model_for_half_sphere = translateMatrix * rotateZMatrix * rotateXMatrix * rotateYMatrix * scaleMatrix;

            drawCurveObj(bezierVAO, lightingShader, model_for_half_sphere, 0.67f, 0.66f, 0.68f, 2.0f);
        }
        




        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAxis_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAxis_Y), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAxis_Z), glm::vec3(1.0f, 0.0f, 0.0f));
        //sphere
        glm::mat4 modelForSphere = glm::mat4(1.0f);
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
        modelForSphere = glm::translate(model, -directionalLightDirection);
        //sphere.setRadius(.4f);
        sphere.drawSphere(lightingShader, modelForSphere);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.02f, 1.19f - cocoaSpeed, -2.1f));
        if (cocoaFall) {
            if (translateMatrix[3].y >= 0.25) {
                cocoaSpeed += cocoaTranslate;
                //cout << translateMatrix[3].y << endl;
            }
            //for (float i = 0.0f; i <= 1.0f; i += 0.2f)
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.02f, 1.19f - cocoaSpeed, -2.1f));
            model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
            cocoa_bean(sphere, lightingShader, model);
            
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.02f, 1.1f - cocoaSpeed, -2.1f));
            model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
            cocoa_bean(sphere, lightingShader, model);
        }
        

        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);


        
        //---------------------------------
        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 2; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.1f)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
            //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // we now draw as many light bulbs as we have directional lights.
        //glBindVertexArray(lightCubeVAO);
        //model = glm::mat4(1.0f);
        //model = glm::translate(model, -directionalLightDirection);
        //model = glm::scale(model, glm::vec3(0.3f)); // Make it a smaller cube
        //ourShader.setMat4("model", model);
        //ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.2f));
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        ////we now draw as many light bulbs as we have spot lights.
        //glBindVertexArray(lightCubeVAO);
        //model = glm::mat4(1.0f);
        //model = glm::translate(model, spotLightPosition);
        //model = glm::scale(model, glm::vec3(0.1f)); // Make it a smaller cube
        //ourShader.setMat4("model", model);
        //ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //-----------------------------
        



        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAxis_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAxis_Y), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAxis_Z), glm::vec3(1.0f, 0.0f, 0.0f));

        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);

        
        lightingShaderWithTexture.setMat4("projection", projection);
        lightingShaderWithTexture.setMat4("view", view);

        
        lightingShaderWithTexture.use(); // check for double usage
        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        //directional light
        directionallight.setUpDirectionalLight(lightingShaderWithTexture);
        //spot Light
        spotlight.setUpSpotLight(lightingShaderWithTexture);

        
        
        
        lightingShaderWithTexture.use();

        // Floor
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 0.0f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.3f, 0.1f, 10.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));   //use this when floor function is called
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        glm::mat4 modelMatrixForContainer = glm::mat4(1.0f);
        modelMatrixForContainer = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);
        //floor(cube, lightingShaderWithTexture, model); //texture becoming black when function is used

        //Wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        sideWall(wall_cube, main_gate_cube, lightingShaderWithTexture, model);

        // Room
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        roomWall(wall_cube, room_door_cube, lightingShaderWithTexture, model);

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.6f, -.1f, 3.8f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        boxShelf(metal_cube, cardboard_cube, lightingShaderWithTexture, model);

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        //Chocolates
        glm :: mat4 translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-1.5f, 0.02f, -3.8f));
        glm :: mat4 scaleMatrix2 = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        glm :: mat4 model2 = translateMatrix3 * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix2;

        rackChocolates(cube2, lightingShaderWithTexture, model2);

        //Hand sign
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(0.0f, 0.25f, 0.52f));
        scaleMatrix2 = glm::scale(identityMatrix, glm::vec3(1.0f, 0.5f, 0.01f));
        model2 = translateMatrix3 * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix2;

        sign_cube.drawCubeWithTexture(lightingShaderWithTexture, model2);

        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAxis_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAxis_Y), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAxis_Z), glm::vec3(1.0f, 0.0f, 0.0f));
        // Chocolate bar
        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(0.0f + chocolateSpeed, 0.2f, -0.5f)); //1.5 e stop
        if (flagForGate) {
            if (translateMatrix3[3].x <= 1.5f) {
                chocolateSpeed += 0.005f;
            }
            translateMatrix3 = glm::translate(identityMatrix, glm::vec3(0.0f + chocolateSpeed, 0.2f, -0.5f)); //1.5 e stop
            scaleMatrix2 = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
            model2 = translateMatrix3 * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix2;

            machineChocolates(choco_bar_cube, lightingShaderWithTexture, model2);
        }

        translateMatrix3 = glm::translate(identityMatrix, glm::vec3(7.f, 0.0f, 7.f));
        scaleMatrix2 = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Y));
        model2 = translateMatrix3 * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix2;
        bathroom_wall(bathroom_wall_cube, toilet_cube, bathroom_floor_cube, basin_cube, mirror_cube, tap_cube, soap_cube, bath_door_cube, lightingShaderWithTexture, model2);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f, float s = 32.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.emission", glm::vec3(0, 0, 0));
    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.3f, 0.3f, 0.3f));
    lightingShader.setFloat("material.shininess", s);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void drawCurveObj(unsigned int& bezierVAO_, Shader& lightingShader, glm::mat4 model,  float r = 1.0f, float g = 1.0f, float b = 1.0f, float shine = 32.0f) {
    lightingShader.use();
    lightingShader.setMat4("model", model);
    lightingShader.setVec3("material.emission", glm::vec3(0, 0, 0));
    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", shine);

    glBindVertexArray(bezierVAO_);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);

    // unbind VAO
    glBindVertexArray(0);
}


//void sideWall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
//{
//    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    glm::mat4 translateMatrix, scaleMatrix, model;
//
//    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 0.0f, -4.0f));
//    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 10.0f));
//    model = alTogether * translateMatrix * scaleMatrix;
//    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075, 32.0f);
//}

//void frontWall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
//{
//    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    glm::mat4 translateMatrix, scaleMatrix, model;
//
//    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 0.0f, -4.0f));
//    scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.3f, 2.0f, 0.1f));
//    model = alTogether * translateMatrix * scaleMatrix;
//    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075, 32.0f);
//}

void roof(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 2.0f, -4.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.3f, 0.1f, 10.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075, 32.0f);
}

//void floor(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
//{
//    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    glm::mat4 translateMatrix, scaleMatrix, model;
//
//    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, -2.0f, -4.0f));
//    scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.3f, 0.1f, 10.0f));
//    model = alTogether * translateMatrix * scaleMatrix;
//    drawCube(cubeVAO, lightingShader, model, 0.51f, 0.44f, 0.38f, 32.0f);
//}

void stick(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    //vertical stand
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.03f, 1.5f, 0.03f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0, 32.0f);

    //horizontal
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.03f, 1.5f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.48f, 0.03f, 0.03f)); //-.48 final
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0, 32.0f);
}


void table(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{

    // Top
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.5f, 0.1f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.87f, 0.72f, 0.53f, 32.0f);

    // Leg 1
    glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.02f, -0.46f, 0.01f));
    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.1f, .5f, 0.1f));
    model1 = alTogether * translateMatrix1 * scaleMatrix1;
    drawCube(cubeVAO, lightingShader, model1, .44f, .47f, .49f, 32.0f);

    // Leg 2
    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.02f, -0.46f, 0.83f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.1f, .5f, 0.1f));
    model2 = alTogether * translateMatrix2 * scaleMatrix2;
    drawCube(cubeVAO, lightingShader, model2, .44f, .47f, .49f, 32.0f);

    // Leg 3
    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(4.0f, -0.46f, 0.01f));
    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.1f, .5f, 0.1f));
    model1 = alTogether * translateMatrix1 * scaleMatrix1;
    drawCube(cubeVAO, lightingShader, model1, .44f, .47f, .49f, 32.0f);

    // Leg 4
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(4.0f, -0.46f, 0.83f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.1f, .5f, 0.1f));
    model2 = alTogether * translateMatrix2 * scaleMatrix2;
    drawCube(cubeVAO, lightingShader, model2, .44f, .47f, .49f, 32.0f);

    // cutter back
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(1.3f, -0.46f, -0.02f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(1.5f, 0.9f, 0.01f));
    model2 = alTogether * translateMatrix2 * scaleMatrix2;
    drawCube(cubeVAO, lightingShader, model2, .44f, .47f, .49f, 32.0f);

    // cutter front
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(1.3f, -0.46f, 1.01f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(1.5f, 0.9f, 0.01f));
    model2 = alTogether * translateMatrix2 * scaleMatrix2;
    drawCube(cubeVAO, lightingShader, model2, .44f, .47f, .49f, 32.0f);

    // cutter top
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(1.3f, 0.35f, -0.01f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(1.5f, 0.01f, 1.02f));
    model2 = alTogether * translateMatrix2 * scaleMatrix2;
    drawCube(cubeVAO, lightingShader, model2, .44f, .47f, .49f, 32.0f);

    //uncut bar
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05f + beltSpeed, 0.1f, 0.2f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.02f, 0.6f));
    glm::vec3 translation = glm::vec3(translateMatrix[3]);
    //bool flagForGate = false;
    bool flagForGateOpen = false;
    if (translateMatrix[3].x <= 1.53) {
        if (uncutBarFlag == true) {
            if (beltSwitch == true)
            {
                beltSpeed += beltTranslate;
            }
            model = alTogether * translateMatrix * scaleMatrix;


            drawCube(cubeVAO, lightingShader, model, 0.25f, 0.1f, 0.0f, 32.0f);
        }
        
    }
    else {
        flagForGate = true;
    }

    // cutter left
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(1.3f, 0.35f - beltGate, -0.01f)); //0.15 e close
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.01f, 0.3f, 1.02f));
    if (flagForGate) {
        if (beltSwitch == true && translateMatrix2[3].y > 0.15)
        {
           beltGate += beltGateTranslate;
           //cout << "inside if " << translateMatrix2[3].y << endl;
        }
        /*if (beltSwitch == true && translateMatrix2[3].y <= 0.15 && translateMatrix2[3].y < 0.35)
        {   
            beltGate -= beltGateTranslate;
            cout << "inside 2nd if " << translateMatrix2[3].y <<" beltgate: " << beltGate << endl;
        }*/
    }
    
    model2 = alTogether * translateMatrix2 * scaleMatrix2;
    drawCube(cubeVAO, lightingShader, model2, .44f, .47f, .49f, 32.0f);

    // cutter right
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(2.8f, 0.35f - beltGate, -0.01f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.01f, 0.3f, 1.02f));
    model2 = alTogether * translateMatrix2 * scaleMatrix2;
    drawCube(cubeVAO, lightingShader, model2, .44f, .47f, .49f, 32.0f);
    


}


void mixer(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{

    // left
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model, rotateYMatrix, rotateZMatrix, rotateXMatrix;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 0.9f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.44f, 0.47f, 0.49f, 10.0f);

    // right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 0.9f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.44f, 0.47f, 0.49f, 10.0f);

    // back
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.9f, .1f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.44f, 0.47f, 0.49f, 10.0f);

    // mixer floor
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .1f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.44f, 0.47f, 0.49f, 10.0f);

    // mixer top1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.9f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.45f, .1f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.44f, 0.47f, 0.49f, 10.0f);

    // mixer top2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.65f, 0.9f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.35f, .1f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.44f, 0.47f, 0.49f, 10.0f);

    // mixer top3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.9f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .1f, 0.3f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.44f, 0.47f, 0.49f, 10.0f);

    // mixer top4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.9f, 0.7f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .1f, 0.3f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.44f, 0.47f, 0.49f, 10.0f);

    // front low
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.1f, 0.9f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.48f, .1f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.44f, 0.47f, 0.49f, 10.0f);

    // front high
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.65f, 0.9f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.3f, .1f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.44f, 0.47f, 0.49f, 10.0f);

    // output tongue
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.1f, 0.58f, .95f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.9f, .02f, .95f));
    model = alTogether *  translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.44f, 0.47f, 0.49f, 10.0f);

    //// slanted
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.9f, .85f));
    //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .02f, .91f));
    //model = alTogether * rotateXMatrix * translateMatrix * scaleMatrix  * rotateYMatrix * rotateZMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.44f, 0.47f, 0.49f, 10.0f);

    //uncut bar
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.154f , 0.6f, .2f + mixerSpeed)); //2.1 e stop
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.769f, 0.02f, 0.6f));
    glm::vec3 translation = glm::vec3(translateMatrix[3]);
    model = alTogether * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.55f, 0.1f, 0.0f, 32.0f); //0.25f for chocolate color
    if (translateMatrix[3].z <= 2.1f) {
        if (mixerSwitch == true)
        {
            mixerSpeed += beltTranslate;
            
        }
        model = alTogether * translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.25f, 0.1f, 0.0f, 32.0f); 
    }
    if (translateMatrix[3].z >= 2.1)
    {
        uncutBarFlag = true;
    }
    //cout << translateMatrix[3].z << " " << uncutBarFlag << endl;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(.5f, 0.2f, 0.5f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f));
    if (fanSwitch == true)
    {
        r += fanSpeed;
        //r = fmod(r, 360);
    }

    model = alTogether * translateMatrix * rotateYMatrix;
    fan(cubeVAO, lightingShader, model);
}

void fan(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float len = .5f; //1;
    float w = 0.15f;  //.15;
    float h = 0.02f; //.05;
    float r = 15.f;
    //fin

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(len, h, w));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1.0f, 0.99f, 0.82f, 10.0f);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(w, h, len));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    //translate2 = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1.0f, 0.99f, 0.82f, 10.0f);
}


void oven(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{

    // left
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.0f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.35f, 0.70f, 0.67f, 10.0f);

    // right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.0f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.35f, 0.70f, 0.67f, 10.0f);

    // back
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, .1f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.35f, 0.70f, 0.67f, 10.0f);

    //// front
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.1f, 0.9f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, .1f));
    //model = alTogether * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.44f, 0.47f, 0.49f, 10.0f);

    //upper tray
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.01f, 0.8f, -0.01f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .02f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.18f, 0.20f, 0.22f, 10.0f);

    //lower tray
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.01f, 0.4f, -0.01f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .02f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.18f, 0.20f, 0.22f, 10.0f);
}

void shelf(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{

    // left
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.01f, 1.0f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0f, 0.76f, 0.55f, 32.0f);

    //right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.01f, 1.0f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0f, 0.76f, 0.55f, 32.0f);

    //mid
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.01f, 1.0f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0f, 0.76f, 0.55f, 32.0f);

    //quarter
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.01f, 1.0f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0f, 0.76f, 0.55f, 32.0f);

    //bottom
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.01f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0f, 0.76f, 0.55f, 32.0f);

    //shelf 1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.2f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.01f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0f, 0.76f, 0.55f, 32.0f);

    //shelf 2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.7f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.01f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0f, 0.76f, 0.55f, 32.0f);

    //shelf 3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.45f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.01f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0f, 0.76f, 0.55f, 32.0f);

    //top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.01f, 0.01f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0f, 0.76f, 0.55f, 32.0f);

    //back
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.01f, 1.01f, 0.01f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0f, 0.76f, 0.55f, 32.0f);
}

void bench(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{

    // sit
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, rotateXMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.2f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.9f, 0.02f, 0.3f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);

    //CUSHION
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.03f, 0.22f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.84f, 0.02f, 0.3f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0f, 1.0f, 1.0f, 32.0f);

    //leg 1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 0.5f, 0.03f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);
    //leg 2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.87f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 0.5f, 0.03f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);
    //leg 3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.27f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 0.2f, 0.03f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);
    //leg 4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.87f, 0.0f, 0.27f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 0.2f, 0.03f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);
    //leg z1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.87f, 0.05f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 0.03f, 0.3f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);
    //leg z2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.05f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 0.03f, 0.3f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);
    //handle z1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.87f, 0.3f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 0.03f, 0.3f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);
    //handle z2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.3f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 0.03f, 0.3f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);
    //handle 3
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.2f, 0.27f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 0.1f, 0.03f));
    model = alTogether * translateMatrix * rotateXMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);
    //handle 4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.87f, 0.2f, 0.27f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 0.1f, 0.03f));
    model = alTogether * translateMatrix * rotateXMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);
    //back
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.45f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.9f, 0.03f, 0.02f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);
    
    //back parts
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01f, 0.25f, 0.03f));
    for (float i = 0.0f; i <= 0.78f; i += 0.11f) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05f + i, 0.2f, 0.0f)); // 0.05 e start 0.83 e sesh
        model = alTogether * translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);
    }
}

void roomTable(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{

    // sit
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, rotateXMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.2f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.7f, 0.02f, 0.4f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.34f, 0.28f, 0.23f, 32.0f);

    //leg 1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.03f, 0.0f, 0.05f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 0.2f, 0.03f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);
    //leg 2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.65f, 0.0f, 0.05f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 0.2f, 0.03f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);
    //leg 3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.03f, 0.0f, 0.3f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 0.2f, 0.03f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);
    //leg 4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.65f, 0.0f, 0.3f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 0.2f, 0.03f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.55f, 0.35f, 0.17f, 32.0f);
}

void ladder(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{

    // left
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.01f, 0.7f, .01f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.0f, 0.0f, 0.0f, 32.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.1f, 0.2f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.01f, 0.7f, .01f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.0f, 0.0f, 0.0f, 32.0f);
    
    for (float i = 0.1f; i <= 0.7; i+= 0.1f) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.1f + i, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.01f, 0.01f, .2f));
        model = alTogether * translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.0f, 0.0f, 0.0f, 32.0f);
    }
}

void floor(Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);


    scale = glm::scale(model, glm::vec3(9.3f, 0.1f, 10.0f));
    translate = glm::translate(model, glm::vec3(-2.0f, 0.0f, -4.0f));
    model = alTogether * translate * scale;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);
}

void boxShelf(Cube cube, Cube cube2, Shader& lightingShaderWithTexture, glm::mat4 alTogether)
{

    // left
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.01f, 1.0f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    // right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.01f, 1.0f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    // back
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, .1f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //upper tray
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.01f, 0.8f, -0.01f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.99f, .02f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //lower tray
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.01f, 0.4f, -0.01f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.99f, .02f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //box1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.03f, 0.4f, 0.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.4f, .3f, 0.7f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
    //box2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5f, 0.4f, 0.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.4f, .3f, 0.7f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
    //box3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.03f, 0.8f, 0.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.4f, .3f, 0.7f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
    //box4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5f, 0.8f, 0.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.4f, .3f, 0.7f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
}

void bathroom_wall(Cube cube, Cube cube1, Cube cube2, Cube cube3, Cube cube4, Cube cube5, Cube cube6, Cube cube7, Shader& lightingShaderWithTexture, glm::mat4 alTogether)
{
    glm::mat4 identity = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotateXMatrix = glm::rotate(identity, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotateYMatrix = glm::rotate(identity, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotateZMatrix = glm::rotate(identity, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    //side left pt1
    scale = glm::scale(identity, glm::vec3(0.1f, 2.05f, 1.2f));
    translate = glm::translate(identity, glm::vec3(-2.0f, -0.1f, -4.0f));
    model = alTogether * translate * scale;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);


    //bath door
    scale = glm::scale(identity, glm::vec3(0.05f, 1.0f, 0.70f));
    translate = glm::translate(identity, glm::vec3(-1.99f, -0.1f, -2.8f));
    if (bathDoorSwitch == true) {
        if (bathDoorSpeed <= 90.0f) {
            bathDoorSpeed += bathDoorTranslate;
        }
    }
    if (bathDoorSwitch == false) {
        if (bathDoorSpeed >= 0.0f) {
            bathDoorSpeed -= bathDoorTranslate;
        }
    }
    //rotateXMatrix = glm::rotate(identity, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identity, glm::radians(rotateAngle_Y + bathDoorSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
    model = alTogether * translate * rotateYMatrix * scale;
    cube7.drawCubeWithTexture(lightingShaderWithTexture, model);

    //side left pt2
    scale = glm::scale(identity, glm::vec3(0.1f, 2.05f, 1.1f));
    translate = glm::translate(identity, glm::vec3(-2.0f, -0.1f, -2.1f));
    model = alTogether * translate * scale;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //side left top pt
    scale = glm::scale(identity, glm::vec3(0.1f, 1.05f, 0.7f));
    translate = glm::translate(identity, glm::vec3(-2.0f, 0.9f, -2.8f));
    model = alTogether * translate * scale;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);


    //back
    scale = glm::scale(identity, glm::vec3(2.1f, 2.05f, 0.1f));
    translate = glm::translate(identity, glm::vec3(-2.0f, -0.1f, -4.0f));
    model = alTogether * translate * scale;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //side right
    scale = glm::scale(identity, glm::vec3(0.1f, 2.05f, 3.0f));
    translate = glm::translate(identity, glm::vec3(0.1f, -0.1f, -4.0f));
    model = alTogether * translate * scale;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //pan
    scale = glm::scale(identity, glm::vec3(.5f, .05f, 0.5f));
    translate = glm::translate(identity, glm::vec3(-1.f, -0.1f, -3.9f));
    model = alTogether * translate * scale;
    cube1.drawCubeWithTexture(lightingShaderWithTexture, model);

    //floor
    scale = glm::scale(identity, glm::vec3(2.2f, .01f, 3.0f));
    translate = glm::translate(identity, glm::vec3(-1.99f, -0.1f, -4.0f));
    model = alTogether * translate * scale;
    cube2.drawCubeWithTexture(lightingShaderWithTexture, model);

    //basin
    scale = glm::scale(identity, glm::vec3(0.5f, .04f, 0.6f));
    translate = glm::translate(identity, glm::vec3(-0.4f, 0.5f, -2.5f));
    model = alTogether * translate * scale * rotateZMatrix;
    cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

    //mirror
    scale = glm::scale(identity, glm::vec3(0.05f, .6f, 0.5f));
    translate = glm::translate(identity, glm::vec3(0.05f, 1.5f, -2.4f));
    model = alTogether * translate * scale * rotateZMatrix;
    cube4.drawCubeWithTexture(lightingShaderWithTexture, model);

    //tap
    scale = glm::scale(identity, glm::vec3(0.3f, .06f, 0.08f));
    translate = glm::translate(identity, glm::vec3(-0.2f, 0.7f, -2.2f));
    model = alTogether * translate * scale * rotateZMatrix;
    cube5.drawCubeWithTexture(lightingShaderWithTexture, model);

    //soap
    scale = glm::scale(identity, glm::vec3(0.1f, .02f, 0.13f));
    translate = glm::translate(identity, glm::vec3(-0.1f, 0.54f, -1.44f));
    model = alTogether * translate * scale * rotateZMatrix;
    cube6.drawCubeWithTexture(lightingShaderWithTexture, model);
}

void soap_container(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{

    // left
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    
    translateMatrix = glm::translate(identityMatrix, glm::vec3(5.3f, 0.5f, 5.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.15f, .02f, .26f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.0f, 0.0f, 0.0f, 32.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(5.3f, 0.52f, 5.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.15f, .025f, .06f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.0f, 0.1f, 0.1f, 32.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(5.3f, 0.52f, 5.7f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.15f, .025f, .06f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.0f, 0.0f, 0.0f, 32.0f);
}
void stairs(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{

    // left
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    float j = 0.0f;
    for (float i = 0.0f; i <= 1.0f; i += .1f) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f + i, 0.0f - i*2));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5f, .1f, .2f));
        model = alTogether * translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.5f, 0.5f, 0.5f, 32.0f);
        j +=  .2f;
    }
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5f, .1f, .2f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.0f, 0.0f, 0.0f, 32.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.1f, -0.2f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5f, .1f, .2f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.0f, 0.0f, 0.0f, 32.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.2f, -0.4f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5f, .1f, .2f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.0f, 0.0f, 0.0f, 32.0f);
}

void cart(unsigned int& cubeVAO, Sphere sphere, Shader& lightingShader, glm::mat4 alTogether)
{

    // left
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;
    glm::mat4 rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.3f, .3f, .02f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.f, 0.5f, 0.5f, 32.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.02f, .3f, .6f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.f, 0.5f, 0.5f, 32.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.3f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.02f, .3f, .6f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.f, 0.5f, 0.5f, 32.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.58f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.3f, .3f, .02f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.f, 0.5f, 0.5f, 32.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.29f, .02f, .59f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.5f, 0.5f, 0.5f, 32.0f);

    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05f, 0.3f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.01f, .3f, .01f));
    model = alTogether * translateMatrix * rotateXMatrix* scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.5f, 0.5f, 0.5f, 32.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, 0.3f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.01f, .3f, .01f));
    model = alTogether * translateMatrix * rotateXMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.5f, 0.5f, 0.5f, 32.0f);

    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.5f, -0.23f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.3f, .02f, .02f));
    model = alTogether * translateMatrix * rotateXMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.5f, 0.5f, 0.5f, 32.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05f, -0.15f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.01f, .15f, .01f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.5f, 0.5f, 0.5f, 32.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, -0.15f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.01f, .15f, .01f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.5f, 0.5f, 0.5f, 32.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05f, -0.15f, 0.55f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.01f, .15f, .01f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.5f, 0.5f, 0.5f, 32.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, -0.15f, 0.55f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.01f, .15f, .01f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.5f, 0.5f, 0.5f, 32.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05f, -0.15f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.001f, .05f, .05f));
    model = alTogether * rotateXMatrix * translateMatrix * scaleMatrix * rotateYMatrix * rotateZMatrix;
    sphere.drawSphere(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.26f, -0.15f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.001f, .05f, .05f));
    model = alTogether * rotateXMatrix * translateMatrix * scaleMatrix * rotateYMatrix * rotateZMatrix;
    sphere.drawSphere(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05f, -0.15f, 0.55f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.001f, .05f, .05f));
    model = alTogether * rotateXMatrix * translateMatrix * scaleMatrix * rotateYMatrix * rotateZMatrix;
    sphere.drawSphere(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.26f, -0.15f, 0.55f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.001f, .05f, .05f));
    model = alTogether * rotateXMatrix * translateMatrix * scaleMatrix * rotateYMatrix * rotateZMatrix;
    sphere.drawSphere(lightingShader, model);

}


void sideWall(Cube cube, Cube cube2, Shader& lightingShaderWithTexture, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, rotateYMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 0.0f, -4.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 10.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(7.2f, 0.0f, -4.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 10.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //back wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 0.0f, -4.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.3f, 2.0f, 0.1f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //front wall pt1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 0.0f, 6.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 2.2f, 0.1f)); //9.3 total
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);
    // front wall pt2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.3f, 0.0f, 6.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 2.2f, 0.1f)); //9.3 total
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);
    //  front wall top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, 1.6f, 6.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 0.6f, 0.1f)); //9.3 total
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);
    // maingate
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, 0.02f, 6.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 1.58f, 0.1f));
    if (mainDoorSwitch == true) {
        if (mainDoorSpeed <= 90.0f) {
            mainDoorSpeed += mainDoorTranslate;
        }
    }
    if (mainDoorSwitch == false) {
        if (mainDoorSpeed >= 0.0f) {
            mainDoorSpeed -= mainDoorTranslate;
        }
    }
    //rotateXMatrix = glm::rotate(identity, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + mainDoorSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
    model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
}

void roomWall(Cube cube, Cube cube2,Shader& lightingShaderWithTexture, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, rotateYMatrix, model;

    //front pt1
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 2.05f, 0.1f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(5.1f, -0.0f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //front pt2
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 2.05f, 0.1f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.4f, -0.0f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //front top
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7f, 1.0f, 0.1f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(5.7f, 1.05f, 1.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //side
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.05f, 5.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(5.1f, -0.0f,-4.0f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //door
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7f, 1.05f, 0.05f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(5.7f, 0.0f, 1.0f));
    if (bathDoorSwitch == true) {
        if (bathDoorSpeed <= 90.0f) {
            bathDoorSpeed += bathDoorTranslate;
        }
    }
    if (bathDoorSwitch == false) {
        if (bathDoorSpeed >= 0.0f) {
            bathDoorSpeed -= bathDoorTranslate;
        }
    }
    //rotateXMatrix = glm::rotate(identity, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + bathDoorSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
    model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
}

void rackChocolates(Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether)
{
    for (float i = 0.13f; i < 0.8f; i += 0.22f) {
        for (float j = 0.2f; j < 0.8; j += 0.22f) {
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 translate = glm::mat4(1.0f);
            glm::mat4 translate2 = glm::mat4(1.0f);
            glm::mat4 scale = glm::mat4(1.0f);

            scale = glm::scale(model, glm::vec3(0.15f, .015f, 0.15f));
            translate = glm::translate(model, glm::vec3(0.0f + i, 0.4f, 0.0f + j));
            model = alTogether * translate * scale;
            cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
    }
    for (float i = 0.13f; i < 0.8f; i += 0.22f) {
        for (float j = 0.2f; j < 0.8; j += 0.22f) {
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 translate = glm::mat4(1.0f);
            glm::mat4 translate2 = glm::mat4(1.0f);
            glm::mat4 scale = glm::mat4(1.0f);
            
            scale = glm::scale(model, glm::vec3(0.15f, .015f, 0.15f));
            translate = glm::translate(model, glm::vec3(0.0f + i, 0.8f, 0.0f + j));
            model = alTogether * translate * scale;
            cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
    }
}

void machineChocolates(Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether)
{
    for (float i = 0.13f; i < 0.8f; i += 0.22f) {
        for (float j = 0.2f; j < 0.8; j += 0.22f) {
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 translate = glm::mat4(1.0f);
            glm::mat4 translate2 = glm::mat4(1.0f);
            glm::mat4 scale = glm::mat4(1.0f);

            scale = glm::scale(model, glm::vec3(0.15f, .015f, 0.15f));
            translate = glm::translate(model, glm::vec3(0.0f + i, 0.4f, 0.0f + j));
            model = alTogether * translate * scale;
            cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
    }
}

void cocoa_bean(Sphere sphere, Shader& lightingShader, glm::mat4 alTogether) {
    /*glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);*/
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix, scaleMatrix, model, rotateYMatrix, rotateZMatrix, rotateXMatrix;

    for (float i = 0.13f; i < 1.8f; i += 0.7f) {
        for (float j = 0.2f; j < 1.8; j += 0.7f) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f + i , 0.0f, .0f + j));
            rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
            rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, .2f, .2f));

            model = alTogether * rotateXMatrix * translateMatrix * scaleMatrix * rotateYMatrix * rotateZMatrix;
            sphere.drawSphere(lightingShader, model);
        }
    }

}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        eyeZ += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        eyeY += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)                   //Up
    {
        /*eyeY -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);*/
        camera.ProcessKeyboard(UP, deltaTime);

    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)                   //Up
    {
        camera.ProcessKeyboard(DOWN, deltaTime);

    }

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (directionalLightOn)
        {
            directionallight.turnOff();
            directionalLightOn = !directionalLightOn;
        }
        else
        {
            directionallight.turnOn();
            directionalLightOn = !directionalLightOn;
        }
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (pointLightOn)
        {
            pointlight1.turnOff();
            pointLightOn = !pointLightOn;
        }
        else
        {
            pointlight1.turnOn();
            pointLightOn = !pointLightOn;
        }
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        if (pointLightOn)
        {
            pointlight2.turnOff();
            pointLightOn = !pointLightOn;
        }
        else
        {
            pointlight2.turnOn();
            pointLightOn = !pointLightOn;
        }
    }
    if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        if (spotLightOn)
        {
            spotlight.turnOff();
            spotLightOn = !spotLightOn;
        }
        else
        {
            spotlight.turnOn();
            spotLightOn = !spotLightOn;
        }
    }
    if (key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        if (ambientToggle)
        {
            pointlight1.turnAmbientOff();
            pointlight2.turnAmbientOff();
            directionallight.turnAmbientOff();
            spotlight.turnAmbientOff();
            ambientToggle = !ambientToggle;
        }
        else
        {
            pointlight1.turnAmbientOn();
            pointlight2.turnAmbientOn();
            directionallight.turnAmbientOn();
            spotlight.turnAmbientOn();
            ambientToggle = !ambientToggle;
        }
    }
    if (key == GLFW_KEY_6 && action == GLFW_PRESS)
    {
        if (diffuseToggle)
        {
            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            directionallight.turnDiffuseOff();
            spotlight.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {
            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            directionallight.turnDiffuseOn();
            spotlight.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }
    }
    if (key == GLFW_KEY_7 && action == GLFW_PRESS)
    {
        if (specularToggle)
        {
            pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
            directionallight.turnSpecularOff();
            spotlight.turnSpecularOff();
            specularToggle = !specularToggle;
        }
        else
        {
            pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
            directionallight.turnSpecularOn();
            spotlight.turnSpecularOn();
            specularToggle = !specularToggle;
        }
    }
    if (key == GLFW_KEY_G && action == GLFW_PRESS)                   //Rotate Fan
    {
        if (fanSwitch == false)
            fanSwitch = true;

        else fanSwitch = false;

    }

    if (key == GLFW_KEY_M && action == GLFW_PRESS)                   // Conveyer belt
    {
        if (beltSwitch == false)
            beltSwitch = true;

        else beltSwitch = false;

    }

    if (key == GLFW_KEY_B && action == GLFW_PRESS)                   // Rotate bowl
    {
        if (bowlSwitch == false)
            bowlSwitch = true;

        else bowlSwitch = false;

    }

    if (key == GLFW_KEY_N && action == GLFW_PRESS)                   // Rotate bowl
    {
        if (mixerSwitch == false)
            mixerSwitch = true;

        else mixerSwitch = false;

    }

    if (key == GLFW_KEY_L && action == GLFW_PRESS)                   // Inside doors
    {
        if (bathDoorSwitch == false)
            bathDoorSwitch = true;

        else bathDoorSwitch = false;

    }

    if (key == GLFW_KEY_K && action == GLFW_PRESS)                   // Inside doors
    {
        if (mainDoorSwitch == false)
            mainDoorSwitch = true;

        else mainDoorSwitch = false;

    }

}

long long nCr(int n, int r)
{
    if (r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L)
{
    double y = 0;
    double x = 0;
    t = t > 1.0 ? 1.0 : t;
    for (int i = 0; i < L + 1; i++)
    {
        long long ncr = nCr(L, i);
        double oneMinusTpow = pow(1 - t, double(L - i));
        double tPow = pow(t, double(i));
        double coef = oneMinusTpow * tPow * ncr;
        x += coef * ctrlpoints[i * 3];
        y += coef * ctrlpoints[(i * 3) + 1];

    }
    xy[0] = float(x);
    xy[1] = float(y);
}

unsigned int hollowBezier(GLfloat ctrlpoints[], int L, vector <float>& coordinates,
    vector <float>& normals,
    vector <int>& indices,
    vector <float>& vertices)
{
    int i, j;
    float x, y, z, r;                //current coordinates
    float theta;
    float nx, ny, nz, lengthInv;    // vertex normal


    const float dtheta = 2 * pi / ntheta;        //angular step size

    float t = 0;
    float dt = 1.0 / nt;
    float xy[2];

    for (i = 0; i <= nt; ++i)              //step through y
    {
        BezierCurve(t, xy, ctrlpoints, L);
        r = xy[0];
        y = xy[1];
        theta = 0;
        t += dt;
        lengthInv = 1.0 / r;

        for (j = 0; j <= ntheta; ++j)
        {
            double cosa = cos(theta);
            double sina = sin(theta);
            z = r * cosa;
            x = r * sina;

            coordinates.push_back(x);
            coordinates.push_back(y);
            coordinates.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            // center point of the circle (0,y,0)
            nx = (x - 0) * lengthInv;
            ny = (y - y) * lengthInv;
            nz = (z - 0) * lengthInv;

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            theta += dtheta;
        }
    }

    // generate index list of triangles
    // k1--k1+1
    // |  / |
    // | /  |
    // k2--k2+1

    int k1, k2;
    for (int i = 0; i < nt; ++i)
    {
        k1 = i * (ntheta + 1);     // beginning of current stack
        k2 = k1 + ntheta + 1;      // beginning of next stack

        for (int j = 0; j < ntheta; ++j, ++k1, ++k2)
        {
            // k1 => k2 => k1+1
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);

            // k1+1 => k2 => k2+1
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }
    }

    size_t count = coordinates.size();
    for (int i = 0; i < count; i += 3)
    {
        vertices.push_back(coordinates[i]);
        vertices.push_back(coordinates[i + 1]);
        vertices.push_back(coordinates[i + 2]);

        vertices.push_back(normals[i]);
        vertices.push_back(normals[i + 1]);
        vertices.push_back(normals[i + 2]);
    }

    unsigned int bezierVAO;
    glGenVertexArrays(1, &bezierVAO);
    glBindVertexArray(bezierVAO);

    // create VBO to copy vertex data to VBO
    unsigned int bezierVBO;
    glGenBuffers(1, &bezierVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);           // for vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // target
        (unsigned int)vertices.size() * sizeof(float), // data size, # of bytes
        vertices.data(),   // ptr to vertex data
        GL_STATIC_DRAW);                   // usage

    // create EBO to copy index data
    unsigned int bezierEBO;
    glGenBuffers(1, &bezierEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);   // for index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
        (unsigned int)indices.size() * sizeof(unsigned int),             // data size, # of bytes
        indices.data(),               // ptr to index data
        GL_STATIC_DRAW);                   // usage

    // activate attrib arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // set attrib arrays with stride and offset
    int stride = 24;     // should be 24 bytes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));

    // unbind VAO, VBO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return bezierVAO;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
