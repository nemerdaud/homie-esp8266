#include "FileSystemManager.hpp"

using namespace HomieInternals;

FileSystemManager::FileSystemManager()
  : fsBegan(false) {
#if defined USE_SPIFFS
  fileSystem = &SPIFFS;
  fileSystemConfig = SPIFFSConfig();
#elif defined USE_LITTLEFS
  fileSystem = &LittleFS;
  fileSystemConfig = LittleFSConfig();
#elif defined USE_SDFS
  fileSystem = &SDFS;
  fileSystemConfig = SDFSConfig();
#else
#error Please select a filesystem adding compiler directive -DUSE_SPIFFS | -DUSE_LITTLEFS | -DUSE_SDFS
#endif
}

bool FileSystemManager::fsBegin() {
  return _fsBeginImpl();
}

bool FileSystemManager::_fsBeginImpl() {
  if (!fsBegan) {
    fileSystemConfig.setAutoFormat(false);
    fileSystem->setConfig(fileSystemConfig);
#ifdef ESP32
    fsBegan = fileSystem->begin(true);
#elif defined(ESP8266)
    fsBegan = fileSystem->begin();
#endif
    if (!fsBegan) {
      // Logger can be added here if needed
    }
  }
  return fsBegan;
}

fs::FS* FileSystemManager::getFileSystem() const { return fileSystem; }
