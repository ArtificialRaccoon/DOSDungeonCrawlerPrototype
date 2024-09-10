#ifndef OVERWORLDSTATE_H
#define OVERWORLDSTATE_H

#include <cstdlib>
#include <algorithm>
#include <memory>
#include "BaseState.h"
#include "DungeonViewState.h"
#include "GlobalEnumerations.h"
#include "GameUIDefines.h"
#include "allegro.h"
#include "PanelElement.h"
#include "ButtonElement.h"
#include "json.h"

class OverworldState : public BaseState
{
    public:
        void InitState();
        void Pause();
        void Resume();
        void AquireInput(GameProcessor* game);
        void ProcessInput(GameProcessor* game);
        void Render(GameProcessor* game);
        void UnloadResources();
        static OverworldState* Instance()
        {
            return &mOverworldState;
        }

    protected:
        OverworldState() { }
        BITMAP *BUFFER;
        BITMAP *OVERWORLDMAP;
        BITMAP *MAPUI;
        FONT *mapFont;
        PALETTE palette;
        std::vector<std::unique_ptr<GUIElement>> GUI;
    
    private:
        int tilesetWidth, tilesetHeight;  
        int ticks, mouseDebounce;
        bool interactPressed = false;
        static OverworldState mOverworldState;
        MIDI *theme;        
    
    private:
        void getNextGUIElement(bool forward);
};

#endif // OVERWORLDSTATE_H
