//
// Created by yabai on 2023/01/19.
//

#ifndef MACHI_ENGINE_REFLECTION_H
#define MACHI_ENGINE_REFLECTION_H

#include <type_traits>
template<typename T, typename U = void>
struct SuperClassTypeDeduction{
    using Type = void;
};


template <typename T>
struct SuperClassTypeDeduction<T, std::void_t<typename T::ThisType>>{
using Type = T::ThisType;


};





#define GENERATE_TYPE_INFO(TypeName) \
private:                             \
friend SuperClassTYpeDeduction;      \
friend TypeInfoInitializer;          \
public:\
using Super = typename SuperClassTypeDeduction<TypeName>::Type; \
using ThisType=TypeName;             \
                                     \
static TypeInfo& StatkcTypeInfo()    \
{                                    \
    static TypeInfo typeInfo{TypeInfoInitializer<ThisType>(#TypeName)}; \
return typeInfo;                     \
}                                     \
virtual const TypeInfo& GetTypeInfo() const                     \
{                                    \
    return m_typeInfo;                                     \
}                                    \
private:                             \
inline static TypeInfo& m_typeInfo = StaticTypeInfo();          \
private:                             \

#endif //MACHI_ENGINE_REFLECTION_H
