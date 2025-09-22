#pragma once

namespace lt::ecs {

/**
 *
 * @ref https://programmingpraxis.com/2012/03/09/sparse-sets/
 */
template<typename Identifier_T = uint32_t>
class TypeErasedSparseSet
{
public:
	TypeErasedSparseSet() = default;

	TypeErasedSparseSet(TypeErasedSparseSet &&) = default;

	TypeErasedSparseSet(const TypeErasedSparseSet &) = default;

	auto operator=(TypeErasedSparseSet &&) -> TypeErasedSparseSet & = default;

	auto operator=(const TypeErasedSparseSet &) -> TypeErasedSparseSet & = default;

	virtual ~TypeErasedSparseSet() = default;

	virtual void remove(Identifier_T identifier) = 0;
};

template<typename Value_T, typename Identifier_T = uint32_t>
class SparseSet: public TypeErasedSparseSet<Identifier_T>
{
public:
	using Dense_T = std::pair<Identifier_T, Value_T>;

	static constexpr auto max_capacity = size_t { 1'000'000 };

	static constexpr auto null_identifier = std::numeric_limits<Identifier_T>().max();

	explicit SparseSet(size_t initial_capacity = 1)
	{
		ensure(
		    initial_capacity <= max_capacity,
		    "Failed to create SparseSet: capacity too large ({} > {})",
		    initial_capacity,
		    max_capacity
		);

		m_dense.reserve(initial_capacity);
		m_sparse.resize(initial_capacity, null_identifier);
	}

	auto insert(Identifier_T identifier, Value_T value) -> Dense_T &
	{
		if (m_sparse.size() < identifier + 1)
		{
			auto new_capacity = std::max(static_cast<size_t>(identifier + 1), m_sparse.size() * 2);
			new_capacity = std::min(new_capacity, max_capacity);

			// log_dbg("Increasing sparse vector size:", m_dead_count);
			// log_dbg("\tdead_count: {}", m_dead_count);
			// log_dbg("\talive_count: {}", m_alive_count);
			// log_dbg("\tsparse.size: {} -> {}", m_sparse.size(), new_capacity);

			m_sparse.resize(new_capacity, null_identifier);
		}

		++m_alive_count;
		m_sparse[identifier] = m_dense.size();
		return m_dense.emplace_back(identifier, std::move(value));
	}

	/** @warn invalidates begin/end iterators
	 *
	 * @todo(Light): make it not invalidate the iterators >:c
	 */
	void remove(Identifier_T identifier) override
	{
		auto &idx = m_sparse[identifier];
		auto &[entity, component] = m_dense[idx];

		auto &[last_entity, last_component] = m_dense.back();
		auto &last_idx = m_sparse[last_entity];

		// removed entity is in dense's back, just pop and invalidate sparse[identifier]
		if (entity == last_entity)
		{
			idx = null_identifier;
			m_dense.pop_back();
		}
		else
		{
			// swap dense's 'back' to 'removed'
			std::swap(component, last_component);
			entity = last_entity;

			// make sparse point to new idx
			last_idx = idx;

			// pop dense and invalidate sparse[identifier]
			idx = null_identifier;
			m_dense.pop_back();
		}

		++m_dead_count;
		--m_alive_count;
	}

	void clear()
	{
		m_dense.clear();
		m_sparse.clear();
		m_alive_count = 0;
	}

	[[nodiscard]] auto contains(Identifier_T identifier) const -> bool
	{
		return m_sparse.size() > identifier               //
		       && m_sparse[identifier] != null_identifier //
		       && m_dense[m_sparse[identifier]].first == identifier;
	}

	auto begin() -> std::vector<Dense_T>::iterator
	{
		return m_dense.begin();
	}

	auto end() -> std::vector<Dense_T>::iterator
	{
		return m_dense.end();
	}

	[[nodiscard]] auto at(Identifier_T identifier) const -> const Dense_T &
	{
		return m_dense.at(m_sparse.at(identifier));
	}

	[[nodiscard]] auto at(Identifier_T identifier) -> Dense_T &
	{
		return m_dense.at(m_sparse.at(identifier));
	}

	/** @warn unsafe, for bound-checked access: use `.at` */
	[[nodiscard]] auto &&operator[](this auto &&self, Identifier_T identifier)
	{
		using Self_T = decltype(self);
		return std::forward<Self_T>(self).m_dense[std::forward<Self_T>(self).m_sparse[identifier]];
	}

	[[nodiscard]] auto get_size() const noexcept -> size_t
	{
		return m_alive_count;
	}

	[[nodiscard]] auto get_capacity() const noexcept -> size_t
	{
		return m_sparse.capacity();
	}

	[[nodiscard]] auto is_empty() const noexcept -> bool
	{
		return m_dense.empty();
	}

private:
	std::vector<Dense_T> m_dense;

	std::vector<Identifier_T> m_sparse;

	size_t m_alive_count {};

	size_t m_dead_count {};
};

} // namespace lt::ecs
