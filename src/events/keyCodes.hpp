#ifndef __KEYCODES_HPP__
#define __KEYCODES_HPP__

namespace engine::events
{
    enum class KeyCode
    {
        Unknown = 0,

        Return = '\r',
        Escape = '\x1B',
        Backspace = '\b',
        Tab = '\t',
        Space = ' ',
        Exclaim = '!',
        Quotedbl = '"',
        Hash = '#',
        Percent = '%',
        Dollar = '$',
        Ampersand = '&',
        Quote = '\'',
        Leftparen = '(',
        Rightparen = ')',
        Asterisk = '*',
        Plus = '+',
        Comma = ',',
        Minus = '-',
        Period = '.',
        Slash = '/',
        Key_0 = '0',
        Key_1 = '1',
        Key_2 = '2',
        Key_3 = '3',
        Key_4 = '4',
        Key_5 = '5',
        Key_6 = '6',
        Key_7 = '7',
        Key_8 = '8',
        Key_9 = '9',
        Colon = ':',
        Semicolon = ';',
        Less = '<',
        Equals = '=',
        Greater = '>',
        Question = '?',
        At = '@',
        Leftbracket = '[',
        Backslash = '\\',
        Rightbracket = ']',
        Caret = '^',
        Underscore = '_',
        Backquote = '`',
        Key_a = 'a',
        Key_b = 'b',
        Key_c = 'c',
        Key_d = 'd',
        Key_e = 'e',
        Key_f = 'f',
        Key_g = 'g',
        Key_h = 'h',
        Key_i = 'i',
        Key_j = 'j',
        Key_k = 'k',
        Key_l = 'l',
        Key_m = 'm',
        Key_n = 'n',
        Key_o = 'o',
        Key_p = 'p',
        Key_q = 'q',
        Key_r = 'r',
        Key_s = 's',
        Key_t = 't',
        Key_u = 'u',
        Key_v = 'v',
        Key_w = 'w',
        Key_x = 'x',
        Key_y = 'y',
        Key_z = 'z',

        Capslock,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        Printscreen,
        Scrolllock,
        Pause,
        Insert,
        Home,
        Pageup,
        Delete,
        End,
        Pagedown,
        Right,
        Left,
        Down,
        Up,

        Numlockclear,
        KP_Divide,
        KP_Multiply,
        KP_Minus,
        KP_Plus,
        KP_Enter,
        KP_1,
        KP_2,
        KP_3,
        KP_4,
        KP_5,
        KP_6,
        KP_7,
        KP_8,
        KP_9,
        KP_0,
        KP_Period,

        LCtrl,
        LShift,
        LAlt,
        LSuper,
        RCtrl,
        RShift,
        RAlt,
        RSuper,
    };
}

#endif
