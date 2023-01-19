#pragma once

#include "enpch.h"
#include "core/base.h"

class Asset;

namespace engine {
	template<typename T>
	std::string to_string(const T& obj);

	std::string to_string(const char* obj);

	std::string to_string(Ref<Asset> asset);

	template<typename ...Args>
	std::string format(const std::string_view fmt, Args&&... args) {
		return std::vformat(fmt, std::make_format_args(args...));
	}
}