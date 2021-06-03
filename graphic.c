
// #define CHARACTER_WIDTH 24
// #define CHARACTER_HEIGHT 48
#ifndef GRAPHIC_C
#define GRAPHIC_C
const unsigned char character_graphic[] = {
    0x00, 0x18, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20,
    0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x10, 0x20,
    0x40, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x20, 0x10, 0x0F, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x40, 0x30, 0x0F, 0x30, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x10, 0x0C, 0x02,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0C, 0x10, 0x60, 0x80,
    0x00, 0x00, 0x00, 0x00};

// #define BOW_WIDTH 40
// #define BOW_HEGIHT 32

const unsigned char bow_release[] = {
    0x00, 0x28, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x02, 0x04,
    0x04, 0x08, 0x10, 0x20, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x87, 0xF8, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xC0, 0x30, 0x0F, 0x00, 0x00, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x20, 0x10,
    0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00};

const unsigned char bow_tense[] = {
    0x00, 0x28, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x40, 0x20, 0x20, 0x10, 0x08, 0x04, 0x02, 0x02, 0x04, 0x04, 0x08,
    0x10, 0x20, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xE0, 0xC0, 0xA0, 0x90, 0x90,
    0x88, 0x84, 0x82, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0xA0, 0xA0, 0xC7, 0xF8, 0x00, 0x00, 0x00,
    0x00, 0x20, 0x30, 0x38, 0x2C, 0x34, 0x16, 0x1A, 0x0F, 0x05, 0x07, 0x03,
    0x01, 0x02, 0x04, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xC2, 0x31,
    0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x20, 0x20, 0x10, 0x10, 0x08,
    0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
#endif