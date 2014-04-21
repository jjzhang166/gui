#ifdef __WAND__
target[name[font.h] type[include]]
dependency[font.o]
#endif

#ifndef GUI_FONT_H
#define GUI_FONT_H

#include <cstdint>
#include <algorithm>

namespace Gui
	{
	class Font
		{
		friend class WindowSystem;

		public:
			enum class Element:uint32_t 
				{
				 CAPTION
				,CAPTION_SMALL
				,MESSAGE
				,ICON
				,WIDGET
				,TOOLTIP
				};
	
			static Font fromThemeGet(Element e);
			
			Font(const Font&)=delete;
			void operator=(const Font&)=delete;
			
			Font(Font&& font):handle(font.handle)
				{font.handle=nullptr;}
			
			Font& operator=(Font&& obj)
				{
				std::swap(obj.handle,handle);
				return *this;
				}
			
			~Font();
	
		private:
			Font(void* h);
			void* handle;
		};
	}

#endif
