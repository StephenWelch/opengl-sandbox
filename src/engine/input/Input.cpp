#include <engine/input/Input.h>

#include <cmath>

void Input::init() {}

void Input::update() {
	float currentTime = glfwGetTime();
	dt = currentTime - lastTime;
	lastTime = currentTime;

	auto displacement = cameraVelocity*dt;
	camera->setPosition(camera->getPosition() + displacement);
}

bool Input::onKeyPressOrRelease(KeyEvent &event) {
	glm::vec3 cameraXAxis = camera->getViewXAxis();
	glm::vec3 cameraYAxis = camera->getViewYAxis();

	auto velocity = glm::vec3(0.0f);
	float speed = 2.5;

	if (window->isKeyPressed(KeyCode::W)) {
		velocity += speed*camera->getTarget();
	}
	if (window->isKeyPressed(KeyCode::S)) {
		velocity -= speed*camera->getTarget();
	}
	if (window->isKeyPressed(KeyCode::A)) {
		velocity -= speed*cameraXAxis;
	}
	if (window->isKeyPressed(KeyCode::D)) {
		velocity += speed*cameraXAxis;
	}
	if (window->isKeyPressed(KeyCode::E)) {
		velocity += speed*cameraYAxis;
	}
	if (window->isKeyPressed(KeyCode::Q)) {
		velocity -= speed*cameraYAxis;
	}
	if (window->isKeyPressed(KeyCode::Space)) {
		velocity += speed*camera->WORLD_UP;
	}
	if (window->isKeyPressed(KeyCode::LeftShift)) {
		velocity -= speed*camera->WORLD_UP;
	}

	cameraVelocity = velocity;

	if (event.GetKeyCode()==KeyCode::Escape) {
		window->requestClose();
	}
	if (window->isKeyPressed(KeyCode::F)) {
		window->setWireframe(true);
	}
	if(window->isKeyReleased(KeyCode::F)) {
		window->setWireframe(false);
	}

	return true;
}

bool Input::onMouseMove(MouseMovedEvent &event) {
	mousePos = {event.GetX(), event.GetY()};

	if (!clickedIn) {
		clickedIn = true;
		lastMousePos = mousePos;
	}

	mouseDelta = mousePos - lastMousePos;
	lastMousePos = mousePos;

	float sensitivity = 0.05f;
	yaw += mouseDelta.x*sensitivity;
	pitch += -mouseDelta.y*sensitivity;
	pitch = std::fmin(89.0f, pitch);
	pitch = std::fmax(-89.0f, pitch);

	glm::vec3 cameraTarget;
	cameraTarget.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
	cameraTarget.y = sin(glm::radians(pitch));
	cameraTarget.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));
	camera->setTarget(glm::normalize(cameraTarget));

	return true;
}
