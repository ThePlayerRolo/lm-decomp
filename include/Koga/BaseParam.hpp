#ifndef BASE_PARAM_HPP
#define BASE_PARAM_HPP

#include <JSystem/JSupport/JSUMemoryInputStream.hpp>

class TParams;

class TBaseParam {
public:
	TBaseParam(TParams* params, const char* paramName, unsigned short code);
	virtual void load(JSUMemoryInputStream&) { }

	// Seems to be replaced by JDrama::TNameRef::calcKeyCode in SMS
	static u16 calcKeyCode(const char* pFileName);

	TBaseParam* next;
	const char* name;
    u16 keyCode;
};

#endif
