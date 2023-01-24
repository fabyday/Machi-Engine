//
// Created by yabai on 2023/01/12.
//

#ifndef MACHI_ENGINE_CONFIG_H
#define MACHI_ENGINE_CONFIG_H
#if defined(__APPLE__)
#include "Apple/config.h"
#elif defined(_WIN64) || defined(_WIN32)
#include "windows/config.h"
#endif
#endif //MACHI_ENGINE_CONFIG_H
