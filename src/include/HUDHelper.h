#ifndef TRAPDOOR_MINIHUD_HELPER_H
#define TRAPDOOR_MINIHUD_HELPER_H
#include <array>
#include <unordered_map>

#include "CommandHelper.h"

namespace trapdoor {
    enum HUDInfoType {
        Base = 0,
        Mspt = 1,
        Vill = 2,
        Redstone = 3,
        Counter = 4,
        Chunk = 5,
        Unknown = 6,
    };

    struct PlayerHudInfo {
        std::string realName;
        bool enable;
        std::array<int, 7> config{};
    };

    class HUDHelper {
       public:
        inline ActionResult setAble(bool able) {
            this->enable = able;
            return {"Success", true};
        }

        void tick();

        ActionResult modifyPlayerInfo(const std::string& playerName, const std::string& item,
                                      int op);

        ActionResult setAblePlayer(const std::string& playerName, bool able);

       private:
        void tickChunk();

        bool enable = false;
        std::unordered_map<std::string, PlayerHudInfo> playerInfos;
    };

}  // namespace trapdoor

#endif
