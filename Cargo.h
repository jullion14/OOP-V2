#pragma once
#include "Transport.h"

class Cargo : public Transport {
protected:
    std::string Cid;
    std::string Clocation;
    time_t Ctime;

public:
    Cargo();
    Cargo(const std::string& id, const std::string& location, time_t time);

    std::string getCid() const;
    std::string getClocation() const;
    time_t getCtime() const;

    void setCid(const std::string& id);
    void setClocation(const std::string& location);
    void setCtime(time_t time);

    void readCargoFile(const std::string& id, const std::string& location, time_t time);
    //void readFile() override;
};
