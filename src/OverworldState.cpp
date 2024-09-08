#include "OverworldState.h"
#include "TownState.h"

OverworldState OverworldState::mOverworldState;

void OverworldState::InitState()
{
    BUFFER = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    OVERWORLDMAP = load_bitmap(".\\OTHER\\WRLDMAP.bmp", palette);
    MAPUI = load_bitmap(".\\OTHER\\MAPUI.bmp", palette);
    mapFont = load_font(".\\OTHER\\BitScrip.bmp", palette, NULL);

    ticks = 0;
    mouseDebounce = 0;
    	
	theme = load_midi(".\\MUSIC\\TROUBLE.MID");
	play_midi(theme, TRUE);    

    std::ifstream ifs(".\\OTHER\\WRLDMAP.jsn");
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    json::jobject guiJson = json::jobject::parse(content);
    tilesetWidth = guiJson["tilesetWidth"];
    tilesetHeight = guiJson["tilesetHeight"];

    std::vector<json::jobject> guiElements = guiJson["guiElements"];
    for(int i = 0; i < guiElements.size(); i++)
    {
        GUIElement newElement(guiElements[i]);
        GUI.push_back(newElement);
    }
}

void OverworldState::Pause()
{

}

void OverworldState::Resume()
{

}

void OverworldState::AquireInput(GameProcessor* game)
{
    interactPressed = false;
    if(keypressed())
    {
        switch(readkey() >> 8)
        {        
            case KEY_W:
            case KEY_UP:
                getNextGUIElement(false);
                break;
            case KEY_S:
            case KEY_DOWN:
                getNextGUIElement(true);
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
        if(iterator.HitTest(mouse_x, mouse_y))
        {
            std::for_each(GUI.begin(), GUI.end(), [](auto &guiElement) { guiElement.setSelected(false); });
            iterator.setSelected(true);
            break;      
        }
    }

    if(mouse_b & 1 && mouseDebounce == 0)
    {
        for(auto &iterator : GUI)
        {
            if(iterator.HitTest(mouse_x, mouse_y))
            {
                interactPressed = true;
                break;      
            }
        }

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
    {
        for(auto &iterator : GUI)
        {
            if(iterator.getSelected())
            {
                switch(iterator.getAction())
                {
                    case 0:
                        break;
                    case 1:
                        game->ChangeState(TownState::Instance());
                        break;
                    case 2:
                        break;
                    case 3:
                        game->ChangeState(DungeonViewState::Instance());
                        break;
                    default:
                        break;
                }                
            }
        }        
    }
}

void OverworldState::Render(GameProcessor* game)
{
    draw_sprite(BUFFER, OVERWORLDMAP, 0, 0);   
    for(auto iterator : GUI)
    {
        if(iterator.getSelected())
        {
            iterator.DrawElement(BUFFER, MAPUI, palette, mapFont, tilesetWidth, tilesetHeight, false);        
            textout_centre_ex(BUFFER, mapFont, iterator.getTextOverlay().c_str(), 234, 18, makecol(255, 255, 255), -1);
        }
    }
    show_mouse(BUFFER);
    draw_sprite(screen, BUFFER, 0, 0);
}


void OverworldState::getNextGUIElement(bool forward)
{    
    auto it = std::find_if(GUI.begin(), GUI.end(), [](GUIElement& elem) { return elem.getSelected(); });
    if (it != GUI.end()) 
    {
        it->setSelected(false);
        if (forward)
            it = (it + 1 == GUI.end()) ? GUI.begin() : it + 1;
        else
            it = (it == GUI.begin()) ? GUI.end() - 1 : it - 1;
    } 
    else
        it = GUI.begin();
    it->setSelected(true);
}

void OverworldState::UnloadResources()
{
    destroy_bitmap(BUFFER);
    destroy_bitmap(OVERWORLDMAP);
    destroy_bitmap(MAPUI);
    destroy_font(mapFont);
	destroy_midi(theme);
    GUI.clear();
}