#ifndef throwif_h
#define throwif_h

#include <vector>
#include <sstream>
#include <stdexcept>
#include <string>

// for convenient and verbose output of throw_if
// exeption messages
#define SOURCE_LOCATION \
	__FILE__, "@", std::to_string (__LINE__), ": "

// convient use of throw if function including source location
// from where exception has been thrown
#define THROW_IF(premise, ...) \
	blurryroots::util::throw_if (premise, SOURCE_LOCATION, ##__VA_ARGS__)

namespace blurryroots { namespace util {

template<class... TArgs> static void
throw_if (bool premise, TArgs... args) {
	if (! premise) {
		return;
	}

	std::vector<std::string> arguments {
		args...
	};

	std::stringstream ss;

	for (auto &a : arguments) {
		ss << a;
	}
	ss << std::endl;

	throw std::runtime_error (ss.str ());
}

}}

#endif
