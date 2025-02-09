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
#include "DecoSet.h"
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
        std::vector<DecoSet> DecoSets;
        std::map<int, DoorType> DoorList;
        std::map<int, SwitchType> SwitchList;
        std::vector<std::vector<MapSpace>> WallMap;
        std::map<std::string, SAMPLE*> Effects;
        Dungeon() {}
        virtual ~Dungeon();
        void LoadDungeon();
    protected:

    private:
};

#endif // DUNGEON_H
