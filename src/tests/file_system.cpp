#include <filesystem>
#include <iostream>
#include "../core/util.h"


using namespace mypt;

template <class ParentPath, class... SubPathes>
inline std::filesystem::path path_join(
    const ParentPath& parent_path,
    const SubPathes&... sub_pathes
)
{
    const size_t num_sub_pathes = sizeof...(sub_pathes);
    std::filesystem::path path(parent_path);
    if constexpr ( num_sub_pathes > 0 )
    {
        path.append( path_join( sub_pathes... ).string() );
    }
    return path;
}

void print(const std::string& str)
{
    std::cout << str << std::endl;
}

inline void create_dir( const std::string& abs_path )
{
    if (std::filesystem::exists(abs_path)) {
        Message("The directory '", abs_path, "' is already existed.");
        return;
    }

    bool result = std::filesystem::create_directory(abs_path);
    Assert(result, "Failed to create directory '" + abs_path + "'.");
}

inline void create_dir( const std::string& parent_path, const std::string& relative_path )
{
    std::filesystem::path path = parent_path;
    path.append(relative_path);
    create_dir(path);
}

inline void create_dirs( const std::string& abs_path )
{
    if (std::filesystem::exists(abs_path)) {
        Message("The directory '", abs_path, "' is already existed.");
        return;
    }

    bool result = std::filesystem::create_directories( abs_path );
    Assert(result, "Failed to create directories '" + abs_path + "'.");
}

inline void create_dirs( const std::string& parent_path, const std::string& relative_path )
{
    std::filesystem::path path = parent_path;
    path.append(relative_path);
    create_dirs(path);
}

int main() {
    std::string current = "./";
    std::string prev = "../";

    // create_dir(current + "hoge");
    // create_dir(current, "fuga");

    // create_dirs(current + "hoge1/hoge2");
    // create_dirs(current + "fuga1/fuga2");

    // create_dir(prev, "tests");

    std::cout << path_join("hoge1") << std::endl;
    std::cout << path_join("hoge1", "hoge2") << std::endl;
    std::cout << path_join("hoge1", "hoge2", "hoge3") << std::endl;
    std::cout << path_join("hoge1", "hoge2", "hoge3", "hoge4") << std::endl;
}