export module lsd.thread;
import std;

export namespace lt::lsd {

using thread_id = std::thread::id;

[[nodiscard]] auto this_thread_id() -> thread_id
{
	return std::this_thread::get_id();
}

} // namespace lt::sd
