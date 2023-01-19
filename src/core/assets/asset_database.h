#pragma once

#include "enpch.h"
#include "core/base.h"

namespace engine {
	class Texture;
	class Shader;

	class AssetDatabase {
	public:
		AssetDatabase(const AssetDatabase&) = delete;

		static void load_database();

		static AssetDatabase* get_instance() { return _instance; }

		static Ref<Texture> load_texture(const std::string& path);
		static Ref<Shader> load_shader(const std::string& path);
	private:
		AssetDatabase();
		~AssetDatabase();

		static AssetDatabase* _instance;

		std::unordered_map<std::string, std::weak_ptr<Texture>> _texture_assets;
		std::unordered_map<std::string, std::weak_ptr<Shader>> _shader_assets;

		Ref<Texture> iload_texture(const std::string& path);
		Ref<Shader> iload_shader(const std::string& path);
	};
}