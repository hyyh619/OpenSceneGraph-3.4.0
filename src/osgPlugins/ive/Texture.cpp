/**********************************************************************
*
*    FILE:            Texture.cpp
*
*    DESCRIPTION:    Read/Write osg::Texture in binary format to disk.
*
*    CREATED BY:        Auto generated by iveGenerated
*                    and later modified by Rune Schmidt Jensen.
*
*    HISTORY:        Created 20.3.2003
*
*    Copyright 2003 VR-C
**********************************************************************/

#include "Exception.h"
#include "Texture.h"
#include "Object.h"

using namespace ive;

void Texture::write(DataOutputStream *out)
{
    // Write Texture's identification.
    out->writeInt(IVETEXTURE);
    // If the osg class is inherited by any other class we should also write this to file.
    osg::Object *obj = dynamic_cast<osg::Object*>(this);
    if (obj)
    {
        ((ive::Object*)(obj))->write(out);
    }
    else
        out_THROW_EXCEPTION("Texture::write(): Could not cast this osg::Texture to an osg::Object.");

    // Write Texture's properties.
    out->writeInt(_wrap_s);
    out->writeInt(_wrap_t);
    out->writeInt(_wrap_r);

    out->writeInt(_min_filter);
    out->writeInt(_mag_filter);
    out->writeFloat(_maxAnisotropy);

    out->writeVec4(_borderColor);

    out->writeInt(_internalFormatMode);

    if (out->getVersion() >= VERSION_0008)
    {
        out->writeInt(_internalFormat);
    }

    if (out->getVersion() >= VERSION_0009)
    {
        out->writeInt(_borderWidth);
        out->writeBool(_useHardwareMipMapGeneration);
        out->writeBool(_unrefImageDataAfterApply);
        out->writeBool(_clientStorageHint);
        out->writeBool(_resizeNonPowerOfTwoHint);
    }

    if (out->getVersion() >= VERSION_0014)
    {
        out->writeInt(_sourceFormat);
        out->writeInt(_sourceType);
    }

    if (out->getVersion() >= VERSION_0043)
    {
        out->writeBool(_use_shadow_comparison);
        out->writeInt(_shadow_compare_func);
        out->writeInt(_shadow_texture_mode);
    }
}

void Texture::read(DataInputStream *in)
{
    // Read Texture's identification.
    int id = in->peekInt();

    if (id == IVETEXTURE)
    {
        // Read Texture's identification.
        id = in->readInt();
        // If the osg class is inherited by any other class we should also read this from file.
        osg::Object *obj = dynamic_cast<osg::Object*>(this);
        if (obj)
        {
            ((ive::Object*)(obj))->read(in);
        }
        else
            in_THROW_EXCEPTION("Texture::read(): Could not cast this osg::Texture to an osg::Object.");

        // Read properties
        _wrap_s = (osg::Texture::WrapMode)in->readInt();
        _wrap_t = (osg::Texture::WrapMode)in->readInt();
        _wrap_r = (osg::Texture::WrapMode)in->readInt();

        _min_filter    = (osg::Texture::FilterMode)in->readInt();
        _mag_filter    = (osg::Texture::FilterMode)in->readInt();
        _maxAnisotropy = in->readFloat();

        _borderColor = in->readVec4();

        _internalFormatMode = (osg::Texture::InternalFormatMode)in->readInt();
        if (in->getVersion() >= VERSION_0008)
        {
            _internalFormat = in->readInt();
        }

        if (in->getVersion() >= VERSION_0009)
        {
            _borderWidth                 = in->readInt();
            _useHardwareMipMapGeneration = in->readBool();
            _unrefImageDataAfterApply    = in->readBool();
            _clientStorageHint           = in->readBool();
            _resizeNonPowerOfTwoHint     = in->readBool();
        }

        if (in->getVersion() >= VERSION_0014)
        {
            _sourceFormat = in->readInt();
            _sourceType   = in->readInt();
        }

        if (in->getVersion() >= VERSION_0043)
        {
            _use_shadow_comparison = in->readBool();
            _shadow_compare_func   = (osg::Texture::ShadowCompareFunc)in->readInt();
            _shadow_texture_mode   = (osg::Texture::ShadowTextureMode)in->readInt();
        }
    }
    else
    {
        in_THROW_EXCEPTION("Texture::read(): Expected Texture identification.");
    }
}