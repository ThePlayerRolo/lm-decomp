#ifndef SIMPLE_MODELER_H_
#define SIMPLE_MODELER_H_

#include "types.h"

class unkSimpleModeler1 {
public: 
    unkSimpleModeler1();
    ~unkSimpleModeler1();

    // TODO figure out what this data is
    /* 0x0 - 0x27C */ u8 _0[0x27C];
    /* 0x280 */ s32 _280; //Some Counter or ptr?
    /* 0x284 */ s32 _284; //Some Counter or ptr?
};

class unkSimpleModeler2 {
public: 
    unkSimpleModeler2();
    ~unkSimpleModeler2();

    // TODO figure out what this data is
    /* 0x0 - 0x78 */ u8 _0[0x78];
    /* 0x7C */ s32 _7C; //Some Counter or ptr?
    /* 0x80 - 0x300 */ u8 _2C[0x284];
    /* 0x304 */ s32 _304; //Some Counter or ptr?
};

class unkSimpleModeler3 {
public: 
    unkSimpleModeler3();
    ~unkSimpleModeler3();

    // TODO figure out what this data is
    /* 0x0 - 0xF4 */ u8 _0[0xF4];
    /* 0xF8 */ s32 _F8; //Some Counter or ptr?
    /* 0xFC - 0x680 */ u8 _A0[0x58C];
    /* 0x684 */ s32 _684; //Some Counter or ptr?
};

namespace Koga {
    class SimpleModeler {
    public:
        SimpleModeler() {}
        /* 0x08 */ virtual ~SimpleModeler();

        static void newSimpleModeler();
        static void deleteSimpleModeler();

        // TODO validate these arguments, especially the void*'s
        // I opted to not match this name because 
        bool fn_800BB6A4(f32, f32, void*, void*);

        bool fn_800BB70C(); //Seems to be some Matrix copying or something similar of unkSimpleModeler3. Missing Args
        void fn_800BB778(); //Draws the models of each class in a loop.

        SimpleModeler* fn_800BB88C();
        void fn_800BB8BC();

        // These are all related to unkSimpleModeler3. Maybe class functions?
        void fn_800BB8CC(); // Sets some value to 0 or nullptr?
        void fn_800BB8D8(); // Deconstructor for sure
        // Some sort constructor or copy elements?
        void fn_800BB918(unkSimpleModeler3*, void*); // TODO validate these arguments, especially the void*'s

        // These are all related to unkSimpleModeler2. Maybe class functions?
        void fn_800BB998(); // Sets some value to 0 or nullptr?
        void fn_800BB9A4(); // Deconstructor for sure
        void fn_800BB9E4(unkSimpleModeler2*, void*); // TODO validate these arguments, especially the void*'s

        // These are all related to unkSimpleModeler1. Maybe class functions?
        void fn_800BBA2C(); // Sets some value to 0 or nullptr?
        void fn_800BBA38(); // Deconstructor for sure
    public:
        /* 0x4 */ unkSimpleModeler1 mUnk1; 
        /* 0x288 */ unkSimpleModeler2 mUnk2; 
        /* 0x58C */ unkSimpleModeler3 mUnk3;

        static SimpleModeler* sCurSimpleModeler;
        static int sSimpleModelerInitialized;
    };

};

#endif
