#include <engine/events/event.hpp>
#include <engine/events/keyboard.hpp>
#include <engine/events/mouse.hpp>
#include <engine/events/window.hpp>
#include <engine/layer/layer.hpp>
#include <engine/layer/layer_stack.hpp>

namespace Light {

LayerStack *LayerStack::s_Context = nullptr;

Scope<LayerStack> LayerStack::Create()
{
	return MakeScope<LayerStack>(new LayerStack());
}

LayerStack::LayerStack(): m_Layers {}, m_Begin(), m_End()
{
	ASSERT(!s_Context, "An instance of 'LayerStack' already exists, do not construct this class!")
	s_Context = this;
}

LayerStack::~LayerStack()
{
	for (Layer *layer : m_Layers)
		delete layer;
}

void LayerStack::AttachLayerImpl(Layer *layer)
{
	// #todo: handle attaching layer inside a for loop
	m_Layers.push_back(layer);
	m_Begin = m_Layers.begin();
	m_End = m_Layers.end();

	LOG(trace, "Attached [{}]", layer->GetName());
}

void LayerStack::DetachLayerImpl(Layer *layer)
{
	// #todo: handle detaching layer inside a for loop
	m_Layers.erase(std::find(m_Layers.begin(), m_Layers.end(), layer));
	m_Begin = m_Layers.begin();
	m_End = m_Layers.end();

	LOG(trace, "Detached [{}]", layer->GetName());
}

} // namespace Light
