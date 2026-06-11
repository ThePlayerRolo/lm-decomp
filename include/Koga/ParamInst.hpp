#ifndef PARAM_INST_HPP
#define PARAM_INST_HPP

#include <JSystem/JGeometry/JGVec3.hpp>
#include "Koga/BaseParam.hpp"

template <typename T> class TParamT : public TBaseParam {
public:
	TParamT(TParams* params, T defaultValue, const char* paramName, u16 code)
	    : TBaseParam(params, paramName, code)
	    , value(defaultValue)
	{
	}

	virtual void load(JSUMemoryInputStream& stream);

	// fabricated
	const T& get() const { return value; }

	T value;
};

template <typename T> class TParamRT : public TParamT<T> {
public:
	TParamRT(TParams* parent, T defaultValue, const char* name, u16 keycode)
	    : TParamT<T>(parent, defaultValue, name, keycode)
	{
	}

	// NOTE: this MUST take a reference, as constants passed
	// to it must be stored in sdata!
	inline void set(const T& param) { this->value = param; };

	// Fabricated
	TParamRT<T>& operator=(const TParamRT<T>& other)
	{
		this->keyCode = other.keyCode;
		this->name    = other.name;
		this->next    = other.next;
		this->value   = other.value;
		return *this;
	}
};

/*
class TParamVec : public TParamT<JGeometry::TVec3<f32> > {
public:
	// fabricated AND wrong
	TParamVec(TParams* parent, JGeometry::TVec3<f32> defaultValue, u16 keycode,
	          const char* name)
	    : TParamT<JGeometry::TVec3<f32> >(parent, defaultValue, keycode, name)
	{
	}
};
*/

#define PARAM_INIT(member, defaultValue)                                       \
	member(this, defaultValue, #member, calcKeyCode(#member))

#endif
