# Copilot Agent Instructions for mod-playerbots in this workspace

## Context

This workspace is primarily for developing `mod-guildgatherers`.
`mod-playerbots` is a dependency and integration surface for that work.

## Hard scope limits

- You may only modify files under:
  - `modules/mod-playerbots`
  - `modules/mod-guildgatherers`
- Do not change files anywhere else in the repository.
- Do not make unrelated improvements in `mod-playerbots`.

## When editing mod-playerbots

- Only make changes that are required to support
  `mod-guildgatherers`.
- Prefer additive integration points, hooks, or narrowly scoped command
  handling over broad behavior changes.
- Preserve existing playerbot behavior for non-guild-gatherer
  scenarios.
- Keep compatibility with upstream playerbot systems and conventions.

## Feature goal to support

`mod-guildgatherers` should allow a player to command bots from the
player's guild to gather materials such as ore, herbs, leather, and
cloth, then deliver those materials to the guild bank.

Example target command:

- `farm copper 200`

Support work in this module should enable that flow without turning
`mod-playerbots` into the primary home of the feature.
