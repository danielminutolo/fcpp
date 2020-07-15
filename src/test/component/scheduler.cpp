// Copyright © 2020 Giorgio Audrito. All Rights Reserved.

#include "gtest/gtest.h"

#include "lib/component/base.hpp"
#include "lib/component/randomizer.hpp"
#include "lib/component/scheduler.hpp"

using namespace fcpp;
using namespace fcpp::component::tags;


struct meantag {};
struct devtag {};

using seq_mul = sequence::multiple<distribution::constant<times_t, 52, 10>, 3>;
using seq_per = sequence::periodic<distribution::constant<times_t, 15, 10>, distribution::uniform_t<times_t, 2, 10, 1, meantag, devtag>, distribution::constant<times_t, 62, 10>, distribution::constant<size_t, 5>>;

using combo1 = component::combine_spec<
    component::scheduler<round_schedule<seq_mul>>,
    component::randomizer<>,
    component::base<>
>;
using combo2 = component::combine_spec<
    component::scheduler<round_schedule<seq_per>>,
    component::scheduler<round_schedule<seq_mul>>,
    component::randomizer<>,
    component::base<>
>;
using combo3 = component::combine_spec<component::scheduler<round_schedule<seq_mul>>,component::base<>>;
using combo4 = component::combine_spec<
    component::scheduler<round_schedule<seq_per,seq_mul>>,
    component::randomizer<>,
    component::base<>
>;


TEST(SchedulerTest, Single) {
    combo1::net  network{common::make_tagged_tuple<>()};
    combo1::node device{network, common::make_tagged_tuple<component::tags::uid,seq_mul>(7,'b')};
    double d;
    d = device.next();
    device.update();
    EXPECT_DOUBLE_EQ(5.2, d);
    d = device.next();
    device.update();
    EXPECT_DOUBLE_EQ(5.2, d);
    d = device.next();
    device.update();
    EXPECT_DOUBLE_EQ(5.2, d);
    d = device.next();
    device.update();
    EXPECT_EQ(TIME_MAX, d);
    d = device.next();
    device.update();
    EXPECT_EQ(TIME_MAX, d);
}

TEST(SchedulerTest, Multiple) {
    {
        combo2::net  network{common::make_tagged_tuple<>()};
        combo2::node device{network, common::make_tagged_tuple<component::tags::uid,devtag>(7,0.0)};
        double d;
        d = device.next();
        device.update();
        EXPECT_DOUBLE_EQ(1.5, d);
        d = device.next();
        device.update();
        EXPECT_DOUBLE_EQ(3.5, d);
        d = device.next();
        EXPECT_DOUBLE_EQ(5.2, d);
        d = device.next();
        device.update();
        EXPECT_DOUBLE_EQ(5.2, d);
        d = device.next();
        device.update();
        EXPECT_DOUBLE_EQ(5.2, d);
        d = device.next();
        device.update();
        EXPECT_DOUBLE_EQ(5.2, d);
        d = device.next();
        device.update();
        EXPECT_DOUBLE_EQ(5.5, d);
        d = device.next();
        device.update();
        EXPECT_EQ(TIME_MAX, d);
        d = device.next();
        device.update();
        EXPECT_EQ(TIME_MAX, d);
    }
    {
        combo4::net  network{common::make_tagged_tuple<>()};
        combo4::node device{network, common::make_tagged_tuple<component::tags::uid,devtag>(7,0.0)};
        double d;
        d = device.next();
        device.update();
        EXPECT_DOUBLE_EQ(1.5, d);
        d = device.next();
        device.update();
        EXPECT_DOUBLE_EQ(3.5, d);
        d = device.next();
        EXPECT_DOUBLE_EQ(5.2, d);
        d = device.next();
        device.update();
        EXPECT_DOUBLE_EQ(5.2, d);
        d = device.next();
        device.update();
        EXPECT_DOUBLE_EQ(5.2, d);
        d = device.next();
        device.update();
        EXPECT_DOUBLE_EQ(5.2, d);
        d = device.next();
        device.update();
        EXPECT_DOUBLE_EQ(5.5, d);
        d = device.next();
        device.update();
        EXPECT_EQ(TIME_MAX, d);
        d = device.next();
        device.update();
        EXPECT_EQ(TIME_MAX, d);
    }
}

TEST(SchedulerTest, NoRandomizer) {
    combo1::net  network{common::make_tagged_tuple<>()};
    combo1::node device{network, common::make_tagged_tuple<component::tags::uid,seq_mul>(7,'b')};
    double d;
    d = device.next();
    device.update();
    EXPECT_DOUBLE_EQ(5.2, d);
    d = device.next();
    device.update();
    EXPECT_DOUBLE_EQ(5.2, d);
    d = device.next();
    device.update();
    EXPECT_DOUBLE_EQ(5.2, d);
    d = device.next();
    device.update();
    EXPECT_EQ(TIME_MAX, d);
    d = device.next();
    device.update();
    EXPECT_EQ(TIME_MAX, d);
}
