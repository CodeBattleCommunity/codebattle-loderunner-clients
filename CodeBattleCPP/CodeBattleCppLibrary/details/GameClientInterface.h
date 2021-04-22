#pragma once

#include <functional>

#include "../LodeRunnerAction.h"
#include "../GameBoard.h"

namespace details
{
    struct GameClient {
    virtual ~GameClient() = default;
    virtual void Run(std::function<LodeRunnerAction(const GameBoard &)> _message_handler) = 0;
};
} // namespace details
