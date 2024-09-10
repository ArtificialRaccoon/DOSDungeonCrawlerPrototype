#include "TownState.h"

TownState TownState::mTownState;

void TownState::InitState()
{
    BUFFER = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);

    ticks = 0;
    mouseDebounce = 0;
    	
    theme = load_midi(".\\MUSIC\\SORROW.MID");
    play_midi(theme, TRUE);    

    UI = load_bitmap(".\\OTHER\\MAINGUI.bmp", palette);
    BGTOWN = load_bitmap(".\\OTHER\\BGTOWN.bmp", palette);
    BGSHOP = load_bitmap(".\\OTHER\\BGSHOP.bmp", palette);
    BGTAVE = load_bitmap(".\\OTHER\\BGTAVE.bmp", palette);
    BGTMPL = load_bitmap(".\\OTHER\\BGTMPL.bmp", palette);
    CHARSHOP = load_bitmap(".\\OTHER\\SPRITE2.bmp", palette);
    CHARTAVE = load_bitmap(".\\OTHER\\SPRITE3.bmp", palette);
    CHARTMPL = load_bitmap(".\\OTHER\\SPRITE4.bmp", palette);
    mapFont = load_font(".\\OTHER\\BitScrip.bmp", palette, NULL);

    std::ifstream ifs(".\\OTHER\\TOWNMENU.jsn");
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    json::jobject guiJson = json::jobject::parse(content);

    tilesetWidth = guiJson["tilesetWidth"];
    tilesetHeight = guiJson["tilesetHeight"];

    std::vector<json::jobject> panelElements = guiJson["panelElements"];
    for(int i = 0; i < panelElements.size(); i++)
    {
        GUI.push_back(std::make_unique<PanelElement>(panelElements[i]));
    }
    
    std::vector<json::jobject> buttonElements = guiJson["buttonElements"];
    for(int i = 0; i < buttonElements.size(); i++)
    {
        GUI.push_back(std::make_unique<ButtonElement>(buttonElements[i]));
    }
}

void TownState::Pause()
{

}

void TownState::Resume()
{

}

void TownState::AquireInput(GameProcessor* game)
{
    if(keypressed())
    {
        switch(readkey() >> 8)
        {        
            case KEY_W:
            case KEY_UP:
                break;
            case KEY_S:
            case KEY_DOWN:
                break;            
            case KEY_ENTER:
                interactPressed = true;
                break;
            case KEY_ESC:
                exit(0);
                break;
        }
    }

    for(auto &iterator : GUI)
    {
        if(iterator->HitTest(mouse_x, mouse_y))
        {
            std::for_each(GUI.begin(), GUI.end(), [](auto &guiElement) { guiElement->setSelected(false); });
            iterator->setSelected(true);
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

void TownState::ProcessInput(GameProcessor* game)
{ 
    if(interactPressed)
        game->ChangeState(DungeonViewState::Instance());
}

void TownState::Render(GameProcessor* game)
{
    draw_sprite(BUFFER, BGTOWN, 0, 0);

    for(auto& iterator : GUI)
    {
        iterator->DrawElement(BUFFER, UI, palette, mapFont, tilesetWidth, tilesetHeight, true);
    }

    show_mouse(BUFFER);
    draw_sprite(screen, BUFFER, 0, 0);
}

void TownState::UnloadResources()
{
    destroy_bitmap(BUFFER);
    destroy_bitmap(BGTOWN);
    destroy_bitmap(BGSHOP);
    destroy_bitmap(BGTAVE);
    destroy_bitmap(BGTMPL);
    destroy_bitmap(CHARSHOP);
    destroy_bitmap(CHARTAVE);
    destroy_bitmap(CHARTMPL);
    destroy_midi(theme);
    GUI.clear();
}