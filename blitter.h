#ifdef __WAND__
dependency[blitter.o]
target[name[blitter.h] type[include]]
#endif

#ifndef BLITTER_H
#define BLITTER_H

#include "window-custom.h"
#include <vector/matrixstorage.h>
#include <herbs/mutexblocklw/mutexblocklw.h>

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
				
			size_t virtual onEvent(uint32_t event_type,size_t param_0,size_t param_1);
				
			static Blitter* create(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent)
				{return new Blitter(gui_obj,style_0,style_1,parent);}
			
			void pixelsSet(const Vector::MatrixStorage<PixelBGRA<float> >& bitmap);
			void pixelsSet(const Vector::MatrixStorage<float>& graymap);
			
		protected:
			Blitter(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent);
			~Blitter();
		
		private:
			Vector::MatrixStorage<PixelBGRA<uint8_t> > image_in;
			Vector::MatrixStorage<PixelBGRA<uint8_t> > image_out;
			void* dc_out;
			Herbs::MutexBlockLW resize_block;
			void bitmapCopy();
		};
	}
	
#endif
