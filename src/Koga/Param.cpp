#include "Koga/Params.hpp"
#include "Koga/UnkUtil.hpp"

TBaseParam::TBaseParam(TParams* params, const char* paramName,
                       unsigned short code)
    : keyCode(code)
    , name(paramName)
    , next(nullptr)
{
	TBaseParam* root = params->mHead;
	if (root != nullptr) {
		TBaseParam* param = root;
		while (param->next != nullptr) {
			param = param->next;
		}
		param->next = this;
		return;
	}

	params->mHead = this;
}

u16 TBaseParam::calcKeyCode(const char* pFileName) {
	return hashStringSeperate(pFileName);
}

void TParams::load(JSUMemoryInputStream& stream)
{
	if (mHead != nullptr) {
		s32 length = stream.readS32();
		for (int i = 0; i < length; i++) {
			u16 keyCode = stream.read16b();
			char buffer[0x50];
			stream.readString(buffer, 0x50);

			TBaseParam* param;
			for (param = mHead; param != nullptr; param = param->next) {
				if (keyCode == param->keyCode && !strcmp(buffer, param->name)) {
					param->load(stream);
					break;
				}
			}
			if (param == nullptr) {
				s32 end = stream.read32b();
				stream.skip(end);
			}
		}
		_8 = true;
	}
}

bool TParams::load(const char* pFileName, JKRFileLoader* pFileLoader) {
	bool ret = false;

	void* resource = nullptr;

	resource = pFileLoader->getResource(pFileName);

	if (resource != nullptr) {
		s32 size = pFileLoader->getResSize(resource);
		JSUMemoryInputStream stream(resource, size);
		load(stream);
		ret =  true;
	}
	return ret;
}
