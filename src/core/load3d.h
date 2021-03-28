#include "vec.h"

namespace mypt {

/** 
 * \brief Loading OBJ file.
 */
void loadObj(
    const std::string& filename,
    std::vector<vec3>& vertices, 
    std::vector<vec3>& normals, 
    std::vector<int3>& faces,
    std::vector<vec2>& texcoords) 
{
    std::ifstream ifs(filename, std::ios::in);
    Assert(ifs.is_open(), "The OBJ file '"+filename+"' is not found");
    while (!ifs.eof()) {
        std::string line;
        if (!std::getline(ifs, line))
            break;

        // creae string stream
        std::istringstream iss(line);
        std::string header;
        iss >> header;

        // vertex --------------------------------------
        if (header == "v")
        {
            float x, y, z;
            iss >> x >> y >> z;
            vertices.emplace_back(x, y, z);
        }
        else if (header == "f")
        {
            // temporal vector to store face information
            std::vector<int> temp_vert_faces;
            std::vector<int> temp_norm_faces;

            // Future work -----------------------------------
            /*std::vector<int> temp_tex_faces;
            std::vector<int> temp_norm_faces;*/
            // ------------------------------------------------ 
            for (std::string buffer; iss >> buffer;)
            {
                int vert_idx, tex_idx, norm_idx;
                if (sscanf(buffer.c_str(), "%d/%d/%d", &vert_idx, &tex_idx, &norm_idx) == 3)
                {
                    // Input - index(vertex)/index(texture)/index(normal)
                    temp_vert_faces.emplace_back(vert_idx - 1);
                    // temp_tex_faces.emplace_back(tex_idx - 1);
                    temp_norm_faces.emplace_back(norm_idx - 1);
                }
                else if (sscanf(buffer.c_str(), "%d//%d", &vert_idx, &norm_idx) == 2)
                {
                    // Input - index(vertex)//index(normal)
                    temp_vert_faces.emplace_back(vert_idx - 1);
                    temp_norm_faces.emplace_back(norm_idx - 1);
                }
                else if (sscanf(buffer.c_str(), "%d/%d", &vert_idx, &tex_idx) == 2)
                {
                    // Input - index(vertex)/index(texture)
                    temp_vert_faces.emplace_back(vert_idx - 1);
                    //temp_tex_faces.emplace_back(tex_idx - 1);
                }
                else if (sscanf(buffer.c_str(), "%d", &vert_idx) == 1)
                {
                    // Input - index(vertex)
                    temp_vert_faces.emplace_back(vert_idx - 1);
                }
                else
                    Throw("Invalid format in face information input.\n");
            }

            Assert(temp_vert_faces.size() >= 3, "The number of faces is less than 3.\n");

            if (temp_vert_faces.size() == 3) {
                int3 face;
                face[0] = temp_vert_faces[0];
                face[1] = temp_vert_faces[1];
                face[2] = temp_vert_faces[2];
                faces.emplace_back(face);
            }

            /** NOTE: Get more then 4 inputs.
             * This case is implemented under the assumption that mesh are configurd 
             * by quad and inputs are partitioned with 4 stride when face input are 
             * more than 4. */
            else
            {
                for (int i = 0; i<int(temp_vert_faces.size() / 4); i++)
                {
                    // The index value of 0th vertex in quad
                    auto base_idx = i * 4;
                    int3 face1;
                    face1[0] = temp_vert_faces[base_idx + 0];
                    face1[1] = temp_vert_faces[base_idx + 1];
                    face1[2] = temp_vert_faces[base_idx + 2];
                    faces.emplace_back(face1);
                    int3 face2;
                    face2[0] = temp_vert_faces[base_idx + 2];
                    face2[1] = temp_vert_faces[base_idx + 3];
                    face2[2] = temp_vert_faces[base_idx + 0];
                    faces.emplace_back(face2);
                }
            }
        }
    }
    ifs.close();
}

/** 
 * \brief Loading PLY file.
 */
void loadPly(
    const std::string& filename,
    std::vector<vec3>& vertices,
    std::vector<vec3>& normals, 
    std::vector<int3>& faces, 
    std::vector<vec2>& texcoords
)
{
    std::ifstream ifs( filename, std::ios::in | std::ios::binary );
    Assert(ifs.is_open(), "The PLY file '"+filename+"' is not found");
    while (!ifs.eof()) {
        std::string line;
        if (!std::getline(ifs, line))
            break;

    }
}

}