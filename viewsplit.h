#ifdef __WAND__
dependency[viewsplit.o]
target[name[viewsplit.h] type[include]]
#endif

#ifndef VIEWSPLIT_H
#define VIEWSPLIT_H

#include "window-custom.h"

namespace Gui
	{
	class Gui;
	
	class ViewSplit:public WindowCustom
		{
		public:
			virtual size_t onEvent(uint32_t event_type,size_t param_0,size_t param_1);
			void firstSet(Window& window)
				{first=&window;}
			
			void secondSet(Window& window)
				{second=&window;}
				
			static ViewSplit* create(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent)
				{return new ViewSplit(gui_obj,style_0,style_1,parent);}
	
		protected:
			ViewSplit(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent):
				WindowCustom(gui_obj,style_0,style_1,parent)
				,first(nullptr),second(nullptr)
				{}
		
		private:
			Window* first;
			Window* second;
		};
	}
	
#endif
