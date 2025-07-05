#pragma once

#include <engine/base/base.hpp>
#include <engine/scene/entity.hpp>

namespace Light {

class NativeScript
{
	friend class Scene;

private:
	Entity m_Entity;
	unsigned int m_UniqueIdentifier = 0; // :#todo

public:
	NativeScript() = default;
	virtual ~NativeScript() = default;

	inline unsigned int GetUID() const
	{
		return m_UniqueIdentifier;
	}

	template<typename T>
	T &GetComponent()
	{
		return m_Entity.GetComponent<T>();
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
