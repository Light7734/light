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

LayerStack::LayerStack(): m_layers {}, m_begin(), m_end()
{
	ASSERT(!s_Context, "An instance of 'LayerStack' already exists, do not construct this class!")
	s_Context = this;
}

LayerStack::~LayerStack()
{
	for (Layer *layer : m_layers)
		delete layer;
}

void LayerStack::AttachLayerImpl(Layer *layer)
{
	// #todo: handle attaching layer inside a for loop
	m_layers.push_back(layer);
	m_begin = m_layers.begin();
	m_end = m_layers.end();

	LOG(trace, "Attached [{}]", layer->GetName());
}

void LayerStack::DetachLayerImpl(Layer *layer)
{
	// #todo: handle detaching layer inside a for loop
	m_layers.erase(std::find(m_layers.begin(), m_layers.end(), layer));
	m_begin = m_layers.begin();
	m_end = m_layers.end();

	LOG(trace, "Detached [{}]", layer->GetName());
}

} // namespace Light
