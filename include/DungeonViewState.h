#ifndef DUNGEONVIEWSTATE_H
#define DUNGEONVIEWSTATE_H

#include <cstdlib>
#include "Dungeon.h"
#include "MazeViewRenderer.h"
#include "BaseState.h"
#include "MazeUI.h"
#include "VisionCone.h"
#include "GlobalEnumerations.h"

class DungeonViewState : public BaseState
{
    public:
        void InitState();
        void Pause();
        void Resume();
        void AquireInput(GameProcessor* game);
        void ProcessInput(GameProcessor* game);
        void Render(GameProcessor* game);
        static DungeonViewState* Instance()
        {
            return &mDungeonViewState;
        }

    protected:
        DungeonViewState() { }
        void ComputeVision(bool calculateForX, int deltaSign, int deltaY, int deltaX);
        BITMAP *BUFFER;

    private:
        Rotation facing;
        int playerX, playerY;
        int deltaX, deltaY;
        int ticks, mouseDebounce;
        Dungeon dungeonObj;
        VisionCone wallCone, decoCone;
        MazeUI mazeUIObj;
        MazeViewRenderer mazeRenderer;
        static DungeonViewState mDungeonViewState;
        int Wrap(int input, int const lowerBound, int const upperBound);
};

#endif // DUNGEONVIEWSTATE_H
