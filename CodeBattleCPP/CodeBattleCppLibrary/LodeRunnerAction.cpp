#include "LodeRunnerAction.h"

#include <cassert>

namespace {
    constexpr const char* const kDrillAction = "ACT";
    constexpr const char* const kDrillLeftAction = "ACT,LEFT";
    constexpr const char* const kDrillRightAction = "ACT,RIGHT";
    constexpr const char* const kGoDownAction = "DOWN";
    constexpr const char* const kGoLeftAction = "LEFT";
    constexpr const char* const kGoRightAction = "RIGHT";
    constexpr const char* const kGoUpAction = "UP";
    constexpr const char* const kSuicideAction = "ACT(0)";
}

LodeRunnerAction LodeRunnerActionFromString(const std::string& str) {
    if(str==kDrillAction)
        return LodeRunnerAction::DRILL;
    if(str==kDrillLeftAction)
        return LodeRunnerAction::DRILL_LEFT;
    if(str==kDrillRightAction)
        return LodeRunnerAction::DRILL_RIGHT;
    if(str==kGoDownAction)
        return LodeRunnerAction::GO_DOWN;
    if(str==kGoLeftAction)
        return LodeRunnerAction::GO_LEFT;
    if(str==kGoRightAction)
        return LodeRunnerAction::GO_RIGHT;
    if(str==kGoUpAction)
        return LodeRunnerAction::GO_UP;
    if(str== kSuicideAction)
        return LodeRunnerAction::SUICIDE;

    assert(("Given string contains invalid LodeRunnerAction", false));
    return LodeRunnerAction::SUICIDE;
}

namespace std
{
    std::string to_string(LodeRunnerAction action) {
        switch (action) {
        case LodeRunnerAction::DRILL:
            return kDrillAction;
        case LodeRunnerAction::DRILL_LEFT:
            return kDrillLeftAction;
        case LodeRunnerAction::DRILL_RIGHT:
            return kDrillRightAction;
        case LodeRunnerAction::GO_DOWN:
            return kGoDownAction;
        case LodeRunnerAction::GO_LEFT:
            return kGoLeftAction;
        case LodeRunnerAction::GO_RIGHT:
            return kGoRightAction;
        case LodeRunnerAction::GO_UP:
            return kGoUpAction;
        case LodeRunnerAction::SUICIDE:
            return kSuicideAction;
        default:
            assert(("Ivalid value of LodeRunnerAction enumeration", false));
            return "";
        }
    }
}