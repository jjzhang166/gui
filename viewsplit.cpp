#ifdef __WAND__
target[name[viewsplit.o] type[object]]
#endif

#include "viewsplit.h"

#include <cstdio>

size_t Gui::ViewSplit::onEvent(uint32_t event_type,size_t param_0,size_t param_1)
	{
	switch(event_type)
		{
		case MessageSize:
			{
			auto size_this=sizeClientFromParam1(param_1);
			Vector::Vector2d<int> size_first={0,0};
			if(first!=nullptr)
				{
				size_first=first->sizeWindowGet();
				size_first.x=size_this.x;
				first->sizeAbsolute(size_first.x,size_first.y);
				first->moveRelative(Vector::Vector2d<float>(-1,-1),Vector::Vector2d<float>(0,0));
				}
				
			if(second!=nullptr)
				{
				auto size_second=second->sizeWindowGet();
				size_second.x=size_this.x;
				size_second.y=size_this.y - size_first.y;
				second->sizeAbsolute(size_second.x,size_second.y);
				second->moveAbsolute(Vector::Vector2d<float>(-1,-1)
					,Vector::Vector2d<float>(0,size_first.y));
				}
			
			}
			break;
		}
	return WindowCustom::onEvent(event_type,param_0,param_1);
	}
