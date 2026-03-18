#include "menu_visual.h"
#include "menu_lib.h"

void menu_visual::main()
{
	menu_lib::set_font(12);

	menu_lib::pice(SDK::FVector2D(110, 10), SDK::FVector2D(menu_lib::size.X - 120, menu_lib::size.Y - 20));

	if (menu_lib::button_color("button_color", SDK::FVector2D(120, 20.0f), SDK::FVector2D(100.0f, 30.0f)))
	{
		printf("gui::button_color click\n");
	}

	if (menu_lib::button_color_text("button_text", SDK::FVector2D(120, 60.0f), SDK::FVector2D(100.0f, 30.0f), L"按钮"))
	{
		printf("gui::button_color_text click\n");
	}

	static bool example_cb = false;
	menu_lib::check_box("check_box", SDK::FVector2D(120, 100.0f), SDK::FVector2D(30.0f, 30.0f), SDK::FVector2D(20.0f, 20.0f), &example_cb);

	const std::wstring cb_str = L"测试选择框：" + std::wstring(example_cb ? L"true" : L"false");
	menu_lib::text(SDK::FVector2D(120, 140.0f), cb_str.c_str());

	static float example_db = 400;
	menu_lib::drag_bar("drag_bar", SDK::FVector2D(120, 180.0f), SDK::FVector2D(200.0f, 30.0f), SDK::FVector2D(10.0f, 30.0f), &example_db, 200, 600);

	const std::wstring db_str = L"测试进度条：" + std::format(L"{:.2f}", example_db);
	menu_lib::text(SDK::FVector2D(120, 220.0f), db_str.c_str());
}