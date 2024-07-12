#ifndef BN_AFFINE_BG_ITEMS_LAND_H
#define BN_AFFINE_BG_ITEMS_LAND_H

#include "bn_affine_bg_item.h"

//{{BLOCK(land_bn_gfx)

//======================================================================
//
//	land_bn_gfx, 1024x1024@8, 
//	+ palette 64 entries, not compressed
//	+ 200 tiles (t reduced) not compressed
//	+ affine map, not compressed, 128x128 
//	Total size: 128 + 12800 + 16384 = 29312
//
//	Time-stamp: 2024-07-09, 13:57:19
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LAND_BN_GFX_H
#define GRIT_LAND_BN_GFX_H

#define land_bn_gfxTilesLen 12800
extern const bn::tile land_bn_gfxTiles[400];

#define land_bn_gfxMapLen 16384
extern const bn::affine_bg_map_cell land_bn_gfxMap[16384];

#define land_bn_gfxPalLen 128
extern const bn::color land_bn_gfxPal[64];

#endif // GRIT_LAND_BN_GFX_H

//}}BLOCK(land_bn_gfx)

namespace bn::affine_bg_items
{
    constexpr inline affine_bg_item land(
            affine_bg_tiles_item(span<const tile>(land_bn_gfxTiles, 400), compression_type::NONE), 
            bg_palette_item(span<const color>(land_bn_gfxPal, 64), bpp_mode::BPP_8, compression_type::NONE),
            affine_bg_map_item(land_bn_gfxMap[0], size(128, 128), compression_type::NONE, 1, false));
}

#endif

