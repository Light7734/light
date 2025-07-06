#pragma once

#include <engine/base/base.hpp>

namespace Light {

class Layer;
class Event;

class LayerStack /* singleton */
{
public:
	static auto create() -> Scope<LayerStack>;

	~LayerStack();

	// #todo: is this needed?
	template<typename t, typename... Args>
	static void emplace_layer(Args &&...args)
	{
		s_context->attach_layer_impl(new t((args)...));
	}

	static void attach_layer(Layer *layer)
	{
		s_context->attach_layer_impl(layer);
	}

	static void detach_layer(Layer *layer)
	{
		s_context->detach_layer_impl(layer);
	}

	auto is_empty() -> bool
	{
		return m_layers.empty();
	}

	auto begin() -> std::vector<Layer *>::iterator
	{
		return m_layers.begin();
	}

	auto end() -> std::vector<Layer *>::iterator
	{
		return m_layers.end();
	}

	auto rbegin() -> std::vector<Layer *>::reverse_iterator
	{
		return m_layers.rbegin();
	}

	auto rend() -> std::vector<Layer *>::reverse_iterator
	{
		return m_layers.rend();
	}

private:
	static LayerStack *s_context;

	std::vector<Layer *> m_layers;

	std::vector<Layer *>::iterator m_begin;

	std::vector<Layer *>::iterator m_end;

	LayerStack();

	void attach_layer_impl(Layer *layer);

	void detach_layer_impl(Layer *layer);
};

} // namespace Light
