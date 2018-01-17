#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "ISubject.h"
#include <vector>

class Camera : public ISubject
{
public:
	Camera();
	~Camera();
	void setAspect(float aspect);
	glm::mat4 getProjectionMatrix() const;
	glm::mat4 getViewMatrix() const;
	void setTarget(float fi, float psi);
	void setTarget(glm::vec3 target);
	void setTarget(float x, float y, float z);
	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 position);

	glm::vec3 getPosition();

	void moveRight();
	void moveLeft();
	void moveForward();
	void moveBackward();
	void moveUp();
	void moveDown();

	void rotateRight();
	void rotateLeft();
	void rotateUp();
	void rotateDown();

	void rotateX(float x);
	void rotateY(float y);

	void addObserver(IObserver* observer) override;
	void removeObserver(IObserver* observer) override;
	
private:
	float moveStep_ = .5f;

	glm::vec3 eye_;
	glm::vec3 target_;
	glm::vec3 up_;
	float fi_;
	float psi_;

	glm::mat4 projection_;

	std::vector<IObserver*> observers_;

	float fov_;
	float aspect_;
	float near_;
	float far_;

	void notifyObservers();
};

