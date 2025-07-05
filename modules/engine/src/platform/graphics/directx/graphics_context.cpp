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
	SetupDeviceAndSwapChain(windowHandle);
	SetupRenderTargets();
	SetupDebugInterface();
}

void dxGraphicsContext::SetupDeviceAndSwapChain(GLFWwindow *windowHandle)
{
	Ref<dxSharedContext> context = std::static_pointer_cast<dxSharedContext>(m_shared_context);

	// swap chain desc
	DXGI_SWAP_CHAIN_DESC sd = { 0 };

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
	UINT flags = NULL;
#ifdef LIGHT_DEBUG
	flags = D3D11_CREATE_DEVICE_DEBUG;
#endif

	// create device and swap chain
	DXC(D3D11CreateDeviceAndSwapChain(
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

void dxGraphicsContext::SetupRenderTargets()
{
	Ref<dxSharedContext> context = std::static_pointer_cast<dxSharedContext>(m_shared_context);

	// set primitive topology
	context->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// create render target view
	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;

	DXC(context->GetSwapChain()->GetBuffer(0u, __uuidof(ID3D11Resource), &backBuffer));
	DXC(context->GetDevice()
	        ->CreateRenderTargetView(backBuffer.Get(), nullptr, &context->GetRenderTargetViewRef())
	);

	// set render target view
	context->GetDeviceContext()
	    ->OMSetRenderTargets(1u, context->GetRenderTargetView().GetAddressOf(), nullptr);
}

void dxGraphicsContext::SetupDebugInterface()
{
#ifdef LIGHT_DEBUG
	Ref<dxSharedContext> context = std::static_pointer_cast<dxSharedContext>(m_shared_context);

	HRESULT hr;
	Microsoft::WRL::ComPtr<ID3D11Debug> debugInterface = nullptr;
	DXC(context->GetDevice()->QueryInterface(__uuidof(ID3D11Debug), &debugInterface));

	Microsoft::WRL::ComPtr<ID3D11InfoQueue> infoQueue = nullptr;
	DXC(debugInterface->QueryInterface(__uuidof(ID3D11InfoQueue), &infoQueue));

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
	infoQueue->Release();
#endif
}

void dxGraphicsContext::LogDebugData()
{
	Ref<dxSharedContext> context = std::static_pointer_cast<dxSharedContext>(m_shared_context);

	// locals
	IDXGIDevice *DXGIDevice;
	IDXGIAdapter *DXGIAdapter;
	DXGI_ADAPTER_DESC DXGIAdapterDesc;

	context->GetDevice()->QueryInterface(__uuidof(IDXGIDevice), (void **)&DXGIDevice);
	DXGIDevice->GetAdapter(&DXGIAdapter);
	DXGIAdapter->GetDesc(&DXGIAdapterDesc);

	// get the adapter's description
	char DefChar = ' ';
	char ch[180];
	WideCharToMultiByte(CP_ACP, 0, DXGIAdapterDesc.Description, -1, ch, 180, &DefChar, NULL);
	std::string adapterDesc(ch);

	// release memory
	DXGIDevice->Release();
	DXGIAdapter->Release();

	// #todo: log more information
	LOG(info, "________________________________________");
	LOG(info, "dxGraphicsContext:");
	LOG(info, "        Renderer: {}", adapterDesc);
	LOG(info, "________________________________________");
}

} // namespace Light
