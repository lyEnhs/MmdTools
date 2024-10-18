#ifndef LYENHS_VIEWER_H_
#define LYENHS_VIEWER_H_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "ViewerLogger.h"
#include "ViewerCommand.h"
#include "ViewerContext.h"

namespace  lyenhs 
{
	class LyViewer
	{
	public:
		LyViewer();
		~LyViewer();

		struct InitializeParameter
		{
			InitializeParameter();

			bool m_msaaEnable;
			int	 m_msaaCount;

			bool		m_initCamera;
			glm::vec3	m_initCameraCenter;
			glm::vec3   m_initCameraEye;
			float		m_initCameraNearClip;
			float		m_initCameraFarClip;
			float		m_initCameraRadius;

			bool		m_initScene;
			float		m_initSceneUnitScale;
		};

		bool Initialize(const InitializeParameter& initParam = InitializeParameter());
		void Uninitslize();

		int Run();

		bool ExecuteCommand(const ViewerCommand& cmd);

	private:
		static void OnMouseButtonStub(GLFWwindow* window, int button, int action, int mods);
		void OnMouseButton(int button, int action, int mods);

		static void OnScrollStub(GLFWwindow* window, double offsetx, double offsety);
		void OnScroll(double offsetx, double offsety);

		static void OnKeyStub(GLFWwindow* window, int key, int scancode, int action, int mods);
		void OnKey(int key, int scancode, int action, int mods);

		static void OnCharStub(GLFWwindow* window, unsigned int codepoint);
		void OnChar(unsigned int codepoint);

		static void OnDropStub(GLFWwindow* window, int count, const char** paths);
		void OnDrop(int count, const char** paths);

	private:
		GLFWwindow* m_window;
		InitializeParameter m_initParam;

		//logUI
		std::shared_ptr<ImGUILogSink>	m_imguiLogSink;

		ViewerContext		m_context;

	};
}


#endif//LYENHS_VIEWER_H_