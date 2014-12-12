// Copyright 2013-2014 Sandia Corporation. Under the terms
// of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
// Government retains certain rights in this software.
//
// Copyright (c) 2013-2014, Sandia Corporation
// All rights reserved.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#ifndef _H_HERMES_MESSAGE_INTERFACE
#define _H_HERMES_MESSAGE_INTERFACE

#include <sst/core/serialization.h>
#include <sst/core/simulation.h>
#include <sst/core/element.h>
#include <sst/core/event.h>
#include <sst/core/module.h>

#include <assert.h>
#include "functor.h"

using namespace SST;

namespace SST {

namespace Hermes {

typedef void*    Addr;
typedef uint32_t Communicator;
typedef uint32_t RankID;

enum PayloadDataType {
    CHAR,
	INT,
	LONG,
	DOUBLE,
	FLOAT,
	COMPLEX
};

typedef struct MessageResponse {
    uint32_t        tag;  
    RankID          src; 
    uint32_t        count;
    bool            status;
} MessageResponse;

class MessageRequestBase {
  public:
    virtual ~MessageRequestBase() {};
};

typedef MessageRequestBase* MessageRequest;


enum ReductionOperation {
	SUM,
	MIN,
	MAX
};

typedef Arg_FunctorBase< int, bool > Functor; 

static const uint32_t AnyTag = -1;
static const uint32_t AnySrc = -1;
static const Communicator GroupWorld = 0;

enum Retval {
    SUCCESS,
    FAILURE
};

class Interface : public Module {
    public:
    virtual void _componentInit(unsigned int phase ) {}
    virtual void _componentSetup( void ) {}
};

class MessageInterface : public Interface {
    public:

    MessageInterface() {}
    virtual ~MessageInterface() {}
    virtual void printStatus( Output& ) {}

    virtual int sizeofDataType( PayloadDataType ) { assert(0); }
    virtual RankID myWorldRank() { assert(0); } 
    virtual int myWorldSize() { assert(0); } 
    virtual void init(Functor*) {}
    virtual void fini(Functor*) {}
    virtual void rank(Communicator group, RankID* rank, Functor*) {}
    virtual void size(Communicator group, int* size, Functor*) {}

    virtual void send(Addr payload, uint32_t count, PayloadDataType dtype, 
        RankID dest, uint32_t tag, Communicator group, 
        Functor* ) {}

    virtual void isend(Addr payload, uint32_t count, PayloadDataType dtype, 
        RankID dest, uint32_t tag, Communicator group, 
        MessageRequest* req, Functor* ) {}

    virtual void recv(Addr target, uint32_t count, PayloadDataType dtype,
        RankID source, uint32_t tag, Communicator group, 
        MessageResponse* resp, Functor*) {}

    virtual void irecv(Addr target, uint32_t count, PayloadDataType dtype, 
        RankID source, uint32_t tag, Communicator group, 
        MessageRequest* req, Functor*) {}

    virtual void allreduce(Addr mydata, Addr result, uint32_t count, 
        PayloadDataType dtype, ReductionOperation op, 
        Communicator group, Functor*) {}

    virtual void reduce(Addr mydata, Addr result, uint32_t count, 
        PayloadDataType dtype, ReductionOperation op, RankID root, 
        Communicator group, Functor*) {}

    virtual void allgather(
        Addr sendbuf, uint32_t sendcnt, PayloadDataType sendtype,
        Addr recvbuf, uint32_t recvcnt, PayloadDataType recvtype,
        Communicator group, Functor*) {}

    virtual void allgatherv(
        Addr sendbuf, uint32_t sendcnt, PayloadDataType sendtype,
        Addr recvbuf, Addr recvcnt, Addr displs, PayloadDataType recvtype,
        Communicator group, Functor*) {}

    virtual void gather(
        Addr sendbuf, uint32_t sendcnt, PayloadDataType sendtype,
        Addr recvbuf, uint32_t recvcnt, PayloadDataType recvtype,
        RankID root, Communicator group, Functor*) {}

    virtual void gatherv(
        Addr sendbuf, uint32_t sendcnt, PayloadDataType sendtype,
        Addr recvbuf, Addr recvcnt, Addr displs, PayloadDataType recvtype,
        RankID root, Communicator group, Functor*) {}

    virtual void alltoall(
        Addr sendbuf, uint32_t sendcnt, PayloadDataType sendtype,
        Addr recvbuf, uint32_t recvcnt, PayloadDataType recvtype,
        Communicator group, Functor*) {}

    virtual void alltoallv(
        Addr sendbuf, Addr sendcnts, Addr senddispls, PayloadDataType sendtype,
        Addr recvbuf, Addr recvcnts, Addr recvdispls, PayloadDataType recvtype,
        Communicator group, Functor*) {}

    virtual void barrier(Communicator group, Functor*) {}

    virtual void probe( int source, uint32_t tag, 
        Communicator group, MessageResponse* resp, Functor* ) {} 

    virtual void wait( MessageRequest req, MessageResponse* resp,
        Functor* ) {};

    virtual void waitany( int count, MessageRequest req[], int *index,
                MessageResponse* resp, Functor* ) {};

    virtual void waitall( int count, MessageRequest req[],
                MessageResponse* resp[], Functor* ) {};

    virtual void test( MessageRequest* req, int& flag, MessageResponse* resp,
        Functor* ) {};

    virtual void comm_split( Communicator, int color, int key,
        Communicator*, Functor* ) {}
    
};

}
}

#endif

