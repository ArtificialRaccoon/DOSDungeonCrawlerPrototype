#ifndef TOWNSTATE_H
#define TOWNSTATE_H

#include <cstdlib>
#include <algorithm>
#include <memory>
#include <fstream>
#include "BaseState.h"
#include "PauseState.h"
#include "InnState.h"
#include "DungeonViewState.h"
#include "GlobalEnumerations.h"
#include "GameUIDefines.h"
#include "allegro.h"
#include "PanelElement.h"
#include "ButtonElement.h"
#include "json.h"

class TownState : public BaseState
{
    public:
        void InitState();
        void Pause();
        void Resume();
        void AquireInput(GameProcessor* game);
        void ProcessInput(GameProcessor* game);
        void Render(GameProcessor* game);
        void getNextGUIElement(bool forward);
        void UnloadResources();
        static TownState* Instance()
        {
            return &mTownState;
        }

    protected:
        TownState() { }
        BITMAP *BUFFER;
        BITMAP *CURRENT_BG;
        BITMAP *BGTOWN;
        std::vector<std::unique_ptr<GUIElement>> GUI;
    
    private:
        int ticks, mouseDebounce;
        bool interactPressed = false;
        static TownState mTownState;
        MIDI *theme;     

        int tilesetWidth;
        int tilesetHeight;   
    
};

#endif // TOWNSTATE_H
