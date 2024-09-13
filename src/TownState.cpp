#include "TownState.h"

TownState TownState::mTownState;

void TownState::InitState()
{
    BUFFER = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);

    ticks = 0;
    mouseDebounce = 0;
    	
    theme = load_midi(".\\MUSIC\\SORROW.MID");
    play_midi(theme, TRUE);    

    BGTOWN = load_bitmap(".\\OTHER\\BGTOWN.bmp", CommonGUI::Instance().GetPalette());
    BGSHOP = load_bitmap(".\\OTHER\\BGSHOP.bmp", CommonGUI::Instance().GetPalette());
    BGTAVE = load_bitmap(".\\OTHER\\BGTAVE.bmp", CommonGUI::Instance().GetPalette());
    BGTMPL = load_bitmap(".\\OTHER\\BGTMPL.bmp", CommonGUI::Instance().GetPalette());
    CHARSHOP = load_bitmap(".\\OTHER\\SPRITE2.bmp", CommonGUI::Instance().GetPalette());
    CHARTAVE = load_bitmap(".\\OTHER\\SPRITE3.bmp", CommonGUI::Instance().GetPalette());
    CHARTMPL = load_bitmap(".\\OTHER\\SPRITE4.bmp", CommonGUI::Instance().GetPalette());

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
        GUI.push_back(std::make_unique<ButtonElement>(buttonElements[i], true));
    }

    //Preselect the Inn when first showing the screen
    auto it = std::find_if(GUI.begin(), GUI.end(), [](const std::unique_ptr<GUIElement>& elem) 
    {
        return dynamic_cast<ButtonElement*>(elem.get()) != nullptr;
    });

    if (it != GUI.end()) 
    {
        ButtonElement* button = dynamic_cast<ButtonElement*>(it->get());
        if (button)
            button->setSelected(true);
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
        if(iterator->HitTest(mouse_x, mouse_y))
        {
            std::for_each(GUI.begin(), GUI.end(), [](auto &guiElement) { guiElement->setSelected(false); });
            iterator->setSelected(true);
            break;      
        }
    }

    if(mouse_b & 1 && mouseDebounce == 0)
    {
        for(auto &iterator : GUI)
        {
            if(iterator->HitTest(mouse_x, mouse_y))
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

void TownState::ProcessInput(GameProcessor* game)
{ 
    if(interactPressed)
    {
        for(auto &iterator : GUI)
        {
            if(iterator->getSelected())
            {
                switch(iterator->getAction())
                {
                    case 0:
                        break;
                    case 1:
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

void TownState::Render(GameProcessor* game)
{
    draw_sprite(BUFFER, BGTOWN, 0, 0);

    for(auto& iterator : GUI)
    {
        iterator->DrawElement(BUFFER, CommonGUI::Instance().GetBitmap(), CommonGUI::Instance().GetPalette(), CommonGUI::Instance().GetFont(), tilesetWidth, tilesetHeight);
    }

    show_mouse(BUFFER);
    draw_sprite(screen, BUFFER, 0, 0);
}

void TownState::getNextGUIElement(bool forward)
{
    auto it = std::find_if(GUI.begin(), GUI.end(), [](const std::unique_ptr<GUIElement>& elem) {
        auto button = dynamic_cast<ButtonElement*>(elem.get());
        return button && button->getSelected();
    });

    if (it != GUI.end()) 
    {
        (*it)->setSelected(false); 
        do 
        {
            if (forward)
                it = (it + 1 == GUI.end()) ? GUI.begin() : it + 1;
            else
                it = (it == GUI.begin()) ? GUI.end() - 1 : it - 1;
        } while (dynamic_cast<ButtonElement*>((*it).get()) == nullptr);

    } 
    else
        it = std::find_if(GUI.begin(), GUI.end(), [](const std::unique_ptr<GUIElement>& elem) { return dynamic_cast<ButtonElement*>(elem.get()) != nullptr; });

    if (it != GUI.end())
        (*it)->setSelected(true);
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