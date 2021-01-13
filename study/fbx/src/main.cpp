#include "fbxsdk.h"


int main(int argc, char **argv)
{
    const char *file_name = "/home/reality/data/modules/viking_room/vikingroom.fbx";
//    const char *file_name = "/home.fbx";
    FbxManager *fbx_manager = FbxManager::Create();

    FbxIOSettings *io_settings = FbxIOSettings::Create(fbx_manager, IOSROOT);
    fbx_manager->SetIOSettings(io_settings);

    // create an importer using the SDK manager.
    FbxImporter *fbx_importer = FbxImporter::Create(fbx_manager, "");

    if(!fbx_importer->Initialize(file_name, -1, fbx_manager->GetIOSettings()))
    {
        printf("Call to FbxImporter::Initialize() failed.\n");
        printf("Error returned: %s\n\n", fbx_importer->GetStatus().GetErrorString());
        exit(-1);
    }

    FbxScene *fbx_scene = FbxScene::Create(fbx_manager, "my_scene");

    fbx_importer->Import(fbx_scene);


    fbx_importer->Destroy();
}
