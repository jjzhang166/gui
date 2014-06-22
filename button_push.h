#ifdef __WAND__
dependency[button_push.o]
target[name[button_push.h] type[include]]
#endif

#ifndef GUI_BUTTONPUSH_H
#define GUI_BUTTONPUSH_H

#include "button.h"

namespace Gui
	{
	class ButtonPush:public Button
		{
		public:
			static ButtonPush* create(Gui& gui_obj
				,uint32_t style_0,uint32_t style_1,Window* parent)
				{return new ButtonPush(gui_obj,style_0,style_1,parent);}
				
			bool checked() const;
			void check(bool state);
			void checkNoBlock(bool state);
		
		protected:
			ButtonPush(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent);
		};
	};
	
#endif
