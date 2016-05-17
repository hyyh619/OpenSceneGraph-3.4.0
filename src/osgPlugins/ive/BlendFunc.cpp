/**********************************************************************
*
*    FILE:            BlendFunc.cpp
*
*    DESCRIPTION:    Read/Write osg::BlendFunc in binary format to disk.
*
*    CREATED BY:        Auto generated by iveGenerated
*                    and later modified by Rune Schmidt Jensen.
*
*    HISTORY:        Created 21.3.2003
*
*    Copyright 2003 VR-C
**********************************************************************/

#include "Exception.h"
#include "BlendFunc.h"
#include "Object.h"

using namespace ive;

void BlendFunc::write(DataOutputStream *out)
{
    bool bSeparate = getSource() != getSourceAlpha() || getDestination() != getDestinationAlpha();

    // Write BlendFunc's identification.
    out->writeInt(bSeparate ? IVEBLENDFUNCSEPARATE : IVEBLENDFUNC);
    // If the osg class is inherited by any other class we should also write this to file.
    osg::Object *obj = dynamic_cast<osg::Object*>(this);
    if (obj)
    {
        ((ive::Object*)(obj))->write(out);
    }
    else
        out_THROW_EXCEPTION("BlendFunc::write(): Could not cast this osg::BlendFunc to an osg::Object.");

    // Write BlendFunc's properties.

    // Write source
    out->writeInt(getSource());
    // Write destination
    out->writeInt(getDestination());

    if (bSeparate)
    {
        // Write source alpha
        out->writeInt(getSourceAlpha());
        // Write destination alpha
        out->writeInt(getDestinationAlpha());
    }
}

void BlendFunc::read(DataInputStream *in)
{
    // Peek on BlendFunc's identification.
    int id = in->peekInt();

    if (id == IVEBLENDFUNC || id == IVEBLENDFUNCSEPARATE)
    {
        // Read BlendFunc's identification.
        id = in->readInt();
        // If the osg class is inherited by any other class we should also read this from file.
        osg::Object *obj = dynamic_cast<osg::Object*>(this);
        if (obj)
        {
            ((ive::Object*)(obj))->read(in);
        }
        else
            in_THROW_EXCEPTION("BlendFunc::read(): Could not cast this osg::BlendFunc to an osg::Object.");

        // Read BlendFunc's properties

        // Read source
        setSource((GLenum)in->readInt());
        // Read destination
        setDestination((GLenum)in->readInt());

        if (id == IVEBLENDFUNCSEPARATE)
        {
            // Read source alpha
            setSourceAlpha((GLenum)in->readInt());

            // Read destination alpha
            setDestinationAlpha((GLenum)in->readInt());
        }
    }
    else
    {
        in_THROW_EXCEPTION("BlendFunc::read(): Expected BlendFunc identification.");
    }
}