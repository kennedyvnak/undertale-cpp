#include "enpch.h"
#include "asset_database.h"
#include "core/rendering/shader.h"
#include "core/rendering/texture.h"

namespace engine {
	AssetDatabase* AssetDatabase::_instance;

	AssetDatabase::AssetDatabase() {}
	AssetDatabase::~AssetDatabase() {}

	void AssetDatabase::load_database() {
		_instance = new AssetDatabase();
	}

	Ref<Texture> AssetDatabase::load_texture(const std::string& path) {
		return AssetDatabase::get_instance()->iload_texture(path);
	}

	Ref<Shader> AssetDatabase::load_shader(const std::string& path) {
		return AssetDatabase::get_instance()->iload_shader(path);
	}

#define TRY_GET_ASSET(map, type)\
	const auto& search = map.find(path);\
	if (search != map.end()) {\
		asset = search->second.lock();\
	} else {\
		asset = create_ref<type>(path);\
		map[path] = asset;\
	}\
	return asset;\

	Ref<Texture> AssetDatabase::iload_texture(const std::string& path) {
		Ref<Texture> asset = nullptr;
		TRY_GET_ASSET(_texture_assets, Texture);
	}

	Ref<Shader> AssetDatabase::iload_shader(const std::string& path) {
		Ref<Shader> asset = nullptr;
		TRY_GET_ASSET(_shader_assets, Shader);
	}

#undef TRY_GET_ASSET
}
