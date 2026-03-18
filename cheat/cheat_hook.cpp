#include "cheat_hook.h"
#include "sdk/SDK/Engine_classes.hpp"
#include "gvalue.h"
#include "gdefine.h"
#include "kismet.h"
#include "cheat.h"
#include "input.h"

#include <Windows.h>

void hk_post_render(void* thisptr, SDK::UCanvas* canvas)
{
    gvalue::def_post_render(thisptr, canvas);
    __try
    {
        gvalue::world = SDK::UWorld::GetWorld();
        gvalue::canvas = canvas;
        gvalue::engine = SDK::UEngine::GetEngine();
        gvalue::controller = SDK::UGameplayStatics::GetPlayerController(gvalue::world, 0);
        gvalue::delta_time = SDK::UGameplayStatics::GetWorldDeltaSeconds(gvalue::world);

        cheat::get()->module_main();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        printf("hk_post_render error : %d\n", GetExceptionCode());
    }

    if (gvalue::is_exit)
    {
        SetWindowLongPtrA(kismet::get_window(), GWLP_WNDPROC, (LONG_PTR)gvalue::def_wnd_proc);
        gvalue::viewport_client_vtb[POST_RENDER_INDEX] = gvalue::def_post_render;
        gvalue::is_clean = true;
    }
}

LRESULT CALLBACK hk_wnd_proc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param)
{
    const bool success = input::get()->main(hwnd, u_msg, w_param, l_param);
    if (!success)
    {
        return TRUE;
    }
    return CallWindowProcA(gvalue::def_wnd_proc, hwnd, u_msg, w_param, l_param);
}

void cheat_hook::main()
{
    do
    {
        gvalue::world = SDK::UWorld::GetWorld();
        Sleep(100);
    } 
    while (!gvalue::world);

    gvalue::viewport_client_vtb = *(void***)gvalue::world->OwningGameInstance->LocalPlayers[0]->ViewportClient;
    DWORD protect = 0;
    VirtualProtect(&gvalue::viewport_client_vtb[POST_RENDER_INDEX], 8, PAGE_EXECUTE_READWRITE, &protect);

    gvalue::def_post_render = (fn_post_render)(gvalue::viewport_client_vtb[POST_RENDER_INDEX]);
    gvalue::viewport_client_vtb[POST_RENDER_INDEX] = &hk_post_render;

    gvalue::def_wnd_proc = (WNDPROC)SetWindowLongPtrA(kismet::get_window(), GWLP_WNDPROC, (LONG_PTR)hk_wnd_proc);
}