/* -*-c++-*- Present3D - Copyright (C) 1999-2006 Robert Osfield
 *
 * This software is open source and may be redistributed and/or modified under
 * the terms of the GNU General Public License (GPL) version 2.0.
 * The full license is in LICENSE.txt file included with this distribution,.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * include LICENSE.txt for more details.
 */

#ifndef SPELLCHCKER_H
#define SPELLCHCKER_H

#include <osgDB/XmlParser>

namespace p3d
{
class SpellChecker
{
public:

SpellChecker();

void checkP3dXml(const std::string &filename) const;
void checkXml(osgDB::XmlNode *xmlNode) const;
void checkWords(const std::string &words) const;

bool isCorrect(const std::string &word) const;

typedef std::list<std::string> WordList;
WordList suggest(const std::string &word) const;
};


class XmlPatcher
{
public:
XmlPatcher();

void stripP3dXml(const std::string &filename, std::ostream &fout) const;
void stripXml(osgDB::XmlNode *xmlNode, std::ostream &fout) const;

osgDB::XmlNode* simplifyP3dXml(const std::string &filename) const;
osgDB::XmlNode* simplifyXml(osgDB::XmlNode *xmlNode) const;

osgDB::XmlNode* mergeP3dXml(const std::string &lhs_filename, const std::string &rhs_filename) const;
osgDB::XmlNode* mergeXml(osgDB::XmlNode *lhs_node, osgDB::XmlNode *rhs_node) const;
};
}

#endif