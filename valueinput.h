#ifdef __WAND__
target[name[valueinput.h] type[include]]
dependency[valueinput.o]
#endif

#ifndef GUI_VALUEINPUT_H
#define GUI_VALUEINPUT_H

#include "textinput.h"
#include "dialog.h"
#include <herbs/intformat/intformat.h>

namespace Gui
	{
	template<class T>
	class ValueInput:public TextInput
		{
		public:			
			static ValueInput* create(Gui& gui_obj
				,uint32_t style_0,uint32_t style_1,Window* parent
				,T& obj)
				{return new ValueInput(gui_obj,style_0,style_1,parent,obj);}

			void valueUpdate();			
			void displayUpdate();
		
		protected:
			ValueInput(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent
				,T& obj):TextInput(gui_obj,style_0,style_1,parent),ptr_obj(&obj)
				{}
	
		private:
			T* ptr_obj;
		};
		
	template<>
	void ValueInput<double>::displayUpdate();
	template<>
	void ValueInput<double>::valueUpdate();
	
	template<>
	void ValueInput<float>::displayUpdate();
	template<>
	void ValueInput<float>::valueUpdate();
	
	template<>
	void ValueInput<Herbs::String>::displayUpdate();
	template<>
	void ValueInput<Herbs::String>::valueUpdate();
	}
	
#endif
