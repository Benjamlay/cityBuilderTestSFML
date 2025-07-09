
#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <functional>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif // TRACY_ENABLE
template <typename TAsset>
class AssetManager {

  std::unordered_map<size_t, TAsset> all_assets_;

public :

  std::string folder_;
  explicit AssetManager(std::string_view folder);
  //void Load();
  void Load(const std::string& name, const std::string& path);
  void LoadAll();
  const TAsset& Get(int index);
  const TAsset& GetTexture(const std::string& name);

};

template <typename TAsset>
AssetManager<TAsset>::AssetManager(std::string_view folder): folder_(folder) {

}


template <typename TAsset>
void AssetManager<TAsset>::Load(const std::string& name, const std::string& path)
{
  {
#ifdef TRACY_ENABLE
    ZoneNamedN(folder_exist_event,"Folder Exist", true);
#endif // TRACY_ENABLE
    if (!std::filesystem::exists(folder_)) {
      return;
    }
  }
#ifdef TRACY_ENABLE
  ZoneNamedN(load_asset_event,"Load Asset", true);
  ZoneTextV(load_asset_event, name.data(), name.size());
#endif // TRACY_ENABLE
  TAsset asset;
  if (!asset.loadFromFile(path)) {
    std::cerr << "Failed to load asset: " << path << std::endl;
    return;
  }

  size_t key = std::hash<std::string>{}(name);
  all_assets_.emplace(key, std::move(asset));
}

template <typename TAsset>
void AssetManager<TAsset>::LoadAll()
{
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif // TRACY_ENABLE
  Load("empty", folder_ + "empty.png");
  Load("grass", folder_ + "grass.png");
  Load("grass2",folder_ + "grass2.png");
  Load("tileSand",folder_ + "tileSand1.png");
  Load("water", folder_ + "water.png");
  Load("tree", folder_ + "tree.png");
  Load("rock", folder_ + "rock.png");
  //TODO: mettre cette methode dans tile_map et non dans l'assetManager
}


template <typename TAsset>

const TAsset& AssetManager<TAsset>::GetTexture(const std::string& name)
{
  size_t key = std::hash<std::string>{}(name);
  auto it = all_assets_.find(key);
  if (it == all_assets_.end()) {throw std::runtime_error("Texture not found: " + name);}
  return it->second;
}


#endif //ASSET_MANAGER_H
