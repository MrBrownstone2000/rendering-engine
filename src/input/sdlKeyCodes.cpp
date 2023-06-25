#include "pch.hpp"
#include "sdlKeyCodes.hpp"

#include <SDL.h>

namespace engine::input
{
    events::MouseButtonType GetMouseButtonType(u8 sdlButton)
    {
        switch (sdlButton)
        {
            case SDL_BUTTON_LEFT:
                return events::MouseButtonType::Left;
            case SDL_BUTTON_RIGHT:
                return events::MouseButtonType::Right;
            case SDL_BUTTON_MIDDLE:
                return events::MouseButtonType::Middle;
            default:
                return events::MouseButtonType::Unknown;
        }
    }

    u8 GetSDLMouseButton(events::MouseButtonType button)
    {
        switch (button)
        {
            case events::MouseButtonType::Left:
                return SDL_BUTTON_LEFT;
            case events::MouseButtonType::Right:
                return SDL_BUTTON_RIGHT;
            case events::MouseButtonType::Middle:
                return SDL_BUTTON_MIDDLE;
            default:
                return 0;
        }
    }

    events::KeyCode GetKeyCode(int sdlKey)
    {
        // Compiler should generate a lookup table for this...
        switch(sdlKey)
        {
            case SDLK_RETURN:  
                return events::KeyCode::Return;
            case SDLK_ESCAPE:  
                return events::KeyCode::Escape;
            case SDLK_BACKSPACE:  
                return events::KeyCode::Backspace;
            case SDLK_TAB:  
                return events::KeyCode::Tab;
            case SDLK_SPACE:  
                return events::KeyCode::Space;
            case SDLK_EXCLAIM:  
                return events::KeyCode::Exclaim;
            case SDLK_QUOTEDBL:  
                return events::KeyCode::Quotedbl;
            case SDLK_HASH:  
                return events::KeyCode::Hash;
            case SDLK_PERCENT:  
                return events::KeyCode::Percent;
            case SDLK_DOLLAR:  
                return events::KeyCode::Dollar;
            case SDLK_AMPERSAND:  
                return events::KeyCode::Ampersand;
            case SDLK_QUOTE:  
                return events::KeyCode::Quote;
            case SDLK_LEFTPAREN:  
                return events::KeyCode::Leftparen;
            case SDLK_RIGHTPAREN:  
                return events::KeyCode::Rightparen;
            case SDLK_ASTERISK:  
                return events::KeyCode::Asterisk;
            case SDLK_PLUS:  
                return events::KeyCode::Plus;
            case SDLK_COMMA:  
                return events::KeyCode::Comma;
            case SDLK_MINUS:  
                return events::KeyCode::Minus;
            case SDLK_PERIOD:  
                return events::KeyCode::Period;
            case SDLK_SLASH:  
                return events::KeyCode::Slash;
            case SDLK_0:  
                return events::KeyCode::Key_0;
            case SDLK_1:  
                return events::KeyCode::Key_1;
            case SDLK_2:  
                return events::KeyCode::Key_2;
            case SDLK_3:  
                return events::KeyCode::Key_3;
            case SDLK_4:  
                return events::KeyCode::Key_4;
            case SDLK_5:  
                return events::KeyCode::Key_5;
            case SDLK_6:  
                return events::KeyCode::Key_6;
            case SDLK_7:  
                return events::KeyCode::Key_7;
            case SDLK_8:  
                return events::KeyCode::Key_8;
            case SDLK_9:  
                return events::KeyCode::Key_9;
            case SDLK_COLON:  
                return events::KeyCode::Colon;
            case SDLK_SEMICOLON:  
                return events::KeyCode::Semicolon;
            case SDLK_LESS:  
                return events::KeyCode::Less;
            case SDLK_EQUALS:  
                return events::KeyCode::Equals;
            case SDLK_GREATER:  
                return events::KeyCode::Greater;
            case SDLK_QUESTION:  
                return events::KeyCode::Question;
            case SDLK_AT:  
                return events::KeyCode::At;
            case SDLK_LEFTBRACKET:  
                return events::KeyCode::Leftbracket;
            case SDLK_BACKSLASH:  
                return events::KeyCode::Backslash;
            case SDLK_RIGHTBRACKET:  
                return events::KeyCode::Rightbracket;
            case SDLK_CARET:  
                return events::KeyCode::Caret;
            case SDLK_UNDERSCORE:  
                return events::KeyCode::Underscore;
            case SDLK_BACKQUOTE:  
                return events::KeyCode::Backquote;
            case SDLK_a:  
                return events::KeyCode::Key_a;
            case SDLK_b:  
                return events::KeyCode::Key_b;
            case SDLK_c:  
                return events::KeyCode::Key_c;
            case SDLK_d:  
                return events::KeyCode::Key_d;
            case SDLK_e:  
                return events::KeyCode::Key_e;
            case SDLK_f:  
                return events::KeyCode::Key_f;
            case SDLK_g:  
                return events::KeyCode::Key_g;
            case SDLK_h:  
                return events::KeyCode::Key_h;
            case SDLK_i:  
                return events::KeyCode::Key_i;
            case SDLK_j:  
                return events::KeyCode::Key_j;
            case SDLK_k:  
                return events::KeyCode::Key_k;
            case SDLK_l:  
                return events::KeyCode::Key_l;
            case SDLK_m:  
                return events::KeyCode::Key_m;
            case SDLK_n:  
                return events::KeyCode::Key_n;
            case SDLK_o:  
                return events::KeyCode::Key_o;
            case SDLK_p:  
                return events::KeyCode::Key_p;
            case SDLK_q:  
                return events::KeyCode::Key_q;
            case SDLK_r:  
                return events::KeyCode::Key_r;
            case SDLK_s:  
                return events::KeyCode::Key_s;
            case SDLK_t:  
                return events::KeyCode::Key_t;
            case SDLK_u:  
                return events::KeyCode::Key_u;
            case SDLK_v:  
                return events::KeyCode::Key_v;
            case SDLK_w:  
                return events::KeyCode::Key_w;
            case SDLK_x:  
                return events::KeyCode::Key_x;
            case SDLK_y:  
                return events::KeyCode::Key_y;
            case SDLK_z:  
                return events::KeyCode::Key_z;
            case SDLK_CAPSLOCK:  
                return events::KeyCode::Capslock;
            case SDLK_F1:  
                return events::KeyCode::F1;
            case SDLK_F2:  
                return events::KeyCode::F2;
            case SDLK_F3:  
                return events::KeyCode::F3;
            case SDLK_F4:  
                return events::KeyCode::F4;
            case SDLK_F5:  
                return events::KeyCode::F5;
            case SDLK_F6:  
                return events::KeyCode::F6;
            case SDLK_F7:  
                return events::KeyCode::F7;
            case SDLK_F8:  
                return events::KeyCode::F8;
            case SDLK_F9:  
                return events::KeyCode::F9;
            case SDLK_F10:  
                return events::KeyCode::F10;
            case SDLK_F11:  
                return events::KeyCode::F11;
            case SDLK_F12:  
                return events::KeyCode::F12;
            case SDLK_PRINTSCREEN:  
                return events::KeyCode::Printscreen;
            case SDLK_SCROLLLOCK:  
                return events::KeyCode::Scrolllock;
            case SDLK_PAUSE:  
                return events::KeyCode::Pause;
            case SDLK_INSERT:  
                return events::KeyCode::Insert;
            case SDLK_HOME:  
                return events::KeyCode::Home;
            case SDLK_PAGEUP:  
                return events::KeyCode::Pageup;
            case SDLK_DELETE:  
                return events::KeyCode::Delete;
            case SDLK_END:  
                return events::KeyCode::End;
            case SDLK_PAGEDOWN:  
                return events::KeyCode::Pagedown;
            case SDLK_RIGHT:  
                return events::KeyCode::Right;
            case SDLK_LEFT:  
                return events::KeyCode::Left;
            case SDLK_DOWN:  
                return events::KeyCode::Down;
            case SDLK_UP:  
                return events::KeyCode::Up;
            case SDLK_NUMLOCKCLEAR:  
                return events::KeyCode::Numlockclear;
            case SDLK_KP_DIVIDE:  
                return events::KeyCode::KP_Divide;
            case SDLK_KP_MULTIPLY:  
                return events::KeyCode::KP_Multiply;
            case SDLK_KP_MINUS:  
                return events::KeyCode::KP_Minus;
            case SDLK_KP_PLUS:  
                return events::KeyCode::KP_Plus;
            case SDLK_KP_ENTER:  
                return events::KeyCode::KP_Enter;
            case SDLK_KP_1:  
                return events::KeyCode::KP_1;
            case SDLK_KP_2:  
                return events::KeyCode::KP_2;
            case SDLK_KP_3:  
                return events::KeyCode::KP_3;
            case SDLK_KP_4:  
                return events::KeyCode::KP_4;
            case SDLK_KP_5:  
                return events::KeyCode::KP_5;
            case SDLK_KP_6:  
                return events::KeyCode::KP_6;
            case SDLK_KP_7:  
                return events::KeyCode::KP_7;
            case SDLK_KP_8:  
                return events::KeyCode::KP_8;
            case SDLK_KP_9:  
                return events::KeyCode::KP_9;
            case SDLK_KP_0:  
                return events::KeyCode::KP_0;
            case SDLK_KP_PERIOD:  
                return events::KeyCode::KP_Period;
            case SDLK_LCTRL:  
                return events::KeyCode::LCtrl;
            case SDLK_LSHIFT:  
                return events::KeyCode::LShift;
            case SDLK_LALT:  
                return events::KeyCode::LAlt;
            case SDLK_LGUI:  
                return events::KeyCode::LSuper;
            case SDLK_RCTRL:  
                return events::KeyCode::RCtrl;
            case SDLK_RSHIFT:  
                return events::KeyCode::RShift;
            case SDLK_RALT:  
                return events::KeyCode::RAlt;
            case SDLK_RGUI:  
                return events::KeyCode::RSuper;
            default:
                return events::KeyCode::Unknown;
        }
    }

