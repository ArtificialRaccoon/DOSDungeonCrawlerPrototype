#ifndef OVERWORLDSTATE_H
#define OVERWORLDSTATE_H

#include <cstdlib>
#include "BaseState.h"
#include "DungeonViewState.h"
#include "GlobalEnumerations.h"
#include "GameUIDefines.h"
#include "allegro.h"

class OverworldState : public BaseState
{
    public:
        void InitState();
        void Pause();
        void Resume();
        void AquireInput(GameProcessor* game);
        void ProcessInput(GameProcessor* game);
        void Render(GameProcessor* game);
        static OverworldState* Instance()
        {
            return &mOverworldState;
        }

    protected:
        OverworldState() { }
        BITMAP *BUFFER;
        BITMAP *OVERWORLDMAP;
        BITMAP *MAPUI;
        PALETTE palette;
    private:
        int ticks, mouseDebounce;
        bool interactPressed = false;
        static OverworldState mOverworldState;
        MIDI *theme;        
};

#endif // OVERWORLDSTATE_H
