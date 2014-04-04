#ifdef __WAND__
dependency[blitter.o]
target[name[blitter.h] type[include]]
#endif

#ifndef BLITTER_H
#define BLITTER_H

#include "window-custom.h"
#include <vector/matrixstorage.h>

namespace Gui
	{
	class Gui;
	
	class Blitter:public WindowCustom
		{
		public:
			template<class T>
			struct PixelBGRA
				{
				T blue;
				T green;
				T red;
				T alpha;
				};
				
			size_t onEvent(uint32_t event_type,size_t param_0,size_t param_1);
				
			static Blitter* create(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent)
				{return new Blitter(gui_obj,style_0,style_1,parent);}
			
			void pixelsSet(const Vector::MatrixStorage<PixelBGRA<float> >& bitmap);
			
		protected:
			Blitter(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent);
			~Blitter();
		
		private:
			const Vector::MatrixStorage<PixelBGRA<float> >* image_in;
			Vector::MatrixStorage<PixelBGRA<uint8_t> > image_out;
			void bitmapCopy();
			void* dc_out;
			void* thread_lock;
		};
	}
	
#endif
