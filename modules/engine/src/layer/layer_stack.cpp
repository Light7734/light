#include <engine/events/event.hpp>
#include <engine/events/keyboard.hpp>
#include <engine/events/mouse.hpp>
#include <engine/events/window.hpp>
#include <engine/layer/layer.hpp>
#include <engine/layer/layer_stack.hpp>

namespace Light {

LayerStack *LayerStack::s_Context = nullptr;

Scope<LayerStack> LayerStack::create()
{
	return make_scope<LayerStack>(new LayerStack());
}

LayerStack::LayerStack(): m_layers {}, m_begin(), m_end()
{
	lt_assert(
	    !s_Context,
	    "An instance of 'LayerStack' already exists, do not construct this class!"
	) s_Context
	    = this;
}

LayerStack::~LayerStack()
{
	for (Layer *layer : m_layers)
		delete layer;
}

void LayerStack::attach_layer_impl(Layer *layer)
{
	// #todo: handle attaching layer inside a for loop
	m_layers.push_back(layer);
	m_begin = m_layers.begin();
	m_end = m_layers.end();

	lt_log(trace, "Attached [{}]", layer->GetName());
}

void LayerStack::detach_layer_impl(Layer *layer)
{
	// #todo: handle detaching layer inside a for loop
	m_layers.erase(std::find(m_layers.begin(), m_layers.end(), layer));
	m_begin = m_layers.begin();
	m_end = m_layers.end();

	lt_log(trace, "Detached [{}]", layer->GetName());
}

} // namespace Light
