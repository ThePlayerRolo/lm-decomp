#ifndef SIMPLE_MODELER_H_
#define SIMPLE_MODELER_H_

#include "types.h"

class unkSimpleModeler1 {
public: 
    unkSimpleModeler1();
    ~unkSimpleModeler1();

    // TODO figure out what this data is
    /* 0x0 - 0x27C */ u8 _0[0x280];
    /* 0x280 */ s32 _280; //Some Counter or ptr?
};

class unkSimpleModeler2 {
public: 
    unkSimpleModeler2();
    ~unkSimpleModeler2();
    void fn_800BB9E4(void*); // TODO validate void* argument

    // TODO figure out what this data is
    /* 0x80 - 0x2FC */ u8 _0[0x300];
    /* 0x300 */ s32 _300; //Some Counter or ptr?
};

class unkSimpleModeler3 {
public: 
    unkSimpleModeler3();
    ~unkSimpleModeler3();
    // Some sort constructor or copy elements?
    void fn_800BB918(void*); // TODO validate void* argument

    // TODO figure out what this data is
    /* 0x0 - 0x67C */ u8 _FC[0x680];
    /* 0x680 */ s32 _680; //Some Counter or ptr?
};

namespace Koga {
    class SimpleModeler {
    public:
        SimpleModeler() {}

        //https://decomp.me/scratch/ILg4C
        /* 0x08 */ virtual ~SimpleModeler() {
            sSimpleModelerInitialized -= 1;
        }

        static void newSimpleModeler();
        static void deleteSimpleModeler();
        static SimpleModeler* getCurSimpleModeler() { return sCurSimpleModeler; }

        // TODO validate these arguments, especially the void*'s
        bool fn_800BB6A4(f32, f32, void*, void*);

        bool fn_800BB70C(); //Seems to be some Matrix copying or something similar of unkSimpleModeler3. Missing Args
        void draw(); //Draws the models of each class in a loop.

        SimpleModeler* fn_800BB88C();
        void fn_800BB8BC();
    public:
        /* 0x4 */ unkSimpleModeler1 mUnk1; 
        /* 0x288 */ unkSimpleModeler2 mUnk2; 
        /* 0x58C */ unkSimpleModeler3 mUnk3;

        static SimpleModeler* sCurSimpleModeler;
        static int sSimpleModelerInitialized;
    };

};

#endif
