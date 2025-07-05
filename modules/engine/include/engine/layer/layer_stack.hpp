#pragma once

#include <engine/base/base.hpp>

namespace Light {

class Layer;
class Event;

class LayerStack /* singleton */
{
public:
	static Scope<LayerStack> create();

	~LayerStack();

	// #todo: is this needed?
	template<typename t, typename... Args>
	static inline void emplace_layer(Args &&...args)
	{
		s_context->attach_layer_impl(new t((args)...));
	}

	static inline void attach_layer(Layer *layer)
	{
		s_context->attach_layer_impl(layer);
	}
	static inline void detach_layer(Layer *layer)
	{
		s_context->detach_layer_impl(layer);
	}

	inline bool is_empty()
	{
		return m_layers.empty();
	}

	std::vector<Layer *>::iterator begin()
	{
		return m_layers.begin();
	}

	std::vector<Layer *>::iterator end()
	{
		return m_layers.end();
	}

	std::vector<Layer *>::reverse_iterator rbegin()
	{
		return m_layers.rbegin();
	}

	std::vector<Layer *>::reverse_iterator rend()
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
