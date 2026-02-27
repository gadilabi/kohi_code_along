#pragma once

#include "defines.h"

#define DEFINE_KEY(name, code) KEY_##name = code

typedef enum button
{
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_MIDDlE,
	BUTTON_MAX_BUTTONS
} button_t;

typedef enum key
{
	/* Printable ASCII (32 - 126) mapped via DEFINE_KEY */
	DEFINE_KEY(SPACE, ' '),            /* 32 */
	DEFINE_KEY(ENTER, 0x0D),
	DEFINE_KEY(TAB, 0x09),
	DEFINE_KEY(SHIFT, 0x10),
	DEFINE_KEY(CONTROL, 0x11),
	DEFINE_KEY(ESCAPE, 0x1B),

	DEFINE_KEY(UP, 0x26),
	DEFINE_KEY(DOWN, 0x28),
	DEFINE_KEY(LEFT, 0x25),
	DEFINE_KEY(RIGHT, 0x27),

	DEFINE_KEY(EXCLAMATION, '!'),
	DEFINE_KEY(QUOTE, '\"'),
	DEFINE_KEY(HASH, '#'),
	DEFINE_KEY(DOLLAR, '$'),
	DEFINE_KEY(PERCENT, '%'),
	DEFINE_KEY(AMPERSAND, '&'),
	DEFINE_KEY(APOSTROPHE, '\''),

	DEFINE_KEY(LEFT_PAREN, '('),
	DEFINE_KEY(RIGHT_PAREN, ')'),
	DEFINE_KEY(ASTERISK, '*'),
	DEFINE_KEY(PLUS, '+'),
	DEFINE_KEY(COMMA, ','),
	DEFINE_KEY(MINUS, '-'),
	DEFINE_KEY(PERIOD, '.'),
	DEFINE_KEY(SLASH, '/'),

	DEFINE_KEY(DIGIT_0, '0'),
	DEFINE_KEY(DIGIT_1, '1'),
	DEFINE_KEY(DIGIT_2, '2'),
	DEFINE_KEY(DIGIT_3, '3'),
	DEFINE_KEY(DIGIT_4, '4'),
	DEFINE_KEY(DIGIT_5, '5'),
	DEFINE_KEY(DIGIT_6, '6'),
	DEFINE_KEY(DIGIT_7, '7'),
	DEFINE_KEY(DIGIT_8, '8'),
	DEFINE_KEY(DIGIT_9, '9'),

	DEFINE_KEY(COLON, ':'),
	DEFINE_KEY(SEMICOLON, ';'),
	DEFINE_KEY(LESS_THAN, '<'),
	DEFINE_KEY(EQUAL, '='),
	DEFINE_KEY(GREATER_THAN, '>'),
	DEFINE_KEY(QUESTION, '?'),
	DEFINE_KEY(AT, '@'),

	/* Uppercase letters */
	DEFINE_KEY(A, 'A'),
	DEFINE_KEY(B, 'B'),
	DEFINE_KEY(C, 'C'),
	DEFINE_KEY(D, 'D'),
	DEFINE_KEY(E, 'E'),
	DEFINE_KEY(F, 'F'),
	DEFINE_KEY(G, 'G'),
	DEFINE_KEY(H, 'H'),
	DEFINE_KEY(I, 'I'),
	DEFINE_KEY(J, 'J'),
	DEFINE_KEY(K, 'K'),
	DEFINE_KEY(L, 'L'),
	DEFINE_KEY(M, 'M'),
	DEFINE_KEY(N, 'N'),
	DEFINE_KEY(O, 'O'),
	DEFINE_KEY(P, 'P'),
	DEFINE_KEY(Q, 'Q'),
	DEFINE_KEY(R, 'R'),
	DEFINE_KEY(S, 'S'),
	DEFINE_KEY(T, 'T'),
	DEFINE_KEY(U, 'U'),
	DEFINE_KEY(V, 'V'),
	DEFINE_KEY(W, 'W'),
	DEFINE_KEY(X, 'X'),
	DEFINE_KEY(Y, 'Y'),
	DEFINE_KEY(Z, 'Z'),

	DEFINE_KEY(LEFT_BRACKET, '['),
	DEFINE_KEY(BACKSLASH, '\\'),
	DEFINE_KEY(RIGHT_BRACKET, ']'),
	DEFINE_KEY(CARET, '^'),
	DEFINE_KEY(UNDERSCORE, '_'),
	DEFINE_KEY(BACKTICK, '`'),

	/* Lowercase letters */
	DEFINE_KEY(a, 'a'),
	DEFINE_KEY(b, 'b'),
	DEFINE_KEY(c, 'c'),
	DEFINE_KEY(d, 'd'),
	DEFINE_KEY(e, 'e'),
	DEFINE_KEY(f, 'f'),
	DEFINE_KEY(g, 'g'),
	DEFINE_KEY(h, 'h'),
	DEFINE_KEY(i, 'i'),
	DEFINE_KEY(j, 'j'),
	DEFINE_KEY(k, 'k'),
	DEFINE_KEY(l, 'l'),
	DEFINE_KEY(m, 'm'),
	DEFINE_KEY(n, 'n'),
	DEFINE_KEY(o, 'o'),
	DEFINE_KEY(p, 'p'),
	DEFINE_KEY(q, 'q'),
	DEFINE_KEY(r, 'r'),
	DEFINE_KEY(s, 's'),
	DEFINE_KEY(t, 't'),
	DEFINE_KEY(u, 'u'),
	DEFINE_KEY(v, 'v'),
	DEFINE_KEY(w, 'w'),
	DEFINE_KEY(x, 'x'),
	DEFINE_KEY(y, 'y'),
	DEFINE_KEY(z, 'z'),

	DEFINE_KEY(LEFT_BRACE, '{'),
	DEFINE_KEY(PIPE, '|'),
	DEFINE_KEY(RIGHT_BRACE, '}'),
	DEFINE_KEY(TILDE, '~')

} key_t;

void input_initialize();
void input_shutdown();
void input_update(f64 delta_time);

// keyboard input
KAPI b8 input_is_keyup(key_t key);
KAPI b8 input_is_keydown(key_t key);
KAPI b8 input_was_keyup(key_t key);
KAPI b8 input_was_keydown(key_t key);

void input_process_key(key_t key, b8 is_pressed);

// mouse input
KAPI b8 input_is_button_down(button_t btn);
KAPI b8 input_is_button_up(button_t btn);
KAPI b8 input_was_button_down(button_t btn);
KAPI b8 input_was_button_up(button_t btn);
KAPI b8 input_get_mouse_position(i32* x, i32* y);
KAPI b8 input_get_previous_mouse_position(i32* x, i32* y);

void input_process_button(button_t, b8 is_pressed);
void input_process_mouse_move(i16 x, i16 y);
void input_process_mouse_wheel(i8 z_delta);
