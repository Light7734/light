#pragma once

namespace lt {

class Layer;
class Event;

class LayerStack
{
public:
	template<typename Layer_T, typename... Args>
	void emplace_layer(Args &&...args)
	{
		attach_layer(create_ref<Layer_T>(std::forward<Args>(args)...));
	}

	void attach_layer(Ref<Layer> layer);

	void detach_layer(const Ref<Layer> &layer);

	[[nodiscard]] auto is_empty() const -> bool
	{
		return m_layers.empty();
	}

	[[nodiscard]] auto begin() -> std::vector<Ref<Layer>>::iterator
	{
		return m_layers.begin();
	}

	[[nodiscard]] auto end() -> std::vector<Ref<Layer>>::iterator
	{
		return m_layers.end();
	}

	[[nodiscard]] auto rbegin() -> std::vector<Ref<Layer>>::reverse_iterator
	{
		return m_layers.rbegin();
	}

	[[nodiscard]] auto rend() -> std::vector<Ref<Layer>>::reverse_iterator
	{
		return m_layers.rend();
	}

private:
	std::vector<Ref<Layer>> m_layers;
};

} // namespace lt
