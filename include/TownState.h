#ifndef TOWNSTATE_H
#define TOWNSTATE_H

#include <cstdlib>
#include <algorithm>
#include "BaseState.h"
#include "DungeonViewState.h"
#include "GlobalEnumerations.h"
#include "GameUIDefines.h"
#include "allegro.h"
#include "GUIElement.h"
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
        void UnloadResources();
        static TownState* Instance()
        {
            return &mTownState;
        }

    protected:
        TownState() { }
        BITMAP *BUFFER;
        BITMAP *BGTOWN;
        BITMAP *BGSHOP;
        BITMAP *BGTAVE;
        BITMAP *BGTMPL;
        BITMAP *CHARSHOP;
        BITMAP *CHARTAVE;
        BITMAP *CHARTMPL;
        PALETTE palette;
        std::vector<GUIElement> GUI;
    
    private:
        int ticks, mouseDebounce;
        bool interactPressed = false;
        static TownState mTownState;
        MIDI *theme;        
    
};

#endif // TOWNSTATE_H
