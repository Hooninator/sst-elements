
#include "spmm_motif.h"

#include <string>
#include <exception>

using namespace SST::Ember;


SpMMGenerator::SpMMGenerator(SST::ComponentId_t id, Params& params): EmberMessagePassingGenerator(id, params, "Null") 
{ 
    algo = params.find(std::string("algorithm"), std::string("1D")); 

}


/* This should actually simulate the SpMM computation */
bool SpMMGenerator::generate(std::queue<EmberEvent*>& evQ) {

    if (algo.compare("1D")==0) {
        //generateSpMM1D(evQ);
        return true;
    } else {
        throw std::runtime_error("Not implemented");
    } 
    return true;
    
}


//void generateSpMM1D(std::queue<EmberEvent*>& evQ) {
//
//}
