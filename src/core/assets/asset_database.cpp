#include "asset_database.h"
#include "core/rendering/shader.h"
#include "core/rendering/texture.h"
#include "core/assets/asset.h"

AssetDatabase* AssetDatabase::_instance;

AssetDatabase::AssetDatabase() {}
AssetDatabase::~AssetDatabase() {}

void AssetDatabase::load_database() {
	_instance = new AssetDatabase();
}

std::shared_ptr<Texture> AssetDatabase::load_texture(const std::string& path) {
	return AssetDatabase::get_instance()->iload_texture(path);
}

std::shared_ptr<Shader> AssetDatabase::load_shader(const std::string& path) {
	return AssetDatabase::get_instance()->iload_shader(path);
}

#define TRY_GET_ASSET(map, type)\
	const auto& search = map.find(path);\
	if (search != map.end()) {\
		asset = search->second.lock();\
	} else {\
		asset = std::make_shared<type>(path);\
		map[path] = asset;\
	}\
	return asset;\

std::shared_ptr<Texture> AssetDatabase::iload_texture(const std::string& path) {
	std::shared_ptr<Texture> asset = nullptr;
	TRY_GET_ASSET(_texture_assets, Texture);
}

std::shared_ptr<Shader> AssetDatabase::iload_shader(const std::string& path) {
	std::shared_ptr<Shader> asset = nullptr;
	TRY_GET_ASSET(_shader_assets, Shader);
}

#undef TRY_GET_ASSET