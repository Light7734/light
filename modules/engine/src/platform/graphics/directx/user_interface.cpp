#include <engine/input/key_codes.hpp>
#include <engine/platform/graphics/directx/shared_context.hpp>
#include <engine/platform/graphics/directx/user_interface.hpp>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>
#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>
#include <imgui.h>

namespace Light {

void dxUserInterface::PlatformImplementation(
    GLFWwindow *windowHandle,
    Ref<SharedContext> sharedContext
)
{
	ImGuiIO &io = ImGui::GetIO();
	Ref<dxSharedContext> context = std::dynamic_pointer_cast<dxSharedContext>(sharedContext);

	ImGui_ImplWin32_Init(glfwGetWin32Window(windowHandle));
	ImGui_ImplDX11_Init(context->GetDevice().Get(), context->GetDeviceContext().Get());
}

dxUserInterface::~dxUserInterface()
{
	// #todo: handle this in a better way
	ImGuiIO &io = ImGui::GetIO();

	if (io.IniFilename == "default_gui_layout.ini")
		io.IniFilename = "user_gui_layout.ini";

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void dxUserInterface::Begin()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void dxUserInterface::End()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
}

void dxUserInterface::LogDebugData()
{
	// #todo: improve
	LOG(info, "________________________________________");
	LOG(info, "UserInterface::");
	LOG(info, "       API    : ImGui");
	LOG(info, "       Version: {}", ImGui::GetVersion());
	LOG(info, "  GraphicsAPI : DirectX");
	LOG(info, "________________________________________");
}

} // namespace Light
