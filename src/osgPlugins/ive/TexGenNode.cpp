/**********************************************************************
*
*    FILE:            TexGenNode.cpp
*
*    DESCRIPTION:    Read/Write osg::TexGenNode in binary format to disk.
*
*    CREATED BY:        Auto generated by iveGenerated
*                    and later modified by Rune Schmidt Jensen.
*
*    HISTORY:        Created 21.3.2003
*
*    Copyright 2003 VR-C
**********************************************************************/

#include "Exception.h"
#include "TexGenNode.h"
#include "Group.h"
#include "TexGen.h"

using namespace ive;

void TexGenNode::write(DataOutputStream *out)
{
    // Write TexGenNode's identification.
    out->writeInt(IVETEXGENNODE);
    // If the osg class is inherited by any other class we should also write this to file.
    osg::Group *group = dynamic_cast<osg::Group*>(this);
    if (group)
    {
        ((ive::Group*)(group))->write(out);
    }
    else
        out_THROW_EXCEPTION("TexGenNode::write(): Could not cast this osg::TexGenNode to an osg::Group.");

    // Write TexGenNode's properties.


    out->writeUInt(getTextureUnit());

    // Write out light
    out->writeBool(getTexGen() != 0);
    if (getTexGen())
    {
        ((ive::TexGen*)(getTexGen()))->write(out);
    }
}

void TexGenNode::read(DataInputStream *in)
{
    // Peek on TexGenNode's identification.
    int id = in->peekInt();

    if (id == IVETEXGENNODE)
    {
        // Read TexGenNode's identification.
        id = in->readInt();
        // If the osg class is inherited by any other class we should also read this from file.
        osg::Group *group = dynamic_cast<osg::Group*>(this);
        if (group)
        {
            ((ive::Group*)(group))->read(in);
        }
        else
            in_THROW_EXCEPTION("TexGenNode::read(): Could not cast this osg::TexGenNode to an osg::Object.");

        // Read TexGenNode's properties


        setTextureUnit(in->readUInt());

        // Read texgen
        if (in->readBool())
        {
            osg::TexGen *texgen = new osg::TexGen();
            ((ive::TexGen*)(texgen))->read(in);
            setTexGen(texgen);
        }
    }
    else
    {
        in_THROW_EXCEPTION("TexGenNode::read(): Expected TexGenNode identification.");
    }
}