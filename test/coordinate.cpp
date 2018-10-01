//*****************************************************************************
// Copyright 2017-2018 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************

#include <memory>
#include <string>

#include "gtest/gtest.h"

#include "ngraph/ngraph.hpp"
#include "util/ndarray.hpp"
#include "util/test_tools.hpp"

using namespace std;
using namespace ngraph;

TEST(coordinate, shape2d)
{
    auto ct = CoordinateTransform({2, 3});
    auto it = ct.begin();
    EXPECT_EQ(*it++, Coordinate({0, 0}));
    EXPECT_EQ(*it++, Coordinate({0, 1}));
    EXPECT_EQ(*it++, Coordinate({0, 2}));
    EXPECT_EQ(*it++, Coordinate({1, 0}));
    EXPECT_EQ(*it++, Coordinate({1, 1}));
    EXPECT_EQ(*it++, Coordinate({1, 2}));
    EXPECT_TRUE(it == ct.end());
}

TEST(coordinate, shape3d)
{
    auto ct = CoordinateTransform({2, 3, 4});
    auto it = ct.begin();
    EXPECT_EQ(*it++, Coordinate({0, 0, 0}));
    EXPECT_EQ(*it++, Coordinate({0, 0, 1}));
    EXPECT_EQ(*it++, Coordinate({0, 0, 2}));
    EXPECT_EQ(*it++, Coordinate({0, 0, 3}));
    EXPECT_EQ(*it++, Coordinate({0, 1, 0}));
    EXPECT_EQ(*it++, Coordinate({0, 1, 1}));
    EXPECT_EQ(*it++, Coordinate({0, 1, 2}));
    EXPECT_EQ(*it++, Coordinate({0, 1, 3}));
    EXPECT_EQ(*it++, Coordinate({0, 2, 0}));
    EXPECT_EQ(*it++, Coordinate({0, 2, 1}));
    EXPECT_EQ(*it++, Coordinate({0, 2, 2}));
    EXPECT_EQ(*it++, Coordinate({0, 2, 3}));
    EXPECT_EQ(*it++, Coordinate({1, 0, 0}));
    EXPECT_EQ(*it++, Coordinate({1, 0, 1}));
    EXPECT_EQ(*it++, Coordinate({1, 0, 2}));
    EXPECT_EQ(*it++, Coordinate({1, 0, 3}));
    EXPECT_EQ(*it++, Coordinate({1, 1, 0}));
    EXPECT_EQ(*it++, Coordinate({1, 1, 1}));
    EXPECT_EQ(*it++, Coordinate({1, 1, 2}));
    EXPECT_EQ(*it++, Coordinate({1, 1, 3}));
    EXPECT_EQ(*it++, Coordinate({1, 2, 0}));
    EXPECT_EQ(*it++, Coordinate({1, 2, 1}));
    EXPECT_EQ(*it++, Coordinate({1, 2, 2}));
    EXPECT_EQ(*it++, Coordinate({1, 2, 3}));
    EXPECT_TRUE(it == ct.end());
}

// CoordinateTransform(const Shape& source_shape,
//                     const Coordinate& source_start_corner,
//                     const Coordinate& source_end_corner,
//                     const Strides& source_strides,
//                     const AxisVector& source_axis_order,
//                     const CoordinateDiff& target_padding_below,
//                     const CoordinateDiff& target_padding_above,
//                     const Strides& source_dilation_strides);

TEST(coordinate, corner)
{
    Shape source_shape{10, 10};
    Coordinate source_start_corner = Coordinate{0, 0};
    Coordinate source_end_corner{source_shape};
    Strides source_strides = Strides(source_shape.size(), 1);
    AxisVector source_axis_order(source_shape.size());
    iota(source_axis_order.begin(), source_axis_order.end(), 0);
    CoordinateDiff target_padding_below = CoordinateDiff(source_shape.size(), 0);
    CoordinateDiff target_padding_above = CoordinateDiff(source_shape.size(), 0);
    Strides source_dilation_strides = Strides(source_shape.size(), 1);

    auto ct = CoordinateTransform(source_shape,
                                  source_start_corner,
                                  source_end_corner,
                                  source_strides,
                                  source_axis_order,
                                  target_padding_below,
                                  target_padding_above,
                                  source_dilation_strides);
    for (const Coordinate& c : ct)
    {
        cout << c << endl;
    }
}

