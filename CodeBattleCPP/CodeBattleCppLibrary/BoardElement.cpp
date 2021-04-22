#include "BoardElement.h"
#include <cassert>

namespace
{
    constexpr const char *const kNONE = u8" ";
    constexpr const char *const kBRICK = u8"#";
    constexpr const char *const kINDESTRUCTIBLE_WALL = u8"☼";
    constexpr const char *const kDRILL_PIT = u8"*";
    constexpr const char *const kYELLOW_GOLD = u8"$";
    constexpr const char *const kGREEN_GOLD = u8"&";
    constexpr const char *const kRED_GOLD = u8"@";
    constexpr const char *const kLADDER = u8"H";
    constexpr const char *const kPIPE = u8"~";
    constexpr const char *const kPIT_FILL_1 = u8"1";
    constexpr const char *const kPIT_FILL_2 = u8"2";
    constexpr const char *const kPIT_FILL_3 = u8"3";
    constexpr const char *const kPIT_FILL_4 = u8"4";
    constexpr const char *const kPORTAL = u8"⊛";
    constexpr const char *const kTHE_SHADOW_PILL = u8"S";

    constexpr const char *const kHERO_DIE = u8"Ѡ";
    constexpr const char *const kHERO_DRILL_LEFT = u8"Я";
    constexpr const char *const kHERO_DRILL_RIGHT = u8"R";
    constexpr const char *const kHERO_LADDER = u8"Y";
    constexpr const char *const kHERO_LEFT = u8"◄";
    constexpr const char *const kHERO_RIGHT = u8"►";
    constexpr const char *const kHERO_FALL_LEFT = u8"]";
    constexpr const char *const kHERO_FALL_RIGHT = u8"[";
    constexpr const char *const kHERO_PIPE_LEFT = u8"{";
    constexpr const char *const kHERO_PIPE_RIGHT = u8"}";

    constexpr const char *const kHERO_SHADOW_DIE = u8"x";
    constexpr const char *const kHERO_SHADOW_DRILL_LEFT = u8"⊰";
    constexpr const char *const kHERO_SHADOW_DRILL_RIGHT = u8"⊱";
    constexpr const char *const kHERO_SHADOW_LADDER = u8"⍬";
    constexpr const char *const kHERO_SHADOW_LEFT = u8"⊲";
    constexpr const char *const kHERO_SHADOW_RIGHT = u8"⊳";
    constexpr const char *const kHERO_SHADOW_FALL_LEFT = u8"⊅";
    constexpr const char *const kHERO_SHADOW_FALL_RIGHT = u8"⊄";
    constexpr const char *const kHERO_SHADOW_PIPE_LEFT = u8"⋜";
    constexpr const char *const kHERO_SHADOW_PIPE_RIGHT = u8"⋝";

    constexpr const char *const kOTHER_HERO_DIE = u8"Z";
    constexpr const char *const kOTHER_HERO_LEFT = u8")";
    constexpr const char *const kOTHER_HERO_RIGHT = u8"(";
    constexpr const char *const kOTHER_HERO_DRILL_LEFT = u8"⌋";
    constexpr const char *const kOTHER_HERO_DRILL_RIGHT = u8"⌊";
    constexpr const char *const kOTHER_HERO_FALL_LEFT = u8"⊐";
    constexpr const char *const kOTHER_HERO_FALL_RIGHT = u8"⊏";
    constexpr const char *const kOTHER_HERO_LADDER = u8"U";
    constexpr const char *const kOTHER_HERO_PIPE_LEFT = u8"Э";
    constexpr const char *const kOTHER_HERO_PIPE_RIGHT = u8"Є";

    constexpr const char *const kOTHER_HERO_SHADOW_DIE = u8"⋈";
    constexpr const char *const kOTHER_HERO_SHADOW_LEFT = u8"⋊";
    constexpr const char *const kOTHER_HERO_SHADOW_RIGHT = u8"⋉";
    constexpr const char *const kOTHER_HERO_SHADOW_LADDER = u8"⋕";
    constexpr const char *const kOTHER_HERO_SHADOW_PIPE_LEFT = u8"⊣";
    constexpr const char *const kOTHER_HERO_SHADOW_PIPE_RIGHT = u8"⊢";
    constexpr const char *const kOTHER_HERO_SHADOW_DRILL_LEFT = u8"⋰";
    constexpr const char *const kOTHER_HERO_SHADOW_DRILL_RIGHT = u8"⋱";
    constexpr const char *const kOTHER_HERO_SHADOW_FALL_LEFT = u8"⋣";
    constexpr const char *const kOTHER_HERO_SHADOW_FALL_RIGHT = u8"⋢";

