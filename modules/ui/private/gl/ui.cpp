#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <input/key_codes.hpp>
#include <ui/gl/ui.hpp>

namespace lt {

void glUserInterface::platform_implementation(
    GLFWwindow *windowHandle,
    Ref<SharedContext> /* shared_context */
)
{
	m_window_handle = windowHandle;

	ImGui_ImplGlfw_InitForOpenGL(windowHandle, false);
	ImGui_ImplOpenGL3_Init();
}

glUserInterface::~glUserInterface()
{
	// #todo: handle this in a better way
	auto &io = ImGui::GetIO();

	if (io.IniFilename == "default_gui_layout.ini")
	{
		io.IniFilename = "user_gui_layout.ini";
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void glUserInterface::begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void glUserInterface::end()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	glfwMakeContextCurrent(m_window_handle);
}

void glUserInterface::log_debug_data()
{
	// #todo: improve
	log_inf("________________________________________");
	log_inf("UserInterface::");
	log_inf("       API    : ImGui");
	log_inf("       Version: {}", ImGui::GetVersion());
	log_inf("  GraphicsAPI : OpenGL");
	log_inf("________________________________________");
}

} // namespace lt
