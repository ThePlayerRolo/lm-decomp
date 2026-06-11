#include "Koga/SimpleModeler.hpp"

dummy_float_data()

namespace Koga {
    //https://decomp.me/scratch/kmGpk
    void SimpleModeler::newSimpleModeler() {
        if (sSimpleModelerInitialized == 0) {
            //fn_800BB88C(); Something funky here, maybe its a part of inline constructor of SimpleModeler? Maybe has a base class?
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
        if (mUnk2._300 >= 32) {
            return false;
        }

        mUnk2.fn_800BB9E4(param_3);
        return true;
    }

    SimpleModeler* SimpleModeler::fn_800BB88C() {
        fn_800BB8BC();
        return this;
    }

    void SimpleModeler::fn_800BB8BC() {
        sSimpleModelerInitialized += 1;
    }
}

unkSimpleModeler3::unkSimpleModeler3() {
    _680 = 0; //Could also be nullptr
}


unkSimpleModeler2::unkSimpleModeler2() {
    _300 = 0; //Could also be nullptr
}

unkSimpleModeler1::unkSimpleModeler1() {
    _280 = 0; //Could also be nullptr
}
