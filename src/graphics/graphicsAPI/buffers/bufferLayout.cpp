#include <pch.h>
#include "bufferLayout.h"

namespace graphics {

    BufferLayout::BufferLayout(std::vector<BufferLayoutElement> layout) {
        uint32_t offset = 0;
        for (auto& element : layout) {
            element.offset = offset;

            offset += element.count * GetShaderDataTypeSize(element.type);
        }
        m_stride = offset;

        m_layout = layout;
    }

}
