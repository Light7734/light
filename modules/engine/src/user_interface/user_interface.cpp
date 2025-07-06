#include <engine/platform/graphics/opengl/user_interface.hpp>
#include <engine/user_interface/user_interface.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <engine/platform/graphics/directx/shared_context.hpp>
	#include <engine/platform/graphics/directx/user_interface.hpp>
#endif

#include <engine/events/char.hpp>
#include <engine/events/event.hpp>
#include <engine/events/keyboard.hpp>
#include <engine/events/mouse.hpp>
#include <engine/graphics/graphics_context.hpp>
#include <engine/input/key_codes.hpp>
#include <imgui.h>

namespace Light {

UserInterface *UserInterface::s_context = nullptr;

auto UserInterface::create(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext)
    -> Scope<UserInterface>
{
	auto scopeUserInterface = Scope<UserInterface> { nullptr };

	switch (GraphicsContext::get_graphics_api())
	{
	case GraphicsAPI::OpenGL: scopeUserInterface = create_scope<glUserInterface>(); break;

	case GraphicsAPI::DirectX: lt_win(scopeUserInterface = create_scope<dxUserInterface>();) break;

	default:
		lt_assert(
		    false,
		    "UserInterface::create: invalid/unsupported 'GraphicsAPI' {}",
		    static_cast<uint32_t>(GraphicsContext::get_graphics_api())
		);
		return nullptr;
	}

	scopeUserInterface->init(windowHandle, sharedContext);
	return std::move(scopeUserInterface);
}

UserInterface::UserInterface()
    : m_dockspace_flags(
          ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar
          | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
          | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus
      )
{
	lt_assert(
	    !s_context,
	    "UserInterface::UserInterface: an instance of 'UserInterface' already exists, do not "
	    "construct this class!"
	);
	s_context = this;
}

void UserInterface::init(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext)
{
	// create context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// configure io
	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	io.ConfigFlags |= ImGuiBackendFlags_PlatformHasViewports;
	io.ConfigFlags |= ImGuiBackendFlags_RendererHasViewports;

	// #todo: handle this in a better way
	if (std::filesystem::exists("user_gui_layout.ini"))
		io.IniFilename = "user_gui_layout.ini";
	else
		io.IniFilename = "default_gui_layout.ini";

	// style
	ImGui::StyleColorsDark();

	platform_implementation(windowHandle, sharedContext);

	// keyboard map
	io.KeyMap[ImGuiKey_Tab] = Key::Tab;
	io.KeyMap[ImGuiKey_LeftArrow] = Key::LeftArrow;
	io.KeyMap[ImGuiKey_RightArrow] = Key::RightArrow;
	io.KeyMap[ImGuiKey_UpArrow] = Key::UpArrow;
	io.KeyMap[ImGuiKey_DownArrow] = Key::DownArrow;
	io.KeyMap[ImGuiKey_PageUp] = Key::PageUp;
	io.KeyMap[ImGuiKey_PageDown] = Key::PageDown;
	io.KeyMap[ImGuiKey_Home] = Key::Home;
	io.KeyMap[ImGuiKey_End] = Key::end;
	io.KeyMap[ImGuiKey_Insert] = Key::Insert;
	io.KeyMap[ImGuiKey_Delete] = Key::Delete;
	io.KeyMap[ImGuiKey_Backspace] = Key::BackSpace;
	io.KeyMap[ImGuiKey_Space] = Key::Space;
	io.KeyMap[ImGuiKey_Enter] = Key::Enter;
	io.KeyMap[ImGuiKey_Escape] = Key::Escape;
	io.KeyMap[ImGuiKey_KeyPadEnter] = Key::Enter;
	io.KeyMap[ImGuiKey_A] = Key::A;
	io.KeyMap[ImGuiKey_C] = Key::C;
	io.KeyMap[ImGuiKey_V] = Key::V;
	io.KeyMap[ImGuiKey_X] = Key::X;
	io.KeyMap[ImGuiKey_Y] = Key::Y;
	io.KeyMap[ImGuiKey_Z] = Key::Z;

	io.Fonts->AddFontFromFileTTF("Assets//Fonts/OpenSans/OpenSans-Bold.ttf", 18.0f);
	io.FontDefault = io.Fonts->AddFontFromFileTTF(
	    "Assets/Fonts/OpenSans/OpenSans-Regular.ttf",
	    18.0f
	);

	set_dark_theme_colors();
}

void UserInterface::dockspace_begin()
{
	ImGuiViewport *viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Dockspace", (bool *)0, s_context->m_dockspace_flags);
	ImGui::PopStyleVar(3);

	ImGuiStyle &style = ImGui::GetStyle();
	float minWinSizeX = style.WindowMinSize.x;
	style.WindowMinSize.x = 370.0f;
	ImGui::DockSpace(
	    ImGui::GetID("MyDockSpace"),
	    ImVec2(0.0f, 0.0f),
	    ImGuiDockNodeFlags_None | ImGuiWindowFlags_NoBackground
	);
	style.WindowMinSize.x = minWinSizeX;
}

void UserInterface::dockspace_end()
{
	ImGui::End();
}

void UserInterface::set_dark_theme_colors()
{
	ImGuiStyle &style = ImGui::GetStyle();
	ImVec4(&colors)[55] = style.Colors;

	style.WindowPadding = ImVec2(0.0f, 0.0f);

	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.11f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);

	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

	colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.21f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.30f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

	colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);

	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);

	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

	colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.21f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

	colors[ImGuiCol_Header] = ImVec4(0.20f, 0.20f, 0.21f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);

	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);

	colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.20f, 0.21f, 1.00f);

	colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);

	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);

	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);

	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);

	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

} // namespace Light
