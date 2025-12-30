import test.test;
import test.expects;
import surface.system;
import surface.events;
import surface.requests;
import ecs.registry;
import memory.scope;
import memory.reference;
import logger;
import math.vec2;
import app.system;
import std;

using ::lt::surface::SurfaceComponent;
using ::lt::surface::System;
using ::lt::test::Case;
using ::lt::test::expect_eq;
using ::lt::test::expect_ne;
using ::lt::test::expect_not_nullptr;
using ::lt::test::expect_throw;
using ::lt::test::Suite;
using ::std::ignore;
using ::lt::test::operator""_suite;

Suite raii = "platform_linux_raii"_suite = [] {
	auto registry = lt::memory::create_ref<lt::ecs::Registry>();
	std::ignore = System { registry };
};
