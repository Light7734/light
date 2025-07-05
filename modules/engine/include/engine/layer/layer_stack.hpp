#pragma once

#include <engine/base/base.hpp>

namespace Light {

class Layer;

class Event;

class LayerStack /* singleton */
{
private:
	static LayerStack *s_Context;

private:
	std::vector<Layer *> m_layers;

	std::vector<Layer *>::iterator m_begin;
	std::vector<Layer *>::iterator m_end;

public:
	static Scope<LayerStack> Create();

	~LayerStack();

	// #todo: is this needed?
	template<typename T, typename... Args>
	static inline void EmplaceLayer(Args &&...args)
	{
		s_Context->AttachLayerImpl(new T((args)...));
	}

	static inline void AttachLayer(Layer *layer)
	{
		s_Context->AttachLayerImpl(layer);
	}
	static inline void DetachLayer(Layer *layer)
	{
		s_Context->DetachLayerImpl(layer);
	}

	inline bool IsEmpty()
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
	LayerStack();

	void AttachLayerImpl(Layer *layer);
	void DetachLayerImpl(Layer *layer);
};

} // namespace Light