    constexpr const char *const kENEMY_LADDER = u8"Q";
    constexpr const char *const kENEMY_LEFT = u8"«";
    constexpr const char *const kENEMY_RIGHT = u8"»";
    constexpr const char *const kENEMY_PIPE_LEFT = u8"<";
    constexpr const char *const kENEMY_PIPE_RIGHT = u8">";
    constexpr const char *const kENEMY_PIT = u8"X";
}

BoardElement BoardElementFromString(const std::string &str)
{
    if (str == kNONE)
        return BoardElement::NONE;
    if (str == kBRICK)
        return BoardElement::BRICK;
    if (str == kINDESTRUCTIBLE_WALL)
        return BoardElement::INDESTRUCTIBLE_WALL;
    if (str == kDRILL_PIT)
        return BoardElement::DRILL_PIT;
    if (str == kYELLOW_GOLD)
        return BoardElement::YELLOW_GOLD;
    if (str == kGREEN_GOLD)
        return BoardElement::GREEN_GOLD;
    if (str == kRED_GOLD)
        return BoardElement::RED_GOLD;
    if (str == kLADDER)
        return BoardElement::LADDER;
    if (str == kPIPE)
        return BoardElement::PIPE;
    if (str == kPIT_FILL_1)
        return BoardElement::PIT_FILL_1;
    if (str == kPIT_FILL_2)
        return BoardElement::PIT_FILL_2;
    if (str == kPIT_FILL_3)
        return BoardElement::PIT_FILL_3;
    if (str == kPIT_FILL_4)
        return BoardElement::PIT_FILL_4;
    if (str == kPORTAL)
        return BoardElement::PORTAL;
    if (str == kTHE_SHADOW_PILL)
        return BoardElement::THE_SHADOW_PILL;
    if (str == kHERO_DIE)
        return BoardElement::HERO_DIE;
    if (str == kHERO_DRILL_LEFT)
        return BoardElement::HERO_DRILL_LEFT;
    if (str == kHERO_DRILL_RIGHT)
        return BoardElement::HERO_DRILL_RIGHT;
    if (str == kHERO_LADDER)
        return BoardElement::HERO_LADDER;
    if (str == kHERO_LEFT)
        return BoardElement::HERO_LEFT;
    if (str == kHERO_RIGHT)
        return BoardElement::HERO_RIGHT;
    if (str == kHERO_FALL_LEFT)
        return BoardElement::HERO_FALL_LEFT;
    if (str == kHERO_FALL_RIGHT)
        return BoardElement::HERO_FALL_RIGHT;
    if (str == kHERO_PIPE_LEFT)
        return BoardElement::HERO_PIPE_LEFT;
    if (str == kHERO_PIPE_RIGHT)
        return BoardElement::HERO_PIPE_RIGHT;
    if (str == kHERO_SHADOW_DIE)
        return BoardElement::HERO_SHADOW_DIE;
    if (str == kHERO_SHADOW_DRILL_LEFT)
        return BoardElement::HERO_SHADOW_DRILL_LEFT;
    if (str == kHERO_SHADOW_DRILL_RIGHT)
        return BoardElement::HERO_SHADOW_DRILL_RIGHT;
    if (str == kHERO_SHADOW_LADDER)
        return BoardElement::HERO_SHADOW_LADDER;
    if (str == kHERO_SHADOW_LEFT)
        return BoardElement::HERO_SHADOW_LEFT;
    if (str == kHERO_SHADOW_RIGHT)
        return BoardElement::HERO_SHADOW_RIGHT;
    if (str == kHERO_SHADOW_FALL_LEFT)
        return BoardElement::HERO_SHADOW_FALL_LEFT;
    if (str == kHERO_SHADOW_FALL_RIGHT)
        return BoardElement::HERO_SHADOW_FALL_RIGHT;
    if (str == kHERO_SHADOW_PIPE_LEFT)
        return BoardElement::HERO_SHADOW_PIPE_LEFT;
    if (str == kHERO_SHADOW_PIPE_RIGHT)
        return BoardElement::HERO_SHADOW_PIPE_RIGHT;
    if (str == kOTHER_HERO_DIE)
        return BoardElement::OTHER_HERO_DIE;
    if (str == kOTHER_HERO_DRILL_LEFT)
        return BoardElement::OTHER_HERO_DRILL_LEFT;
    if (str == kOTHER_HERO_DRILL_RIGHT)
        return BoardElement::OTHER_HERO_DRILL_RIGHT;
    if (str == kOTHER_HERO_FALL_LEFT)
        return BoardElement::OTHER_HERO_FALL_LEFT;
    if (str == kOTHER_HERO_FALL_RIGHT)
        return BoardElement::OTHER_HERO_FALL_RIGHT;
    if (str == kOTHER_HERO_LEFT)
        return BoardElement::OTHER_HERO_LEFT;
    if (str == kOTHER_HERO_RIGHT)
        return BoardElement::OTHER_HERO_RIGHT;
    if (str == kOTHER_HERO_LADDER)
        return BoardElement::OTHER_HERO_LADDER;
    if (str == kOTHER_HERO_PIPE_LEFT)
        return BoardElement::OTHER_HERO_PIPE_LEFT;
    if (str == kOTHER_HERO_PIPE_RIGHT)
        return BoardElement::OTHER_HERO_PIPE_RIGHT;
    if (str == kOTHER_HERO_SHADOW_DIE)
        return BoardElement::OTHER_HERO_SHADOW_DIE;
    if (str == kOTHER_HERO_SHADOW_DRILL_LEFT)
        return BoardElement::OTHER_HERO_SHADOW_DRILL_LEFT;
    if (str == kOTHER_HERO_SHADOW_DRILL_RIGHT)
        return BoardElement::OTHER_HERO_SHADOW_DRILL_RIGHT;
    if (str == kOTHER_HERO_SHADOW_FALL_LEFT)
        return BoardElement::OTHER_HERO_SHADOW_FALL_LEFT;
    if (str == kOTHER_HERO_SHADOW_FALL_RIGHT)
        return BoardElement::OTHER_HERO_SHADOW_FALL_RIGHT;
    if (str == kOTHER_HERO_SHADOW_LEFT)
        return BoardElement::OTHER_HERO_SHADOW_LEFT;
    if (str == kOTHER_HERO_SHADOW_RIGHT)
        return BoardElement::OTHER_HERO_SHADOW_RIGHT;
    if (str == kOTHER_HERO_SHADOW_LADDER)
        return BoardElement::OTHER_HERO_SHADOW_LADDER;
    if (str == kOTHER_HERO_SHADOW_PIPE_LEFT)
        return BoardElement::OTHER_HERO_SHADOW_PIPE_LEFT;
    if (str == kOTHER_HERO_SHADOW_PIPE_RIGHT)
        return BoardElement::OTHER_HERO_SHADOW_PIPE_RIGHT;
    if (str == kENEMY_LADDER)
        return BoardElement::ENEMY_LADDER;
    if (str == kENEMY_LEFT)
        return BoardElement::ENEMY_LEFT;
    if (str == kENEMY_RIGHT)
        return BoardElement::ENEMY_RIGHT;
    if (str == kENEMY_PIPE_LEFT)
        return BoardElement::ENEMY_PIPE_LEFT;
    if (str == kENEMY_PIPE_RIGHT)
        return BoardElement::ENEMY_PIPE_RIGHT;
    if (str == kENEMY_PIT)
        return BoardElement::ENEMY_PIT;

    assert(false);
    return BoardElement::NONE;
}

