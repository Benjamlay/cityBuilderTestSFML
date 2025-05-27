
#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include <string>
#include <vector>

template <typename TAsset>
class AssetManager {

  std::string folder_;
  std::vector<TAsset> assets_;
  TAsset default_asset_;

public :
  explicit AssetManager(std::string folder);
  void Load();
  const TAsset& Get(int index);

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
const TAsset& AssetManager<TAsset>::Get(int index) {
  if (index < 0 || index >= assets_.size()) {
    return default_asset_;
  }

  return assets_[index];
}


#endif //ASSET_MANAGER_H
