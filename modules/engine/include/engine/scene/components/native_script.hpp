#pragma once

#include <engine/base/base.hpp>
#include <engine/scene/components/scriptable_entity.hpp>

namespace Light {

struct NativeScriptComponent
{
	NativeScript *instance;

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
};

} // namespace Light
