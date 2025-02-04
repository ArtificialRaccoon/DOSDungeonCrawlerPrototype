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

    //"Simpleson" doesn't play nicely with arrays of arrays
    //so instead we use a single dimensional array, where
    //the length of each row is defined as WallLength
    int wallLength = (int)dungeonObj["WallLength"];

    vector<int> wallArray = dungeonObj["Walls"];
    for(int i = 0; i < wallLength; i++)
    {
        vector<MapSpace> row;
        for(int j = 0; j < wallLength; j++)
        {
            MapSpace newWall;
            if(wallArray[i * 10 + j] > 0)
            {
                newWall.TypeFlag = SpaceType::WALL;
                newWall.WallSetId = wallArray[i * 10 + j];
            }
            row.push_back(newWall);
        }
        WallMap.push_back(row);
    }   
}

Dungeon::~Dungeon()
{

}
