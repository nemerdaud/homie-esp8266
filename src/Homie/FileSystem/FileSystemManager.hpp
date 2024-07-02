#ifndef FILESYSTEMMANAGER_HPP
#define FILESYSTEMMANAGER_HPP

#include <FS.h>
#ifdef USE_SPIFFS
#include <SPIFFS.h>
#elif defined(USE_LITTLEFS)
#include <LittleFS.h>
#elif defined(USE_SDFS)
#include <SDFS.h>
#endif

namespace HomieInternals {
class FileSystemManager {
 public:
  FileSystemManager();
  virtual ~FileSystemManager() {}
  bool fsBegin();
  fs::FS* getFileSystem() const;

 protected:
  FS* fileSystem;
  bool fsBegan;
  FSConfig fileSystemConfig;

 private:
  bool _fsBeginImpl();
};
}  // namespace HomieInternals

#endif // FILESYSTEMMANAGER_HPP
