#include "OverworldState.h"

OverworldState OverworldState::mOverworldState;

void OverworldState::InitState()
{
    BUFFER = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    OVERWORLDMAP = load_bitmap(".\\OTHER\\WRLDMAP.bmp", palette);
    MAPUI = load_bitmap(".\\OTHER\\MAPUI.bmp", palette);
    
    ticks = 0;
    mouseDebounce = 0;
    	
	theme = load_midi(".\\MUSIC\\TROUBLE.MID");
	play_midi(theme, TRUE);    
}

void OverworldState::Pause()
{

}

void OverworldState::Resume()
{

}

void OverworldState::AquireInput(GameProcessor* game)
{
    if(keypressed())
    {
        switch(readkey() >> 8)
        {        
            case KEY_ENTER:
                interactPressed = true;
                break;
            case KEY_ESC:
                exit(0);
                break;
        }
    }

    if(mouse_b & 1 && mouseDebounce == 0)
    {
        mouseDebounce++;
    }

    ticks++;
    if(ticks == 60)
        ticks = 0;

    if(mouseDebounce > 0)
    {
        if(mouse_b & 1)
        {
            mouseDebounce++;
            if(mouseDebounce >= 15)
                mouseDebounce = 0;
        }
        else
            mouseDebounce = 0;
    }
}

void OverworldState::ProcessInput(GameProcessor* game)
{ 
    if(interactPressed)
        game->ChangeState(DungeonViewState::Instance());
}

void OverworldState::Render(GameProcessor* game)
{ 
    draw_sprite(BUFFER, OVERWORLDMAP, 0, 0);    
    show_mouse(BUFFER);
    draw_sprite(screen, BUFFER, 0, 0);
}
