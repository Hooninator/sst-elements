#include "../mpi/embermpigen.h"

#include "sst_config.h"
#include <string>
#include <queue>

namespace SST {
namespace Ember {

class SpMMGenerator : public EmberMessagePassingGenerator {
public:
    
    int m; int n; int k;
    
    std::string algo;

    SST_ELI_REGISTER_SUBCOMPONENT_DERIVED(
        SpMMGenerator,
        "ember",
        "SpMMMotif",
        SST_ELI_ELEMENT_VERSION(1,0,0),
        "Performs an idle on the node, no traffic can be generated.",
        SST::Ember::EmberGenerator
    );

    SST_ELI_DOCUMENT_STATISTICS(
        { "time-Init", "Time spent in Init event",             "ns", 0},
        { "time-Finalize", "Time spent in Finalize event",     "ns", 0},
        { "time-Rank", "Time spent in Rank event",             "ns", 0},
        { "time-Size", "Time spent in Size event",             "ns", 0},
        { "time-Send", "Time spent in Recv event",             "ns", 0},
        { "time-Recv", "Time spent in Recv event",             "ns", 0},
        { "time-Irecv", "Time spent in Irecv event",           "ns", 0},
        { "time-Isend", "Time spent in Isend event",           "ns", 0},
        { "time-Wait", "Time spent in Wait event",             "ns", 0},
        { "time-Waitall", "Time spent in Waitall event",       "ns", 0},
        { "time-Waitany", "Time spent in Waitany event",       "ns", 0},
        { "time-Compute", "Time spent in Compute event",       "ns", 0},
        { "time-Barrier", "Time spent in Barrier event",       "ns", 0},
        { "time-Alltoallv", "Time spent in Alltoallv event",   "ns", 0},
        { "time-Alltoall", "Time spent in Alltoall event",     "ns", 0},
        { "time-Allreduce", "Time spent in Allreduce event",   "ns", 0},
        { "time-Reduce", "Time spent in Reduce event",         "ns", 0},
        { "time-Bcast", "Time spent in Bcast event",           "ns", 0},
        { "time-Gettime", "Time spent in Gettime event",       "ns", 0},
        { "time-Commsplit", "Time spent in Commsplit event",   "ns", 0},
        { "time-Commcreate", "Time spent in Commcreate event", "ns", 0},
    );

    SpMMGenerator( SST::ComponentId_t id, Params& params );
    bool generate( std::queue<EmberEvent*>& evQ );
    //void generateSpMM1D( std::queue<EmberEvent*>& evQ );
};


} //Ember
} //SST
