# Playerbots API Guide

This guide describes how to use the `mod-playerbots` API to create standalone modules that interact with or extend bot behavior in AzerothCore.

## Getting Started

To use the API, include the umbrella header in your module:

```cpp
#include "PlayerbotAPI.h"
```

## Bot Lifecycle Hooks

You can register callbacks that trigger when a bot logs in or out of the world.

### Registering Hooks

```cpp
void MyModule_OnBotLogin(Player* bot) {
    // Perform logic when a bot logs in
    LOG_INFO("module", "Bot joined the world: {}", bot->GetName());
}

// In your module's script loader or equivalent
sPlayerbotModAPI.RegisterOnBotLogin(MyModule_OnBotLogin);
sPlayerbotModAPI.RegisterOnBotLogout(MyModule_OnBotLogout);
```

## Dynamic AI Object Registration

External modules can register their own Strategies, Actions, and Triggers.

### Registering a Custom Strategy

```cpp
class MyCustomStrategy : public Strategy {
    // Implementation...
};

Strategy* CreateMyCustomStrategy(PlayerbotAI* ai) {
    return new MyCustomStrategy(ai);
}

// Register the strategy
sPlayerbotModAPI.RegisterStrategy("my-strategy", CreateMyCustomStrategy);
```

Once registered, `mod-playerbots` will be able to instantiate your strategy by name.

## Controlling Bots Programmatically

The API allows you to toggle strategies on specific bots using their GUID.

### Adding/Removing Strategies

```cpp
ObjectGuid botGuid = ...;
// Add a strategy to the bot's non-combat engine
sPlayerbotModAPI.AddStrategyToBot(botGuid, "my-strategy", BOT_STATE_NON_COMBAT);

// Remove a strategy
sPlayerbotModAPI.RemoveStrategyFromBot(botGuid, "my-strategy", BOT_STATE_NON_COMBAT);
```

## Practical Example: mod-guild-gatherers

If you are building a gathering module, you might:
1. Register a `gatherer` strategy.
2. Use `OnBotLogin` to check if a bot belongs to a "Gathering Guild".
3. If it does, call `AddStrategyToBot(bot->GetGUID(), "gatherer", BOT_STATE_NON_COMBAT)`.

The bot will now use your custom gathering logic whenever it is not in combat.
