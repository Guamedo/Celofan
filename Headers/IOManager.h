#ifndef CELOFAN_IOMANAGER_H
#define CELOFAN_IOMANAGER_H


#include <vector>
#include <string>

namespace Celofan {

    class IOManager {
    public:
        static bool readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer);
    };

}

#endif //CELOFAN_IOMANAGER_H
