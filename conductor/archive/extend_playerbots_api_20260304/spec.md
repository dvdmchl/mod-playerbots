# Specification: Extend mod-playerbots API

## Goal
Modify `mod-playerbots` to provide a stable, external API and script hooks that allow other AzerothCore modules to interact with, control, and extend playerbots without modifying the core `mod-playerbots` source code.

## Requirements

### 1. Bot Lifecycle Hooks
Expose hooks to detect and react to bot lifecycle events:
- `OnBotLogin`: Called when a bot character is logged into the world.
- `OnBotLogout`: Called when a bot character is logged out.
- `OnBotCommand`: Intercept or respond to commands sent to bots.

### 2. Custom Logic Registration API
Provide a mechanism for external modules to register:
- **Custom Strategies:** New behavioral strategies (e.g., "gatherer") that can be toggled on/off.
- **Custom Actions:** New tasks bots can perform (e.g., "moveToNode", "gatherHerb").
- **Custom Triggers:** New conditions for actions (e.g., "nearbyResourceDetected").

### 3. State & Management Interface
A clean interface for external modules to:
- Query bot properties (e.g., level, skills, current behavior).
- Get a bot's `PlayerbotAI` or `PlayerbotMgr` object by character GUID.
- Trigger specific actions or strategies on a bot programmatically.

### 4. Developer Documentation
- A header file designed for external module inclusion.
- A README explaining how to link to and use the `mod-playerbots` API.

## Success Criteria
- An external module can successfully toggle a "gatherer" strategy on a bot.
- An external module can receive a notification when a specific bot logs in.
- No core modifications to `mod-playerbots` are required once the API is exposed.
