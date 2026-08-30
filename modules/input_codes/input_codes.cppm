/**
 * @note: The reason this is a separate module, rather than being in the `Input` module is that
 * the input is received from the hardware through the `Surface` module, and it is further parsed
 * inside the `Input` module, USING the `Surface` module's events.
 *
 * Hence, both `Surface` and `Input` needs to agree to the same input codes, while `Input` depends
 * on `Surface`. The simplest solution is to keep the codes in a 3rd module and make both depend on
 * it. (I did not want to give `Surface` the responsibility of defining input codes...)
 */
export module input.codes;

import preliminary;

export namespace lt {

// NOLINTNEXTLINE(performance-enum-size)
enum class Key : u16
{
	none = 0,

	left_button,
	l_button = left_button,

	right_button,
	r_button = right_button,

	middle_button,
	m_button = middle_button,

	// the buttons on the sidse of some mouses
	x_button_1,
	x_button_2,

	// Mouse-wheel movement is treated like a key, deal with it.
	wheel_down,
	wheel_up,

	escape,
	escp = escape,
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

	/** Input was received but was none of the above. */
	unknown,
};

[[nodiscard]] constexpr auto to_string(Key key) -> std::string
{
	using enum Key;
	switch (key)
	{
	case none: return "<none>";

	case left_button: return "left_button";
	case right_button: return "right_button";
	case middle_button: return "middle_button";

	case x_button_1: return "x_button_1";
	case x_button_2: return "x_button_2";

	case wheel_down: return "wheel_down";
	case wheel_up: return "wheel_up";

	case escape: return "escape";
	case backspace: return "backspace";
	case tab: return "tab";
	case capslock: return "capslock";
	case enter: return "enter";
	case space: return "space";
	case delete_: return "delete";

	case shift: return "shift";
	case right_shift: return "right_shift";
	case control: return "control";
	case right_control: return "right_control";
	case alt: return "alt";
	case right_alt: return "right_alt";

	case pageup: return "pageup";
	case pagedown: return "pagedown";
	case home: return "home";
	case end: return "end";

	case left_arrow: return "left_arrow";
	case up_arrow: return "up_arrow";
	case right_arrow: return "right_arrow";
	case down_arrow: return "down_arrow";

	case cancel: return "cancel";
	case pause: return "pause";
	case select: return "select";
	case print: return "print";
	case snapshot: return "snapshot";
	case insert: return "insert";
	case help: return "help";
	case sleep: return "sleep";

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

	case super: return "super";
	case right_super: return "right_super";

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

} // namespace lt

template<>
struct std::formatter<lt::Key>: std::formatter<std::string_view>
{
	template<typename FormatContext>
	auto format(lt::Key key, FormatContext &ctx) const
	{
		return std::formatter<std::string_view>::format(lt::to_string(key), ctx);
	}
};