    int GetSDLKeyCode(events::KeyCode key)
    {
        switch (key)
        {
            case events::KeyCode::Return:
                return SDLK_RETURN; 
            case events::KeyCode::Escape:
                return SDLK_ESCAPE; 
            case events::KeyCode::Backspace:
                return SDLK_BACKSPACE; 
            case events::KeyCode::Tab:
                return SDLK_TAB; 
            case events::KeyCode::Space:
                return SDLK_SPACE; 
            case events::KeyCode::Exclaim:
                return SDLK_EXCLAIM; 
            case events::KeyCode::Quotedbl:
                return SDLK_QUOTEDBL; 
            case events::KeyCode::Hash:
                return SDLK_HASH; 
            case events::KeyCode::Percent:
                return SDLK_PERCENT; 
            case events::KeyCode::Dollar:
                return SDLK_DOLLAR; 
            case events::KeyCode::Ampersand:
                return SDLK_AMPERSAND; 
            case events::KeyCode::Quote:
                return SDLK_QUOTE; 
            case events::KeyCode::Leftparen:
                return SDLK_LEFTPAREN; 
            case events::KeyCode::Rightparen:
                return SDLK_RIGHTPAREN; 
            case events::KeyCode::Asterisk:
                return SDLK_ASTERISK; 
            case events::KeyCode::Plus:
                return SDLK_PLUS; 
            case events::KeyCode::Comma:
                return SDLK_COMMA; 
            case events::KeyCode::Minus:
                return SDLK_MINUS; 
            case events::KeyCode::Period:
                return SDLK_PERIOD; 
            case events::KeyCode::Slash:
                return SDLK_SLASH; 
            case events::KeyCode::Key_0:
                return SDLK_0; 
            case events::KeyCode::Key_1:
                return SDLK_1; 
            case events::KeyCode::Key_2:
                return SDLK_2; 
            case events::KeyCode::Key_3:
                return SDLK_3; 
            case events::KeyCode::Key_4:
                return SDLK_4; 
            case events::KeyCode::Key_5:
                return SDLK_5; 
            case events::KeyCode::Key_6:
                return SDLK_6; 
            case events::KeyCode::Key_7:
                return SDLK_7; 
            case events::KeyCode::Key_8:
                return SDLK_8; 
            case events::KeyCode::Key_9:
                return SDLK_9; 
            case events::KeyCode::Colon:
                return SDLK_COLON; 
            case events::KeyCode::Semicolon:
                return SDLK_SEMICOLON; 
            case events::KeyCode::Less:
                return SDLK_LESS; 
            case events::KeyCode::Equals:
                return SDLK_EQUALS; 
            case events::KeyCode::Greater:
                return SDLK_GREATER; 
            case events::KeyCode::Question:
                return SDLK_QUESTION; 
            case events::KeyCode::At:
                return SDLK_AT; 
            case events::KeyCode::Leftbracket:
                return SDLK_LEFTBRACKET; 
            case events::KeyCode::Backslash:
                return SDLK_BACKSLASH; 
            case events::KeyCode::Rightbracket:
                return SDLK_RIGHTBRACKET; 
            case events::KeyCode::Caret:
                return SDLK_CARET; 
            case events::KeyCode::Underscore:
                return SDLK_UNDERSCORE; 
            case events::KeyCode::Backquote:
                return SDLK_BACKQUOTE; 
            case events::KeyCode::Key_a:
                return SDLK_a; 
            case events::KeyCode::Key_b:
                return SDLK_b; 
            case events::KeyCode::Key_c:
                return SDLK_c; 
            case events::KeyCode::Key_d:
                return SDLK_d; 
            case events::KeyCode::Key_e:
                return SDLK_e; 
            case events::KeyCode::Key_f:
                return SDLK_f; 
            case events::KeyCode::Key_g:
                return SDLK_g; 
            case events::KeyCode::Key_h:
                return SDLK_h; 
            case events::KeyCode::Key_i:
                return SDLK_i; 
            case events::KeyCode::Key_j:
                return SDLK_j; 
            case events::KeyCode::Key_k:
                return SDLK_k; 
            case events::KeyCode::Key_l:
                return SDLK_l; 
            case events::KeyCode::Key_m:
                return SDLK_m; 
            case events::KeyCode::Key_n:
                return SDLK_n; 
            case events::KeyCode::Key_o:
                return SDLK_o; 
            case events::KeyCode::Key_p:
                return SDLK_p; 
            case events::KeyCode::Key_q:
                return SDLK_q; 
            case events::KeyCode::Key_r:
                return SDLK_r; 
            case events::KeyCode::Key_s:
                return SDLK_s; 
            case events::KeyCode::Key_t:
                return SDLK_t; 
            case events::KeyCode::Key_u:
                return SDLK_u; 
            case events::KeyCode::Key_v:
                return SDLK_v; 
            case events::KeyCode::Key_w:
                return SDLK_w; 
            case events::KeyCode::Key_x:
                return SDLK_x; 
            case events::KeyCode::Key_y:
                return SDLK_y; 
            case events::KeyCode::Key_z:
                return SDLK_z; 
            case events::KeyCode::Capslock:
                return SDLK_CAPSLOCK; 
            case events::KeyCode::F1:
                return SDLK_F1; 
            case events::KeyCode::F2:
                return SDLK_F2; 
            case events::KeyCode::F3:
                return SDLK_F3; 
            case events::KeyCode::F4:
                return SDLK_F4; 
            case events::KeyCode::F5:
                return SDLK_F5; 
            case events::KeyCode::F6:
                return SDLK_F6; 
            case events::KeyCode::F7:
                return SDLK_F7; 
            case events::KeyCode::F8:
                return SDLK_F8; 
            case events::KeyCode::F9:
                return SDLK_F9; 
            case events::KeyCode::F10:
                return SDLK_F10; 
            case events::KeyCode::F11:
                return SDLK_F11; 
            case events::KeyCode::F12:
                return SDLK_F12; 
            case events::KeyCode::Printscreen:
                return SDLK_PRINTSCREEN; 
            case events::KeyCode::Scrolllock:
                return SDLK_SCROLLLOCK; 
            case events::KeyCode::Pause:
                return SDLK_PAUSE; 
            case events::KeyCode::Insert:
                return SDLK_INSERT; 
            case events::KeyCode::Home:
                return SDLK_HOME; 
            case events::KeyCode::Pageup:
                return SDLK_PAGEUP; 
            case events::KeyCode::Delete:
                return SDLK_DELETE; 
            case events::KeyCode::End:
                return SDLK_END; 
            case events::KeyCode::Pagedown:
                return SDLK_PAGEDOWN; 
            case events::KeyCode::Right:
                return SDLK_RIGHT; 
            case events::KeyCode::Left:
                return SDLK_LEFT; 
            case events::KeyCode::Down:
                return SDLK_DOWN; 
            case events::KeyCode::Up:
                return SDLK_UP; 
            case events::KeyCode::Numlockclear:
                return SDLK_NUMLOCKCLEAR; 
            case events::KeyCode::KP_Divide:
                return SDLK_KP_DIVIDE; 
            case events::KeyCode::KP_Multiply:
                return SDLK_KP_MULTIPLY; 
            case events::KeyCode::KP_Minus:
                return SDLK_KP_MINUS; 
            case events::KeyCode::KP_Plus:
                return SDLK_KP_PLUS; 
            case events::KeyCode::KP_Enter:
                return SDLK_KP_ENTER; 
            case events::KeyCode::KP_1:
                return SDLK_KP_1; 
            case events::KeyCode::KP_2:
                return SDLK_KP_2; 
            case events::KeyCode::KP_3:
                return SDLK_KP_3; 
            case events::KeyCode::KP_4:
                return SDLK_KP_4; 
            case events::KeyCode::KP_5:
                return SDLK_KP_5; 
            case events::KeyCode::KP_6:
                return SDLK_KP_6; 
            case events::KeyCode::KP_7:
                return SDLK_KP_7; 
            case events::KeyCode::KP_8:
                return SDLK_KP_8; 
            case events::KeyCode::KP_9:
                return SDLK_KP_9; 
            case events::KeyCode::KP_0:
                return SDLK_KP_0; 
            case events::KeyCode::KP_Period:
                return SDLK_KP_PERIOD; 
            case events::KeyCode::LCtrl:
                return SDLK_LCTRL; 
            case events::KeyCode::LShift:
                return SDLK_LSHIFT; 
            case events::KeyCode::LAlt:
                return SDLK_LALT; 
            case events::KeyCode::LSuper:
                return SDLK_LGUI; 
            case events::KeyCode::RCtrl:
                return SDLK_RCTRL; 
            case events::KeyCode::RShift:
                return SDLK_RSHIFT; 
            case events::KeyCode::RAlt:
                return SDLK_RALT; 
            case events::KeyCode::RSuper:
                return SDLK_RGUI; 
            default:
                return SDLK_UNKNOWN;
        }
    }

