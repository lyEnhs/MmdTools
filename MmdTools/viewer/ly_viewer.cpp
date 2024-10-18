#include "ly_viewer.h"
#include <Path.h>
#include <Base/Log.h>
#include <Base/Singleton.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <ImGuizmo.h>

namespace lyenhs
{
	float lastTime;
	float deltaTime;
	LyViewer::LyViewer()
		:m_window(nullptr)
	{

	}

	LyViewer::~LyViewer()
	{


	}

	LyViewer::InitializeParameter::InitializeParameter()
	:m_msaaEnable(false)
	,m_msaaCount(4)
	,m_initCamera(false)
	,m_initCameraCenter(0, 0, 0)
	,m_initCameraEye(0, 0, 10)
	,m_initCameraNearClip(0.1f)
	,m_initCameraFarClip(1000.0f)
	,m_initCameraRadius(10.0f)
	,m_initScene(false)
	,m_initSceneUnitScale(1.0f)
	{

	}

	bool LyViewer::Initialize(const InitializeParameter& initParam /* = InitializeParameter() */)
	{
		SABA_INFO("Exe path = {}", PathUtil::GetExePath());

		m_initParam = initParam;

		auto logger = saba::Singleton<saba::Logger>::Get();
		m_imguiLogSink = logger->AddSink<ImGUILogSink>();

		SABA_INFO("CurDir={}", m_context.GetWorkDir());

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		if (m_initParam.m_msaaEnable)
		{
			m_context.EnableMSAA(true);
			m_context.SetMSAACount(m_initParam.m_msaaCount);
		}

		m_window = glfwCreateWindow(800, 600, "lyenhs 3d viewer", nullptr, nullptr);
		if (m_window == nullptr)
		{
			SABA_INFO("create window failed!!!");
			glfwTerminate();
			return false;
		}

		glfwSetWindowUserPointer(m_window, this);
		glfwSetMouseButtonCallback(m_window, OnMouseButtonStub);
		glfwSetScrollCallback(m_window, OnScrollStub);
		glfwSetKeyCallback(m_window, OnKeyStub);
		glfwSetCharCallback(m_window, OnCharStub);
		glfwSetDropCallback(m_window, OnDropStub);

		glfwMakeContextCurrent(m_window);

		//IMGUI
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(m_window, false);
		ImGui_ImplOpenGL3_Init("#version 150");

		//glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			SABA_INFO("init glad failed!!!");
			return false;
		}
		glEnable(GL_DEPTH_TEST);

		lastTime = static_cast<float>(glfwGetTime());
		return true;
	}


	void LyViewer::Uninitslize()
	{

	}

	int LyViewer::Run()
	{

		while (!glfwWindowShouldClose(m_window))
		{
			float currentTime = static_cast<float>(glfwGetTime());
			deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::BeginFrame();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//glViewport(0, 0, 800, 600);
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}

		glfwTerminate();
		return 0;
	}

	bool LyViewer::ExecuteCommand(const ViewerCommand& cmd)
	{
		return true;
	}


	void LyViewer::OnMouseButtonStub(GLFWwindow* window, int button, int action, int mods)
	{
		LyViewer* viewer = (LyViewer*)glfwGetWindowUserPointer(window);
		if (viewer)
		{
			viewer->OnMouseButton(button, action, mods);
		}
	}

	void LyViewer::OnMouseButton(int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
		
		}

	}


	void LyViewer::OnScrollStub(GLFWwindow* window, double offsetx, double offsety)
	{
		LyViewer* viewer = (LyViewer*)glfwGetWindowUserPointer(window);
		if (viewer)
		{
			viewer->OnScroll(offsetx, offsety);
		}
	}

	void LyViewer::OnScroll(double offsetx, double offsety)
	{

	}

	void LyViewer::OnKeyStub(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		LyViewer* viewer = (LyViewer*)glfwGetWindowUserPointer(window);
		if (viewer)
		{
			viewer->OnKey(key, scancode, action, mods);
		}
	}

	void LyViewer::OnKey(int key, int scancode, int action, int mods)
	{

	}

	void LyViewer::OnCharStub(GLFWwindow* window, unsigned int codepoint)
	{
		LyViewer* viewer = (LyViewer*)glfwGetWindowUserPointer(window);
		if (viewer)
		{
			viewer->OnChar(codepoint);
		}
	}

	void LyViewer::OnChar(unsigned int codepoint)
	{

	}

	void LyViewer::OnDropStub(GLFWwindow* window, int count, const char** paths)
	{
		LyViewer* viewer = (LyViewer*)glfwGetWindowUserPointer(window);
		if (viewer)
		{
			viewer->OnDrop(count, paths);
		}
	}

	void LyViewer::OnDrop(int count, const char** paths)
	{
		if (count > 0)
		{
			std::vector<std::string> args;
			for (int i=0; i<count; ++i)
			{
				SABA_INFO("Drop File. {}", paths[i]);
				args.emplace_back(paths[i]);
			}
		}

	}
}
