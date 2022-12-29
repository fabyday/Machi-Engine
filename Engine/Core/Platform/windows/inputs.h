//MIT License 
//Copyright(c) 2022 fabyday
// 
// 
//Permission is hereby granted, free of charge, to any person
//obtaining a copy of this softwareand associated documentation
//files(the "Software"), to deal in the Software without
//restriction, including without limitation the rights to use,
//copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the
//Software is furnished to do so, subject to the following
//conditions :
//
//The above copyright noticeand this permission notice shall be
//included in all copies or substantial portions of the Software.
// 
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//OTHER DEALINGS IN THE SOFTWARE.
#pragma once

#include <winuser.h>


            /*
             * Virtual Keys, Standard Set
             */
#define MACHI_LBUTTON        0x01
#define MACHI_RBUTTON        0x02
#define MACHI_CANCEL         0x03
#define MACHI_MBUTTON        0x04    /* NOT contiguous with L & RBUTTON */

#if(_WIN32_WINNT >= 0x0500)
#define MACHI_XBUTTON1       0x05    /* NOT contiguous with L & RBUTTON */
#define MACHI_XBUTTON2       0x06    /* NOT contiguous with L & RBUTTON */
#endif /* _WIN32_WINNT >= 0x0500 */

             /*
              * 0x07 : reserved
              */


#define MACHI_BACK           0x08
#define MACHI_TAB            0x09

              /*
               * 0x0A - 0x0B : reserved
               */

#define MACHI_CLEAR          0x0C
#define MACHI_RETURN         0x0D

               /*
                * 0x0E - 0x0F : unassigned
                */

#define MACHI_SHIFT          0x10
#define MACHI_CONTROL        0x11
#define MACHI_MENU           0x12
#define MACHI_PAUSE          0x13
#define MACHI_CAPITAL        0x14

#define MACHI_KANA           0x15
#define MACHI_HANGEUL        0x15  /* old name - should be here for compatibility */
#define MACHI_HANGUL         0x15
#define MACHI_IME_ON         0x16
#define MACHI_JUNJA          0x17
#define MACHI_FINAL          0x18
#define MACHI_HANJA          0x19
#define MACHI_KANJI          0x19
#define MACHI_IME_OFF        0x1A

#define MACHI_ESCAPE         0x1B

#define MACHI_CONVERT        0x1C
#define MACHI_NONCONVERT     0x1D
#define MACHI_ACCEPT         0x1E
#define MACHI_MODECHANGE     0x1F

#define MACHI_SPACE          0x20
#define MACHI_PRIOR          0x21
#define MACHI_NEXT           0x22
#define MACHI_END            0x23
#define MACHI_HOME           0x24
#define MACHI_LEFT           0x25
#define MACHI_UP             0x26
#define MACHI_RIGHT          0x27
#define MACHI_DOWN           0x28
#define MACHI_SELECT         0x29
#define MACHI_PRINT          0x2A
#define MACHI_EXECUTE        0x2B
#define MACHI_SNAPSHOT       0x2C
#define MACHI_INSERT         0x2D
#define MACHI_DELETE         0x2E
#define MACHI_HELP           0x2F

                /*
                 * MACHI_0 - MACHI_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
                 * 0x3A - 0x40 : unassigned
                 * MACHI_A - MACHI_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
                 */

#define MACHI_LWIN           0x5B
#define MACHI_RWIN           0x5C
#define MACHI_APPS           0x5D

                 /*
                  * 0x5E : reserved
                  */

#define MACHI_SLEEP          0x5F

#define MACHI_NUMPAD0        0x60
#define MACHI_NUMPAD1        0x61
#define MACHI_NUMPAD2        0x62
#define MACHI_NUMPAD3        0x63
#define MACHI_NUMPAD4        0x64
#define MACHI_NUMPAD5        0x65
#define MACHI_NUMPAD6        0x66
#define MACHI_NUMPAD7        0x67
#define MACHI_NUMPAD8        0x68
#define MACHI_NUMPAD9        0x69
#define MACHI_MULTIPLY       0x6A
#define MACHI_ADD            0x6B
#define MACHI_SEPARATOR      0x6C
#define MACHI_SUBTRACT       0x6D
#define MACHI_DECIMAL        0x6E
#define MACHI_DIVIDE         0x6F
#define MACHI_F1             0x70
#define MACHI_F2             0x71
#define MACHI_F3             0x72
#define MACHI_F4             0x73
#define MACHI_F5             0x74
#define MACHI_F6             0x75
#define MACHI_F7             0x76
#define MACHI_F8             0x77
#define MACHI_F9             0x78
#define MACHI_F10            0x79
#define MACHI_F11            0x7A
#define MACHI_F12            0x7B
#define MACHI_F13            0x7C
#define MACHI_F14            0x7D
#define MACHI_F15            0x7E
#define MACHI_F16            0x7F
#define MACHI_F17            0x80
#define MACHI_F18            0x81
#define MACHI_F19            0x82
#define MACHI_F20            0x83
#define MACHI_F21            0x84
#define MACHI_F22            0x85
#define MACHI_F23            0x86
#define MACHI_F24            0x87

