#include "config.h"
#include "json.hpp"

#include <fstream>

namespace reality
{
    namespace pikachu
    {

    Config *Config::instance = nullptr;
    Config *Config::getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Config();
        }
        return  instance;
    }

    Config::Config()
    {}

    void Config::parse(const std::string &config_path)
    {
        nlohmann::json config;
        try {
            std::ifstream ifs(config_path);
            ifs >> config;
            m_data_dir = config.at("data_dir");

        } catch(...)
        {
            printf("cannot parse panda config path\n");
            exit(1);
        }
    }

    std::string &Config::data_dir()
    {
        return m_data_dir;
    }

    }
}