TEST(coordinate, strides)
{
    Shape source_shape{10, 10};
    Coordinate source_start_corner = Coordinate{0, 0};
    Coordinate source_end_corner{source_shape};
    Strides source_strides = Strides(source_shape.size(), 1);
    AxisVector source_axis_order(source_shape.size());
    iota(source_axis_order.begin(), source_axis_order.end(), 0);
    CoordinateDiff target_padding_below = CoordinateDiff(source_shape.size(), 0);
    CoordinateDiff target_padding_above = CoordinateDiff(source_shape.size(), 0);
    Strides source_dilation_strides = Strides(source_shape.size(), 1);

    auto ct = CoordinateTransform(source_shape,
                                  source_start_corner,
                                  source_end_corner,
                                  source_strides,
                                  source_axis_order,
                                  target_padding_below,
                                  target_padding_above,
                                  source_dilation_strides);
    for (const Coordinate& c : ct)
    {
        cout << ct.to_source_coordinate(c) << endl;
    }
}

TEST(coordinate, axis_order)
{
    Shape source_shape{10, 10};
    Coordinate source_start_corner = Coordinate{0, 0};
    Coordinate source_end_corner{source_shape};
    Strides source_strides = Strides(source_shape.size(), 1);
    AxisVector source_axis_order(source_shape.size());
    iota(source_axis_order.begin(), source_axis_order.end(), 0);
    CoordinateDiff target_padding_below = CoordinateDiff(source_shape.size(), 0);
    CoordinateDiff target_padding_above = CoordinateDiff(source_shape.size(), 0);
    Strides source_dilation_strides = Strides(source_shape.size(), 1);

    auto ct = CoordinateTransform(source_shape,
                                  source_start_corner,
                                  source_end_corner,
                                  source_strides,
                                  source_axis_order,
                                  target_padding_below,
                                  target_padding_above,
                                  source_dilation_strides);

    for (const Coordinate& c : ct)
    {
        cout << c << endl;
    }
}

TEST(coordinate, padding)
{
    Shape source_shape{10, 10};
    Coordinate source_start_corner = Coordinate{0, 0};
    Coordinate source_end_corner{source_shape};
    Strides source_strides = Strides(source_shape.size(), 1);
    AxisVector source_axis_order(source_shape.size());
    iota(source_axis_order.begin(), source_axis_order.end(), 0);
    CoordinateDiff target_padding_below = CoordinateDiff(source_shape.size(), 0);
    CoordinateDiff target_padding_above = CoordinateDiff(source_shape.size(), 0);
    Strides source_dilation_strides = Strides(source_shape.size(), 1);

    auto ct = CoordinateTransform(source_shape,
                                  source_start_corner,
                                  source_end_corner,
                                  source_strides,
                                  source_axis_order,
                                  target_padding_below,
                                  target_padding_above,
                                  source_dilation_strides);

    for (const Coordinate& c : ct)
    {
        cout << c << endl;
    }
}

TEST(coordinate, dilation)
{
    Shape source_shape{10, 10};
    Coordinate source_start_corner = Coordinate{0, 0};
    Coordinate source_end_corner{source_shape};
    Strides source_strides = Strides(source_shape.size(), 1);
    AxisVector source_axis_order(source_shape.size());
    iota(source_axis_order.begin(), source_axis_order.end(), 0);
    CoordinateDiff target_padding_below = CoordinateDiff(source_shape.size(), 0);
    CoordinateDiff target_padding_above = CoordinateDiff(source_shape.size(), 0);
    Strides source_dilation_strides = Strides(source_shape.size(), 1);

    auto ct = CoordinateTransform(source_shape,
                                  source_start_corner,
                                  source_end_corner,
                                  source_strides,
                                  source_axis_order,
                                  target_padding_below,
                                  target_padding_above,
                                  source_dilation_strides);

    for (const Coordinate& c : ct)
    {
        cout << c << endl;
    }
}
