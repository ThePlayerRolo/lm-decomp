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

	/* 0x4 */ TBaseParam* mNext;
	/* 0x8 */ const char* mName;
    /* 0xC */ u16 mHash;
	/* 0xE */ u16 mType;
};

#endif
