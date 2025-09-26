#include "Application.h"

// glew, glfw
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// glm
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// standard C++ headers
#include <iostream>
#include <fstream>
#include <sstream>

#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Callbacks.h"

Application::Application() {}

void Application::Init() {
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	printf("OpenGL Version: %s\n",glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %d.%d.%d\n", major, minor, revision);
}

void Application::SetUpCallbacks() {
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
}

void Application::TyVeci() {
	float points_triangle[] = {
		// pos              // color
		0.0f, 0.5f, 0.0f,   1.f, 0.f, 0.f, 1.f,
		0.5f, -0.5f, 0.0f,  0.f, 1.f, 0.f, 1.f,
		-0.5f, -0.5f, 0.0f, 0.f, 0.f, 1.f, 1.f,
	};

	float points_rectangle[] = {
		// pos            // color
		0.5f, 0.5f, 0.0f, 1.f, 0.f, 0.f, 1.f,
		1.0f, 0.5f, 0.0f, 0.f, 0.f, 1.f, 1.f,
		1.0f, 1.0f, 0.0f, 0.f, 1.f, 0.f, 1.f,
		0.5f, 0.5f, 0.0f, 1.f, 0.f, 0.f, 1.f,
		0.5f, 1.0f, 0.0f, 1.f, 1.f, 0.f, 1.f,
		1.0f, 1.0f, 0.0f, 0.f, 1.f, 0.f, 1.f,
	};


	// vertex buffer object (VBO)
	vb1 = new VertexBuffer(points_triangle, sizeof(points_triangle));
	vb1->SetLayout({
		{ElementType::Float, 3},
		{ElementType::Float, 4}
	});

	vb2 = new VertexBuffer(points_rectangle, sizeof(points_rectangle));
	vb2->SetLayout({
		{ElementType::Float, 3},
		{ElementType::Float, 4}
	});

	// vertex array object (VAO)
	va1 = new VertexArray(vb1);

	va2 = new VertexArray();
	va2->AddVertexBuffer(*vb2);

	shaderProgram = new ShaderProgram(
		ReadShaderSource("../assets/vertex_shader.glsl"),
		ReadShaderSource("../assets/fragment_shader.glsl")
	);
}

void Application::Run() {
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram->Use();

		va1->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		va2->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::Shutdown() {
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
