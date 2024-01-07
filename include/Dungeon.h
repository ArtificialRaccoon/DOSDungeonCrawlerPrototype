#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <string>
#include <fstream>
#include "json.h"
#include "WallSet.h"
#include "WallDeco.h"

using namespace std;

class Dungeon
{
    public:
        int Id;
        std::string Name;
        std::string FloorSet;
        std::string Theme;
        std::vector<WallSet> WallSets;
        std::vector<WallDeco> WallDecos;
        std::vector< std::vector<int> > WallMap;
        std::vector< std::vector<int> > DecoMap;
        Dungeon() {}
        virtual ~Dungeon();
        void LoadDungeon();
    protected:

    private:
};

#endif // DUNGEON_H
