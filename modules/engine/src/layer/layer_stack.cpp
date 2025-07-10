#include <engine/layer/layer.hpp>
#include <engine/layer/layer_stack.hpp>

namespace lt {

void LayerStack::attach_layer(Ref<Layer> layer)
{
	log_trc("Attaching layer [{}]", layer->get_name());
	m_layers.emplace_back(std::move(layer));
}

void LayerStack::detach_layer(const Ref<Layer> &layer)
{
	log_trc("Detaching layer [{}]", layer->get_name());
	m_layers.erase(std::find(m_layers.begin(), m_layers.end(), layer));
}

} // namespace lt
