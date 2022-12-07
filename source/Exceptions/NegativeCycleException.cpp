#include <Exceptions/NegativeCycleException.h>
#include <cassert>


const GraphAlgorithm NegativeCycleException::WhatAlgorithm() const {
    return NegativeCycleBelongAlgorithm;
}
NegativeCycleException::NegativeCycleException(const GraphAlgorithm &s) : NegativeCycleBelongAlgorithm(s), GLException("nothing"){
    switch(s){
        case SingleSource_BellmanFord:
            NegativeCycleException::message = "Bellman-Ford";
            break;
        case MultiSource_Floyd:
            NegativeCycleException::message = "Floyd";
            break;
        default:
            assert(0);
            break;
    }
}

std::string NegativeCycleException::GetMessage() const {
    return message;
}