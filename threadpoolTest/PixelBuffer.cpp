#include "PixelBuffer.h"

PixelBuffer::PixelBuffer(size_t width, size_t height)
    : width(width), height(height), rawData(new unsigned char[width * height * 3])
{
}


PixelBuffer::~PixelBuffer()
{
    delete[] this->rawData;
}

void const PixelBuffer::setPixel(
    const int x,
    const int y,
    const unsigned char r,
    const unsigned char g,
    const unsigned char b//, 
    //const unsigned char a
) noexcept 
{
    const auto baseIndex = (y * this->width + x) * 3;
    this->rawData[baseIndex] = r;
    this->rawData[baseIndex + 1] = g;
    this->rawData[baseIndex + 2] = b;
}


// overload for using index
void const PixelBuffer::setPixel(
    const int baseIndex,
    const unsigned char r,
    const unsigned char g,
    const unsigned char b
) noexcept
{
    this->rawData[baseIndex] = r;
    this->rawData[baseIndex + 1] = g;
    this->rawData[baseIndex + 2] = b;
}

inline unsigned char* const PixelBuffer::getData() const noexcept
{
    return rawData;
}

const std::vector<int> PixelBuffer::getChunkBounds(const int nChunks) const noexcept
{
    const int area = this->width * this->height;
    const int chunkLen = area / nChunks;

    std::vector<int> ret = { 0 };

    for(int i = chunkLen - 1; i < area - 1; i += chunkLen)
    {
        if(i > area) {
            ret.emplace_back(i - area);
        } else {
            ret.emplace_back(i);
        }
    }

    ret.emplace_back(area - 1);
    return ret;
}