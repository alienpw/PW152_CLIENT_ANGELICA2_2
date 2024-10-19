/********************************************************************
    created:    2024/10/18
    file name:  TypeList.h
    author:     yaojun (updated by assistant)

    purpose:    TypeList
*********************************************************************/

#pragma once

#include "TPBase.h"

using DWORD = unsigned long;

//////////////////////////////////////////////////////////////////////////
// basic definition for TypeList
//////////////////////////////////////////////////////////////////////////
template<typename HeadType, typename TailType>
struct TypeList {
    using Head = HeadType;
    using Tail = TailType;
};

// begin namespace TL
namespace TL {

    //////////////////////////////////////////////////////////////////////////
    // helper for generating typelist
    //////////////////////////////////////////////////////////////////////////

    template<typename T1>
    struct TypeListGenerator1 {
        using Result = TypeList<T1, NullType>;
    };

    template<typename T1, typename T2>
    struct TypeListGenerator2 {
        using Result = TypeList<T1, typename TypeListGenerator1<T2>::Result>;
    };

    template<typename T1, typename T2, typename T3>
    struct TypeListGenerator3 {
        using Result = TypeList<T1, typename TypeListGenerator2<T2, T3>::Result>;
    };

    template<typename T1, typename T2, typename T3, typename T4>
    struct TypeListGenerator4 {
        using Result = TypeList<T1, typename TypeListGenerator3<T2, T3, T4>::Result>;
    };

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    struct TypeListGenerator5 {
        using Result = TypeList<T1, typename TypeListGenerator4<T2, T3, T4, T5>::Result>;
    };

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    struct TypeListGenerator6 {
        using Result = TypeList<T1, typename TypeListGenerator5<T2, T3, T4, T5, T6>::Result>;
    };

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    struct TypeListGenerator7 {
        using Result = TypeList<T1, typename TypeListGenerator6<T2, T3, T4, T5, T6, T7>::Result>;
    };

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    struct TypeListGenerator8 {
        using Result = TypeList<T1, typename TypeListGenerator7<T2, T3, T4, T5, T6, T7, T8>::Result>;
    };

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
    struct TypeListGenerator9 {
        using Result = TypeList<T1, typename TypeListGenerator8<T2, T3, T4, T5, T6, T7, T8, T9>::Result>;
    };

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
    struct TypeListGenerator10 {
        using Result = TypeList<T1, typename TypeListGenerator9<T2, T3, T4, T5, T6, T7, T8, T9, T10>::Result>;
    };

    //////////////////////////////////////////////////////////////////////////
    // Length() operation of typelist
    //////////////////////////////////////////////////////////////////////////

    template<typename TTypeList>
    struct Length {
        constexpr static int value = 1 + Length<typename TTypeList::Tail>::value;
    };

    template<>
    struct Length<NullType> {
        constexpr static int value = 0;
    };

    //////////////////////////////////////////////////////////////////////////
    // TypeAt() operation of typelist
    //////////////////////////////////////////////////////////////////////////

    namespace Private {

        template<DWORD Index>
        struct TypeAtHelper {
            template<typename TTypeList>
            struct In {
                using Result = typename TypeAtHelper<Index - 1>::template In<typename TTypeList::Tail>::Result;
            };
        };

        template<>
        struct TypeAtHelper<0> {
            template<typename TTypeList>
            struct In {
                using Result = typename TTypeList::Head;
            };
        };
    }

    template<typename TTypeList, DWORD Index>
    struct TypeAt {
        using Result = typename Private::TypeAtHelper<Index>::template In<TTypeList>::Result;
    };

    //////////////////////////////////////////////////////////////////////////
    // convert each type in typelist to its pointer type
    //////////////////////////////////////////////////////////////////////////

    template<typename TTypeList>
    struct TypeList2PtrTypeList {
        using Result = TypeList<typename TTypeList::Head*, typename TypeList2PtrTypeList<typename TTypeList::Tail>::Result>;
    };

    template<>
    struct TypeList2PtrTypeList<NullType> {
        using Result = NullType;
    };

    //////////////////////////////////////////////////////////////////////////
    // convert each type in typelist to its const pointer type
    //////////////////////////////////////////////////////////////////////////

    template<typename TTypeList>
    struct TypeList2ConstPtrTypeList {
        using Result = TypeList<const typename TTypeList::Head*, typename TypeList2ConstPtrTypeList<typename TTypeList::Tail>::Result>;
    };

    template<>
    struct TypeList2ConstPtrTypeList<NullType> {
        using Result = NullType;
    };

    //////////////////////////////////////////////////////////////////////////
    // get sub head typelist
    //////////////////////////////////////////////////////////////////////////

    namespace Private {

        template<DWORD HeadN>
        struct HeadSubTypeListHelper {
            template<typename TTypeList>
            struct In {
                using Result = TypeList<typename TTypeList::Head, typename HeadSubTypeListHelper<HeadN - 1>::template In<typename TTypeList::Tail>::Result>;
            };
        };

        template<>
        struct HeadSubTypeListHelper<0> {
            template<typename TTypeList>
            struct In {
                using Result = NullType;
            };
        };
    }

    template<typename TTypeList, DWORD HeadN>
    struct HeadSubTypeList {
        using Result = typename Private::HeadSubTypeListHelper<HeadN>::template In<TTypeList>::Result;
    };

} // end namespace TL
