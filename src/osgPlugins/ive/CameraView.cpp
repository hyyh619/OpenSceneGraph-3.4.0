/**********************************************************************
*
*    FILE:            CameraView.cpp
*
*    DESCRIPTION:    Read/Write osg::CameraView in binary format to disk.
*
*    CREATED BY:        Auto generated by iveGenerate
*                    and later modified by Rune Schmidt Jensen.
*
*    HISTORY:        Created 25.3.2003
*
*    Copyright 2003 VR-C
**********************************************************************/

#include "Exception.h"
#include "CameraView.h"
#include "Transform.h"

using namespace ive;

void CameraView::write(DataOutputStream *out)
{
    // Write CameraView's identification.
    out->writeInt(IVECAMERAVIEW);
    // If the osg class is inherited by any other class we should also write this to file.
    osg::Transform *trans = dynamic_cast<osg::Transform*>(this);
    if (trans)
    {
        ((ive::Transform*)(trans))->write(out);
    }
    else
        out_THROW_EXCEPTION("CameraView::write(): Could not cast this osg::CameraView to an osg::Transform.");

    // Write CameraView's properties.
    out->writeVec3(getPosition());
    out->writeQuat(getAttitude());
    out->writeDouble(getFieldOfView());
    out->writeInt(getFieldOfViewMode());
    out->writeDouble(getFocalLength());
}

void CameraView::read(DataInputStream *in)
{
    // Peek on CameraView's identification.
    int id = in->peekInt();

    if (id == IVECAMERAVIEW)
    {
        // Read CameraView's identification.
        id = in->readInt();
        // If the osg class is inherited by any other class we should also read this from file.
        osg::Transform *trans = dynamic_cast<osg::Transform*>(this);
        if (trans)
        {
            ((ive::Transform*)(trans))->read(in);
        }
        else
            in_THROW_EXCEPTION("CameraView::read(): Could not cast this osg::CameraView to an osg::Transform.");

        // Read CameraView's properties
        setPosition(in->readVec3());
        setAttitude(in->readQuat());
        setFieldOfView(in->readDouble());
        setFieldOfViewMode((FieldOfViewMode)in->readInt());
        setFocalLength(in->readDouble());
    }
    else
    {
        in_THROW_EXCEPTION("CameraView::read(): Expected CameraView identification.");
    }
}