export module input.codes;
import std;

export enum class Key: std::uint16_t {
	none = 0,

	left_mouse_button,
	right_mouse_button,
	middle_mouse_button,

	left_mouse = left_mouse_button,
	right_mouse = right_mouse_button,
	middle_mouse = middle_mouse_button,

	l_mouse = left_mouse_button,
	r_mouse = right_mouse_button,
	m_mouse = middle_mouse_button,

	backspace,
	tab,
	capslock,
	enter,
	space,
	delete_,

	shift,
	left_shit = shift,
	l_shift = shift,

	right_shift,
	r_shift = right_shift,

	control,
	left_control = control,
	l_control = control,
	ctrl = control,
	left_ctrl = control,
	l_ctrl = control,

	right_control,
	r_control = right_control,
	right_ctrl = right_control,
	r_ctrl = right_control,

	alt,
	left_alt = alt,
	l_alt = alt,

	right_alt,
	r_alt = right_alt,

	pageup,
	pagedown,
	home,
	end,

	left_arrow,
	l_arrow = left_arrow,

	up_arrow,
	u_arrow = up_arrow,

	right_arrow,
	r_arrow = right_arrow,

	down_arrow,
	d_arrow = down_arrow,

	cancel,
	pause,
	select,
	print,
	snapshot, // aka. print-screen
	insert,
	help,
	sleep,
	eep = sleep,

	digit_0,
	digit_1,
	digit_2,
	digit_3,
	digit_4,
	digit_5,
	digit_6,
	digit_7,
	digit_8,
	digit_9,

	/* letters */
	a,
	b,
	c,
	d,
	e,
	f,
	g,
	h,
	i,
	j,
	k,
	l,
	m,
	n,
	o,
	p,
	q,
	r,
	s,
	t,
	u,
	v,
	w,
	x,
	y,
	z,

	super,
	left_super = super,
	l_super = super,

	right_super,
	r_super = right_super,

	kp_0,
	kp_1,
	kp_2,
	kp_3,
	kp_4,
	kp_5,
	kp_6,
	kp_7,
	kp_8,
	kp_9,
	kp_decimal,
	kp_divide,
	kp_multiply,
	kp_subtract,
	kp_add,
	kp_enter,
	kp_equal,

	/* function */
	f1,
	f2,
	f3,
	f4,
	f5,
	f6,
	f7,
	f8,
	f9,
	f10,
	f11,
	f12,

	unknown,
};

export [[nodiscard]] constexpr auto to_string(Key key) -> std::string
{
	using enum Key;
	switch (key)
	{
	case none: return "<none>";

	/* mouse */
	case left_mouse_button: return "left_mouse_button";
	case right_mouse_button: return "right_mouse_button";
	case middle_mouse_button: return "middle_mouse_button";

	/* editing / control */
	case backspace: return "backspace";
	case tab: return "tab";
	case capslock: return "capslock";
	case enter: return "enter";
	case space: return "space";
	case delete_: return "delete";

	/* modifiers */
	case shift: return "shift";
	case control: return "control";
	case right_control: return "right_control";
	case alt: return "alt";
	case right_alt: return "right_alt";

	/* navigation */
	case pageup: return "pageup";
	case pagedown: return "pagedown";
	case home: return "home";
	case end: return "end";

	case left_arrow: return "left_arrow";
	case up_arrow: return "up_arrow";
	case right_arrow: return "right_arrow";
	case down_arrow: return "down_arrow";

	/* system */
	case cancel: return "cancel";
	case pause: return "pause";
	case select: return "select";
	case print: return "print";
	case snapshot: return "snapshot";
	case insert: return "insert";
	case help: return "help";
	case sleep: return "sleep";

	/* digits */
	case digit_0: return "0";
	case digit_1: return "1";
	case digit_2: return "2";
	case digit_3: return "3";
	case digit_4: return "4";
	case digit_5: return "5";
	case digit_6: return "6";
	case digit_7: return "7";
	case digit_8: return "8";
	case digit_9: return "9";

	/* letters */
	case a: return "a";
	case b: return "b";
	case c: return "c";
	case d: return "d";
	case e: return "e";
	case f: return "f";
	case g: return "g";
	case h: return "h";
	case i: return "i";
	case j: return "j";
	case k: return "k";
	case l: return "l";
	case m: return "m";
	case n: return "n";
	case o: return "o";
	case p: return "p";
	case q: return "q";
	case r: return "r";
	case s: return "s";
	case t: return "t";
	case u: return "u";
	case v: return "v";
	case w: return "w";
	case x: return "x";
	case y: return "y";
	case z: return "z";

	/* super / meta */
	case super: return "super";
	case right_super: return "right_super";

	/* keypad */
	case kp_0: return "kp_0";
	case kp_1: return "kp_1";
	case kp_2: return "kp_2";
	case kp_3: return "kp_3";
	case kp_4: return "kp_4";
	case kp_5: return "kp_5";
	case kp_6: return "kp_6";
	case kp_7: return "kp_7";
	case kp_8: return "kp_8";
	case kp_9: return "kp_9";
	case kp_decimal: return "kp_decimal";
	case kp_divide: return "kp_divide";
	case kp_multiply: return "kp_multiply";
	case kp_subtract: return "kp_subtract";
	case kp_add: return "kp_add";
	case kp_enter: return "kp_enter";
	case kp_equal: return "kp_equal";

	/* function keys */
	case f1: return "f1";
	case f2: return "f2";
	case f3: return "f3";
	case f4: return "f4";
	case f5: return "f5";
	case f6: return "f6";
	case f7: return "f7";
	case f8: return "f8";
	case f9: return "f9";
	case f10: return "f10";
	case f11: return "f11";
	case f12: return "f12";

	case unknown: return "<unknown>";
	}

	return "<invalid>";
}
