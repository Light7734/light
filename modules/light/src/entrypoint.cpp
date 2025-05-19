auto main() -> int32_t
try
{
	std::cout << "Light built and ran fine...";

	return 0;
}
catch (const std::exception &exp)
{
	std::cout << "\n\nUnhandled std exception: " << exp.what() << std::endl; // NOLINT
	return -1;
}
catch (...)
{
	std::cout << "\n\nUnhandled exception" << std::endl; // NOLINT
	return -1;
}
