#include <engine/events/event.hpp>
#include <engine/events/keyboard.hpp>
#include <engine/events/mouse.hpp>
#include <engine/events/window.hpp>
#include <engine/layer/layer.hpp>
#include <engine/layer/layer_stack.hpp>

namespace Light {

LayerStack::~LayerStack()
{
	for (auto *layer : m_layers)
	{
		delete layer;
	}
}

void LayerStack::attach_layer_impl(Layer *layer)
{
	// #todo: handle attaching layer inside a for loop
	m_layers.push_back(layer);
	m_begin = m_layers.begin();
	m_end = m_layers.end();

	log_trc("Attached [{}]", layer->get_name());
}

void LayerStack::detach_layer_impl(Layer *layer)
{
	// #todo: handle detaching layer inside a for loop
	m_layers.erase(std::find(m_layers.begin(), m_layers.end(), layer));
	m_begin = m_layers.begin();
	m_end = m_layers.end();

	log_trc("Detached [{}]", layer->get_name());
}

} // namespace Light
