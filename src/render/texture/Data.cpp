/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

/**
 * TODO: Refactor this class using c++ operators
 */

#include "Data.h"
#include "exceptions.h"
#include "util/files.h"
#include <SOIL.h>

using namespace texture;

Data::Data(uint32_t width, uint32_t height, uint32_t channels)
    : m_width(width),
      m_height(height),
      m_channels(channels),
      m_data(std::make_unique<uint8_t[]>(width * height * channels)) {

    if (width == 0 || height == 0 || channels == 0) {
        char msg[100];
        snprintf(msg, sizeof(msg), "Trying to create invalid texture (width:%d, height:%d, channels:%d).", width, height, channels);
        throw invalid_texture_error(msg);    }

}

Data::Data(const std::string &fileName, int flags) {
    int width, height, channels;
    std::string path = util::files::path<util::files::type::texture>(fileName).c_str();
    std::unique_ptr<uint8_t[]> data(SOIL_load_image(path.c_str(), &width, &height, &channels, flags & 0x7)); // use mask of 3 LSB
    if (width > 0 && height > 0 && channels > 0) {
        m_width = (uint32_t) width;
        m_height = (uint32_t) height;
        m_channels = (uint32_t) channels;
        m_data = std::move(data);
    } else {
        char msg[150];
        snprintf(msg, sizeof(msg), "Trying to load invalid texture (path: %s, width:%d, height:%d, channels:%d).", path.c_str(), width, height, channels);
        throw invalid_texture_error(msg);
    }
}

uint32_t Data::width() const {
    return m_width;
}

uint32_t Data::height() const {
    return m_height;
}

uint32_t Data::channels() const {
    return m_channels;
}

const std::unique_ptr<uint8_t[], std::default_delete<uint8_t[]>> &Data::getData() const {
    return m_data;
}

std::unique_ptr<uint8_t[]> &Data::getData() {
    return m_data;
}
