#ifdef __WAND__

dependency[
	gui.o
]
target[
	name[
		gui.h
	]
	type[
		include
	]
]
#endif

#ifndef guard_Gui_H
#define guard_Gui_H

#include <herbs/application/application.h>
#include <cstddef>

namespace Gui
	{
	/**Base class for a graphical application.
	*/
	class Gui:public Herbs::Application
		{
		friend class Window;
		public:
			Gui(Herbs::LogWriter& writer):
				Herbs::Application(writer),window_count(0),dialog_active(nullptr)
				{}
			
			/**Runs the message loop as long as there are Window objects 
			* associated with current thread.
			*/
			int run();
			
			/**Lets the object commit suicide.
			*/
			void destroy();
			
			/**Frees all resources.
			*/
			~Gui();
			
		private:
			size_t window_count;
			
			void windowCountInc()
				{++window_count;}
				
			void windowCountDec()
				{--window_count;}
			
			void* dialog_active;
		};
	}

#endif
