#pragma once

#include <stdint.h>

namespace Light {

namespace Key {
enum : uint16_t
{
	/* digits */
	D0 = 48,
	D1 = 49,
	D2 = 50,
	D3 = 51,
	D4 = 52,
	D5 = 53,
	D6 = 54,
	D7 = 55,
	D8 = 56,
	D9 = 57,
	Semicolon = 59, // ;
	Equal = 61,     // =

	/* letters */
	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90,

	/* brackets */
	LeftBracket = 91,        // [
	LBracket = LeftBracket,  // [
	RightBracket = 93,       // ]
	RBracket = RightBracket, // ]

	/* arrow */
	Right = 262,
	RightArrow = Right,
	RArrow = Right,
	Left = 263,
	LeftArrow = Left,
	LArrow = Left,
	Down = 264,
	DownArrow = Down,
	DArrow = Down,
	Up = 265,
	UpArrow = Up,
	UArrow = Up,

	/* page */
	PageUp = 266,
	PageDown = 267,

	/* home/end */
	Home = 268,
	End = 269,

	/* toggles */
	CapsLock = 280,
	ScrollLock = 281,
	NumLock = 282,
	NumberLock = NumLock,

	/* function */
	F1 = 290,
	F2 = 291,
	F3 = 292,
	F4 = 293,
	F5 = 294,
	F6 = 295,
	F7 = 296,
	F8 = 297,
	F9 = 298,
	F10 = 299,
	F11 = 300,
	F12 = 301,
	F13 = 302,
	F14 = 303,
	F15 = 304,
	F16 = 305,
	F17 = 306,
	F18 = 307,
	F19 = 308,
	F20 = 309,
	F21 = 310,
	F22 = 311,
	F23 = 312,
	F24 = 313,
	F25 = 314,

	/* keypad */
	Kp0 = 320,
	Kp1 = 321,
	Kp2 = 322,
	Kp3 = 323,
	Kp4 = 324,
	Kp5 = 325,
	Kp6 = 326,
	Kp7 = 327,
	Kp8 = 328,
	Kp9 = 329,
	KpDecimal = 330,
	KpDivide = 331,
	KpMultiply = 332,
	KpSubstract = 333,
	KpAdd = 334,
	KpEnter = 335,
	KpEqual = 336,

	/* modifiers */
	LeftShift = 340,
	LShift = LeftShift,
	LeftControl = 341,
	LControl = LeftControl,
	LeftAlt = 342,
	LAlt = LeftAlt,
	LeftSuper = 343,
	LSuper = LeftSuper,
	RightShift = 344,
	RShift = 344,
	RightControl = 345,
	RControl = 345,
	RightAlt = 346,
	RAlt = 346,
	RightSuper = 347,
	RSuper = 347,

	/* misc */
	Space = 32,
	Apostrophe = 39, // '
	Quote = Apostrophe,

	Comma = 44,           // ,
	Minus = 45,           // -
	Period = 46,          // .
	Slash = 47,           // /
	ForwardSlash = Slash, // /
	BackSlash = 92,       // \

	GraveAccent = 96,     // `
	Console = GraveAccent,
	World1 = 161, // non-US #1
	World2 = 162, // non-US #2
	Escape = 256,
	Esc = Escape,
	Enter = 257,
	Tab = 258,
	BackSpace = 259,
	Insert = 260,
	Delete = 261,

	PrintScreen = 283,
	Pause = 284,

	Menu = 348,

};
}

} // namespace Light
