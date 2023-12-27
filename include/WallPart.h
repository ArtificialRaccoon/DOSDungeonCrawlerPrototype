#ifndef WALLPART_H
#define WALLPART_H

#include <vector>

using namespace std;

class WallPart
{
    public:
        WallPart() {}
        virtual ~WallPart() {}
        int height, width;
        int startX, startY;
        int startTileX, startTileY;
        std::vector<int> tileData;
    protected:

    private:
};

#endif // WALLPART_H
