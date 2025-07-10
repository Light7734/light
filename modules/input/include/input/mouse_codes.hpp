#pragma once

#include <cstdint>

namespace Light::Mouse {

enum : uint8_t
{
	Button1 = 0,
	Button2 = 1,
	Button3 = 2,
	Button4 = 3,
	Button5 = 4,
	Button6 = 5,
	Button7 = 6,
	Button8 = 7,

	LButton = Button1,
	RButton = Button2,
	MButton = Button3,
};

}
