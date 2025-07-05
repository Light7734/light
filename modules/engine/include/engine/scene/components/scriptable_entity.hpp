#pragma once

#include <engine/base/base.hpp>
#include <engine/scene/entity.hpp>

namespace Light {

class NativeScript
{
	friend class Scene;

private:
	Entity m_entity;
	unsigned int m_unique_identifier = 0; // :#todo

public:
	NativeScript() = default;
	virtual ~NativeScript() = default;

	inline unsigned int GetUID() const
	{
		return m_unique_identifier;
	}

	template<typename T>
	T &GetComponent()
	{
		return m_entity.GetComponent<T>();
	}

protected:
	virtual void OnCreate()
	{
	}
	virtual void OnDestroy()
	{
	}
	virtual void OnUpdate(float ts)
	{
	}
};

} // namespace Light
