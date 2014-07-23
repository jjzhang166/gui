#ifdef __WAND__
dependency[glviewport.o]
target[name[glviewport.h] type[include]]
#endif

#ifndef GLVIEWPORT_H
#define GLVIEWPORT_H

#include "window-custom.h"
#include <herbs/mutexblocklw/mutexblocklw.h>

namespace Gui
	{
	class Gui;
	
	class GlViewport:public WindowCustom
		{
		public:
			size_t virtual onEvent(uint32_t event_type,size_t param_0,size_t param_1);
			
			void contextGrab();
			void contextRelease();
			void buffersSwap();

			class GlBlock
				{
				public:
					GlBlock(GlViewport& viewport):m_viewport(viewport)
						{m_viewport.contextGrab();}
					
					~GlBlock()
						{m_viewport.contextRelease();}
				private:
					GlViewport& m_viewport;
				};
			
			virtual void onRender()=0;
			virtual void onResize(int width,int height)=0;
		
		protected:
			GlViewport(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent);
			~GlViewport();
		
		private:
			Herbs::MutexBlockLW render_mutex;
			
			void* dc_out;
			void* rc;
			void bitmapCopy();
		};
	}
	
#endif
