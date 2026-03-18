#include "cheat.h"
#include "cheat_init.h"
#include "cheat_hook.h"
#include "cheat_exit.h"
#include "gui.h"
#include "menu.h"
#include "network.h"
#include "save.h"
#include "gdefine.h"

#include <Windows.h>

cheat* cheat::get()
{
	static cheat inst;
	return &inst;
}

void cheat::main()
{
	cheat_init::main();
	cheat_hook::main();
	cheat_exit::main();
}

void cheat::module_init()
{
	network::get()->init();
	init_save();
}

void cheat::module_main()
{
	gui::main();
	menu::get()->main();
	network::get()->main();
}

void cheat::init_save()
{
	save::get()->load_mem(SAVE_PATH);
}
