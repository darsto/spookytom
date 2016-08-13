/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "gtest/gtest.h"

#include "render/texture/Packer.h"

using namespace texture;

class TestPacker : public Packer {
public:
    TestPacker(uint32_t expectedWidth)
        : Packer(),
          m_expectedSize(expectedWidth){
    }

    using Node = Packer::Node;
    using Packer::nodes;

    uint32_t m_expectedSize;
};

TestPacker basicSquarePacker(bool sort) {
    TestPacker data(6);
    if (sort) {
        data.add(Rectangle(3, 3));
        data.add(Rectangle(3, 3));
        data.add(Rectangle(2, 2));
        data.add(Rectangle(2, 2));
        data.add(Rectangle(1, 1));
        data.add(Rectangle(1, 1));
        data.add(Rectangle(1, 1));
    } else {
        data.add(Rectangle(1, 1));
        data.add(Rectangle(3, 3));
        data.add(Rectangle(2, 2));
        data.add(Rectangle(1, 1));
        data.add(Rectangle(2, 2));
        data.add(Rectangle(1, 1));
        data.add(Rectangle(3, 3));

    }
    return data;
}

TestPacker basicRectanglePacker(bool sort) {
    TestPacker data(6);
    if (sort) {
        data.add(Rectangle(3, 3));
        data.add(Rectangle(3, 2));
        data.add(Rectangle(1, 3));
        data.add(Rectangle(1, 2));
        data.add(Rectangle(2, 1));
        data.add(Rectangle(2, 1));
        data.add(Rectangle(2, 1));
        data.add(Rectangle(1, 1));
    } else {
        data.add(Rectangle(1, 2));
        data.add(Rectangle(2, 1));
        data.add(Rectangle(3, 2));
        data.add(Rectangle(2, 1));
        data.add(Rectangle(3, 3));
        data.add(Rectangle(2, 1));
        data.add(Rectangle(1, 1));
        data.add(Rectangle(1, 3));

    }
    return data;
}

void EXPECT_EQ_TEX(uint32_t width, uint32_t height, const Rectangle &tex) {
    EXPECT_EQ(width, tex.width());
    EXPECT_EQ(height, tex.height());
}

TEST(TexturePackerTest, binTreeSquaresSorted) {
    TestPacker packer = basicSquarePacker(true);

    packer.pack();
    const TestPacker::Node *node = packer.nodes();

    EXPECT_EQ(packer.m_expectedSize, packer.size().width());
    EXPECT_EQ(packer.m_expectedSize, packer.size().height());

    EXPECT_EQ_TEX(3, 3, node->rectangle());
    EXPECT_EQ_TEX(3, 3, node->right()->rectangle());
    EXPECT_EQ_TEX(2, 2, node->down()->rectangle());
    EXPECT_EQ_TEX(2, 2, node->down()->right()->rectangle());
    EXPECT_EQ_TEX(1, 1, node->down()->right()->right()->rectangle());
    EXPECT_EQ_TEX(1, 1, node->down()->right()->right()->right()->rectangle());
    EXPECT_EQ_TEX(1, 1, node->down()->right()->right()->down()->rectangle());

    EXPECT_EQ(nullptr, node->right()->right());
    EXPECT_EQ(nullptr, node->right()->down());
    EXPECT_EQ(nullptr, node->down()->right()->right()->right()->right());
    EXPECT_EQ(nullptr, node->down()->right()->right()->right()->down());
    EXPECT_EQ(nullptr, node->down()->right()->right()->down()->right());
    EXPECT_EQ(nullptr, node->down()->right()->right()->down()->down());
    EXPECT_EQ(nullptr, node->down()->right()->down());
    EXPECT_EQ(nullptr, node->down()->down());
}

