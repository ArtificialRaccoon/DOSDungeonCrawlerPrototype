#include "BaseState.h"
#include "GameProcessor.h"
#include "GameUIDefines.h"
#include "Item.h"

void GameProcessor::InitializeGame() 
{
	if (allegro_init() != 0)
		exit(0);

	install_keyboard();
	install_mouse();

	set_color_depth(8);
	if (set_gfx_mode(GFX_MODEX, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0) != 0) 
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
		exit(0);
	}

	PALETTE palette;
	BITMAP *cursor = load_bitmap(".\\OTHER\\CURSOR.bmp", palette);
	set_mouse_sprite(cursor);
	set_mouse_sprite_focus(0, 0);

	//Load the default font
	font = load_bitmap_font(".\\OTHER\\BitScrip.bmp", palette, nullptr);

	reserve_voices (32, -1);    
    if (install_sound (DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) < 0)
	{
		printf ("Error initializing sound card");
		exit(0);
	}	

	//Read in the items available in game
	std::vector<Item> items = Item::readItemData(".\\OTHER\\ITEMS.jsn");
}

void GameProcessor::HandleEvents() { states.back()->ProcessInput(this); }

void GameProcessor::ProcessEvents() 
{
	show_mouse(NULL);
	states.back()->AquireInput(this);
}

void GameProcessor::Render() { states.back()->Render(this); }

void GameProcessor::DeallocateResources() {}

void GameProcessor::ChangeState(BaseState *state) 
{
	// cleanup the current state
	if (!states.empty()) 
	{
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->InitState();
}

void GameProcessor::PushState(BaseState *state) 
{
	// pause current state
	if (!states.empty())
		states.back()->Pause();

	// store and init the new state
	states.push_back(state);
	states.back()->InitState();
}

void GameProcessor::PopState() 
{
	// cleanup the current state
	if (!states.empty()) 
		states.pop_back();

	// resume previous state
	if (!states.empty())
		states.back()->Resume();
}
