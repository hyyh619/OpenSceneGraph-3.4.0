/**********************************************************************
*
*    FILE:            Transform.cpp
*
*    DESCRIPTION:    Read/Write osg::Transform in binary format to disk.
*
*    CREATED BY:        Auto generated by iveGenerate
*                    and later modified by Rune Schmidt Jensen.
*
*    HISTORY:        Created 25.3.2003
*
*    Copyright 2003 VR-C
**********************************************************************/

#include "Exception.h"
#include "Transform.h"
#include "Group.h"

using namespace ive;

void Transform::write(DataOutputStream *out)
{
    // Write Transform's identification.
    out->writeInt(IVETRANSFORM);
    // If the osg class is inherited by any other class we should also write this to file.
    osg::Group *group = dynamic_cast<osg::Group*>(this);
    if (group)
    {
        ((ive::Group*)(group))->write(out);
    }
    else
        out_THROW_EXCEPTION("Transform::write(): Could not cast this osg::Transform to an osg::Group.");

    // Write Transform's properties.
    out->writeInt(getReferenceFrame());
}

void Transform::read(DataInputStream *in)
{
    // Peek on Transform's identification.
    int id = in->peekInt();

    if (id == IVETRANSFORM)
    {
        // Read Transform's identification.
        id = in->readInt();
        // If the osg class is inherited by any other class we should also read this from file.
        osg::Group *group = dynamic_cast<osg::Group*>(this);
        if (group)
        {
            ((ive::Group*)(group))->read(in);
        }
        else
            in_THROW_EXCEPTION("Transform::read(): Could not cast this osg::Transform to an osg::Group.");

        // Read Transform's properties
        setReferenceFrame((osg::Transform::ReferenceFrame)in->readInt());
    }
    else
    {
        in_THROW_EXCEPTION("Transform::read(): Expected Transform identification.");
    }
}