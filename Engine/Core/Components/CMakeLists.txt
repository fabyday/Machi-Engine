set(src "Mobject.cpp" "ComponentManager.cpp" )

add_library(Components SHARED ${src} )
TARGET_CONFIGURE_SETUP(Components "COMPONENTS")
target_link_libraries(Components PUBLIC Machi::Logger EnTT::EnTT)
add_library(Machi::Components ALIAS Components)
