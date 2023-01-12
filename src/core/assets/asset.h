#pragma once

#include <string>

class Asset {
public:
	Asset(const std::string& path);
	~Asset();

	inline const std::string& get_path() const& { return _path; }
private:
	std::string _path;
};