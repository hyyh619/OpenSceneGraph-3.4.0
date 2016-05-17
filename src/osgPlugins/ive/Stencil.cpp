/**********************************************************************
*
*    FILE:            Stencil.cpp
*
*    DESCRIPTION:    Read/Write osg::Stencil in binary format to disk.
*
*    CREATED BY:        Auto generated by iveGenerated
*                    and later modified by Rune Schmidt Jensen.
*
*    HISTORY:        Created 21.3.2003
*
*    Copyright 2003 VR-C
**********************************************************************/

#include "Exception.h"
#include "Stencil.h"
#include "Object.h"

using namespace ive;

void Stencil::write(DataOutputStream *out)
{
    // Write Stencil's identification.
    out->writeInt(IVESTENCIL);
    // If the osg class is inherited by any other class we should also write this to file.
    osg::Object *obj = dynamic_cast<osg::Object*>(this);
    if (obj)
    {
        ((ive::Object*)(obj))->write(out);
    }
    else
        out_THROW_EXCEPTION("Stencil::write(): Could not cast this osg::Stencil to an osg::Object.");

    // Write Stencil's properties.

    out->writeInt(getFunction());
    out->writeInt(getFunctionRef());
    out->writeUInt(getFunctionMask());

    out->writeInt(getStencilFailOperation());
    out->writeInt(getStencilPassAndDepthFailOperation());
    out->writeInt(getStencilPassAndDepthPassOperation());

    out->writeUInt(getWriteMask());
}

void Stencil::read(DataInputStream *in)
{
    // Peek on Stencil's identification.
    int id = in->peekInt();

    if (id == IVESTENCIL)
    {
        // Read Stencil's identification.
        id = in->readInt();
        // If the osg class is inherited by any other class we should also read this from file.
        osg::Object *obj = dynamic_cast<osg::Object*>(this);
        if (obj)
        {
            ((ive::Object*)(obj))->read(in);
        }
        else
            in_THROW_EXCEPTION("Stencil::read(): Could not cast this osg::Stencil to an osg::Object.");

        setFunction((Function)in->readInt());
        setFunctionRef(in->readInt());
        setFunctionMask(in->readUInt());

        setStencilFailOperation((Operation)in->readInt());
        setStencilPassAndDepthFailOperation((Operation)in->readInt());
        setStencilPassAndDepthPassOperation((Operation)in->readInt());

        setWriteMask(in->readUInt());
    }
    else
    {
        in_THROW_EXCEPTION("Stencil::read(): Expected Stencil identification.");
    }
}