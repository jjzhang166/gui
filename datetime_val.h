#ifdef __WAND__
target[name[datetime_val.h] type[include]]
#endif

#ifndef GUI_DATETIMEVAL_H
#define GUI_DATETIMEVAL_H

#include "datetime.h"

namespace Gui
	{
	class DatetimeVal:public Datetime
		{
		public:
			static void init();
			
			static DatetimeVal* create(Gui& gui_obj
				,uint32_t style_0,uint32_t style_1,Window* parent
				,Herbs::Timestamp& val)
				{return new DatetimeVal(gui_obj,style_0,style_1,parent,val);}
		
			void valueUpdate()
				{m_val=Datetime::timeGet();}
				
			void displayUpdate()
				{Datetime::timeSet(m_val);}
		
		protected:
			DatetimeVal(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent
				,Herbs::Timestamp& val):
				Datetime(gui_obj,style_0,style_1,parent),m_val(val)
				{}

		private:
			Herbs::Timestamp& m_val;
		};
	};
	
#endif
