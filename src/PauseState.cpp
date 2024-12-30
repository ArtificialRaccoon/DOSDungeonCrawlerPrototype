#include "PauseState.h"

PauseState PauseState::mPauseState;

void PauseState::InitState()
{
    BUFFER = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    clear_to_color(BUFFER, makecol(16, 16, 16));

    ticks = 0;
    mouseDebounce = 0;

    std::ifstream ifs(".\\OTHER\\PAUSMENU.jsn");
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    json::jobject guiJson = json::jobject::parse(content);

    tilesetWidth = guiJson["tilesetWidth"];
    tilesetHeight = guiJson["tilesetHeight"];

    std::vector<json::jobject> panelElements = guiJson["panelElements"];
    for(int i = 0; i < panelElements.size(); i++)
    {
        GUI.push_back(std::make_unique<PanelElement>(panelElements[i], tilesetWidth, tilesetHeight));
    }

    std::vector<json::jobject> buttonElements = guiJson["buttonElements"];
    for(int i = 0; i < buttonElements.size(); i++)
    {        
        GUI.push_back(std::make_unique<ButtonElement>(buttonElements[i], tilesetWidth, tilesetHeight, true));
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

void PauseState::Pause()
{

}

void PauseState::Resume()
{

}

void PauseState::AquireInput(GameProcessor* game)
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
                game->PopState();
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

void PauseState::ProcessInput(GameProcessor* game)
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
                        exit(0);
                        break;
                    default:
                        break;
                } 
            }
        }        
    }
}

void PauseState::Render(GameProcessor* game)
{
    for(auto& iterator : GUI)
    {
        iterator->DrawElement(BUFFER, CommonGUI::Instance().GetBitmap(), CommonGUI::Instance().GetPalette(), CommonGUI::Instance().GetFont());
    }

    show_mouse(BUFFER);
    draw_sprite(screen, BUFFER, 0, 0);
}

void PauseState::getNextGUIElement(bool forward)
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

void PauseState::UnloadResources()
{
    destroy_bitmap(BUFFER);
    GUI.clear();
}