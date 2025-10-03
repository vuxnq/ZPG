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
#include "Transformation.h"
#include "Model.h"
#include "DrawableObject.h"


#include "assets/models/sphere.h"



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

	// depth comparisons and update the depth buffer
	glEnable(GL_DEPTH_TEST);

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

void Application::CreateModels() {
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
	ref<VertexBuffer> vb1 = make_ref(new VertexBuffer(points_triangle, sizeof(points_triangle)));
	vb1->SetLayout({
		{ElementType::Float, 3},
		{ElementType::Float, 4}
	});

	ref<VertexBuffer> vb2 = make_ref(new VertexBuffer(points_rectangle, sizeof(points_rectangle)));
	vb2->SetLayout({
		{ElementType::Float, 3},
		{ElementType::Float, 4}
	});

	// vertex array object (VAO)
	ref<VertexArray> va1 = make_ref(new VertexArray(vb1));
	ref<VertexArray> va2 = make_ref(new VertexArray(vb2));

	// Models
	ref<Model> triangleModel = make_ref(new Model(va1));
	ref<Model> rectangleModel = make_ref(new Model(va2));

	// DrawableObjects
	triangleObject = new DrawableObject(triangleModel, make_ref(new Transformation()));
	rectangleObject = new DrawableObject(rectangleModel, make_ref(new Transformation()));


	ref<Shader> vertexShader = make_ref(new Shader("../assets/vertex_shader.glsl", GL_VERTEX_SHADER));
	ref<Shader> fragmentShader = make_ref(new Shader("../assets/fragment_shader.glsl", GL_FRAGMENT_SHADER));
	shaderProgram = make_ref(new ShaderProgram({vertexShader, fragmentShader}));


	// sphere ////////////////////////////
	ref<VertexBuffer> sphereVBO = make_ref(new VertexBuffer(sphere, sizeof(sphere), {
		{ElementType::Float, 3},
		{ElementType::Float, 3}
	}));
	ref<VertexArray> sphereVAO = make_ref(new VertexArray(sphereVBO));
	ref<Model> sphereModel = make_ref(new Model(sphereVAO));

	ref<Transformation> t = make_ref<Transformation>();
	t->Add(make_ref(new DynamicRotateTransform(0, 50, glm::vec3(0.0f, 1.0f, 0.0f))));
	t->Add(make_ref(new ScaleTransform(0.5)));
	t->Add(make_ref(new RotateTransform(45, glm::vec3(0.0f, 0.0f, 1.0f))));
	t->Add(make_ref(new TranslateTransform(glm::vec3(0.0f, 0.5f, 0.0f))));

	sphereObject = new DrawableObject(sphereModel, t);
	sphereObject->SetShaderProgram(shaderProgram);
	// end: sphere ////////////////////////////
}

void Application::Run() {
	float lastTime = 0.f;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentTime = glfwGetTime();
		float delta = currentTime - lastTime;
		lastTime = currentTime;

		shaderProgram->Use();

		sphereObject->Update(delta);
		sphereObject->Draw();

		shaderProgram->SetUniform("modelMatrix", glm::mat4(1.0f));

		triangleObject->Draw();
		rectangleObject->Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::Shutdown() {
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