TEST(TexturePackerTest, binTreeRectanglesSorted) {
    TestPacker packer = basicRectanglePacker(true);

    packer.pack();
    const TestPacker::Node *node = packer.nodes();

    EXPECT_EQ(packer.m_expectedSize, packer.size().width());
    EXPECT_EQ(packer.m_expectedSize, packer.size().height());

    EXPECT_EQ_TEX(3, 3, node->rectangle());
    EXPECT_EQ_TEX(3, 2, node->right()->rectangle());
    EXPECT_EQ_TEX(2, 1, node->right()->down()->rectangle());
    EXPECT_EQ_TEX(1, 1, node->right()->down()->right()->rectangle());
    EXPECT_EQ_TEX(1, 3, node->down()->rectangle());
    EXPECT_EQ_TEX(2, 1, node->down()->right()->rectangle());
    EXPECT_EQ_TEX(2, 1, node->down()->right()->right()->rectangle());
    EXPECT_EQ_TEX(1, 2, node->down()->right()->down()->rectangle());

    EXPECT_EQ(nullptr, node->right()->right());
    EXPECT_EQ(nullptr, node->right()->down()->right()->right());
    EXPECT_EQ(nullptr, node->right()->down()->right()->down());
    EXPECT_EQ(nullptr, node->right()->down()->down());
    EXPECT_EQ(nullptr, node->down()->right()->right()->right());
    EXPECT_EQ(nullptr, node->down()->right()->right()->down());
    EXPECT_EQ(nullptr, node->down()->right()->down()->right());
    EXPECT_EQ(nullptr, node->down()->right()->down()->down());
    EXPECT_EQ(nullptr, node->down()->down());
}

TEST(TexturePackerTest, binTreeSquaresUnorted) {
    TestPacker packer = basicSquarePacker(false);

    packer.pack();
    const TestPacker::Node *node = packer.nodes();

    EXPECT_EQ(packer.m_expectedSize, packer.size().width());
    EXPECT_EQ(packer.m_expectedSize, packer.size().height());

    EXPECT_EQ_TEX(3, 3, node->rectangle());
    EXPECT_EQ_TEX(3, 3, node->right()->rectangle());
    EXPECT_EQ_TEX(2, 2, node->down()->rectangle());
    EXPECT_EQ_TEX(2, 2, node->down()->right()->rectangle());
    EXPECT_EQ_TEX(1, 1, node->down()->right()->right()->rectangle());
    EXPECT_EQ_TEX(1, 1, node->down()->right()->right()->right()->rectangle());
    EXPECT_EQ_TEX(1, 1, node->down()->right()->right()->down()->rectangle());

    EXPECT_EQ(nullptr, node->right()->right());
    EXPECT_EQ(nullptr, node->right()->down());
    EXPECT_EQ(nullptr, node->down()->right()->right()->right()->right());
    EXPECT_EQ(nullptr, node->down()->right()->right()->right()->down());
    EXPECT_EQ(nullptr, node->down()->right()->right()->down()->right());
    EXPECT_EQ(nullptr, node->down()->right()->right()->down()->down());
    EXPECT_EQ(nullptr, node->down()->right()->down());
    EXPECT_EQ(nullptr, node->down()->down());
}

TEST(TexturePackerTest, binTreeRectanglesUnsorted) {
    TestPacker packer = basicRectanglePacker(false);

    packer.pack();
    const TestPacker::Node *node = packer.nodes();

    EXPECT_EQ(packer.m_expectedSize, packer.size().width());
    EXPECT_EQ(packer.m_expectedSize, packer.size().height());

    EXPECT_EQ_TEX(3, 3, node->rectangle());
    EXPECT_EQ_TEX(3, 2, node->right()->rectangle());
    EXPECT_EQ_TEX(2, 1, node->right()->down()->rectangle());
    EXPECT_EQ_TEX(1, 1, node->right()->down()->right()->rectangle());
    EXPECT_EQ_TEX(1, 3, node->down()->rectangle());
    EXPECT_EQ_TEX(2, 1, node->down()->right()->rectangle());
    EXPECT_EQ_TEX(2, 1, node->down()->right()->right()->rectangle());
    EXPECT_EQ_TEX(1, 2, node->down()->right()->down()->rectangle());

    EXPECT_EQ(nullptr, node->right()->right());
    EXPECT_EQ(nullptr, node->right()->down()->right()->right());
    EXPECT_EQ(nullptr, node->right()->down()->right()->down());
    EXPECT_EQ(nullptr, node->right()->down()->down());
    EXPECT_EQ(nullptr, node->down()->right()->right()->right());
    EXPECT_EQ(nullptr, node->down()->right()->right()->down());
    EXPECT_EQ(nullptr, node->down()->right()->down()->right());
    EXPECT_EQ(nullptr, node->down()->right()->down()->down());
    EXPECT_EQ(nullptr, node->down()->down());
}