#ifdef __WAND__
target[name[fader_impl.h] type[include]]
#endif

#ifndef GUI_FADERIMPL_H
#define GUI_FADERIMPL_H

#include "fader.h"
#include <mathext/valuemap.h>

namespace Gui
	{
	template<class T>
	class FaderImpl:public Fader
		{
		public:
			static FaderImpl* create(Gui& gui_obj
				,uint32_t style_0,uint32_t style_1,Window* parent
				,MathExt::ValueMap<T>& val_map)
				{
				FaderImpl* ret=new FaderImpl(gui_obj,style_0,style_1,parent,val_map);
				ret->nDivsSet(64);
				ret->valueSet(0);
				return ret;
				}
			
			virtual double positionSet(Fader::pos_t pos,Fader::pos_t n_divs) const
				{
				double pos_norm=double(pos)/n_divs;
				return m_val_map.forward( pos_norm*m_domain.m_higher 
					+ (1-pos_norm)*m_domain.m_lower );
				}
				
			virtual Fader::pos_t positionGet(double pos_new,Fader::pos_t n_divs) const
				{
				double pos_norm=(pos_new - m_range.m_lower)/
					(m_range.m_higher - m_range.m_lower);
				return n_divs*m_val_map.backward(pos_norm) + 0.5;
				}
			
		protected:
			FaderImpl(Gui& gui_obj,uint32_t style_0,uint32_t style_1
				,Window* parent,MathExt::ValueMap<T>& val_map):
				Fader(gui_obj,style_0,style_1,parent)
				,m_val_map(val_map)
				,m_domain(val_map.domain())
				,m_range(val_map.range())
				{}
			
		private:
			MathExt::ValueMap<T>& m_val_map;
			MathExt::Interval<T> m_domain;
			MathExt::Interval<T> m_range;
		};
	}

#endif
