/**********************************************************************
*
*    FILE:            Drawable.cpp
*
*    DESCRIPTION:    Read/Write osg::Drawable in binary format to disk.
*
*    CREATED BY:        Auto generated by iveGenerated
*                    and later modified by Rune Schmidt Jensen.
*
*    HISTORY:        Created 18.3.2003
*
*    Copyright 2003 VR-C
**********************************************************************/

#include "Exception.h"
#include "Drawable.h"
#include "ClusterCullingCallback.h"
#include "Object.h"
#include "StateSet.h"


using namespace ive;

void Drawable::write(DataOutputStream *out)
{
    // Write Drawable's identification.
    out->writeInt(IVEDRAWABLE);
    // If the osg class is inherited by any other class we should also write this to file.
    osg::Object *obj = dynamic_cast<osg::Object*>(this);
    if (obj)
    {
        ((ive::Object*)(obj))->write(out);
    }
    else
        out_THROW_EXCEPTION("Drawable::write(): Could not cast this osg::Drawable to an osg::Object.");

    // Write Drawable's properties.

    // Write stateset if any
    out->writeBool(getStateSet() != 0);
    if (getStateSet())
    {
        out->writeStateSet(getStateSet());
    }


    osg::ClusterCullingCallback *ccc = dynamic_cast<osg::ClusterCullingCallback*>(getCullCallback());
    out->writeBool(ccc != 0);
    if (ccc)
    {
        ((ive::ClusterCullingCallback*)(ccc))->write(out);
    }


    if (out->getVersion() >= VERSION_0010)
    {
        const osg::BoundingBox &bb = getInitialBound();
        out->writeBool(bb.valid());
        if (bb.valid())
        {
            out->writeFloat(bb.xMin());
            out->writeFloat(bb.yMin());
            out->writeFloat(bb.zMin());
            out->writeFloat(bb.xMax());
            out->writeFloat(bb.yMax());
            out->writeFloat(bb.zMax());
        }
    }

    // Write support display list.
    out->writeBool(getSupportsDisplayList());

    // Write use display list.
    out->writeBool(getUseDisplayList());

    // Write use display list.
    out->writeBool(getUseVertexBufferObjects());
}

void Drawable::read(DataInputStream *in)
{
    // Read Drawable's identification.
    int id = in->peekInt();

    if (id == IVEDRAWABLE)
    {
        // Code to read Drawable's properties.
        id = in->readInt();
        // If the osg class is inherited by any other class we should also read this from file.
        osg::Object *obj = dynamic_cast<osg::Object*>(this);
        if (obj)
        {
            ((ive::Object*)(obj))->read(in);
        }
        else
            in_THROW_EXCEPTION("Drawable::read(): Could not cast this osg::Drawable to an osg::Object.");

        // Read in drawable's properties

        // Read stateset if any
        if (in->readBool())
        {
            setStateSet(in->readStateSet());
        }

        if (in->readBool())
        {
            osg::ClusterCullingCallback *ccc = new osg::ClusterCullingCallback();
            ((ive::ClusterCullingCallback*)(ccc))->read(in);
            setCullCallback(ccc);
        }


        if (in->getVersion() >= VERSION_0010)
        {
            if (in->readBool())
            {
                osg::BoundingBox bb;
                bb.xMin() = in->readFloat();
                bb.yMin() = in->readFloat();
                bb.zMin() = in->readFloat();
                bb.xMax() = in->readFloat();
                bb.yMax() = in->readFloat();
                bb.zMax() = in->readFloat();
                setInitialBound(bb);
            }
        }

        // Read support display list
        setSupportsDisplayList(in->readBool());

        // Read use display list
        setUseDisplayList(in->readBool());

        // Read use display list
        setUseVertexBufferObjects(in->readBool());
    }
    else
    {
        in_THROW_EXCEPTION("Drawable::read(): Expected Drawable identification.");
    }
}