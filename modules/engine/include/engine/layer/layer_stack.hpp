#pragma once



namespace Light {

class Layer;
class Event;

class LayerStack
{
public:
	static auto instance() -> LayerStack &
	{
		static auto instance = LayerStack {};
		return instance;
	}

	template<typename Layer_T, typename... Args>
	static void emplace_layer(Args &&...args)
	{
		instance().attach_layer_impl(create_ref<Layer_T>(std::forward<Args>(args)...));
	}

	static void attach_layer(Ref<Layer> layer)
	{
		instance().attach_layer_impl(std::move(layer));
	}

	static void detach_layer(const Ref<Layer> &layer)
	{
		instance().detach_layer_impl(layer);
	}

	auto is_empty() -> bool
	{
		return m_layers.empty();
	}

	auto begin() -> std::vector<Ref<Layer>>::iterator
	{
		return m_layers.begin();
	}

	auto end() -> std::vector<Ref<Layer>>::iterator
	{
		return m_layers.end();
	}

	auto rbegin() -> std::vector<Ref<Layer>>::reverse_iterator
	{
		return m_layers.rbegin();
	}

	auto rend() -> std::vector<Ref<Layer>>::reverse_iterator
	{
		return m_layers.rend();
	}

private:
	std::vector<Ref<Layer>> m_layers;

	LayerStack() = default;

	void attach_layer_impl(Ref<Layer> layer);

	void detach_layer_impl(const Ref<Layer> &layer);
};

} // namespace Light
