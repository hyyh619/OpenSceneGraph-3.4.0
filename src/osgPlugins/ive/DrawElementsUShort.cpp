/**********************************************************************
*
*    FILE:            DrawElementsUShort.cpp
*
*    DESCRIPTION:    Read/Write osg::DrawElementsUShort in binary format to disk.
*
*    CREATED BY:        Auto generated by iveGenerated
*                    and later modified by Rune Schmidt Jensen.
*
*    HISTORY:        Created 20.3.2003
*
*    Copyright 2003 VR-C
**********************************************************************/

#include "Exception.h"
#include "DrawElementsUShort.h"
#include "PrimitiveSet.h"
#include <osg/Endian>

using namespace ive;

void DrawElementsUShort::write(DataOutputStream *out)
{
    // Write DrawElementsUShort's identification.
    out->writeInt(IVEDRAWELEMENTSUSHORT);

    // If the osg class is inherited by any other class we should also write this to file.
    osg::PrimitiveSet *prim = dynamic_cast<osg::PrimitiveSet*>(this);
    if (prim)
    {
        ((ive::PrimitiveSet*)(prim))->write(out);
    }
    else
        out_THROW_EXCEPTION("DrawElementsUShort::write(): Could not cast this osg::DrawElementsUShort to an osg::PrimitiveSet.");

    // Write DrawElementsUShort's properties.

    // Write array length and its elements.
    out->writeInt(size());
    if (size() != 0)
        out->writeCharArray((const char*)&front(), size() * SHORTSIZE);
}

void DrawElementsUShort::read(DataInputStream *in)
{
    // Read DrawElementsUShort's identification.
    int id = in->peekInt();

    if (id == IVEDRAWELEMENTSUSHORT)
    {
        // Code to read DrawElementsUShort's properties.
        id = in->readInt();
        // If the osg class is inherited by any other class we should also read this from file.
        osg::PrimitiveSet *prim = dynamic_cast<osg::PrimitiveSet*>(this);
        if (prim)
        {
            ((ive::PrimitiveSet*)(prim))->read(in);
        }
        else
            in_THROW_EXCEPTION("DrawElementsUShort::read(): Could not cast this osg::DrawElementsUShort to an osg::PrimitiveSet.");

        // Read array length and its elements.
        int size = in->readInt();
        resize(size);
        in->readCharArray((char*)&front(), size * SHORTSIZE);

        if (in->_byteswap)
        {
            for (int i = 0; i < size; i++)
            {
                osg::swapBytes((char*)&((*this)[i]), SHORTSIZE);
            }
        }
    }
    else
    {
        in_THROW_EXCEPTION("DrawElementsUShort::read(): Expected DrawElementsUShort identification.");
    }
}