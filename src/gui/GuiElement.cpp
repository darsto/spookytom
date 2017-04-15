/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "GuiElement.h"

constexpr const unsigned int GuiElement::TYPE;

GuiElement::GuiElement(double x, double y, double width, double height, const std::string &tex, uint32_t color)
    : m_x(x),
      m_y(y),
      m_width(width),
      m_height(height),
      m_angle(0),
      m_tex(tex),
      m_color(color) {

}

bool GuiElement::contains(double coordX, double coordY) {
    return coordX >= x() && coordY >= y() && coordX <= x() + width() && coordY < y() + height();
}

double GuiElement::x() const {
    return m_x;
}

void GuiElement::x(double x) {
    m_x = x;
}

double GuiElement::y() const {
    return m_y;
}

void GuiElement::y(double y) {
    m_y = y;
}

double GuiElement::width() const {
    return m_width;
}

void GuiElement::width(double width) {
    GuiElement::m_width = width;
}

double GuiElement::height() const {
    return m_height;
}

void GuiElement::height(double height) {
    GuiElement::m_height = height;
}

double GuiElement::angle() const {
    return m_angle;
}

const std::string & GuiElement::texPos() const {
    return m_tex;
}

uint32_t GuiElement::color() const {
    return m_color;
}

GuiElement::~GuiElement() {}