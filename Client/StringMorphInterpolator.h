#include <CEGUIInterpolator.h>

namespace CEGUI
{
	class StringMorphInterpolator : public Interpolator
	{
	public:

	   virtual ~StringMorphInterpolator(void){}

		virtual const String& getType() const;

		virtual String interpolateAbsolute(const String& value1,
										   const String& value2,
										   float position);
		virtual String interpolateRelative(const String& base,
										   const String& value1,
										   const String& value2,
										   float position);
		virtual String interpolateRelativeMultiply(const String& base,
				const String& value1,
				const String& value2,
				float position);

	protected:
	   String combineStrings(const String& str1, const String& str2, float position);
	};
}