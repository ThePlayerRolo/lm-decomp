#ifndef TOOL_DATA_H_
#define TOOL_DATA_H_

#include "types.h"
#include "JSystem/JORReflexible.hpp"

// Very similar to https://github.com/doldecomp/sms/blob/main/include/MarioUtil/ToolData.hpp
// But searchItemInfo() isn't inlined here, and there are more getValue*() variants.

namespace Koga {
    class ToolData : public JORReflexible {
    public:
        ToolData();
        virtual ~ToolData();

        #define JMAP_VALUE_TYPE_LONG       0
        #define JMAP_VALUE_TYPE_STRING     1
        #define JMAP_VALUE_TYPE_FLOAT      2
        #define JMAP_VALUE_TYPE_LONG_2     3
        #define JMAP_VALUE_TYPE_SHORT      4
        #define JMAP_VALUE_TYPE_BYTE       5
        #define JMAP_VALUE_TYPE_STRING_PTR 6
        #define JMAP_VALUE_TYPE_NULL       7

        struct JMapItem {
            u32 mHash;     // 0x0
            u32 mMask;     // 0x4
            u16 mOffsData; // 0x8
            u8 mShift;     // 0xA
            u8 mType;      // 0xB
        };

        struct JMapData {
            const JMapItem *getItem(u32 i) const {
                return &mItems[i];
            }

            s32 mNumEntries;         // 0x0
            s32 mNumFields;          // 0x4
            s32 mDataOffset;         // 0x8
            u32 mEntrySize;          // 0xC
            const JMapItem mItems[]; // 0x10
        };

        inline const JMapData* getJMapData() {
            return mData;
        }

        inline void setJMapData(JMapData* pData) {
            mData = pData;
        }

        template<typename T>
        inline T getUnsignedValue(int entryIndex, int fieldIndex) const {
            const JMapItem* pField = &mData->mItems[fieldIndex];
            const void* ptr = reinterpret_cast<const u32*>(reinterpret_cast<const u8*>(mData) + mData->mDataOffset + 
                (entryIndex * mData->mEntrySize) + pField->mOffsData);
            return (*reinterpret_cast<const T*>(ptr) & pField->mMask) >> pField->mShift;
        }

        template<typename T>
        inline const T getSignedValue(int entryIndex, int fieldIndex) const {
            const void* ptr = getDataPointer(mData, &mData->mItems[fieldIndex], entryIndex, fieldIndex);
            return *reinterpret_cast<const T*>(ptr);
        }

        BOOL attach(const JMapData*);
        void reset();
        BOOL getValue(int, const char*, u32*) const;
        BOOL getValue(int, const char*, s32*) const;
        BOOL getValue(int, const char*, u8*) const;
        BOOL getValue(int, const char*, f32*) const;
        BOOL getValue(int, const char*, const char**) const;
        s32 searchItemInfo(const char*) const;
        s32 findEntryByValue(int, const u32, int);
        s32 findEntryByValue(int, const char*, int);

    private:
        /* 0x04 */ const JMapData* mData;

        inline u32 hashString(const char* key) const
        {
            u32 stringHash = 0;
            char current_char;

            while ((current_char = *key) != 0) {
                key++;
                stringHash = (current_char + (stringHash << 8)) % 0x1FFFFD9;
            }
            return stringHash;
        }

        inline const void* getDataPointer(const JMapData* pData, const JMapItem* pField, int entryIndex, int fieldIndex) const {
            return reinterpret_cast<const u32*>(reinterpret_cast<const u8*>(pData) + pData->mDataOffset + 
                (entryIndex * pData->mEntrySize) + pField->mOffsData);
        }

        inline const u32 getExpectedUnsignedValue(int entryIndex, int fieldIndex) {
            const JMapItem* pField = mData->getItem(fieldIndex);
            const void* ptr = getDataPointer(mData, pField, entryIndex, fieldIndex);
            return (*reinterpret_cast<const u32*>(ptr) & pField->mMask) >> pField->mShift;
        }

        inline const f32 getFloatValue(int entryIndex, int fieldIndex) const {
            return *reinterpret_cast<const f32*>(getDataPointer(mData, &mData->mItems[fieldIndex], entryIndex, fieldIndex));
        }

        inline const bool getBoolValue(int entryIndex, int fieldIndex) const {
            const JMapItem* pField = &mData->mItems[fieldIndex];
            u32 entryOffset = entryIndex * mData->mEntrySize;
            const void* ptr = reinterpret_cast<const u32*>(reinterpret_cast<const u8*>(mData) + mData->mDataOffset + 
                entryOffset + pField->mOffsData);
            return *reinterpret_cast<const u32*>(ptr) & pField->mMask;
        }

        inline const char* getStringValue(int entryIndex, int fieldIndex) const {
            return reinterpret_cast<const char*>(getDataPointer(mData, &mData->mItems[fieldIndex], entryIndex, fieldIndex));
        };
    };
}


#endif
