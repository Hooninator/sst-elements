// Copyright 2009-2020 NTESS. Under the terms
// of Contract DE-NA0003525 with NTESS, the U.S.
// Government retains certain rights in this software.
//
// Copyright (c) 2009-2020, NTESS
// All rights reserved.
//
// Portions are copyright of other developers:
// See the file CONTRIBUTORS.TXT in the top level directory
// the distribution for more information.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.


#ifndef _LLYR_PE_H
#define _LLYR_PE_H

#include <sst/core/output.h>
#include <sst/core/interfaces/simpleMem.h>

#include <map>
#include <queue>
#include <vector>
#include <bitset>
#include <cstdint>

#include "graph.h"
#include "lsQueue.h"
#include "llyrTypes.h"

using namespace SST::Interfaces;

namespace SST {
namespace Llyr {

class ProcessingElement
{
public:
    ProcessingElement(opType op_binding, uint32_t processor_id, uint32_t queue_depth,
                      LSQueue* lsqueue, SimpleMem*  mem_interface);
    ~ProcessingElement();

    uint32_t bindInputQueue(uint32_t id);
    uint32_t bindOutputQueue(uint32_t id);

    uint32_t getInputQueueId(uint32_t id) const { return input_queue_map_.at(id); }
    uint32_t getOutputQueueId(uint32_t id) const { return output_queue_map_.at(id); }
    uint32_t getInputQueueSrc(uint32_t id);
    uint32_t getOutputQueueDst(uint32_t id);

    void     pushInputQueue(uint32_t id, uint64_t &inVal );

    void     setOpBinding(opType binding) { op_binding_ = binding; }
    opType   getOpBinding() const { return op_binding_; }

    void     setProcessorId(uint32_t id) { processor_id_ = id; }
    uint32_t getProcessorId() const { return processor_id_; }

    bool     getPendingOp() const { return pending_op_; }

    bool     doSend(std::vector< Edge* >* adjacencyList);
    bool     doCompute();
    bool     doLoad(uint64_t addr);

    //TODO for testing only
    bool     fakeInit();

protected:


private:
    opType   op_binding_;
    uint32_t processor_id_;

    //used to stall execution - waiting on mem/queues full
    bool pending_op_;

    //input and output queues per PE
    uint32_t queue_depth_;

    std::vector< std::queue< LlyrData >* >* input_queues_;
    std::vector< std::queue< LlyrData >* >* output_queues_;

    //need to connect PEs to queues -- src/dst, queue_id
    std::map< uint32_t, uint32_t > input_queue_map_;
    std::map< uint32_t, uint32_t > output_queue_map_;

    LSQueue* lsqueue_;

    SimpleMem*  mem_interface_;
    SST::Output* output_;

    void printInputQueue();
    void printOutputQueue();

};


}
}

#endif
