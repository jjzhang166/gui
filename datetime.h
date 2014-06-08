#ifdef __WAND__
dependency[datetime.o]
target[name[datetime.h] type[include]]
#endif

#ifndef GUI_DATETIME_H
#define GUI_DATETIME_H

#include "window-system.h"
#include <herbs/timet/timet.h>

namespace Gui
	{
	class Datetime:public WindowSystem
		{
		public:
			static void init();
			
			static Datetime* create(Gui& gui_obj
				,uint32_t style_0,uint32_t style_1,Window* parent)
				{return new Datetime(gui_obj,style_0,style_1,parent);}
				
			virtual size_t onEvent(uint32_t event_type,size_t param_0,size_t param_1);
			
			Herbs::String titleGet() const;
			
			void timeSet(Herbs::Timestamp time);
			Herbs::Timestamp timeGet() const;
			
			void sizeMinimize();
		
		protected:
			Datetime(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent);

		private:
			Vector::Vector2d<int> size_min;
		};
	};
	
#endif
