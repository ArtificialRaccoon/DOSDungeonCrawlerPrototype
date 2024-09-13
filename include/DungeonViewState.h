#ifndef DUNGEONVIEWSTATE_H
#define DUNGEONVIEWSTATE_H

#include <cstdlib>
#include "CommonGUI.h"
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
        void UnloadResources();
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
        bool interactPressed = false;
        Dungeon dungeonObj;
        VisionCone wallCone, decoCone;
        MazeUI mazeUIObj;
        MazeViewRenderer mazeRenderer;
        static DungeonViewState mDungeonViewState;
        int Wrap(int input, int const lowerBound, int const upperBound);
        void UpdateCone(MapSpace* coneArray, bool calculateForX, int a, int b, int mapN1, int mapN2, int deltaSign, int xOffset, int arrayLen, int pivotPoint);
        MIDI *theme; 
};

#endif // DUNGEONVIEWSTATE_H
