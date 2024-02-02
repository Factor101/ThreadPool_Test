#pragma once
#include <vector>

class PixelBuffer
{
    private:
    size_t width;
    size_t height;
    unsigned char* rawData;

    public:
    PixelBuffer(size_t width, size_t height);

    ~PixelBuffer();

    inline size_t const getWidth() const noexcept
    {
    	return this->width;
    }

    inline size_t const getHeight() const noexcept
    {
        return this->height;
    }

    void const setPixel(
        const int x,
        const int y,
        const unsigned char r,
        const unsigned char g,
        const unsigned char b//, 
        //const unsigned char a
    ) noexcept;

    void const setPixel(
        const int i,
        const unsigned char r,
        const unsigned char g,
        const unsigned char b
    ) noexcept;

    inline unsigned char* const getData() const noexcept;

    const std::vector<int> getChunkBounds(const int nChunks) const noexcept;
};