namespace std
{
    std::string to_string(BoardElement element)
    {
        switch (element)
        {
        case BoardElement::NONE:
            return kNONE;
        case BoardElement::BRICK:
            return kBRICK;
        case BoardElement::INDESTRUCTIBLE_WALL:
            return kINDESTRUCTIBLE_WALL;
        case BoardElement::DRILL_PIT:
            return kDRILL_PIT;
        case BoardElement::YELLOW_GOLD:
            return kYELLOW_GOLD;
        case BoardElement::GREEN_GOLD:
            return kGREEN_GOLD;
        case BoardElement::RED_GOLD:
            return kRED_GOLD;
        case BoardElement::LADDER:
            return kLADDER;
        case BoardElement::PIPE:
            return kPIPE;
        case BoardElement::PIT_FILL_1:
            return kPIT_FILL_1;
        case BoardElement::PIT_FILL_2:
            return kPIT_FILL_2;
        case BoardElement::PIT_FILL_3:
            return kPIT_FILL_3;
        case BoardElement::PIT_FILL_4:
            return kPIT_FILL_4;
        case BoardElement::PORTAL:
            return kPORTAL;
        case BoardElement::THE_SHADOW_PILL:
            return kTHE_SHADOW_PILL;
        case BoardElement::HERO_DIE:
            return kHERO_DIE;
        case BoardElement::HERO_DRILL_LEFT:
            return kHERO_DRILL_LEFT;
        case BoardElement::HERO_DRILL_RIGHT:
            return kHERO_DRILL_RIGHT;
        case BoardElement::HERO_LADDER:
            return kHERO_LADDER;
        case BoardElement::HERO_LEFT:
            return kHERO_LEFT;
        case BoardElement::HERO_RIGHT:
            return kHERO_RIGHT;
        case BoardElement::HERO_FALL_LEFT:
            return kHERO_FALL_LEFT;
        case BoardElement::HERO_FALL_RIGHT:
            return kHERO_FALL_RIGHT;
        case BoardElement::HERO_PIPE_LEFT:
            return kHERO_PIPE_LEFT;
        case BoardElement::HERO_PIPE_RIGHT:
            return kHERO_PIPE_RIGHT;
        case BoardElement::HERO_SHADOW_DIE:
            return kHERO_SHADOW_DIE;
        case BoardElement::HERO_SHADOW_DRILL_LEFT:
            return kHERO_SHADOW_DRILL_LEFT;
        case BoardElement::HERO_SHADOW_DRILL_RIGHT:
            return kHERO_SHADOW_DRILL_RIGHT;
        case BoardElement::HERO_SHADOW_LADDER:
            return kHERO_SHADOW_LADDER;
        case BoardElement::HERO_SHADOW_LEFT:
            return kHERO_SHADOW_LEFT;
        case BoardElement::HERO_SHADOW_RIGHT:
            return kHERO_SHADOW_RIGHT;
        case BoardElement::HERO_SHADOW_FALL_LEFT:
            return kHERO_SHADOW_FALL_LEFT;
        case BoardElement::HERO_SHADOW_FALL_RIGHT:
            return kHERO_SHADOW_FALL_RIGHT;
        case BoardElement::HERO_SHADOW_PIPE_LEFT:
            return kHERO_SHADOW_PIPE_LEFT;
        case BoardElement::HERO_SHADOW_PIPE_RIGHT:
            return kHERO_SHADOW_PIPE_RIGHT;
        case BoardElement::OTHER_HERO_DIE:
            return kOTHER_HERO_DIE;
        case BoardElement::OTHER_HERO_DRILL_LEFT:
            return kOTHER_HERO_DRILL_LEFT;
        case BoardElement::OTHER_HERO_DRILL_RIGHT:
            return kOTHER_HERO_DRILL_RIGHT;
        case BoardElement::OTHER_HERO_FALL_LEFT:
            return kOTHER_HERO_FALL_LEFT;
        case BoardElement::OTHER_HERO_FALL_RIGHT:
            return kOTHER_HERO_FALL_RIGHT;
        case BoardElement::OTHER_HERO_LEFT:
            return kOTHER_HERO_LEFT;
        case BoardElement::OTHER_HERO_RIGHT:
            return kOTHER_HERO_RIGHT;
        case BoardElement::OTHER_HERO_LADDER:
            return kOTHER_HERO_LADDER;
        case BoardElement::OTHER_HERO_PIPE_LEFT:
            return kOTHER_HERO_PIPE_LEFT;
        case BoardElement::OTHER_HERO_PIPE_RIGHT:
            return kOTHER_HERO_PIPE_RIGHT;
        case BoardElement::OTHER_HERO_SHADOW_DIE:
            return kOTHER_HERO_SHADOW_DIE;
        case BoardElement::OTHER_HERO_SHADOW_DRILL_LEFT:
            return kOTHER_HERO_SHADOW_DRILL_LEFT;
        case BoardElement::OTHER_HERO_SHADOW_DRILL_RIGHT:
            return kOTHER_HERO_SHADOW_DRILL_RIGHT;
        case BoardElement::OTHER_HERO_SHADOW_FALL_LEFT:
            return kOTHER_HERO_SHADOW_FALL_LEFT;
        case BoardElement::OTHER_HERO_SHADOW_FALL_RIGHT:
            return kOTHER_HERO_SHADOW_FALL_RIGHT;
        case BoardElement::OTHER_HERO_SHADOW_LEFT:
            return kOTHER_HERO_SHADOW_LEFT;
        case BoardElement::OTHER_HERO_SHADOW_RIGHT:
            return kOTHER_HERO_SHADOW_RIGHT;
        case BoardElement::OTHER_HERO_SHADOW_LADDER:
            return kOTHER_HERO_SHADOW_LADDER;
        case BoardElement::OTHER_HERO_SHADOW_PIPE_LEFT:
            return kOTHER_HERO_SHADOW_PIPE_LEFT;
        case BoardElement::OTHER_HERO_SHADOW_PIPE_RIGHT:
            return kOTHER_HERO_SHADOW_PIPE_RIGHT;
        case BoardElement::ENEMY_LADDER:
            return kENEMY_LADDER;
        case BoardElement::ENEMY_LEFT:
            return kENEMY_LEFT;
        case BoardElement::ENEMY_RIGHT:
            return kENEMY_RIGHT;
        case BoardElement::ENEMY_PIPE_LEFT:
            return kENEMY_PIPE_LEFT;
        case BoardElement::ENEMY_PIPE_RIGHT:
            return kENEMY_PIPE_RIGHT;
        case BoardElement::ENEMY_PIT:
            return kENEMY_PIT;
        default:
            assert(false);
            return kNONE;
        }
    }
}