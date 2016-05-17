/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield
 *
 * This library is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
 */

#include <osgGA/GUIEventHandler>
#include <osgGA/EventVisitor>

using namespace osgGA;


GUIEventHandler::~GUIEventHandler()
{}


// adapt EventHandler usage to old style GUIEventHandler usage
bool GUIEventHandler::handle(osgGA::Event *event, osg::Object *object, osg::NodeVisitor *nv)
{
    osgGA::EventVisitor    *ev = dynamic_cast<osgGA::EventVisitor*>(nv);
    osgGA::GUIEventAdapter *ea = event->asGUIEventAdapter();

    if (ea && ev && ev->getActionAdapter())
    {
#if 1
        bool handled = handle(*ea, *(ev->getActionAdapter()), object, nv);
        if (handled)
            ea->setHandled(true);

        return handled;
#else
        return handleWithCheckAgainstIgnoreHandledEventsMask(*ea, *(ev->getActionAdapter()), object, nv);
#endif
    }

    return false;
}