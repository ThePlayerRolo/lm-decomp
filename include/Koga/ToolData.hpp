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
            s32 mNumEntries;         // 0x0
            s32 mNumFields;          // 0x4
            s32 mDataOffset;         // 0x8
            u32 mEntrySize;          // 0xC
            const JMapItem mItems[]; // 0x10
        };

        BOOL attach(const JMapData* data);
        void reset();
        s32 searchItemInfo(const char* key) const;
        BOOL getValueMasked(int entryIndex, const char* key, u32* valueOut) const;
        BOOL getValueBit(int entryIndex, const char* key, u8* bitOut) const;
        BOOL getValue(int entryIndex, const char* key, s32* valueOut) const;
        BOOL getValue(int entryIndex, const char* key, float* valueOut) const;
        BOOL getValue(int entryIndex, const char* key, const char** valueOut) const;
    private:
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

        /* 0x04 */ const JMapData* mData;
    };
}


#endif
