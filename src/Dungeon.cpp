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

    //Fetch the DoorSets
    std::vector<std::string> doorSetArray = dungeonObj["DoorSets"];
    for(int i = 0; i < doorSetArray.size(); i++)
    {
        WallSet newWallset;
        newWallset.LoadWallSet(doorSetArray[i].c_str());
        DoorSets.push_back(newWallset);
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

    vector<int> wallArray = dungeonObj["Walls"];
    for(int i = 0; i < wallLength; i++)
    {
        vector<MapSpace> row;
        for(int j = 0; j < wallLength; j++)
        {
            MapSpace newWall;
            if(wallArray[i * 10 + j] > 0)
            {
                newWall.TypeFlag = WALL;
                newWall.WallSetId = wallArray[i * 10 + j];
            }
            row.push_back(newWall);
        }
        WallMap.push_back(row);
    }

    vector<json::jobject> switchArray = dungeonObj["Switches"];
    for(int i = 0; i < switchArray.size(); i++)
    {
        json::jobject switchObj = switchArray[i];
        vector<int> locArray = switchObj["Location"]; 
        std::string switchTile = switchObj["SpriteSheet"];
        int switchState = switchObj["InitialState"];    

        WallMap[locArray[0]][locArray[1]].TypeFlag = WallMap[locArray[0]][locArray[1]].TypeFlag | SWITCH;
    }

    vector<json::jobject> doorArray = dungeonObj["Doors"];
    for(int i = 0; i < doorArray.size(); i++)
    {
        DoorType doorObj;
        json::jobject doorJson = doorArray[i];         
        vector<int> locArray = doorJson["Location"]; 
        doorObj.Id = doorJson["Id"];
        doorObj.DoorSetId = doorJson["DoorSetId"];
        doorObj.DoorSpriteSheet = string(doorJson["DoorSprite"]);        
        WallMap[locArray[0]][locArray[1]].TypeFlag = WallMap[locArray[0]][locArray[1]].TypeFlag | DOOR; 
        WallMap[locArray[0]][locArray[1]].DoorId = doorJson["Id"];
        DoorList[doorJson["Id"]] = doorObj;
    }
}

Dungeon::~Dungeon()
{

}
