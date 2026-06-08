#include "Koga/ToolData.hpp"
#include "types.h"
#include "macros.h"

Koga::ToolData::ToolData() {
    mData = nullptr;
}

Koga::ToolData::~ToolData() {

}

BOOL Koga::ToolData::attach(const JMapData* data) {
    if (data == nullptr) {
        return FALSE;
    }
    mData = data;
    return TRUE;
}

void Koga::ToolData::reset() {
	mData = nullptr;
}

s32 Koga::ToolData::searchItemInfo(const char* key) const {
    s32 nFields = mData->mNumFields;
	u32 hash = hashString(key);

    // Stop the getValue* functions from inlining this
    FORCE_DONT_INLINE;

	for (int i = 0; i < nFields; ++i) {
		if (hash == mData->mItems[i].mHash) {
			return i;
		}
	}

	return -1;
}

BOOL Koga::ToolData::getValueBit(int entryIndex, const char* key, u8* bitOut) const {
	s32 itemIndex = searchItemInfo(key);
	if (itemIndex < 0) {
		return FALSE;
	}

	u32 entryOffset = entryIndex * mData->mEntrySize;
	s32 dataOffset = mData->mDataOffset;
	const JMapItem* item = &mData->mItems[itemIndex];
	const u8* valuePtr = reinterpret_cast<const u8*>(mData) + dataOffset + entryOffset + item->mOffsData;
	u32 value = *reinterpret_cast<const u32*>(valuePtr);
	*bitOut = ((value & item->mMask) != 0);
	return TRUE;
}

BOOL Koga::ToolData::getValueMasked(int entryIndex, const char* key, u32* valueOut) const {
    s32 itemIndex = searchItemInfo(key);
	if (itemIndex < 0) {
		return FALSE;
	}

	u32 entryOffset = entryIndex * mData->mEntrySize;
	s32 dataOffset = mData->mDataOffset;
    const JMapItem* item = &mData->mItems[itemIndex];
	const u8* valuePtr = reinterpret_cast<const u8*>(mData) + dataOffset + entryOffset + item->mOffsData;
	u32 value = *reinterpret_cast<const u32*>(valuePtr);
	*valueOut = (value & item->mMask) >> item->mShift;
	return TRUE;
}

BOOL Koga::ToolData::getValue(int entryIndex, const char* key, s32* valueOut) const {
    s32 itemIndex = searchItemInfo(key);
	if (itemIndex < 0) {
		return FALSE;
	}

	u32 entryOffset = entryIndex * mData->mEntrySize;
	s32 dataOffset = mData->mDataOffset;
    const JMapItem* item = &mData->mItems[itemIndex];
	const u8* valuePtr = reinterpret_cast<const u8*>(mData) + dataOffset + entryOffset + item->mOffsData;
	s32 value = *reinterpret_cast<const s32*>(valuePtr);
	*valueOut = value;
	return TRUE;
}

BOOL Koga::ToolData::getValue(int entryIndex, const char* key, float* valueOut) const {
    s32 itemIndex = searchItemInfo(key);
	if (itemIndex < 0) {
		return FALSE;
	}

    u32 entryOffset = entryIndex * mData->mEntrySize;
	s32 dataOffset = mData->mDataOffset;
    const JMapItem* item = &mData->mItems[itemIndex];
	const u8* valuePtr = reinterpret_cast<const u8*>(mData) + dataOffset + entryOffset + item->mOffsData;
	*valueOut = *reinterpret_cast<const float*>(valuePtr);
	return TRUE;
}

BOOL Koga::ToolData::getValue(int entryIndex, const char* key, const char** valueOut) const {
    s32 itemIndex = searchItemInfo(key);
	if (itemIndex < 0) {
		return FALSE;
	}

	u32 entryOffset = entryIndex * mData->mEntrySize;
	s32 dataOffset = mData->mDataOffset;
    const JMapItem* item = &mData->mItems[itemIndex];
	const u8* valuePtr = reinterpret_cast<const u8*>(mData) + dataOffset + entryOffset + item->mOffsData;
	*valueOut = reinterpret_cast<const char*>(valuePtr);
	return TRUE;
}
