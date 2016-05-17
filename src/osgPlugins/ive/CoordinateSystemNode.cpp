/**********************************************************************
*
*    FILE:            CoordinateSystemNode.cpp
*
*    DESCRIPTION:    Read/Write osg::CoordinateSystemNode in binary format to disk.
*
*    CREATED BY:        Auto generated by iveGenerator
*                    and later modified by Rune Schmidt Jensen.
*
*    HISTORY:        Created 9.4.2003
*
*    Copyright 2003 VR-C
**********************************************************************/

#include "Exception.h"
#include "CoordinateSystemNode.h"
#include "EllipsoidModel.h"
#include "Group.h"

using namespace ive;

void CoordinateSystemNode::write(DataOutputStream *out)
{
    // Write CoordinateSystemNode's identification.
    out->writeInt(IVECOORDINATESYSTEMNODE);
    // If the osg class is inherited by any other class we should also write this to file.
    osg::Group *group = dynamic_cast<osg::Group*>(this);
    if (group)
    {
        ((ive::Group*)(group))->write(out);
    }
    else
        out_THROW_EXCEPTION("CoordinateSystemNode::write(): Could not cast this osg::CoordinateSystemNode to an osg::Group.");

    // Write CoordinateSystemNode's properties.

    out->writeString(getFormat());
    out->writeString(getCoordinateSystem());

    out->writeBool(getEllipsoidModel() != 0);
    if (getEllipsoidModel())
    {
        ((ive::EllipsoidModel*)(getEllipsoidModel()))->write(out);
    }
}

void CoordinateSystemNode::read(DataInputStream *in)
{
    // Peek on CoordinateSystemNode's identification.
    int id = in->peekInt();

    if (id == IVECOORDINATESYSTEMNODE)
    {
        // Read CoordinateSystemNode's identification.
        id = in->readInt();
        // If the osg class is inherited by any other class we should also read this from file.
        osg::Group *group = dynamic_cast<osg::Group*>(this);
        if (group)
        {
            ((ive::Group*)(group))->read(in);
        }
        else
            in_THROW_EXCEPTION("CoordinateSystemNode::read(): Could not cast this osg::CoordinateSystemNode to an osg::Group.");

        // Read CoordinateSystemNode's properties

        // Read format string
        setFormat(in->readString());

        // Read coord string
        setCoordinateSystem(in->readString());

        bool readEllipsoidModel = in->readBool();
        if (readEllipsoidModel)
        {
            osg::EllipsoidModel *em = new osg::EllipsoidModel();
            ((ive::EllipsoidModel*)(em))->read(in);
            setEllipsoidModel(em);
        }
    }
    else
    {
        in_THROW_EXCEPTION("CoordinateSystemNode::read(): Expected CoordinateSystemNode identification.");
    }
}