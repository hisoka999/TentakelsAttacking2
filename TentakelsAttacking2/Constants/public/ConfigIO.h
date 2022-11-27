//
// Purpur Tentakel
// 27.10.2022
//

#pragma once

/**
 * checks if any config exists.
 * if so the config gets loaded and the values get set in the constats structs.
 * else a new config is generated.
 */
void LoadConfig();
/**
 * overrides the old config
 * saves the config by exporting the values in the chonstants structs.
 * is unsed to generate a complete new config.
 */
void SaveConfig();
