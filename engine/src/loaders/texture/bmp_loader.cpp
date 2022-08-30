/*
# ______       ____   ___
#   |     \/   ____| |___|    
#   |     |   |   \  |   |       
#-----------------------------------------------------------------------
# Copyright 2022, tyra - https://github.com/h4570/tyra
# Licenced under Apache License 2.0
# André Guilherme <andregui17@outlook.com>
# NOTE: This is was based on: https://github.com/wolfysdl/tyrav1/blob/tyrav1-develop/src/engine/loaders/bmp_loader.cpp
*/

#include "debug/debug.hpp"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <string>
#include <draw_buffers.h>
#include "loaders/texture/bmp_loader.hpp"
#include "file/file_utils.hpp"

namespace Tyra {

BmpLoader::BmpLoader() {}

BmpLoader::~BmpLoader() {}

//Working: Hell yeah
TextureBuilderData *BmpLoader::load(const char *fullpath) {
    std::string path = fullpath;
    TYRA_ASSERT(!path.empty(), "The provided path is empty");

    auto filename = FileUtils::getFilenameFromPath(fullpath);

    FILE *file = fopen(fullpath, "rb");
    TYRA_ASSERT(file != nullptr, "Failed to load file"); 

    fread(header, sizeof(u8), 54, file);
    TYRA_ASSERT(header, "Failed to check the header itself!!!");

    auto* result = new TextureBuilderData();
    result->name = filename;

    TextureLoader::getTextureSize(result->width, result->height, result->bpp); 

    u64 rowPadded = (result->width * 3 + 3) & (~3);
    unsigned char row[rowPadded];

    //Offset file stream to raster data
    fseek(file, 10, SEEK_SET);
    RGB rgb;

//TODO: Add switch case for the detection of the bits..
    u32 x = 0;
    for (u32 i = 0; i < result->height; i++) {
        fread(&row, sizeof(unsigned char), sizeof(row), file);
        for (u32 j = 0; j < result->width * 3; j += 3) {
             // Convert (B, G, R) to (R, G, B)
            rgb.r = ((u32)x, row[j+2]);
            rgb.g = ((u32)x + 1, row[j + 1]);
            rgb.b = ((u32)x + 2, row[j]); 
            x += 3;
        }
    }
    fclose(file);
}

};