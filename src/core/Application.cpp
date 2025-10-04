#include "core/Application.h"

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

#include "core/Callbacks.h"
#include "core/ShaderProgram.h"
#include "object/VertexBuffer.h"
#include "object/VertexArray.h"
#include "object/Model.h"
#include "object/DrawableObject.h"
#include "transform/Transformation.h"

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

void Application::OnCreate() {
	ref<Shader> vertexShader = make_ref(new Shader("../assets/vertex_shader.glsl", GL_VERTEX_SHADER));
	ref<Shader> fragmentShader = make_ref(new Shader("../assets/fragment_shader.glsl", GL_FRAGMENT_SHADER));
	shaderProgram = make_ref(new ShaderProgram({vertexShader, fragmentShader}));

	// Scenes /////////////////////////////
	// scene1 - triangle
	float points_triangle[] = {
		// pos              // color
		0.0f, 0.5f, 0.0f,   1.f, 0.f, 0.f, 1.f,
		0.5f, -0.5f, 0.0f,  0.f, 1.f, 0.f, 1.f,
		-0.5f, -0.5f, 0.0f, 0.f, 0.f, 1.f, 1.f,
	};

	ref<VertexBuffer> triangleVBO = make_ref(new VertexBuffer(points_triangle, sizeof(points_triangle)));
	triangleVBO->SetLayout({
		{ElementType::Float, 3},
		{ElementType::Float, 4}
	});
	ref<VertexArray> triangleVAO = make_ref(new VertexArray(triangleVBO));
	ref<Model> triangleModel = make_ref(new Model(triangleVAO));
	ref<DrawableObject> triangleObject = make_ref(new DrawableObject(
		triangleModel,
		make_ref(new DynamicRotateTransform(90, glm::vec3(0.0f, 0.0f, 1.0f), 1)),
		shaderProgram
	));

	ref<Scene> scene1 = make_ref(new Scene());
	scene1->AddDrawableObject(triangleObject);

	sceneManager.AddScene("scene1", scene1);

	// scene2 - balls :p
	ref<VertexBuffer> sphereVBO = make_ref(new VertexBuffer(sphere, sizeof(sphere), {
		{ElementType::Float, 3},
		{ElementType::Float, 3}
	}));
	ref<VertexArray> sphereVAO = make_ref(new VertexArray(sphereVBO));
	ref<Model> sphereModel = make_ref(new Model(sphereVAO));

	ref<Transformation> transformation = make_ref<Transformation>();

	transformation->Add(make_ref(new TranslateTransform(glm::vec3(1.0f, 1.0f, 0.0f))));
	transformation->Add(make_ref(new DynamicRotateTransform(45, glm::vec3(0.0f, 1.0f, 0.0f), 3)));
	transformation->Add(make_ref(new ScaleTransform(0.5)));
	transformation->Add(make_ref(new RotateTransform(45, glm::vec3(0.0f, 0.0f, 1.0f))));
	transformation->Add(make_ref(new TranslateTransform(glm::vec3(0.0f, 0.5f, 0.0f))));
	transformation->Add(make_ref(new DynamicTranslateTransform(glm::vec3(0.0f, -0.5f, 0.0f), 0.5)));
	transformation->Add(make_ref(new DynamicScaleTransform(-1, 0.1)));

	ref<DrawableObject> sphereObject = make_ref(new DrawableObject(sphereModel, transformation, shaderProgram));

	ref<Scene> scene2 = make_ref(new Scene());
	scene2->AddDrawableObject(sphereObject);

	sceneManager.AddScene("scene2", scene2);

	sceneManager.SetActiveScene("scene2");
}

void Application::Run() {
	float lastTime = 0.0f;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentTime = glfwGetTime();
		float delta = currentTime - lastTime;
		lastTime = currentTime;

		sceneManager.GetActiveScene()->OnUpdate(delta);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::Shutdown() {
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
