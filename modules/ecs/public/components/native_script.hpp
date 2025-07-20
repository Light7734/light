#pragma once

#include <ecs/components/scriptable_entity.hpp>

namespace lt {

struct NativeScriptComponent
{
	NativeScript *(*CreateInstance)();

	void (*DestroyInstance)(NativeScriptComponent *);

	template<typename t>
	void bind()
	{
		CreateInstance = []() {
			return static_cast<NativeScript *>(new t());
		};
		DestroyInstance = [](NativeScriptComponent *nsc) {
			delete (t *)(nsc->instance);
			nsc->instance = nullptr;
		};
	}

	NativeScript *instance;
};

} // namespace lt
