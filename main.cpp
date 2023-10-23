// vim: set ts=5 sw=4 sts=4 et:
#include <SketchUpAPI/SketchUp.h>

#include <iostream>
//#include <set>
//#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/DefaultLogger.hpp>
#include <assimp/version.h>

#include "output_sketchup_error.h"

//namespace fs = std::filesystem;
// #define SU_CALL(func) if ((func) != SU_ERROR_NONE) throw std::exception()

// Quick debugging
#define CHECK(r) if (r != SU_ERROR_NONE) { \
    std::cout << "SU Error line: " << __LINE__ << "\n"; \
    output_sketchup_error(r); return 1; }

std::string getfilename(std::string path)
{
    path = path.substr(path.find_last_of("/\\") + 1);
    size_t dot_i = path.find_last_of('.');
    return path.substr(0, dot_i);
}

int main(int argc, char *argv[]) {

    Assimp::Importer importer;

    printf("Using assimp version %u.%u.%u\n", aiGetVersionMajor(), aiGetVersionMinor(), aiGetVersionPatch());
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " file\n";
        // std::string exts;
        // importer.GetExtensionList(exts);
        // std::cout << "supported extensionss:" << std::endl << exts;
        return 1;
    }


    const double Scale{ 39.3701 };
    // Log to STDERR in this case
    //Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE, aiDefaultLogStream_STDERR);


    std::string filename = argv[1];
    std::string basename = getfilename(filename);
    //   std::string logname = filename + ".log";
    //   Assimp::DefaultLogger::create(logname.c_str());
    // importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT);

    const aiScene *scene = importer.ReadFile(
            filename,
            aiProcess_JoinIdenticalVertices |
            aiProcess_Triangulate |
            aiProcess_ValidateDataStructure |
            aiProcess_PreTransformVertices |
            aiProcess_SortByPType |
            aiProcess_FixInfacingNormals |
            0
            );

    if (!scene)
    {
        std::cout << "An error occured: " << importer.GetErrorString() << "\n";
        return 1;
    }


    // Setup the SketchUp API data structures.

    // Always initialize the API before using it
    SUInitialize();

    // Create the model
    SUModelRef model = SU_INVALID;
    SUResult res = SUModelCreate(&model);
    CHECK(res);

    // Get the entity container of the model
    SUEntitiesRef entities = SU_INVALID;
    res = SUModelGetEntities(model, &entities);
    CHECK(res);

    //unsigned int mesh_index;
    aiMesh *mesh;
    unsigned int face_count = 0;
    aiVector3D vertex;

    printf("model has %i meshes.\n", scene->mNumMeshes);
    // Iterate each scene mesh
    //for (unsigned int i = 0; i < root_node->mNumMeshes; i++) {
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {

        mesh = scene->mMeshes[i];
        face_count = mesh->mNumFaces;
        printf("  mesh[%i] - name:%s, faces: %i, types:", i, mesh->mName.C_Str(), face_count);
        const unsigned int ptypes = mesh->mPrimitiveTypes;
        //printf("types: %i ", ptypes);
        if (ptypes & aiPrimitiveType_POINT) {
            printf(" point");
        }
        if (ptypes & aiPrimitiveType_LINE) {
            printf(" line");
        }
        if (ptypes & aiPrimitiveType_TRIANGLE) {
            printf(" triangle");
        }
        if (ptypes & aiPrimitiveType_POLYGON) {
            printf(" polygon");
        }
        puts("");

        // Create a new Group for each Mesh
        SUGroupRef grp = SU_INVALID;
        res = SUGroupCreate(&grp);
        CHECK(res);

        res = SUEntitiesAddGroup(entities, grp);
        CHECK(res);

        SUGroupSetName(grp, mesh->mName.C_Str());

        SUEntitiesRef gents = SU_INVALID;
        res = SUGroupGetEntities(grp, &gents);
        CHECK(res);

        SUGeometryInputRef geom_input = SU_INVALID;
        res = SUGeometryInputCreate(&geom_input);
        CHECK(res);

        SULoopInputRef outer_loop = SU_INVALID;

        aiFace *faces = mesh->mFaces;
        unsigned int v_i;
        int c = 0;
        for (size_t i = 0; i < face_count; i++) {
            // std::cout << "Face " << i << " has " << faces[i].mNumIndices << " vertices.\n";

            // Create a Loop for each face
            res = SULoopInputCreate(&outer_loop);

            unsigned int vcnt = faces[i].mNumIndices;
            // printf("    face[%lli] has %i indices\n", i, vcnt);
            //if (vcnt == 2) {
            //	SUPoint3D pt1, pt2;
            //	pt1.x = mesh->mVertices[0].x * Scale;
            //	pt1.y = mesh->mVertices[0].y * Scale;
            //	pt1.z = mesh->mVertices[0].z * Scale;
            //	pt2.x = mesh->mVertices[1].x * Scale;
            //	pt2.y = mesh->mVertices[1].y * Scale;
            //	pt2.z = mesh->mVertices[1].z * Scale;
            //	SUEdgeRef edge = SU_INVALID;
            //	SUEdgeCreate(&edge, &pt1, &pt2);
            //	//continue;
            //}
            for (size_t j = 0; j < faces[i].mNumIndices; j++) {
                v_i = faces[i].mIndices[j];
                // std::cout << v_i << " ";
                vertex = mesh->mVertices[v_i];
                SUPoint3D pt;
                pt.x = vertex.x * Scale;
                pt.y = vertex.y * Scale;
                pt.z = vertex.z * Scale;

                /*
                   std::cout << "(";
                   std::cout << pt.x;
                   std::cout << ", ";
                   std::cout << pt.y;
                   std::cout << ", ";
                   std::cout << pt.z;
                   std::cout <<  ") ";
                   */

                res = SUGeometryInputAddVertex(geom_input, &pt);
                CHECK(res);

                if (vcnt > 2) {
                    res = SULoopInputAddVertexIndex(outer_loop, c);
                    CHECK(res);
                }
                c++;
            }
            // printf("c: %i\n", c);
            if (vcnt > 2) {
                res = SUGeometryInputAddFace(geom_input, &outer_loop, NULL);
            }
            else if (vcnt == 2) {
                res = SUGeometryInputAddEdge(geom_input, c-1, c-2, NULL);
                CHECK(res);
            }
            else {
                printf("vcnt = %i\n", vcnt);
            }
            SULoopInputRelease(&outer_loop);
        }
        res = SUEntitiesFill(gents, geom_input, true);
        CHECK(res);
        SUGeometryInputRelease(&geom_input);
    }

    std::string outname = basename + ".skp";
    std::cout << "Writing model...\n";
    res = SUModelSaveToFileWithVersion(model, outname.c_str(), SUModelVersion::SUModelVersion_SU8);
    CHECK(res);
    if (res == SU_ERROR_NONE) {
        std::cout << "Success." << "\n";
    }

    res = SUModelRelease(&model);
    CHECK(res);

    SUTerminate();

    // ShellExecute(GetDesktopWindow(), "open", outname.c_str(), NULL, NULL, SW_SHOW);
    // system("pause");
    return 0;
}
