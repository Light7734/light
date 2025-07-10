#pragma once

#include <base/base.hpp>

/* windows */
#ifdef _WIN32
	#define NOMINMAX
	#include <Windows.h>
	#undef NOMINMAX
#endif

/** Stdlib */
#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <math.h>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#include <time.h>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
