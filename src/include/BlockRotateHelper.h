#ifndef TRAPDOOR_BLOCK_ROTATE_H
#define TRAPDOOR_BLOCK_ROTATE_H

// clang-format off
#include "Global.h"
#include <MC/BlockPos.hpp>
#include <MC/BlockSource.hpp>
#include <MC/BlockInstance.hpp>
#include <MC/Vec3.hpp>
#include "CommandHelper.h"
// clang-format on

namespace trapdoor {

    ActionResult setBlockRotationAble(bool able);
    bool rotateBlock(BlockSource* bs, BlockInstance* bi, const Vec3& clickPos, unsigned char face);
    void initRotateBlockHelper();
}  // namespace trapdoor

#endif