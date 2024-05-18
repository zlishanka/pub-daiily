#pragma once

#include <string>

#define Subcomponent 	AvailCV

namespace Subcomponent {

const std::string name = "AvailCV";

const int VER_MAJOR = 1;		// range: [00 to 99]
const int VER_MINOR = 5;		// range: [00 to 99]
const int VER_PATCH = 6;		// range: [00 to 99]


// Some APIs to access versions:

inline const int getBuildVer() {
	return VER_MAJOR * 10000 + VER_MINOR * 100 + VER_PATCH;
}

inline const std::string getBuildVerStr() {
	return std::to_string(VER_MAJOR) + "." + std::to_string(VER_MINOR) + "." + std::to_string(VER_PATCH);
}

inline const int getBuildVerMajor() { return VER_MAJOR; }
inline const int getBuildVerMinor() { return VER_MINOR; }
inline const int getBuildVerPatch() { return VER_PATCH; }

} // namespace Subcomponent

