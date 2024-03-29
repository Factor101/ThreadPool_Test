#pragma once
typedef struct RgbColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RgbColor;

typedef struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;

RgbColor HsvToRgb(HsvColor hsv) noexcept
{
    RgbColor rgb;
    unsigned char region, p, q, t;
    unsigned int h, s, v, remainder;

    if(hsv.s == 0)
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    // converting to 16 bit to prevent overflow
    h = hsv.h;
    s = hsv.s;
    v = hsv.v;

    region = h / 43;
    remainder = (h - (region * 43)) * 6;

    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch(region)
    {
        case 0:
        rgb.r = v;
        rgb.g = t;
        rgb.b = p;
        break;
        case 1:
        rgb.r = q;
        rgb.g = v;
        rgb.b = p;
        break;
        case 2:
        rgb.r = p;
        rgb.g = v;
        rgb.b = t;
        break;
        case 3:
        rgb.r = p;
        rgb.g = q;
        rgb.b = v;
        break;
        case 4:
        rgb.r = t;
        rgb.g = p;
        rgb.b = v;
        break;
        default:
        rgb.r = v;
        rgb.g = p;
        rgb.b = q;
        break;
    }

    return rgb;
}