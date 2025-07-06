#include <engine/events/window.hpp>
#include <engine/graphics/blender.hpp"            // required for forward declaratio>
#include <engine/graphics/buffers.hpp"            // required for forward declaratio>
#include <engine/graphics/render_command.hpp"      // required for forward declaratio>
#include <engine/graphics/renderer.hpp"           // required for forward declaratio>
#include <engine/platform/graphics/directx/graphics_context.hpp>
#include <engine/platform/graphics/directx/shared_context.hpp>
#include <engine/user_interface/user_interface.hpp" // required for forward declaratio>
#include <engine/utils/resource_manager.hpp"     // required for forward declaratio>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>

namespace Light {

dxGraphicsContext::dxGraphicsContext(GLFWwindow *windowHandle)
    : m_window_handle(windowHandle)
    , m_debug_interface(nullptr)
{
	// set 'GraphicsAPI';
	m_graphics_api = GraphicsAPI::DirectX;

	m_shared_context = std::make_shared<dxSharedContext>();

	// setup stuff
	setup_device_and_swap_chain(windowHandle);
	setup_render_targets();
	setup_debug_interface();
}

void dxGraphicsContext::setup_device_and_swap_chain(GLFWwindow *windowHandle)
{
	auto context = std::static_pointer_cast<dxSharedContext>(m_shared_context);

	// swap chain desc
	auto sd = DXGI_SWAP_CHAIN_DESC { 0 };

	// buffer desc
	sd.BufferDesc.Width = 1u;
	sd.BufferDesc.Height = 1u;
	sd.BufferDesc.RefreshRate.Numerator = NULL;   // :#todo
	sd.BufferDesc.RefreshRate.Denominator = NULL; // :#todo
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// sample desc (for multi sampling) #todo: implement multi-samplingz
	sd.SampleDesc.Count = 1u;
	sd.SampleDesc.Quality = 0u;

	// #todo: support swap chains with more than 1 back-buffer
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1u;

	// #todo: don't handle Windows's window with glfw, create it yourself
	sd.OutputWindow = static_cast<HWND>(glfwGetWin32Window(windowHandle));
	sd.Windowed = true;

	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	sd.Flags = NULL;

	// determine device flags
	auto flags = UINT { NULL };
#ifdef LIGHT_DEBUG
	flags = D3D11_CREATE_DEVICE_DEBUG;
#endif

	// create device and swap chain
	dxc(D3D11CreateDeviceAndSwapChain(
	    nullptr,
	    D3D_DRIVER_TYPE_HARDWARE,
	    NULL,
	    flags,
	    nullptr,
	    NULL,
	    D3D11_SDK_VERSION,
	    &sd,
	    &context->GetSwapChainRef(),
	    &context->GetDeviceRef(),
	    nullptr,
	    &context->GetDeviceContextRef()
	));
}

void dxGraphicsContext::setup_render_targets()
{
	auto context = std::static_pointer_cast<dxSharedContext>(m_shared_context);

	// set primitive topology
	context->get_device_context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// create render target view
	auto backBuffer = Microsoft::WRL::ComPtr<ID3D11Resource> {};

	dxc(context->get_swap_chain()->GetBuffer(0u, __uuidof(ID3D11Resource), &backBuffer));
	dxc(context->get_device()
	        ->CreateRenderTargetView(backBuffer.Get(), nullptr, &context->GetRenderTargetViewRef())
	);

	// set render target view
	context->get_device_context()
	    ->OMSetRenderTargets(1u, context->get_render_target_view().GetAddressOf(), nullptr);
}

void dxGraphicsContext::setup_debug_interface()
{
#ifdef LIGHT_DEBUG
	Ref<dxSharedContext> context = std::static_pointer_cast<dxSharedContext>(m_shared_context);

	HRESULT hr;
	Microsoft::WRL::ComPtr<ID3D11Debug> debugInterface = nullptr;
	dxc(context->get_device()->QueryInterface(__uuidof(ID3D11Debug), &debugInterface));

	Microsoft::WRL::ComPtr<ID3D11InfoQueue> infoQueue = nullptr;
	dxc(debugInterface->QueryInterface(__uuidof(ID3D11InfoQueue), &infoQueue));

	infoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
	infoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);

	D3D11_MESSAGE_ID hide[] = {
		D3D11_MESSAGE_ID_UNKNOWN,
		// #todo: add more messages here as needed
	};

	D3D11_INFO_QUEUE_FILTER filter = {};
	filter.DenyList.NumIDs = _countof(hide);
	filter.DenyList.pIDList = hide;
	infoQueue->AddStorageFilterEntries(&filter);
	infoQueue->release();
#endif
}

void dxGraphicsContext::log_debug_data()
{
	auto context = std::static_pointer_cast<dxSharedContext>(m_shared_context);

	// locals
	auto *DXGIDevice = (IDXGIDevice *) {};
	auto *DXGIAdapter = (IDXGIAdapter *) {};
	auto *DXGIAdapterDesc = (DXGI_ADAPTER_DESC *) {};

	context->get_device()->QueryInterface(__uuidof(IDXGIDevice), (void **)&DXGIDevice);
	DXGIDevice->GetAdapter(&DXGIAdapter);
	DXGIAdapter->GetDesc(&DXGIAdapterDesc);

	// get the adapter's description
	auto DefChar = ' ';
	char ch[180];
	WideCharToMultiByte(CP_ACP, 0, DXGIAdapterDesc.Description, -1, ch, 180, &DefChar, NULL);
	auto adapterDesc = std::string { ch };

	// release memory
	DXGIDevice->release();
	DXGIAdapter->release();

	// #todo: log more information
	log_inf("________________________________________");
	log_inf("dxGraphicsContext:");
	log_inf("        renderer: {}", adapterDesc);
	log_inf("________________________________________");
}

} // namespace Light
