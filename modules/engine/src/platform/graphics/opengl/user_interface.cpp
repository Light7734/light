#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <engine/input/key_codes.hpp>
#include <engine/platform/graphics/opengl/user_interface.hpp>
#include <imgui.h>

namespace Light {

void glUserInterface::PlatformImplementation(
    GLFWwindow *windowHandle,
    Ref<SharedContext> sharedContext
)
{
	m_window_handle = windowHandle;

	ImGui_ImplGlfw_InitForOpenGL(windowHandle, false);
	ImGui_ImplOpenGL3_Init();
}

glUserInterface::~glUserInterface()
{
	// #todo: handle this in a better way
	ImGuiIO &io = ImGui::GetIO();

	if (io.IniFilename == "default_gui_layout.ini")
		io.IniFilename = "user_gui_layout.ini";

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void glUserInterface::Begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void glUserInterface::End()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	glfwMakeContextCurrent(m_window_handle);
}

void glUserInterface::LogDebugData()
{
	// #todo: improve
	LOG(info, "________________________________________");
	LOG(info, "UserInterface::");
	LOG(info, "       API    : ImGui");
	LOG(info, "       Version: {}", ImGui::GetVersion());
	LOG(info, "  GraphicsAPI : OpenGL");
	LOG(info, "________________________________________");
}

} // namespace Light
