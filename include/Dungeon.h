#ifndef DUNGEON_H
#define DUNGEON_H

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "json.h"
#include "DoorType.h"
#include "SwitchType.h"
#include "WallSet.h"
#include "WallDeco.h"
#include "MapSpace.h"

using namespace std;

class Dungeon
{
    public:
        int Id;
        std::string Name;
        std::string FloorSet;
        std::string Theme;
        std::vector<WallSet> WallSets;
        std::vector<WallSet> DoorSets;
        std::vector<WallDeco> WallDecos;
        std::map<std::string, WallDeco> SwitchSets;
        std::map<std::string, WallDeco> DoorClosedSets;
        std::map<int, DoorType> DoorList;
        std::map<int, SwitchType> SwitchList;
        std::vector<std::vector<MapSpace>> WallMap;
        Dungeon() {}
        virtual ~Dungeon();
        void LoadDungeon();
    protected:

    private:
};

#endif // DUNGEON_H
