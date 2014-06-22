#ifdef __WAND__
target[name[button_push.o] type[object]]
#endif

#include "button_push.h"
#include <windows.h>

Gui::ButtonPush::ButtonPush(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent)
	:Button(gui_obj,style_0,style_1|BS_PUSHLIKE|BS_CHECKBOX,parent)
	{}

bool Gui::ButtonPush::checked() const
	{return SendMessage((HWND)handle,BM_GETCHECK,0,0)==BST_CHECKED;}

void Gui::ButtonPush::check(bool state)
	{
	SendMessage((HWND)handle,BM_SETCHECK,state?BST_CHECKED:BST_UNCHECKED,0);
	}
	
void Gui::ButtonPush::checkNoBlock(bool state)
	{
	PostMessage((HWND)handle,BM_SETCHECK,state?BST_CHECKED:BST_UNCHECKED,0);
	}