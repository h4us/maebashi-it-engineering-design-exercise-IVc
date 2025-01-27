/**
 * Scancode to character map, for US keyboard
 */

const sc2char = new Array(223).fill(null);
const sc2char_md_shift = new Array(223).fill(null);

const us_latin = 'abcdefghijklmnopqrstuvwxyz1234567890';
const us_latin_md_shift = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()';

for (let i = 0; i < us_latin.length; i++) {
  sc2char[i + 0x04] = us_latin.charAt(i);
  sc2char_md_shift[i + 0x04] = us_latin_md_shift.charAt(i);
}

const us_symbols = [
  ' ', '-', '=', '[', ']', '\\', null, ';', '\'', '`', ',', '.', '/'
];
const us_symbols_md_shift = [
  ' ', '_', '+', '{', '}', '|', null, ':', '"', '~', '<', '>', '?'
];
for (let i = 0; i < us_symbols.length; i++) {
  sc2char[i + 0x2c] = us_symbols[i];
  sc2char_md_shift[i + 0x2c] = us_symbols_md_shift[i];
}

export default [
  sc2char,
  sc2char_md_shift
];

/*
export declare enum Key {
    Escape = 0,
    F1 = 1,
    F2 = 2,
    F3 = 3,
    F4 = 4,
    F5 = 5,
    F6 = 6,
    F7 = 7,
    F8 = 8,
    F9 = 9,
    F10 = 10,
    F11 = 11,
    F12 = 12,
    F13 = 13,
    F14 = 14,
    F15 = 15,
    F16 = 16,
    F17 = 17,
    F18 = 18,
    F19 = 19,
    F20 = 20,
    F21 = 21,
    F22 = 22,
    F23 = 23,
    F24 = 24,
    Print = 25,
    ScrollLock = 26,
    Pause = 27,
    Grave = 28,
    Num1 = 29,
    Num2 = 30,
    Num3 = 31,
    Num4 = 32,
    Num5 = 33,
    Num6 = 34,
    Num7 = 35,
    Num8 = 36,
    Num9 = 37,
    Num0 = 38,
    Minus = 39,
    Equal = 40,
    Backspace = 41,
    Insert = 42,
    Home = 43,
    PageUp = 44,
    NumLock = 45,
    NumPadEqual = 46,
    Divide = 47,
    Multiply = 48,
    Subtract = 49,
    Tab = 50,
    Q = 51,
    W = 52,
    E = 53,
    R = 54,
    T = 55,
    Y = 56,
    U = 57,
    I = 58,
    O = 59,
    P = 60,
    LeftBracket = 61,
    RightBracket = 62,
    Backslash = 63,
    Delete = 64,
    End = 65,
    PageDown = 66,
    NumPad7 = 67,
    NumPad8 = 68,
    NumPad9 = 69,
    Add = 70,
    CapsLock = 71,
    A = 72,
    S = 73,
    D = 74,
    F = 75,
    G = 76,
    H = 77,
    J = 78,
    K = 79,
    L = 80,
    Semicolon = 81,
    Quote = 82,
    Return = 83,
    NumPad4 = 84,
    NumPad5 = 85,
    NumPad6 = 86,
    LeftShift = 87,
    Z = 88,
    X = 89,
    C = 90,
    V = 91,
    B = 92,
    N = 93,
    M = 94,
    Comma = 95,
    Period = 96,
    Slash = 97,
    RightShift = 98,
    Up = 99,
    NumPad1 = 100,
    NumPad2 = 101,
    NumPad3 = 102,
    Enter = 103,
    LeftControl = 104,
    LeftSuper = 105,
    LeftWin = 106,
    LeftCmd = 107,
    LeftAlt = 108,
    Space = 109,
    RightAlt = 110,
    RightSuper = 111,
    RightWin = 112,
    RightCmd = 113,
    Menu = 114,
    RightControl = 115,
    Fn = 116,
    Left = 117,
    Down = 118,
    Right = 119,
    NumPad0 = 120,
    Decimal = 121,
    Clear = 122,
    AudioMute = 123,
    AudioVolDown = 124,
    AudioVolUp = 125,
    AudioPlay = 126,
    AudioStop = 127,
    AudioPause = 128,
    AudioPrev = 129,
    AudioNext = 130,
    AudioRewind = 131,
    AudioForward = 132,
    AudioRepeat = 133,
    AudioRandom = 134
}
 */
