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

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

void init();
void update();
void draw();

int playFieldWidth = 10, playFieldHeight = 10;

FloorManager* floorManager;
std::shared_ptr<GameObject> camera;

double lastFrameTime = 0;
std::list<std::shared_ptr<GameObject>> objects;
std::list<std::shared_ptr<GameObject>> walls;


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

void addGameObject(std::shared_ptr<GameObject> ob) {
    objects.push_back(ob);
}


void addWall(std::shared_ptr<GameObject> ob) {
    walls.push_back(ob);
}


void init()
{
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
    });

    floorManager = new FloorManager(15, 15);
    camera = std::make_shared<GameObject>();

    auto center = floorManager->getCenterPoint();
    camera->position = glm::vec3(-center.x,center.y + 8,-center.z);
    camera->addComponent(std::make_shared<PlayerComponent>());
    camera->addComponent(std::make_shared<CameraComponent>(window));

 /*   auto o = std::make_shared<GameObject>();
    o->position = glm::vec3(0, 6, 0);
    o->addComponent(std::make_shared<PlaneComponent>(25,25, nullptr, 1));

    addGameObject(o);*/

 

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
    double currentFrameTime = glfwGetTime();
    double deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    camera->update(deltaTime);

    for (auto xTiles : floorManager->tiles) {
        for (auto tile : xTiles) {
            tile->update(deltaTime);
        }
    }
    for (auto object : objects) {
        object->update(deltaTime);
    }

    for (auto object : walls) {
        object->update(deltaTime);
    }

}

void draw()
{
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

    /*tigl::begin(GL_QUADS);
    tigl::addVertex(Vertex::PCN(glm::vec3(-50, -1, -50), glm::vec4(1, 0, 0, 1), glm::vec3(0, 1, 0)));
    tigl::addVertex(Vertex::PCN(glm::vec3(-50, -1, 50), glm::vec4(0, 1, 0, 1), glm::vec3(0, 1, 0)));
    tigl::addVertex(Vertex::PCN(glm::vec3(50, -1, 50), glm::vec4(0, 0, 1, 1), glm::vec3(0, 1, 0)));
    tigl::addVertex(Vertex::PCN(glm::vec3(50, -1, -50), glm::vec4(0, 0, 1, 1), glm::vec3(0, 1, 0)));
    tigl::end();*/

    floorManager->draw();

    for (auto ob : objects) {
        ob->draw();
    }

    for (auto ob : walls) {
        ob->draw();
    }
    

}