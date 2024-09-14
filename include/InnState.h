#ifndef INNSTATE_H
#define INNSTATE_H

#include <cstdlib>
#include <algorithm>
#include <memory>
#include <fstream>
#include "BaseState.h"
#include "TownState.h"
#include "GlobalEnumerations.h"
#include "GameUIDefines.h"
#include "allegro.h"
#include "PanelElement.h"
#include "ButtonElement.h"
#include "json.h"

class InnState : public BaseState
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
        static InnState* Instance()
        {
            return &mInnState;
        }

    protected:
        InnState() { }
        BITMAP *BUFFER;
        BITMAP *CURRENT_BG;
        BITMAP *BGTAVE;
        BITMAP *INNKEEPER;
        std::vector<std::unique_ptr<GUIElement>> GUI;
    
    private:
        int ticks, mouseDebounce;
        bool interactPressed = false;
        static InnState mInnState;
        MIDI *theme;     

        int tilesetWidth;
        int tilesetHeight;   
    
};

#endif // INNSTATE_H
