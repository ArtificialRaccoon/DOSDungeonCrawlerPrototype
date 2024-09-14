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
	if (set_gfx_mode(GFX_VGA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0) != 0) 
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

	//There is a strange bug with my cross compiled version of
	//DJGPP or Allegro.  If the mouse rubs against the mouse
	//range for too long, it'll segfault.  This issue happens
	//even in the example code files, suggesting its the cross
	//compiled code.  This just solves the crash stupidly.
	set_mouse_range(SCREEN_WIDTH * -2, SCREEN_HEIGHT * -2, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);

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
	poll_mouse();

	//There is some sort of bug in the cross-compiled
	//version of DJGPP or Allegro which causes a crash if
	//the mouse hit against the mouse range.  This does
	//solve the issue (along with making the rage larger
	//then the screen); it's just dumb.
	bool mouse_on_screen = true;
	int newX, newY = 0;

	if (mouse_x < 0) 
	{
		newX = 0;
		mouse_on_screen = false;
	} 
	else if (mouse_x > SCREEN_WIDTH - 1) 
	{
		newX = SCREEN_WIDTH - 1;
		mouse_on_screen = false;
	} 
	else
		newX = mouse_x;

	if (mouse_y < 0) 
	{
		newY = 0;
		mouse_on_screen = false;
	} 
	else if (mouse_y > SCREEN_HEIGHT - 1) 
	{
		newY = SCREEN_HEIGHT - 1;
		mouse_on_screen = false;
	} 
	else
		newY = mouse_y;

	if (!mouse_on_screen)
		position_mouse(newX, newY);	

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
