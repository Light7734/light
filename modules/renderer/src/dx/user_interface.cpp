#include <input/key_codes.hpp>
#include <renderer/dx/shared_context.hpp>
#include <renderer/dx/user_interface.hpp>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>
#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>
#include <imgui.h>

namespace lt {

void dxUserInterface::platform_implementation(
    GLFWwindow *windowHandle,
    Ref<SharedContext> sharedContext
)
{
	auto &io = ImGui::GetIO();
	auto context = std::dynamic_pointer_cast<dxSharedContext>(sharedContext);

	ImGui_ImplWin32_Init(glfwGetWin32Window(windowHandle));
	ImGui_ImplDX11_Init(context->get_device().Get(), context->get_device_context().Get());
}

dxUserInterface::~dxUserInterface()
{
	// #todo: handle this in a better way
	auto &io = ImGui::GetIO();

	if (io.IniFilename == "default_gui_layout.ini")
		io.IniFilename = "user_gui_layout.ini";

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void dxUserInterface::begin()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void dxUserInterface::end()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
}

void dxUserInterface::log_debug_data()
{
	// #todo: improve
	log_inf("________________________________________");
	log_inf("UserInterface::");
	log_inf("       API    : ImGui");
	log_inf("       Version: {}", ImGui::GetVersion());
	log_inf("  GraphicsAPI : DirectX");
	log_inf("________________________________________");
}

} // namespace lt
