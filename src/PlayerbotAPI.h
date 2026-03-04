/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license, you may redistribute it
 * and/or modify it under version 3 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_PLAYERBOTAPI_H
#define _PLAYERBOT_PLAYERBOTAPI_H

/**
 * Umbrella header for mod-playerbots API.
 * Include this in external modules to interact with and extend playerbots.
 */

#include "Bot/PlayerbotModAPI.h"

// Forward declarations and common enums from mod-playerbots
#include "SharedDefines.h"

// Re-expose BotState for API users
#ifndef BOT_STATE_MAX
enum BotState
{
    BOT_STATE_COMBAT = 0,
    BOT_STATE_NON_COMBAT = 1,
    BOT_STATE_DEAD = 2,

    BOT_STATE_MAX
};
#endif

#endif
