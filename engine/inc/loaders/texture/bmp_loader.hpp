/*
# ______       ____   ___
#   |     \/   ____| |___|    
#   |     |   |   \  |   |       
#-----------------------------------------------------------------------
# Copyright 2022, tyra - https://github.com/h4570/tyra
# Licenced under Apache License 2.0
# André Guilherme <andregui17@outlook.com>
*/

#pragma once

#include "loaders/texture/base/texture_loader.hpp"
#include "renderer/core/texture/models/texture.hpp"
//#include "renderer/3d/bbox/bbox.hpp"
namespace Tyra {
    //TODO: Add a class for manage RGB and RGBA colors and if possible textures;
typedef struct 
{
    u8 r;
    u8 g;  
    u8 b;
} RGB;

class BmpLoader : public TextureLoader {     

public:   
    BmpLoader();
    ~BmpLoader();

    inline TextureBuilderData *load(const std::string &fullpath) {
        return load(fullpath.c_str());
    }       

    TextureBuilderData *load(const char* fullpath);

private:
    TextureBuilderData *result;
    u8 header[54]; 
    u32 width[18];
    u32 height[22];
    u32 dataOffset[10];   
    };
}