    int GetSDLScanCode(events::KeyCode key)
    {
        switch (key)
        {
            case events::KeyCode::Return:
                return SDL_SCANCODE_RETURN; 
            case events::KeyCode::Escape:
                return SDL_SCANCODE_ESCAPE; 
            case events::KeyCode::Backspace:
                return SDL_SCANCODE_BACKSPACE; 
            case events::KeyCode::Tab:
                return SDL_SCANCODE_TAB; 
            case events::KeyCode::Space:
                return SDL_SCANCODE_SPACE; 
            case events::KeyCode::Quote:
                return SDL_SCANCODE_APOSTROPHE; 
            case events::KeyCode::Comma:
                return SDL_SCANCODE_COMMA; 
            case events::KeyCode::Minus:
                return SDL_SCANCODE_MINUS; 
            case events::KeyCode::Period:
                return SDL_SCANCODE_PERIOD; 
            case events::KeyCode::Slash:
                return SDL_SCANCODE_SLASH; 
            case events::KeyCode::Key_0:
                return SDL_SCANCODE_0; 
            case events::KeyCode::Key_1:
                return SDL_SCANCODE_1; 
            case events::KeyCode::Key_2:
                return SDL_SCANCODE_2; 
            case events::KeyCode::Key_3:
                return SDL_SCANCODE_3; 
            case events::KeyCode::Key_4:
                return SDL_SCANCODE_4; 
            case events::KeyCode::Key_5:
                return SDL_SCANCODE_5; 
            case events::KeyCode::Key_6:
                return SDL_SCANCODE_6; 
            case events::KeyCode::Key_7:
                return SDL_SCANCODE_7; 
            case events::KeyCode::Key_8:
                return SDL_SCANCODE_8; 
            case events::KeyCode::Key_9:
                return SDL_SCANCODE_9; 
            case events::KeyCode::Semicolon:
                return SDL_SCANCODE_SEMICOLON; 
            case events::KeyCode::Equals:
                return SDL_SCANCODE_EQUALS; 
            case events::KeyCode::Leftbracket:
                return SDL_SCANCODE_LEFTBRACKET; 
            case events::KeyCode::Backslash:
                return SDL_SCANCODE_BACKSLASH; 
            case events::KeyCode::Rightbracket:
                return SDL_SCANCODE_RIGHTBRACKET; 
            case events::KeyCode::Backquote:
                return SDL_SCANCODE_GRAVE; 
            case events::KeyCode::Key_a:
                return SDL_SCANCODE_A; 
            case events::KeyCode::Key_b:
                return SDL_SCANCODE_B; 
            case events::KeyCode::Key_c:
                return SDL_SCANCODE_C; 
            case events::KeyCode::Key_d:
                return SDL_SCANCODE_D; 
            case events::KeyCode::Key_e:
                return SDL_SCANCODE_E; 
            case events::KeyCode::Key_f:
                return SDL_SCANCODE_F; 
            case events::KeyCode::Key_g:
                return SDL_SCANCODE_G; 
            case events::KeyCode::Key_h:
                return SDL_SCANCODE_H; 
            case events::KeyCode::Key_i:
                return SDL_SCANCODE_I; 
            case events::KeyCode::Key_j:
                return SDL_SCANCODE_J; 
            case events::KeyCode::Key_k:
                return SDL_SCANCODE_K; 
            case events::KeyCode::Key_l:
                return SDL_SCANCODE_L; 
            case events::KeyCode::Key_m:
                return SDL_SCANCODE_M; 
            case events::KeyCode::Key_n:
                return SDL_SCANCODE_N; 
            case events::KeyCode::Key_o:
                return SDL_SCANCODE_O; 
            case events::KeyCode::Key_p:
                return SDL_SCANCODE_P; 
            case events::KeyCode::Key_q:
                return SDL_SCANCODE_Q; 
            case events::KeyCode::Key_r:
                return SDL_SCANCODE_R; 
            case events::KeyCode::Key_s:
                return SDL_SCANCODE_S; 
            case events::KeyCode::Key_t:
                return SDL_SCANCODE_T; 
            case events::KeyCode::Key_u:
                return SDL_SCANCODE_U; 
            case events::KeyCode::Key_v:
                return SDL_SCANCODE_V; 
            case events::KeyCode::Key_w:
                return SDL_SCANCODE_W; 
            case events::KeyCode::Key_x:
                return SDL_SCANCODE_X; 
            case events::KeyCode::Key_y:
                return SDL_SCANCODE_Y; 
            case events::KeyCode::Key_z:
                return SDL_SCANCODE_Z; 
            case events::KeyCode::Capslock:
                return SDL_SCANCODE_CAPSLOCK; 
            case events::KeyCode::F1:
                return SDL_SCANCODE_F1; 
            case events::KeyCode::F2:
                return SDL_SCANCODE_F2; 
            case events::KeyCode::F3:
                return SDL_SCANCODE_F3; 
            case events::KeyCode::F4:
                return SDL_SCANCODE_F4; 
            case events::KeyCode::F5:
                return SDL_SCANCODE_F5; 
            case events::KeyCode::F6:
                return SDL_SCANCODE_F6; 
            case events::KeyCode::F7:
                return SDL_SCANCODE_F7; 
            case events::KeyCode::F8:
                return SDL_SCANCODE_F8; 
            case events::KeyCode::F9:
                return SDL_SCANCODE_F9; 
            case events::KeyCode::F10:
                return SDL_SCANCODE_F10; 
            case events::KeyCode::F11:
                return SDL_SCANCODE_F11; 
            case events::KeyCode::F12:
                return SDL_SCANCODE_F12; 
            case events::KeyCode::Printscreen:
                return SDL_SCANCODE_PRINTSCREEN; 
            case events::KeyCode::Scrolllock:
                return SDL_SCANCODE_SCROLLLOCK; 
            case events::KeyCode::Pause:
                return SDL_SCANCODE_PAUSE; 
            case events::KeyCode::Insert:
                return SDL_SCANCODE_INSERT; 
            case events::KeyCode::Home:
                return SDL_SCANCODE_HOME; 
            case events::KeyCode::Pageup:
                return SDL_SCANCODE_PAGEUP; 
            case events::KeyCode::Delete:
                return SDL_SCANCODE_DELETE; 
            case events::KeyCode::End:
                return SDL_SCANCODE_END; 
            case events::KeyCode::Pagedown:
                return SDL_SCANCODE_PAGEDOWN; 
            case events::KeyCode::Right:
                return SDL_SCANCODE_RIGHT; 
            case events::KeyCode::Left:
                return SDL_SCANCODE_LEFT; 
            case events::KeyCode::Down:
                return SDL_SCANCODE_DOWN; 
            case events::KeyCode::Up:
                return SDL_SCANCODE_UP; 
            case events::KeyCode::Numlockclear:
                return SDL_SCANCODE_NUMLOCKCLEAR; 
            case events::KeyCode::KP_Divide:
                return SDL_SCANCODE_KP_DIVIDE; 
            case events::KeyCode::KP_Multiply:
                return SDL_SCANCODE_KP_MULTIPLY; 
            case events::KeyCode::KP_Minus:
                return SDL_SCANCODE_KP_MINUS; 
            case events::KeyCode::KP_Plus:
                return SDL_SCANCODE_KP_PLUS; 
            case events::KeyCode::KP_Enter:
                return SDL_SCANCODE_KP_ENTER; 
            case events::KeyCode::KP_1:
                return SDL_SCANCODE_KP_1; 
            case events::KeyCode::KP_2:
                return SDL_SCANCODE_KP_2; 
            case events::KeyCode::KP_3:
                return SDL_SCANCODE_KP_3; 
            case events::KeyCode::KP_4:
                return SDL_SCANCODE_KP_4; 
            case events::KeyCode::KP_5:
                return SDL_SCANCODE_KP_5; 
            case events::KeyCode::KP_6:
                return SDL_SCANCODE_KP_6; 
            case events::KeyCode::KP_7:
                return SDL_SCANCODE_KP_7; 
            case events::KeyCode::KP_8:
                return SDL_SCANCODE_KP_8; 
            case events::KeyCode::KP_9:
                return SDL_SCANCODE_KP_9; 
            case events::KeyCode::KP_0:
                return SDL_SCANCODE_KP_0; 
            case events::KeyCode::KP_Period:
                return SDL_SCANCODE_KP_PERIOD; 
            case events::KeyCode::LCtrl:
                return SDL_SCANCODE_LCTRL; 
            case events::KeyCode::LShift:
                return SDL_SCANCODE_LSHIFT; 
            case events::KeyCode::LAlt:
                return SDL_SCANCODE_LALT; 
            case events::KeyCode::LSuper:
                return SDL_SCANCODE_LGUI; 
            case events::KeyCode::RCtrl:
                return SDL_SCANCODE_RCTRL; 
            case events::KeyCode::RShift:
                return SDL_SCANCODE_RSHIFT; 
            case events::KeyCode::RAlt:
                return SDL_SCANCODE_RALT; 
            case events::KeyCode::RSuper:
                return SDL_SCANCODE_RGUI; 
            default:
                return SDL_SCANCODE_UNKNOWN;
        }
    }
}