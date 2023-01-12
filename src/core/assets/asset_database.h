#pragma once

#include <memory>
#include <string>
#include <unordered_map>

class Texture;
class Shader;

class AssetDatabase {
public:
	AssetDatabase(const AssetDatabase&) = delete;

	static void load_database();

	static AssetDatabase* get_instance() { return _instance; }

	static std::shared_ptr<Texture> load_texture(const std::string& path);
	static std::shared_ptr<Shader> load_shader(const std::string& path);
private:
	AssetDatabase();
	~AssetDatabase();

	static AssetDatabase* _instance;

	std::unordered_map<std::string, std::weak_ptr<Texture>> _texture_assets;
	std::unordered_map<std::string, std::weak_ptr<Shader>> _shader_assets;

	std::shared_ptr<Texture> iload_texture(const std::string& path);
	std::shared_ptr<Shader> iload_shader(const std::string& path);
};
