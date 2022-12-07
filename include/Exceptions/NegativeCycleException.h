#ifndef NEGATIVECYCLE_EXCEPTION_H
#define NEGATIVECYCLE_EXCEPTION_H
#include <Exceptions/GLException.h>

enum GraphAlgorithm{
    SingleSource_BellmanFord = 789,
    MultiSource_Floyd
};
class NegativeCycleException : public GLException{
public:
    explicit NegativeCycleException(const GraphAlgorithm &s);
    const GraphAlgorithm WhatAlgorithm() const;
    virtual std::string GetMessage() const;

private:
    GraphAlgorithm NegativeCycleBelongAlgorithm;
};
std::ostream &operator<<(std::ostream &os, const NegativeCycleException &e);

#endif //NEGATIVECYCLE_EXCEPTION_H
