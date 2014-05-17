#ifdef __WAND__

dependency[
	test.o
]
target[
	name[
		test.h
	]
	type[
		include
	]
]
#endif

#ifndef guard_test_H
#define guard_test_H

#include "gui.h"

namespace Gui
	{
	class WindowCustom;
	
	class Test:public Gui
		{
		public:			
			Test(Herbs::LogWriter& logwriter,Herbs::Directory&& dir);
			
			/**Lets the object commit suicide.
			*/
			void destroy();
			
			/**Frees all resources.
			*/
			~Test();

		private:
			WindowCustom* mainwin;
		};
	}

#endif
