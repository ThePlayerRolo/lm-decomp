#include "Koga/SimpleModeler.hpp"

dummy_float_data()

unkSimpleModeler1::~unkSimpleModeler1() {
    delete this;
}

unkSimpleModeler2::~unkSimpleModeler2() {
    delete this;
}

unkSimpleModeler3::~unkSimpleModeler3() {
    delete this;    
}

namespace Koga {
    
    //https://decomp.me/scratch/ILg4C
    SimpleModeler::~SimpleModeler() {
        delete this;
        sSimpleModelerInitialized -= 1;
    }

    //https://decomp.me/scratch/kmGpk
    void SimpleModeler::newSimpleModeler() {
        if (sSimpleModelerInitialized == 0) {
            //fn_800BB88C();
            sCurSimpleModeler = new SimpleModeler();
        }
    }

    void SimpleModeler::deleteSimpleModeler() {
        if (sSimpleModelerInitialized == 1) {
            delete sCurSimpleModeler;
        }
    }

    //Adding this here, although its probably some struct nonsense here: https://decomp.me/scratch/HzVXW
    bool SimpleModeler::fn_800BB6A4(f32 param_1, f32 param_2, void* param_3, void* param_4) {
        if (mUnk2._304 >= 32) {
            return false;
        }

        fn_800BB9E4(&mUnk2, param_3);
        return true;
    }

    SimpleModeler* SimpleModeler::fn_800BB88C() {
        fn_800BB8BC();
        return this;
    }

    void SimpleModeler::fn_800BB8BC() {
        sSimpleModelerInitialized+=1;
    }

    // As noted in the header, these may just be functions in the class, unsure, but they match 100%
    void SimpleModeler::fn_800BB8CC() {
        mUnk3._F8 = 0;
    }

    void SimpleModeler::fn_800BB998() {
        mUnk2._7C = 0;
    }

    void SimpleModeler::fn_800BBA2C(){
        mUnk1._280 = 0;
    }
}
