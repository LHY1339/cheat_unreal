#include "menu_misc.h"
#include "menu_lib.h"

void menu_misc::main()
{
	menu_lib::set_font(12);

	menu_lib::pice(SDK::FVector2D(110, 10), SDK::FVector2D(menu_lib::size.X - 120, menu_lib::size.Y - 20));
}