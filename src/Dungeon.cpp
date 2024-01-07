#include "Dungeon.h"

void Dungeon::LoadDungeon()
{
    std::ifstream ifs(".\\DUNGEONS\\DUN1FLR1.dun");
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    json::jobject dungeonObj = json::jobject::parse(content);

    
    //Fetch FloorSet / Background
    FloorSet = dungeonObj.get("FloorSet");

    //Fetch the WallSets
    std::vector<std::string> wallSetArray = dungeonObj["WallSets"];
    for(int i = 0; i < wallSetArray.size(); i++)
    {
        WallSet newWallset;
        newWallset.LoadWallSet(wallSetArray[i].c_str());
        WallSets.push_back(newWallset);
    }

    //Load the theme music
    Theme = dungeonObj.get("Theme");

    //Fetch the Wall Decorations
    std::vector<std::string> wallDecoArray = dungeonObj["WallDeco"];
    for(int i = 0; i < wallDecoArray.size(); i++)
    {
        WallDeco newWalldeco;
        newWalldeco.LoadWallDeco(wallDecoArray[i].c_str());
        WallDecos.push_back(newWalldeco);
    }
    
    //"Simpleson" doesn't play nicely with arrays of arrays
    //so instead we use a single dimensional array, where
    //the length of each row is defined as WallLength
    int wallLength = (int)dungeonObj["WallLength"];

    //Fetch the wall map
    vector<int> wallArray = dungeonObj["Walls"];
    for(int i = 0; i < wallLength; i++)
    {
        vector<int> row;
        for(int j = 0; j < wallLength; j++)
        {
            row.push_back(wallArray[i * 10 + j]);
        }
        WallMap.push_back(row);
    }

    //Fetch the decoration map
    vector<int> decoArray = dungeonObj["WallDecos"];
    for(int i = 0; i < wallLength; i++)
    {
        vector<int> row;
        for(int j = 0; j < wallLength; j++)
        {
            row.push_back(decoArray[i * 10 + j]);
        }
        DecoMap.push_back(row);
    }
}

Dungeon::~Dungeon()
{

}
