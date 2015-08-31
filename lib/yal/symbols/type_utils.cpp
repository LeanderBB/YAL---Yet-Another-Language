#include "yal/symbols/type_utils.h"

namespace yal
{

static const bool
sTypePromotionTable [kConstantTypeMax][kConstantTypeMax] =
{
    // none   id      text     i32     u32     i64     u64     bool    f32     f64
    {true,  false,  false,  false,  false,  false,  false,  false,  false,  false}, // none
    {false, true ,  false,  false,  false,  false,  false,  false,  false,  false}, // id
    {false, false,  true,   false,  false,  false,  false,  false,  false,  false}, // text
    {false, false,  false,   true,  false,  false,  false,  true,   false,  false}, // i32
    {false, false,  false,  false,  true,   false,  false,  true,   false,  false}, // u32
    {false, false,  false,  false,  false,  true ,  false,  true,   false,  false}, // i64
    {false, false,  false,  false,  false,  false,  true ,  true,   false,  false}, // u64
    {false, false,  false,  true ,  true ,  true,   true,   true,   false,  false}, // bool
    {false, false,  false,  false,  false,  false,  false,  false,  true ,  true }, // f32
    {false, false,  false,  false,  false,  false,  false,  false,  false,  true }  // f64
};

bool
CanTypeBePromoted(const DataType from,
                  const DataType to)
{
    if (from.origin != kSymbolDataOriginBuiltin
            || to.origin != kSymbolDataOriginBuiltin)
    {
        return false;
    }

    if(from.data.builtin >= kConstantTypeMax
            || to.data.builtin >= kConstantTypeMax)
    {
        return false;
    }

    return sTypePromotionTable[from.data.builtin][to.data.builtin];
}

bool
IsValidBoolean(const DataType from)
{
    return (from.origin == kSymbolDataOriginBuiltin)
            ? sTypePromotionTable[from.data.builtin][kConstantTypeBool]
            : false;
}


}

