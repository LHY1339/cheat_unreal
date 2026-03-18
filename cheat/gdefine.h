#pragma once

#define CHEAT_DEBUG
#define UE_4_27

#define WINDOW_CLASS_NAME L"UnrealWindow"
#define WINDOW_NAME L"FPSSteamGame  "

#define CHEAT_VERSION "26.3.25"
#define CHEAT_HEART "fps"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 1314

#define SAVE_PATH "C:\LHY1339\fps_steam_game\config.cheat"

#ifdef UE_4_27
#define POST_RENDER_INDEX 0x63
#endif
#ifdef UE_5_3
#define POST_RENDER_INDEX 0x70
#endif
#ifdef UE_5_5
#define POST_RENDER_INDEX 0x72
#endif
#ifdef UE_5_6
#define POST_RENDER_INDEX 0x6F
#endif
#ifdef UE_5_7
#define POST_RENDER_INDEX 0x6F
#endif