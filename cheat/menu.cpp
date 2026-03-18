#include "menu.h"
#include "menu_lib.h"
#include "gui.h"
#include "render.h"
#include "gvalue.h"
#include "gdefine.h"
#include "color.h"
#include "menu_visual.h"
#include "menu_player.h"
#include "menu_level.h"
#include "menu_misc.h"

enum class menu_page
{
	visual,
	player,
	level,
	misc,
};

menu_page page = menu_page::visual;
float current_y = 10.0f;

menu* menu::get()
{
	static menu inst;
	return &inst;
}

void menu::main()
{
	if (gvalue::menu_open)
	{
		background();
		basic();
		left();
		tip();
		cursor();
	}
	lable();
}

void menu::background()
{
	gui::drag(
		menu_lib::pos,
		menu_lib::size,
		menu_lib::drag_pos,
		menu_lib::is_drag
	);

	render::fill_box(
		SDK::FVector2D(menu_lib::pos.X - 2, menu_lib::pos.Y - 2),
		SDK::FVector2D(menu_lib::size.X + 4, menu_lib::size.Y + 4),
		color::get()->outline_col
	);

	render::fill_box(
		SDK::FVector2D(menu_lib::pos.X, menu_lib::pos.Y),
		SDK::FVector2D(menu_lib::size.X, menu_lib::size.Y),
		color::get()->back_col
	);
}

void menu::basic()
{
	switch (page)
	{
	case menu_page::visual:
		menu_visual::main();
		break;
	case menu_page::player:
		menu_player::main();
		break;
	case menu_page::level:
		menu_level::main();
		break;
	case menu_page::misc:
		menu_misc::main();
		break;
	}
}

void menu::left()
{
	menu_lib::set_font(12);

	menu_lib::pice(SDK::FVector2D(0, 0), SDK::FVector2D(100, menu_lib::size.Y));

	const float target_y = 10 + (int)page * 40;
	current_y = current_y + (target_y - current_y) * 15 * gvalue::delta_time;
	render::fill_box(menu_lib::attach(10, current_y), SDK::FVector2D(80, 30), color::get()->normal_col);

#define BUTTON(_page_,_name_,_ypos_) \
if (menu_lib::button_text(#_page_, SDK::FVector2D(10, _ypos_), SDK::FVector2D(80, 30), L#_name_)) \
{ \
	page = menu_page::_page_; \
}

	BUTTON(visual, 视觉, 10);
	BUTTON(player, 玩家, 50);
	BUTTON(level, 关卡, 90);
	BUTTON(misc, 杂项, 130);

#undef BUTTON

	if (menu_lib::button_text("", SDK::FVector2D(10, menu_lib::size.Y - 40), SDK::FVector2D(80, 30), L"LHY1339 "))
	{
		system("start https://ifdian.net/a/lhy1339");
	}
}

void menu::tip()
{
	menu_lib::set_font(12);

	auto one_tip = [&](const int& y_pos, const int& x_size, const UC::FString& str)
		{
			render::fill_box(
				SDK::FVector2D(menu_lib::pos.X - 2, menu_lib::pos.Y + menu_lib::size.Y + y_pos - 2), 
				SDK::FVector2D(x_size + 4, 39),
				SDK::FLinearColor(0.4f, 0.1f, 0.0f, 1.0f)
			);

			render::fill_box(
				SDK::FVector2D(menu_lib::pos.X, menu_lib::pos.Y + menu_lib::size.Y + y_pos),
				SDK::FVector2D(x_size, 35),
				SDK::FLinearColor(0.1f, 0.06f, 0.0f, 1.0f)
			);

			menu_lib::text(SDK::FVector2D(10, menu_lib::size.Y + y_pos + 8), str);
		};

	one_tip(10, menu_lib::size.X, L"本修改器永久免费开源，问题反馈QQ群：1071845133");
	if (gvalue::version != "" && gvalue::version != CHEAT_VERSION)
	{
		one_tip(55, 160, L"有新版本可以下载");
	}
}

void menu::cursor()
{
	render::fill_box(
		SDK::FVector2D(gvalue::mouse.x - 2, gvalue::mouse.y - 2),
		SDK::FVector2D(4, 4),
		color::get()->cursor_col
	);
}

void menu::lable()
{
	render::draw_text(
		gvalue::engine->TinyFont,
		L"按下 Ins（Insert）显示/隐藏菜单\n按下 Del（Delete）退出",
		SDK::FVector2D(10.0f, 10.0f),
		SDK::FVector2D(1.0f, 1.0f),
		SDK::FLinearColor(1, 1, 1, 1),
		1.0f,
		SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f),
		SDK::FVector2D(0.0f, 0.0f),
		false,
		false,
		false,
		SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)
	);
}