#if(_WIN32_WINNT >= 0x0604)

                  /*
                   * 0x88 - 0x8F : UI navigation
                   */

#define MACHI_NAVIGATION_VIEW     0x88 // reserved
#define MACHI_NAVIGATION_MENU     0x89 // reserved
#define MACHI_NAVIGATION_UP       0x8A // reserved
#define MACHI_NAVIGATION_DOWN     0x8B // reserved
#define MACHI_NAVIGATION_LEFT     0x8C // reserved
#define MACHI_NAVIGATION_RIGHT    0x8D // reserved
#define MACHI_NAVIGATION_ACCEPT   0x8E // reserved
#define MACHI_NAVIGATION_CANCEL   0x8F // reserved

#endif /* _WIN32_WINNT >= 0x0604 */

#define MACHI_NUMLOCK        0x90
#define MACHI_SCROLL         0x91

                   /*
                    * NEC PC-9800 kbd definitions
                    */
#define MACHI_OEM_NEC_EQUAL  0x92   // '=' key on numpad

                    /*
                     * Fujitsu/OASYS kbd definitions
                     */
#define MACHI_OEM_FJ_JISHO   0x92   // 'Dictionary' key
#define MACHI_OEM_FJ_MASSHOU 0x93   // 'Unregister word' key
#define MACHI_OEM_FJ_TOUROKU 0x94   // 'Register word' key
#define MACHI_OEM_FJ_LOYA    0x95   // 'Left OYAYUBI' key
#define MACHI_OEM_FJ_ROYA    0x96   // 'Right OYAYUBI' key

                     /*
                      * 0x97 - 0x9F : unassigned
                      */

                      /*
                       * MACHI_L* & MACHI_R* - left and right Alt, Ctrl and Shift virtual keys.
                       * Used only as parameters to GetAsyncKeyState() and GetKeyState().
                       * No other API or message will distinguish left and right keys in this way.
                       */
#define MACHI_LSHIFT         0xA0
#define MACHI_RSHIFT         0xA1
#define MACHI_LCONTROL       0xA2
#define MACHI_RCONTROL       0xA3
#define MACHI_LMENU          0xA4
#define MACHI_RMENU          0xA5

#if(_WIN32_WINNT >= 0x0500)
#define MACHI_BROWSER_BACK        0xA6
#define MACHI_BROWSER_FORWARD     0xA7
#define MACHI_BROWSER_REFRESH     0xA8
#define MACHI_BROWSER_STOP        0xA9
#define MACHI_BROWSER_SEARCH      0xAA
#define MACHI_BROWSER_FAVORITES   0xAB
#define MACHI_BROWSER_HOME        0xAC

#define MACHI_VOLUME_MUTE         0xAD
#define MACHI_VOLUME_DOWN         0xAE
#define MACHI_VOLUME_UP           0xAF
#define MACHI_MEDIA_NEXT_TRACK    0xB0
#define MACHI_MEDIA_PREV_TRACK    0xB1
#define MACHI_MEDIA_STOP          0xB2
#define MACHI_MEDIA_PLAY_PAUSE    0xB3
#define MACHI_LAUNCH_MAIL         0xB4
#define MACHI_LAUNCH_MEDIA_SELECT 0xB5
#define MACHI_LAUNCH_APP1         0xB6
#define MACHI_LAUNCH_APP2         0xB7

#endif /* _WIN32_WINNT >= 0x0500 */

                       /*
                        * 0xB8 - 0xB9 : reserved
                        */

#define MACHI_OEM_1          0xBA   // ';:' for US
#define MACHI_OEM_PLUS       0xBB   // '+' any country
#define MACHI_OEM_COMMA      0xBC   // ',' any country
#define MACHI_OEM_MINUS      0xBD   // '-' any country
#define MACHI_OEM_PERIOD     0xBE   // '.' any country
#define MACHI_OEM_2          0xBF   // '/?' for US
#define MACHI_OEM_3          0xC0   // '`~' for US

                        /*
                         * 0xC1 - 0xC2 : reserved
                         */

#if(_WIN32_WINNT >= 0x0604)

                         /*
                          * 0xC3 - 0xDA : Gamepad input
                          */

