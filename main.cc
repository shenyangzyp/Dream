#define CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h>

#include <process.h>
#include "hge_include.h"
#include "resource_manage.h"
#include "gui_manage.h"
#include "game_manage.h"
#include "gui_mouse.h"
#include "game_logic.h"
#include "gui_textview.h"
bool FrameFunc()
{
  g_gui_manage->Control();
  if( g_game_manage->GetGameState() == GS_PLAYING) {
    g_game_logic->Walk();
  }
  if( g_game_manage->GetGameState() == GS_END)
    return true;
	return false;
}

bool RenderFunc()
{
	HGE* pHge = hgeCreate( HGE_VERSION);
	pHge->Gfx_BeginScene();
	pHge->Gfx_Clear( 0xFFFFFFFF);
  g_gui_manage->Render();
  g_gui_mouse->Render();
	pHge->Gfx_EndScene();
	return false;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  //_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	HGE* pHge = hgeCreate( HGE_VERSION);
  pHge->System_SetState( HGE_LOGFILE, "log.txt");
	pHge->System_SetState( HGE_FRAMEFUNC, FrameFunc);
	pHge->System_SetState( HGE_RENDERFUNC, RenderFunc);
	pHge->System_SetState( HGE_WINDOWED, true);
	pHge->System_SetState( HGE_TITLE, "Dream Game");
	pHge->System_SetState( HGE_SCREENWIDTH, 640);
	pHge->System_SetState( HGE_SCREENHEIGHT, 480);
	pHge->System_SetState( HGE_USESOUND, true);
	pHge->System_SetState( HGE_DONTSUSPEND, true);
	pHge->System_SetState( HGE_SHOWSPLASH, false);//unuse the logo of hge
	pHge->System_SetState( HGE_ZBUFFER, false);
	pHge->System_SetState( HGE_FPS, 30);
  g_resource_manage = new ResourceManage();
  g_gui_manage = new GUIManage();
  g_gui_manage->Init();
  g_game_manage = new GameManage(); 
  g_gui_manage->GetRoot()->SetOnDraw();
  g_game_logic = new GameLogic();

	if( pHge->System_Initiate())
	{
    g_gui_mouse = new GUIMouse();
    g_game_manage->SetBegin();
		pHge->System_Start();
	}
	pHge->Release();

  return 0;
}
