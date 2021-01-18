#ifndef REALITY_PIKACHU_CONFIG_H
#define REALITY_PIKACHU_CONFIG_H

#include <string>

namespace reality
{
namespace pikachu {
    class Config
    {
    private:
        static Config *instance;
        Config();
        ~Config() = default;
        Config(const Config &) = default;
        Config &operator=(const Config &) = default;

    public:
        static Config *getInstance();
        void parse(const std::string &path);
        std::string &data_dir();

    private:
        std::string m_config_path;
        std::string m_data_dir;
    };
}
}


#endif
