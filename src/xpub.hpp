/*
    Copyright (c) 2007-2010 iMatix Corporation

    This file is part of 0MQ.

    0MQ is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    0MQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __ZMQ_XPUB_HPP_INCLUDED__
#define __ZMQ_XPUB_HPP_INCLUDED__

#include "socket_base.hpp"
#include "array.hpp"
#include "pipe.hpp"
#include "dist.hpp"
#include "fq.hpp"

namespace zmq
{

    class xpub_t : public socket_base_t
    {
    public:

        xpub_t (class ctx_t *parent_, uint32_t tid_);
        ~xpub_t ();

        //  Implementations of virtual functions from socket_base_t.
        void xattach_pipes (class reader_t *inpipe_, class writer_t *outpipe_,
            const blob_t &peer_identity_);
        int xsend (zmq_msg_t *msg_, int flags_);
        bool xhas_out ();
        int xrecv (zmq_msg_t *msg_, int flags_);
        bool xhas_in ();

    private:

        //  Hook into the termination process.
        void process_term (int linger_);

        //  Distributor of messages holding the list of outbound pipes.
        dist_t dist;

        //  Fair queuer for inbound subscriptions.
        fq_t fq;

        xpub_t (const xpub_t&);
        const xpub_t &operator = (const xpub_t&);
    };

}

#endif
