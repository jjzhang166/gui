#ifdef __WAND__
target[name[valueinput.o] type[object]]
#endif

#include "valueinput.h"
#include <herbs/intformat/intformat.h>
#include <herbs/floatformat/floatformat.h>

namespace Gui
	{
	template<class T>
	void ValueInput<T>::valueUpdate()
		{*ptr_obj=Herbs::toInt<T>(titleGet().begin());}
		
	template<class T>
	void ValueInput<T>::displayUpdate()
		{titleSet(Herbs::IntFormat<T>(*ptr_obj) );}
		
	template void ValueInput<int32_t>::valueUpdate();
	template void ValueInput<uint32_t>::valueUpdate();
	template void ValueInput<int64_t>::valueUpdate();
	template void ValueInput<uint64_t>::valueUpdate();
	
	template void ValueInput<int32_t>::displayUpdate();
	template void ValueInput<uint32_t>::displayUpdate();
	template void ValueInput<int64_t>::displayUpdate();
	template void ValueInput<uint64_t>::displayUpdate();
	
	
	template<>
	void ValueInput<double>::displayUpdate()	
		{titleSet(Herbs::FloatFormat<15>(*ptr_obj));}
		
	template<>
	void ValueInput<double>::valueUpdate()	
		{*ptr_obj=Herbs::toDouble(titleGet().begin());}
		
	
	template<>
	void ValueInput<float>::displayUpdate()	
		{titleSet(Herbs::FloatFormat<7>(*ptr_obj));}
		
	template<>
	void ValueInput<float>::valueUpdate()	
		{*ptr_obj=Herbs::toDouble(titleGet().begin());}

	template<>
	void ValueInput<Herbs::String>::displayUpdate()		
		{
		titleSet(ptr_obj->begin());
		}
	
	template<>
	void ValueInput<Herbs::String>::valueUpdate()
		{
		*ptr_obj=titleGet();
		}
		
	}
