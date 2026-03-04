# Product Guidelines: mod-playerbots

## Prose Style
- **Clarity & Precision:** Use direct and technical language when describing bot behaviors, strategies, and configurations.
- **Terminology:** Maintain consistency with World of Warcraft and AzerothCore terminology (e.g., "aggro," "tank," "healer," "pulling," "grinding").
- **Documentation:** Provide clear and concise descriptions for each bot command and configuration setting.

## User Experience (UX)
- **Intuitive Chat Interface:** Bot commands should follow a logical and consistent syntax.
- **Immediate Feedback:** Bots should provide clear and immediate feedback to player commands.
- **Graceful Failure:** When a bot cannot perform an action, it should inform the player with a clear explanation (e.g., "I am out of mana," "I cannot reach that target").
- **Realism over Optimization:** Prioritize player-like behavior (e.g., looting items, eating/drinking between pulls) over absolute combat efficiency.

## Design & Aesthetics
- **Consistent Branding:** Use the project's iconography and name consistently across all platforms and documentation.
- **UI Integration:** Ensure that bot management through client AddOns feels seamless and native to the WoW user interface.

## Technical Standards
- **Performance First:** All AI logic and bot behaviors must be optimized to minimize impact on server performance.
- **Scalability:** The system should scale gracefully from a few bots to thousands of concurrent characters.
- **Stability:** New features and bug fixes must be rigorously tested on all supported platforms to ensure server stability.
