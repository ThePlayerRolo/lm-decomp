#ifndef PARAMS_HPP
#define PARAMS_HPP

#include "Koga/BaseParam.hpp"

#include <JSystem/JKernel/JKRFileLoader.hpp>

class TParams {
public:
	TParams()
	    : mPrmPath(nullptr)
	    , mHead(nullptr)
	{
	}
	TParams(const char* prm)
	    : mPrmPath(prm)
	    , mHead(nullptr)
	{
	}

	static void finalize();

	void load(JSUMemoryInputStream& stream);
	bool load(const char* pFileName, JKRFileLoader* pFileLoader);

	static void init();

public:
	/* 0x00 */ const char* mPrmPath;
	/* 0x04 */ TBaseParam* mHead;
	/* 0x08 */ bool _8;

	static JKRFileLoader* mArc;
	static JKRFileLoader* mSceneArc;
};

#endif
