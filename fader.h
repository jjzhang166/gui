#ifdef __WAND__
dependency[fader.o]
target[name[fader.h] type[include]]
#endif

#ifndef GUI_FADER_H
#define GUI_FADER_H

#include "window-system.h"

namespace Gui
	{
	class Fader:public WindowSystem
		{
		public:
			typedef uint32_t pos_t;
			static void init();
			void nDivsSet(pos_t n_divs);
			
			double valueGet() const;
			void valueSet(double v);
			
			virtual size_t onEvent(uint32_t event_type,size_t param_0,size_t param_1);
			virtual double positionSet(pos_t pos,pos_t n_divs) const=0;
			virtual pos_t positionGet(double pos_new,pos_t n_divs) const=0;
			
			
		
		protected:
			Fader(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent);

		private:
			void* font_sys_current;
			float font_height;
			float font_width;
			

			
		};
	};
	
#endif
