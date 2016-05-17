/**********************************************************************
*
*    FILE:            LineWidth.cpp
*
*    DESCRIPTION:    Read/Write osg::LineWidth in binary format to disk.
*
*    CREATED BY:        Auto generated by iveGenerator
*                    and later modified by Rune Schmidt Jensen.
*
*    HISTORY:        Created 27.3.2003
*
*    Copyright 2003 VR-C
**********************************************************************/

#include "Exception.h"
#include "LineWidth.h"
#include "Object.h"

using namespace ive;

void LineWidth::write(DataOutputStream *out)
{
    // Write CullFace's identification.
    out->writeInt(IVELINEWIDTH);
    // If the osg class is inherited by any other class we should also write this to file.
    osg::Object *obj = dynamic_cast<osg::Object*>(this);
    if (obj)
    {
        ((ive::Object*)(obj))->write(out);
    }
    else
        out_THROW_EXCEPTION("LineWidth::write(): Could not cast this osg::LineWidth to an osg::Object.");

    // Write LineWidth's properties.
    out->writeFloat(getWidth());
}

void LineWidth::read(DataInputStream *in)
{
    // Peek on LineWidth's identification.
    int id = in->peekInt();

    if (id == IVELINEWIDTH)
    {
        // Read LineWidth's identification.
        id = in->readInt();
        // If the osg class is inherited by any other class we should also read this from file.
        osg::Object *obj = dynamic_cast<osg::Object*>(this);
        if (obj)
        {
            ((ive::Object*)(obj))->read(in);
        }
        else
            in_THROW_EXCEPTION("LineWidth::read(): Could not cast this osg::LineWidth to an osg::Object.");

        // Read LineWidth's properties
        setWidth(in->readFloat());
    }
    else
    {
        in_THROW_EXCEPTION("LineWidth::read(): Expected LineWidth identification.");
    }
}