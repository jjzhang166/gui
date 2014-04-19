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
					virtual double y(double x)=0;
					virtual double x(double y)=0;
				};
		
			static void init();
			
			double valueGet() const;
			
			void valueSet(double v);
			
			static Fader* create(Gui& gui_obj
				,uint32_t style_0,uint32_t style_1,Window* parent
				,Fadefunc& f)
				{return new Fader(gui_obj,style_0,style_1,parent,f);}
			
			virtual size_t onEvent(uint32_t event_type,size_t param_0,size_t param_1);
		
		protected:
			Fader(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent
				,Fadefunc& f);
		private:
			Fadefunc& m_f;
		};
	};
	
#endif
