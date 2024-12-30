#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include <cstdlib>
#include <algorithm>
#include <memory>
#include <fstream>
#include "BaseState.h"
#include "InnState.h"
#include "DungeonViewState.h"
#include "GlobalEnumerations.h"
#include "GameUIDefines.h"
#include "allegro.h"
#include "PanelElement.h"
#include "ButtonElement.h"
#include "json.h"

class PauseState : public BaseState
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
        static PauseState* Instance()
        {
            return &mPauseState;
        }

    protected:
        PauseState() { }
        BITMAP *BUFFER;
        std::vector<std::unique_ptr<GUIElement>> GUI;
    
    private:
        int ticks, mouseDebounce;
        bool interactPressed = false;
        static PauseState mPauseState;

        int tilesetWidth;
        int tilesetHeight;   
    
};

#endif // PAUSESTATE_H