#define MACHI_GAMEPAD_A                         0xC3 // reserved
#define MACHI_GAMEPAD_B                         0xC4 // reserved
#define MACHI_GAMEPAD_X                         0xC5 // reserved
#define MACHI_GAMEPAD_Y                         0xC6 // reserved
#define MACHI_GAMEPAD_RIGHT_SHOULDER            0xC7 // reserved
#define MACHI_GAMEPAD_LEFT_SHOULDER             0xC8 // reserved
#define MACHI_GAMEPAD_LEFT_TRIGGER              0xC9 // reserved
#define MACHI_GAMEPAD_RIGHT_TRIGGER             0xCA // reserved
#define MACHI_GAMEPAD_DPAD_UP                   0xCB // reserved
#define MACHI_GAMEPAD_DPAD_DOWN                 0xCC // reserved
#define MACHI_GAMEPAD_DPAD_LEFT                 0xCD // reserved
#define MACHI_GAMEPAD_DPAD_RIGHT                0xCE // reserved
#define MACHI_GAMEPAD_MENU                      0xCF // reserved
#define MACHI_GAMEPAD_VIEW                      0xD0 // reserved
#define MACHI_GAMEPAD_LEFT_THUMBSTICK_BUTTON    0xD1 // reserved
#define MACHI_GAMEPAD_RIGHT_THUMBSTICK_BUTTON   0xD2 // reserved
#define MACHI_GAMEPAD_LEFT_THUMBSTICK_UP        0xD3 // reserved
#define MACHI_GAMEPAD_LEFT_THUMBSTICK_DOWN      0xD4 // reserved
#define MACHI_GAMEPAD_LEFT_THUMBSTICK_RIGHT     0xD5 // reserved
#define MACHI_GAMEPAD_LEFT_THUMBSTICK_LEFT      0xD6 // reserved
#define MACHI_GAMEPAD_RIGHT_THUMBSTICK_UP       0xD7 // reserved
#define MACHI_GAMEPAD_RIGHT_THUMBSTICK_DOWN     0xD8 // reserved
#define MACHI_GAMEPAD_RIGHT_THUMBSTICK_RIGHT    0xD9 // reserved
#define MACHI_GAMEPAD_RIGHT_THUMBSTICK_LEFT     0xDA // reserved

#endif /* _WIN32_WINNT >= 0x0604 */


#define MACHI_OEM_4          0xDB  //  '[{' for US
#define MACHI_OEM_5          0xDC  //  '\|' for US
#define MACHI_OEM_6          0xDD  //  ']}' for US
#define MACHI_OEM_7          0xDE  //  ''"' for US
#define MACHI_OEM_8          0xDF

                          /*
                           * 0xE0 : reserved
                           */

                           /*
                            * Various extended or enhanced keyboards
                            */
#define MACHI_OEM_AX         0xE1  //  'AX' key on Japanese AX kbd
#define MACHI_OEM_102        0xE2  //  "<>" or "\|" on RT 102-key kbd.
#define MACHI_ICO_HELP       0xE3  //  Help key on ICO
#define MACHI_ICO_00         0xE4  //  00 key on ICO

#if(WINVER >= 0x0400)
#define MACHI_PROCESSKEY     0xE5
#endif /* WINVER >= 0x0400 */

#define MACHI_ICO_CLEAR      0xE6


#if(_WIN32_WINNT >= 0x0500)
#define MACHI_PACKET         0xE7
#endif /* _WIN32_WINNT >= 0x0500 */

                            /*
                             * 0xE8 : unassigned
                             */

                             /*
                              * Nokia/Ericsson definitions
                              */
#define MACHI_OEM_RESET      0xE9
#define MACHI_OEM_JUMP       0xEA
#define MACHI_OEM_PA1        0xEB
#define MACHI_OEM_PA2        0xEC
#define MACHI_OEM_PA3        0xED
#define MACHI_OEM_WSCTRL     0xEE
#define MACHI_OEM_CUSEL      0xEF
#define MACHI_OEM_ATTN       0xF0
#define MACHI_OEM_FINISH     0xF1
#define MACHI_OEM_COPY       0xF2
#define MACHI_OEM_AUTO       0xF3
#define MACHI_OEM_ENLW       0xF4
#define MACHI_OEM_BACKTAB    0xF5

#define MACHI_ATTN           0xF6
#define MACHI_CRSEL          0xF7
#define MACHI_EXSEL          0xF8
#define MACHI_EREOF          0xF9
#define MACHI_PLAY           0xFA
#define MACHI_ZOOM           0xFB
#define MACHI_NONAME         0xFC
#define MACHI_PA1            0xFD
#define MACHI_OEM_CLEAR      0xFE

// mouse donw and up
#define MACHI_MOUSEFIRST                   0x0200
#define MACHI_MOUSEMOVE                    0x0200
#define MACHI_LBUTTONDOWN                  0x0201
#define MACHI_LBUTTONUP                    0x0202
#define MACHI_LBUTTONDBLCLK                0x0203
#define MACHI_RBUTTONDOWN                  0x0204
#define MACHI_RBUTTONUP                    0x0205
#define MACHI_RBUTTONDBLCLK                0x0206
#define MACHI_MBUTTONDOWN                  0x0207
#define MACHI_MBUTTONUP                    0x0208
#define MACHI_MBUTTONDBLCLK                0x0209
