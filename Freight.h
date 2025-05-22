#pragma once
#include "Transport.h"

class Freight : public Transport {
protected:
    std::string Fid;
    std::string Flocation;
    time_t Ftime;

public:
    Freight();
    Freight(const std::string& id, const std::string& location, time_t time);

    std::string getFid() const;
    std::string getFlocation() const;
    time_t getFtime() const;

    void setFid(const std::string& id);
    void setFlocation(const std::string& location);
    void setFtime(time_t time);

    void readFreightFile(const std::string& id, const std::string& location, time_t time);
    //void readFile() override;
};
