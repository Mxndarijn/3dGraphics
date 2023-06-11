#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "FloorManager.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "CameraComponent.h"
#include "FloorTile.h"
#include "PlaneComponent.h"
#include "GravityComponent.h"
#include "GameManager.h"
#include "BoundingBoxComponent.h"
#include "CollisionComponent.h"
#include "ObjModel.h"
#include "Texture.h"
#include "ModelComponent.h"

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

void init();
void update();
void draw();

int playFieldWidth = 10, playFieldHeight = 10;

std::shared_ptr<GameManager> gameManager;
std::shared_ptr<GameObject> camera;

float lastFrameTime = 0;


//Create Window
int main(void)
{
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(1400, 800, "ColorDance", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);

    tigl::init();

    init();

	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();


    return 0;
}

// Creates camera and Gamemanager.
// Adds default objects.
// Starts shadow.
void init()
{
    std::cout << "Init" << std::endl;
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
    });

    camera = std::make_shared<GameObject>();
    gameManager = std::make_shared<GameManager>(camera);

    auto center = gameManager->getFloorManager()->getCenterPoint();
    // Set camera to center + y 12
    camera->position = glm::vec3(center.x,center.y +50,center.z);
    camera->addComponent(std::make_shared<PlayerComponent>());
    camera->addComponent(std::make_shared<CameraComponent>(window));
    // Create bounding box around player
    camera->addComponent(std::make_shared<BoundingBoxComponent>(glm::vec3(-2,-8,-2), glm::vec3(2,0,2)));
    camera->addComponent(std::make_shared<CollisionComponent>(gameManager));
    camera->addComponent(std::make_shared<GravityComponent>());

    auto bulbasaur = std::make_shared<GameObject>();
    bulbasaur->position = glm::vec3(center.x + 10, center.y + 30, center.z + 5);
    bulbasaur->addComponent(std::make_shared<ModelComponent>(gameManager->getModels()[3]));
    bulbasaur->addComponent(std::make_shared<BoundingBoxComponent>(glm::vec3(-2, -0.5, -1), glm::vec3(1, 2, 2)));
    bulbasaur->addComponent(std::make_shared<GravityComponent>());
    bulbasaur->addComponent(std::make_shared<CollisionComponent>(gameManager));
    bulbasaur->scale *= 5;

    gameManager->addGameObject(bulbasaur);


 
    // Enable Lightning
    glEnable(GL_DEPTH_TEST);
    tigl::shader->enableLighting(true);
    tigl::shader->setLightCount(1);
    tigl::shader->setLightDirectional(0, true);
    tigl::shader->setLightPosition(0, glm::normalize(glm::vec3(1, 1, 1)));
    tigl::shader->setLightAmbient(0, glm::vec3(0.5f, 0.5f, 0.5f));
    tigl::shader->setLightDiffuse(0, glm::vec3(0.5f, 0.5f, 0.5f));
    tigl::shader->setLightSpecular(0, glm::vec3(1, 1, 1));
    tigl::shader->setShinyness(0);

    

}


void update()
{
    float currentFrameTime = glfwGetTime();
    float deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    camera->update(deltaTime);

    gameManager->update(deltaTime);

}

void draw()
{
    // Default
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

    auto cameraComponent = camera->getComponent<CameraComponent>();

    tigl::shader->setProjectionMatrix(projection);
    tigl::shader->setViewMatrix(cameraComponent->getMatrix());
    tigl::shader->setModelMatrix(glm::mat4(1.0f));

    tigl::shader->enableColor(true);

    glEnable(GL_DEPTH_TEST);

    gameManager->draw();
   
}