//
// Created by hw on 2017/8/2.
//

#include "MadeFileUtils.h"

std::string MadeFileUtils::copyFile(const std::string &filename) {
    // 资源路径
    std::string sourcePath = FileUtils::getInstance()->fullPathForFilename(filename);
    Data data = FileUtils::getInstance()->getDataFromFile(sourcePath);

    // 可写路径
    std::string destPath = FileUtils::getInstance()->getWritablePath() + filename;
    FILE *fp = fopen(destPath.c_str(), "w+");
    if (fp) {
        size_t size = fwrite(data.getBytes(), sizeof(unsigned char), data.getSize(), fp);
        fclose(fp);

        if (size > 0) {
            return destPath;
        }
    }
    CCLOG("copy file %s failed.", filename.c_str());
    return nullptr;
}
