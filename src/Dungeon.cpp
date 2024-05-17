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
                newWall.TypeFlag = SpaceType::WALL;
                newWall.WallSetId = wallArray[i * 10 + j];
            }
            row.push_back(newWall);
        }
        WallMap.push_back(row);
    }

    vector<json::jobject> switchArray = dungeonObj["Switches"];
    for(int i = 0; i < switchArray.size(); i++)
    {
        SwitchType switchObj;
        json::jobject switchJson = switchArray[i];
        vector<int> locArray = switchJson["Location"]; 
        switchObj.Id = switchJson["Id"];
        switchObj.SwitchSpriteSheet = string(switchJson["SpriteSheet"]);
        switchObj.SwitchState = switchJson["InitialState"];    
        switchObj.Location[0] = locArray[0];
        switchObj.Location[1] = locArray[1];
        WallMap[locArray[0]][locArray[1]].TypeFlag = WallMap[locArray[0]][locArray[1]].TypeFlag | SpaceType::SWITCH;
        WallMap[locArray[0]][locArray[1]].SwitchId = switchJson["Id"];
        
        //Load Sound Effect
        Effects[string(switchJson["Effect"])] = load_sample((".\\SFX\\" + string(switchJson["Effect"]) + ".WAV").c_str());
        switchObj.Effect = string(switchJson["Effect"]);
        SwitchList[switchJson["Id"]] = switchObj;

        //Load Switch Spritesheets
        std::string upSheetName = string(switchJson["SpriteSheet"]).append("A");
        WallDeco upSheet;
        upSheet.LoadWallDeco(upSheetName.c_str());
        if(SwitchSets.find(upSheetName) == SwitchSets.end())
            SwitchSets[upSheetName] = upSheet;

        std::string downSheetName = string(switchJson["SpriteSheet"]).append("B");
        WallDeco downSheet;
        downSheet.LoadWallDeco(downSheetName.c_str());
        if(SwitchSets.find(downSheetName) == SwitchSets.end())
            SwitchSets[downSheetName] = downSheet;
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
        WallMap[locArray[0]][locArray[1]].TypeFlag = WallMap[locArray[0]][locArray[1]].TypeFlag | SpaceType::DOOR; 
        WallMap[locArray[0]][locArray[1]].DoorId = doorJson["Id"];

        //Load Combination
        vector<json::jobject> combination = doorJson["Combination"];
        for(int j = 0; j < combination.size(); j++)
        {
            json::jobject comboItem = combination[j];
            int switchId = comboItem["SwitchId"];
            int switchState = comboItem["SwitchState"];
            doorObj.Combination[switchId] = switchState;
        }

        //Load Door Spritesheets
        WallDeco doorSheet;
        doorSheet.LoadWallDeco(doorObj.DoorSpriteSheet);
        if(DoorClosedSets.find(doorObj.DoorSpriteSheet) == DoorClosedSets.end())
            DoorClosedSets[doorObj.DoorSpriteSheet] = doorSheet;
    
        //Load Sound Effect
        Effects[string(doorJson["Effect"])] = load_sample((".\\SFX\\" + string(doorJson["Effect"]) + ".WAV").c_str());
        doorObj.Effect = string(doorJson["Effect"]);
        DoorList[doorJson["Id"]] = doorObj;        
    }    
}

Dungeon::~Dungeon()
{

}
