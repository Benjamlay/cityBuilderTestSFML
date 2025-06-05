
#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include <iostream>
#include <string>
#include <vector>

template <typename TAsset>
class AssetManager {

  std::vector<TAsset> assets_;
  std::unordered_map<std::string, TAsset> all_assets_;
  TAsset default_asset_;

public :

  std::string folder_;
  explicit AssetManager(std::string folder);
  void Load();
  void Load(const std::string& name, const std::string& path);
  void Load_All();
  const TAsset& Get(int index);
  const TAsset& GetTexture(std::string name);

};

template <typename TAsset>
AssetManager<TAsset>::AssetManager(std::string folder): folder_(folder) {

}

template <typename TAsset>
void AssetManager<TAsset>::Load() {
  if (!std::filesystem::exists(folder_)) {
    return;
  }
  assets_.emplace_back(TAsset(folder_ + "empty.png"));
  assets_.emplace_back(TAsset(folder_ + "grass.png"));
  assets_.emplace_back(TAsset(folder_ + "grass2.png"));
  assets_.emplace_back(TAsset(folder_ + "tileSand1.png"));
  assets_.emplace_back(TAsset(folder_ + "water.png"));
}

template <typename TAsset>
void AssetManager<TAsset>::Load(const std::string& name, const std::string& path)
{
  if (!std::filesystem::exists(folder_)) {
    return;
  }
  TAsset asset;
  if (!asset.loadFromFile(path)) {
    std::cerr << "Failed to load asset: " << path << std::endl;
    return;
  }
  all_assets_.emplace(name, std::move(asset));
}

template <typename TAsset>
void AssetManager<TAsset>::Load_All()
{
  Load("empty", folder_ + "empty.png");
  Load("grass", folder_ + "grass.png");
  Load("grass2",folder_ + "grass2.png");
  Load("tileSand",folder_ + "tileSand1.png");
  Load("water", folder_ + "water.png");
}



template <typename TAsset>
const TAsset& AssetManager<TAsset>::Get(int index) {
  if (index < 0 || index >= assets_.size()) {
    return default_asset_;
  }

  return assets_[index];
}

template <typename TAsset>

const TAsset& AssetManager<TAsset>::GetTexture(std::string name)
{
  return all_assets_.at(name);

}


#endif //ASSET_MANAGER_H
