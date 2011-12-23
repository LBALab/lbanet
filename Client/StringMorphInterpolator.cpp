
#include "StringMorphInterpolator.h"

#include <CEGUIString.h>

namespace CEGUI
{
	/********************************************
	* StringMorph interpolator
	********************************************/
	const String& StringMorphInterpolator::getType() const
	{
		static String type = "StringMorph";
		return type;
	}

	//----------------------------------------------------------------------------//
	String StringMorphInterpolator::interpolateAbsolute(const String& value1,
			const String& value2,
			float position)
	{
		return combineStrings(value1, value2, position);
	}

	//----------------------------------------------------------------------------//
	String StringMorphInterpolator::interpolateRelative(const String& base,
			const String& value1,
			const String& value2,
			float position)
	{
		return base + combineStrings(value1, value2, position);
	}

	//----------------------------------------------------------------------------//
	String StringMorphInterpolator::interpolateRelativeMultiply(const String& base,
			const String& value1,
			const String& value2,
			float position)
	{
		// todo: not sure what to do here
		return base;
	}

	//----------------------------------------------------------------------------//
	String StringMorphInterpolator::combineStrings(const String& str1, const String& str2, float position)
	{
	   String::size_type s1size = str1.size();
	   String::size_type s2size = str2.size();

	   if(s1size <= s2size)
	   {
		  // the result string should grow
		  String::size_type s2partsize = static_cast<String::size_type>(s2size*position);
		  String::size_type ressize = std::max(s1size, s2partsize);

		  String res(str1);
		  res.resize(ressize);
		  for(String::size_type i=0; i< s2partsize; ++i)
			 res[i] = str2[i];

		  return res;
	   }
	   else
	   {
		  //the result string should shrink
		  String::size_type s1partsize = static_cast<String::size_type>(s1size*(1-position));
		  String::size_type s2partsize = ((s1partsize>s2size)?0:s2size-s1partsize);
		  String::size_type ressize = std::max(s1partsize, s2size);

		  String res(str1.substr(s1size-s1partsize-s2partsize));
		  for(String::size_type i=0; i< s2partsize; ++i)
			 res[i] = str2[i];

		  return res;
	   }
	}
}