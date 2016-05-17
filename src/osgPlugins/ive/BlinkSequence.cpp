/**********************************************************************
*
*    FILE:            BlinkSequence.cpp
*
*    DESCRIPTION:    Read/Write osgSim::BlinkSequence in binary format to disk.
*
*    CREATED BY:        Auto generated by iveGenerator
*                    and later modified by Rune Schmidt Jensen.
*
*    HISTORY:        Created 5.9.2003
*
**********************************************************************/

#include "Exception.h"
#include "BlinkSequence.h"
#include "Object.h"

using namespace ive;

void BlinkSequence::write(DataOutputStream *out)
{
    // Write BlinkSequence's identification.
    out->writeInt(IVEBLINKSEQUENCE);
    // If the osgSim class is inherited by any other class we should also write this to file.
    osg::Object *obj = dynamic_cast<osg::Object*>(this);
    if (obj)
    {
        ((ive::Object*)(obj))->write(out);
    }
    else
        out_THROW_EXCEPTION("BlinkSequence::write(): Could not cast this osgSim::BlinkSequence to an osg::Object.");

    // Write BlinkSequence's properties.

    // Write out pulse data.
    unsigned int size = getNumPulses();
    out->writeInt(size);

    for (unsigned int i = 0; i < size; i++)
    {
        double    length;
        osg::Vec4 color;
        getPulse(i, length, color);
        out->writeDouble(length);
        out->writeVec4(color);
    }

    // Write out phase shift.
    out->writeDouble(getPhaseShift());
    // Write out SequenceGroup.
    if (getSequenceGroup())
        out->writeDouble(getSequenceGroup()->_baseTime);
    else
        out->writeDouble(0.0);
}

void BlinkSequence::read(DataInputStream *in)
{
    // Peek on BlinkSequence's identification.
    int id = in->peekInt();

    if (id == IVEBLINKSEQUENCE)
    {
        // Read BlinkSequence's identification.
        id = in->readInt();
        // If the osgSim class is inherited by any other class we should also read this from file.
        osg::Object *obj = dynamic_cast<osg::Object*>(this);
        if (obj)
        {
            ((ive::Object*)(obj))->read(in);
        }
        else
            in_THROW_EXCEPTION("BlinkSequence::read(): Could not cast this osgSim::BlinkSequence to an osg::Object.");

        // Read BlinkSequence's properties

        // Read in pulse data.
        unsigned int size = in->readInt();

        for (unsigned int i = 0; i < size; i++)
        {
            double    length = in->readDouble();
            osg::Vec4 color  = in->readVec4();
            addPulse(length, color);
        }

        // Read in phase shift.
        setPhaseShift(in->readDouble());

        // Read in SequenceGroup
        double baseTime = in->readDouble();
        if (baseTime != 0.0)
            setSequenceGroup(new osgSim::SequenceGroup(baseTime));
    }
    else
    {
        in_THROW_EXCEPTION("BlinkSequence::read(): Expected BlinkSequence identification.");
    }
}