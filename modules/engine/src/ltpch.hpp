#pragma once

/* engine */
#include <engine/base/base.hpp>

/* windows */
#ifdef _WIN32
	#define NOMINMAX
	#include <Windows.h>
	#undef NOMINMAX
#endif

/* containers */
#include <array>
#include <bitset>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/* misc */
#include <algorithm>
#include <functional>
#include <memory>
#include <tuple>
#include <utility>

/* input/output */
#include <fstream>
#include <iostream>
#include <sstream>

/* multi threading */
#include <atomic>
#include <thread>

/* string */
#include <string>
#include <string_view>

/* filesystem */
#include <filesystem>

/* c libraries */
#include <math.h>
#include <time.h>
