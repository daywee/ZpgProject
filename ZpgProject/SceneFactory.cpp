#include "SceneFactory.h"
#include "ModelLoader.h"


Scene* SceneFactory::testScene(Camera* camera)
{
	Scene* scene = new Scene(new Shader("Shaders/Vertex/VertexShader.glsl", "Shaders/Fragment/FragmentShader.glsl"));

	Object* object1 = new Object(Sphere);
	Object* object2 = new Object(Plain);
	Object* object3 = new Object(SuziFlat);
	Object* object4 = new Object(SuziSmooth);
	Object* object5 = new Object(Plain);

	scene->registerUpdatable(object1);
	scene->registerRenderable(object1);
	object1->onUpdate([object1]()
	{
		object1->transformation()->setPosition(glm::vec3(glm::sin(glfwGetTime()) * 5, 0, 0));
	});
	scene->registerUpdatable(object2);
	scene->registerRenderable(object2);
	scene->registerUpdatable(object3);
	scene->registerRenderable(object3);
	object3->onUpdate([object3]()
	{
		object3->transformation()->setAngleDegrees(object3->transformation()->getAngleDegrees() + 0.3f);
	});
	scene->registerUpdatable(object4);
	scene->registerRenderable(object4);
	scene->registerUpdatable(object5);
	scene->registerRenderable(object5);

	object1->transformation()->setPosition(glm::vec3(5.f, 0.f, 0.f));
	object2->transformation()->setPosition(glm::vec3(0.f, -5.f, 0.f));
	object3->transformation()->setPosition(glm::vec3(-5.f, 0.f, 0.f));
	object4->transformation()->setPosition(glm::vec3(0.f, 5.f, 0.f));
	object5->transformation()->setPosition(glm::vec3(0.f, 0.f, 5.f));

	Light* light = new Light(glm::vec3(0, 0, 0));
	scene->registerRenderable(light);

	camera->addObserver(scene);
	camera->setPosition(0, 0, 10);
	return scene;
}

Scene* SceneFactory::cubeScene(Camera* camera)
{
	Scene* scene = new Scene(new Shader("Shaders/Vertex/VertexShader.glsl", "Shaders/Fragment/FragmentShader.glsl"));

	ModelLoader* loader = new ModelLoader();
	const auto object = loader->load("Models/Cube/cube.obj");

	object->transformation()->setPosition(glm::vec3(5.f, 0.f, 0.f));
	scene->registerUpdatable(object);
	scene->registerRenderable(object);
	
	Light* light = new Light(glm::vec3(0, 0, 0));
	scene->registerRenderable(light);

	camera->addObserver(scene);
	camera->setPosition(0, 0, 10);
	return scene;
}

Scene* SceneFactory::houseScene(Camera* camera)
{
	Scene* scene = new Scene(new Shader("Shaders/Vertex/VertexShader.glsl", "Shaders/Fragmetn/FragmentShader.glsl"));

	ModelLoader* loader = new ModelLoader();
	LoadedObject* object = loader->load("Models/House/house.obj");

	/*Object* plain = new Object(Plain);
	plain->transformation()->setSize(glm::vec3(100));
	scene->registerRenderable(plain);*/


	object->transformation()->setPosition(glm::vec3(5.f, 0.f, 0.f));
	scene->registerUpdatable(object);
	scene->registerRenderable(object);

	Light* light = new Light(glm::vec3(10, 10, 10));
	scene->registerRenderable(light);

	camera->addObserver(scene);
	camera->setPosition(0, 0, 10);
	return scene;
}
