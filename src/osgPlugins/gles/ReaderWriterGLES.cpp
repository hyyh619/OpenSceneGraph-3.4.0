/* -*-c++-*- OpenSceneGraph - Copyright (C) Cedric Pinson
 *
 * This application is open source and may be redistributed and/or modified
 * freely and without restriction, both in commercial and non commercial
 * applications, as long as this copyright notice is maintained.
 *
 * This application is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <osg/Notify>
#include <osg/Geode>
#include <osg/Version>
#include <osg/Endian>

#include <osgDB/ReaderWriter>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgDB/Registry>
#include <osgDB/FileUtils>
#include <osgDB/FileNameUtils>

#include <string>

#include "UnIndexMeshVisitor"
#include "OpenGLESGeometryOptimizer"

using namespace osg;


class ReaderWriterGLES : public osgDB::ReaderWriter
{
public:

struct OptionsStruct
{
    std::string  enableWireframe;
    bool         generateTangentSpace;
    int          tangentSpaceTextureUnit;
    bool         disableTriStrip;
    bool         disableMergeTriStrip;
    bool         disablePreTransform;
    bool         disablePostTransform;
    unsigned int triStripCacheSize;
    unsigned int triStripMinSize;
    bool         useDrawArray;
    bool         disableIndex;
    unsigned int maxIndexValue;

    OptionsStruct()
    {
        enableWireframe         = "";
        generateTangentSpace    = false;
        tangentSpaceTextureUnit = 0;
        disableTriStrip         = false;
        disableMergeTriStrip    = false;
        disablePreTransform     = false;
        disablePostTransform    = false;
        triStripCacheSize       = 16;
        triStripMinSize         = 2;
        useDrawArray            = false;
        disableIndex            = false;
        maxIndexValue           = 0;
    }
};


ReaderWriterGLES()
{
    supportsExtension("gles", "OpenGL ES optimized format");

    supportsOption("enableWireframe[=inline]", "create a wireframe geometry for each triangles geometry. The wire geometry will be stored along the solid geometry if 'inline' is specified.");
    supportsOption("generateTangentSpace", "Build tangent space to each geometry");
    supportsOption("tangentSpaceTextureUnit=<unit>", "Specify on which texture unit normal map is");
    supportsOption("triStripCacheSize=<int>", "set the cache size when doing tristrip");
    supportsOption("triStripMinSize=<int>", "set the minimum accepted length for a strip");
    supportsOption("disableMergeTriStrip", "disable the merge of all tristrip into one");
    supportsOption("disableTriStrip", "disable generation of tristrip");
    supportsOption("disablePreTransform", "disable pre-transform of geometries after split");
    supportsOption("disablePostTransform", "disable post-transform of geometries (called during geometry splitting)");
    supportsOption("useDrawArray", "prefer drawArray instead of drawelement with split of geometry");
    supportsOption("disableIndex", "Do not index the geometry");
    supportsOption("maxIndexValue=<int>", "set the maximum index value (first index is 0)");
}

virtual const char* className() const
{
    return "GLES Optimizer";
}

virtual osg::Node* optimizeModel(const Node &node, const OptionsStruct &options) const
{
    osg::Node *model = osg::clone(&node);

    if (options.disableIndex)
    {
        UnIndexMeshVisitor unindex;
        model->accept(unindex);
    }
    else
    {
        OpenGLESGeometryOptimizer optimizer;

        optimizer.setUseDrawArray(options.useDrawArray);
        optimizer.setTripStripCacheSize(options.triStripCacheSize);
        optimizer.setTripStripMinSize(options.triStripMinSize);
        optimizer.setDisableTriStrip(options.disableTriStrip);
        optimizer.setDisableMergeTriStrip(options.disableMergeTriStrip);
        optimizer.setDisablePreTransform(options.disablePreTransform);
        optimizer.setDisablePostTransform(options.disablePostTransform);
        optimizer.setWireframe(options.enableWireframe);
        if (options.generateTangentSpace)
        {
            optimizer.setTexCoordChannelForTangentSpace(options.tangentSpaceTextureUnit);
        }

        if (options.maxIndexValue)
        {
            optimizer.setMaxIndexValue(options.maxIndexValue);
        }

        model = optimizer.optimize(*model);
    }

    return model;
}


virtual ReadResult readNode(const std::string &fileName, const osgDB::ReaderWriter::Options *options) const
{
    std::string ext = osgDB::getLowerCaseFileExtension(fileName);

    if (!acceptsExtension(ext))
        return ReadResult::FILE_NOT_HANDLED;

    OSG_INFO << "ReaderWriterGLES( \"" << fileName << "\" )" << std::endl;

    // strip the pseudo-loader extension
    std::string realName = osgDB::getNameLessExtension(fileName);

    if (realName.empty())
        return ReadResult::FILE_NOT_HANDLED;

    // recursively load the subfile.
    osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(realName, options);
    if (!node)
    {
        // propagate the read failure upwards
        OSG_WARN << "Subfile \"" << realName << "\" could not be loaded" << std::endl;
        return ReadResult::FILE_NOT_HANDLED;
    }

    OptionsStruct _options;
    _options = parseOptions(options);
    node     = optimizeModel(*node, _options);

    return node.release();
}

virtual osgDB::ReaderWriter::WriteResult writeNode(const Node &node,
                                                   const std::string &fileName,
                                                   const osgDB::ReaderWriter::Options *options) const
{
    std::string ext = osgDB::getLowerCaseFileExtension(fileName);

    if (!acceptsExtension(ext))
        return WriteResult::FILE_NOT_HANDLED;

    std::string realFileName = osgDB::getNameLessExtension(fileName);
    if (realFileName.empty())
        return WriteResult::FILE_NOT_HANDLED;

    // gles optimization
    OptionsStruct _options;
    _options = parseOptions(options);
    ref_ptr<Node> optimizedNode = optimizeModel(node, _options);

    // forward writing to next plugin
    ref_ptr<ReaderWriter> rw = getReaderWriter(realFileName);
    if (rw)
    {
        return rw->writeNode(*optimizedNode, realFileName, options);
    }
    else
    {
        return WriteResult::ERROR_IN_WRITING_FILE;
    }
}

ReaderWriterGLES::OptionsStruct parseOptions(const osgDB::ReaderWriter::Options *options) const
{
    OptionsStruct localOptions;

    if (options)
    {
        osg::notify(NOTICE) << "options " << options->getOptionString() << std::endl;
        std::istringstream iss(options->getOptionString());
        std::string        opt;

        while (iss >> opt)
        {
            // split opt into pre= and post=
            std::string pre_equals;
            std::string post_equals;

            size_t found = opt.find("=");
            if (found != std::string::npos)
            {
                pre_equals  = opt.substr(0, found);
                post_equals = opt.substr(found + 1);
            }
            else
            {
                pre_equals = opt;
            }

            if (pre_equals == "enableWireframe")
            {
                if (post_equals == "inline")
                {
                    localOptions.enableWireframe = "inline";
                }
                else
                {
                    localOptions.enableWireframe = "outline";
                }
            }

            if (pre_equals == "useDrawArray")
            {
                localOptions.useDrawArray = true;
            }

            if (pre_equals == "disableMergeTriStrip")
            {
                localOptions.disableMergeTriStrip = true;
            }

            if (pre_equals == "disablePreTransform")
            {
                localOptions.disablePreTransform = true;
            }

            if (pre_equals == "disablePostTransform")
            {
                localOptions.disablePostTransform = true;
            }

            if (pre_equals == "disableTriStrip")
            {
                localOptions.disableTriStrip = true;
            }

            if (pre_equals == "generateTangentSpace")
            {
                localOptions.generateTangentSpace = true;
            }

            if (pre_equals == "disableIndex")
            {
                localOptions.disableIndex = true;
            }

            if (post_equals.length() > 0)
            {
                if (pre_equals == "tangentSpaceTextureUnit")
                {
                    localOptions.tangentSpaceTextureUnit = atoi(post_equals.c_str());
                }

                if (pre_equals == "triStripCacheSize")
                {
                    localOptions.triStripCacheSize = atoi(post_equals.c_str());
                }

                if (pre_equals == "triStripMinSize")
                {
                    localOptions.triStripMinSize = atoi(post_equals.c_str());
                }

                if (pre_equals == "maxIndexValue")
                {
                    localOptions.maxIndexValue = atoi(post_equals.c_str());
                }
            }
        }
    }

    return localOptions;
}

protected:
ReaderWriter* getReaderWriter(const std::string &fileName) const
{
    ref_ptr<osgDB::Registry> registry = osgDB::Registry::instance();
    std::string              ext      = osgDB::getLowerCaseFileExtension(fileName);
    return registry->getReaderWriterForExtension(ext);
}
};

// now register with Registry to instantiate the above
// reader/writer.
REGISTER_OSGPLUGIN(gles, ReaderWriterGLES)