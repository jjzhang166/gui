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
		friend class Window;

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
	
			Font(Element e)
				{fromElement(e,1.0f);}
				
			Font(Element e,float scale_factor)
				{fromElement(e,scale_factor);}
			
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
			void fromElement(Element e,float scale_factor);
			
			void* handle;
		};
	}

#endif
