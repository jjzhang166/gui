#ifdef __WAND__
dependency[fader.o]
target[name[fader.h] type[include]]
#endif

#ifndef FADER_H
#define FADER_H

#include "window-system.h"

namespace Gui
	{
	class Fader:public WindowSystem
		{
		public:
			class Fadefunc
				{
				public:
					virtual double valueGet(uint32_t pos,uint32_t min
						,uint32_t max)=0;
						
					virtual uint32_t positionGet(double fader_val
						,uint32_t min,uint32_t max)=0;
				};
		
			static void init();
			
			double valueGet() const;
			
			void valueSet(double v);
			
			static Fader* create(Gui& gui_obj
				,uint32_t style_0,uint32_t style_1,Window* parent
				,Fadefunc& f)
				{return new Fader(gui_obj,style_0,style_1,parent,f);}
			
			virtual size_t onEvent(uint32_t event_type,size_t param_0,size_t param_1);
			
			void minSet(uint32_t x);
			void maxSet(uint32_t x);
		
		protected:
			Fader(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent
				,Fadefunc& f);
		private:
			Fadefunc& m_f;
			void* font_sys_current;
			float font_height;
			float font_width;
		};
	};
	
#endif
