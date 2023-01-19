#pragma once

#include "enpch.h"

class Asset;

namespace engine {
	template<typename T>
	std::string to_string(const T& obj);

	std::string to_string(const char* obj);

	std::string to_string(std::shared_ptr<Asset> asset);

	template<typename ...Args>
	std::string format(const std::string_view fmt, Args&&... args) {
		return std::vformat(fmt, std::make_format_args(args...));
	}
}