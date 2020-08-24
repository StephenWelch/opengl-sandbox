#include <engine/input/Input.h>

#include <cmath>
#include <engine/Application.h>

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

	if (event.getKeyCode() == KeyCode::W && window->isKeyPressed(KeyCode::W)) {
		velocity += speed*camera->getTarget();
	}
	if (event.getKeyCode() == KeyCode::S && window->isKeyPressed(KeyCode::S)) {
		velocity -= speed*camera->getTarget();
	}
	if (event.getKeyCode() == KeyCode::A && window->isKeyPressed(KeyCode::A)) {
		velocity -= speed*cameraXAxis;
	}
	if (event.getKeyCode() == KeyCode::D && window->isKeyPressed(KeyCode::D)) {
		velocity += speed*cameraXAxis;
	}
	if (event.getKeyCode() == KeyCode::E && window->isKeyPressed(KeyCode::E)) {
		velocity += speed*cameraYAxis;
	}
	if (event.getKeyCode() == KeyCode::Q && window->isKeyPressed(KeyCode::Q)) {
		velocity -= speed*cameraYAxis;
	}
	if (event.getKeyCode() == KeyCode::Space && window->isKeyPressed(KeyCode::Space)) {
		velocity += speed*camera->WORLD_UP;
	}
	if (event.getKeyCode() == KeyCode::LeftShift && window->isKeyPressed(KeyCode::LeftShift)) {
		velocity -= speed*camera->WORLD_UP;
	}

	cameraVelocity = velocity;

	if (event.getKeyCode()==KeyCode::Escape) {
		window->requestClose();
	}
	if (event.getKeyCode() == KeyCode::F && window->isKeyPressed(KeyCode::F)) {
		window->setWireframe(true);
	}
	if(event.getKeyCode() == KeyCode::F && window->isKeyReleased(KeyCode::F)) {
		window->setWireframe(false);
	}

	auto &app = Application::get();

	if(event.getKeyCode() == KeyCode::GraveAccent && window->isKeyReleased(KeyCode::GraveAccent)) {
		app.setImguiVisible(!app.isImguiVisible());

		if(app.isImguiVisible()) {
			window->setMouseLocked(false);
			app.setImguiVisible(true);
			clickedIn = false;
		} else {
			window->setMouseLocked(true);
			app.setImguiVisible(false);
			clickedIn = true;
		}
	}

	return true;
}

bool Input::onMouseMove(MouseMovedEvent &event) {
	if(Application::get().isImguiVisible() && !clickedIn) {
		lastClickedIn = false;
		return false;
	}

	mousePos = {event.getX(), event.getY()};

	if(!clickedIn) {
		clickedIn = true;
	}
	if(clickedIn && !lastClickedIn) {
		lastMousePos = mousePos;
	}
	lastClickedIn = clickedIn;

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

bool Input::onMouseButton(MouseButtonPressedEvent &event) {
	if(!clickedIn && event.getMouseButton() == MouseCode::ButtonLeft) {
		Application::get().getWindow()->setMouseLocked(true);
	clickedIn = true;
	}

	return true;
}
