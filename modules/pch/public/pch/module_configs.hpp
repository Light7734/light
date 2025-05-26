namespace lt {

#ifdef LIGHT_ENABLE_CHECK
constexpr bool light_enabled_check = true;
#else
constexpr bool light_enabled_check = false;
#endif

#ifdef LIGHT_ENABLE_ENSURE
constexpr bool light_enabled_ensure = true;
#else
constexpr bool light_enabled_ensure = false;
#endif

} // namespace lt
