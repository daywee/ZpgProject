#include "SceneFactory.h"


Scene* SceneFactory::getTestScene1(Camera* camera)
{
	Scene* scene = new Scene(new Shader("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl"));

	Object* object1 = new Object(Sphere);
	Object* object2 = new Object(Plain);
	Object* object3 = new Object(SuziFlat);
	Object* object4 = new Object(SuziSmooth);
	Object* object5 = new Object(Plain);

	scene->addObject(object1);
	object1->onUpdate = [object1]()
	{
		object1->transformation()->setPosition(glm::vec3(glm::sin(glfwGetTime()) * 5, 0, 0));
	};
	scene->addObject(object2);
	scene->addObject(object3);
	object3->onUpdate = [object3]()
	{
		object3->transformation()->setAngleDegrees(object3->transformation()->getAngleDegrees() + 0.3f);
	};
	scene->addObject(object4);
	scene->addObject(object5);

	object1->transformation()->setPosition(glm::vec3(5.f, 0.f, 0.f));
	object2->transformation()->setPosition(glm::vec3(0.f, -5.f, 0.f));
	object3->transformation()->setPosition(glm::vec3(-5.f, 0.f, 0.f));
	object4->transformation()->setPosition(glm::vec3(0.f, 5.f, 0.f));
	object5->transformation()->setPosition(glm::vec3(0.f, 0.f, 5.f));

	Light* light = new Light(glm::vec3(0, 0, 0));
	scene->addLight(light);

	camera->addObserver(scene);
	camera->setPosition(0, 0, 10);
	return scene;
}
