#include <GLFW/glfw3.h>
#include <math.h>

struct Bat
{
	float x1, y1;
	float x2, y2;
};

struct Ball
{
	float radius;
	float xc;
	float yc;
	int num_segments;
};

void Draw(struct Bat bat1, struct Bat bat2, Ball ball)
{

	glBegin(GL_QUADS);
	glVertex2f(bat1.x1, bat1.y1);
	glVertex2f(bat1.x2, bat1.y1);
	glVertex2f(bat1.x2, bat1.y2);
	glVertex2f(bat1.x1, bat1.y2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(bat2.x1, bat2.y1);
	glVertex2f(bat2.x2, bat2.y1);
	glVertex2f(bat2.x2, bat2.y2);
	glVertex2f(bat2.x1, bat2.y2);
	glEnd();

	//Draw circle
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < ball.num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(ball.num_segments);//get the current angle

		float x = ball.radius * cosf(theta);//calculate the x component
		float y = ball.radius * sinf(theta);//calculate the y component

		glVertex2f((x + ball.xc), (y + ball.yc));//output vertex

	}
	glEnd();

}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	struct Ball ball;
	ball.radius = 0.015f;
	ball.xc = 0.0f;
	ball.yc = 0.0f;
	ball.num_segments = 200;

	double currentFrame = glfwGetTime();
	double lastFrame = currentFrame;
	double deltaTime;
	double speed = 0.5;

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	const int monitorHeight = mode->height;
	const int monitorWidth = mode->width;
	const int screenWidth = 600;
	const int screenHeight = 600;
	
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(screenWidth, screenHeight, "Classic Pong", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, ((monitorWidth / 2) - (screenWidth / 2)), ((monitorHeight / 2) - (screenHeight / 2)));

	struct Bat bat1, bat2;

	bat1.x1 = -0.9f;
	bat1.y1 = -0.1f;
	bat1.x2 = -0.875f;
	bat1.y2 = 0.1f;

	bat2.x1 = 0.875f;
	bat2.y1 = -0.1f;
	bat2.x2 = 0.9f;
	bat2.y2 = 0.1f;

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Press W and S to move bat1

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			bat1.y1 += (float)(deltaTime * speed);
			bat1.y2 += (float)(deltaTime * speed);
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			bat1.y1 -= (float)(deltaTime * speed);
			bat1.y2 -= (float)(deltaTime * speed);
		}

		//Press Up and down arrow to move bat2

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			bat2.y1 += (float)(deltaTime * speed);
			bat2.y2 += (float)(deltaTime * speed);
		}

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			bat2.y1 -= (float)(deltaTime * speed);
			bat2.y2 -= (float)(deltaTime * speed);
		}

		//Check out of bounds for bat1
		if (bat1.y1 < -1.0f)
		{
			bat1.y1 = -1.0f;
			bat1.y2 = -0.8f;
		}
		if (bat1.y2 > 1.0f)
		{
			bat1.y2 = 1.0f;
			bat1.y1 = 0.8f;
		}

		//check out of bounds for bat2
		if (bat2.y1 < -1.0f)
		{
			bat2.y1 = -1.0f;
			bat2.y2 = -0.8f;
		}
		if (bat2.y2 > 1.0f)
		{
			bat2.y2 = 1.0f;
			bat2.y1 = 0.8f;
		}

		Draw(bat1, bat2, ball);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		//Press ESC to exit game..
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			break;
		}

	}

	glfwTerminate();
	return 0;
}

