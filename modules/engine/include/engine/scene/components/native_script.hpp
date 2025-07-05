#pragma once

#include <engine/base/base.hpp>
#include <engine/scene/components/scriptable_entity.hpp>

namespace Light {

struct NativeScriptComponent
{
	NativeScript *instance;

	NativeScript *(*CreateInstance)();
	void (*DestroyInstance)(NativeScriptComponent *);

	template<typename T>
	void Bind()
	{
		CreateInstance = []() {
			return static_cast<NativeScript *>(new T());
		};
		DestroyInstance = [](NativeScriptComponent *nsc) {
			delete (T *)(nsc->instance);
			nsc->instance = nullptr;
		};
	}
};

} // namespace Light
