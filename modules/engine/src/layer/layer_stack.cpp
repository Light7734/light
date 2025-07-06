#include <engine/events/event.hpp>
#include <engine/events/keyboard.hpp>
#include <engine/events/mouse.hpp>
#include <engine/events/window.hpp>
#include <engine/layer/layer.hpp>
#include <engine/layer/layer_stack.hpp>

namespace Light {

void LayerStack::attach_layer_impl(Ref<Layer> layer)
{
	log_trc("Attaching [{}]", layer->get_name());
	m_layers.emplace_back(std::move(layer));
}

void LayerStack::detach_layer_impl(const Ref<Layer> &layer)
{
	log_trc("Detaching [{}]", layer->get_name());
	m_layers.erase(std::find(m_layers.begin(), m_layers.end(), layer));
}

} // namespace Light
