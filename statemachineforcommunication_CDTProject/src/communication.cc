
#include "communication.hh"

#include "umlrtinsignal.hh"
#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_connect_req[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_connect_req = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_connect_req
};

static UMLRTObject_field fields_disconnect_req[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_disconnect_req = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_disconnect_req
};

static UMLRTObject_field fields_over_time[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_over_time = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_over_time
};

static UMLRTObject_field fields_send_data[] = 
{
    {
        "data",
        &UMLRTType_charptr,
        0,
        1,
        0
    }
};

static UMLRTObject payload_send_data = 
{
    sizeof( char * ),
    1,
    fields_send_data
};

static UMLRTObject_field fields_ack_data[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_ack_data = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_ack_data
};

static UMLRTObject_field fields_connection_ok[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_connection_ok = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_connection_ok
};

static UMLRTObject_field fields_disconnect_ok[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_disconnect_ok = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_disconnect_ok
};

static UMLRTObject_field fields_reset[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_reset = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_reset
};

communication::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTInSignal communication::Base::connect_req() const
{
    UMLRTInSignal signal;
    signal.initialize( "connect_req", signal_connect_req, srcPort, &payload_connect_req );
    return signal;
}

UMLRTInSignal communication::Base::disconnect_req() const
{
    UMLRTInSignal signal;
    signal.initialize( "disconnect_req", signal_disconnect_req, srcPort, &payload_disconnect_req );
    return signal;
}

UMLRTInSignal communication::Base::over_time() const
{
    UMLRTInSignal signal;
    signal.initialize( "over_time", signal_over_time, srcPort, &payload_over_time );
    return signal;
}

UMLRTInSignal communication::Base::send_data() const
{
    UMLRTInSignal signal;
    signal.initialize( "send_data", signal_send_data, srcPort, &payload_send_data );
    return signal;
}

UMLRTOutSignal communication::Base::ack_data() const
{
    UMLRTOutSignal signal;
    signal.initialize( "ack_data", signal_ack_data, srcPort, &payload_ack_data );
    return signal;
}

UMLRTOutSignal communication::Base::connection_ok() const
{
    UMLRTOutSignal signal;
    signal.initialize( "connection_ok", signal_connection_ok, srcPort, &payload_connection_ok );
    return signal;
}

UMLRTOutSignal communication::Base::disconnect_ok() const
{
    UMLRTOutSignal signal;
    signal.initialize( "disconnect_ok", signal_disconnect_ok, srcPort, &payload_disconnect_ok );
    return signal;
}

UMLRTOutSignal communication::Base::reset() const
{
    UMLRTOutSignal signal;
    signal.initialize( "reset", signal_reset, srcPort, &payload_reset );
    return signal;
}

communication::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal communication::Conj::connect_req() const
{
    UMLRTOutSignal signal;
    signal.initialize( "connect_req", signal_connect_req, srcPort, &payload_connect_req );
    return signal;
}

UMLRTOutSignal communication::Conj::disconnect_req() const
{
    UMLRTOutSignal signal;
    signal.initialize( "disconnect_req", signal_disconnect_req, srcPort, &payload_disconnect_req );
    return signal;
}

UMLRTOutSignal communication::Conj::over_time() const
{
    UMLRTOutSignal signal;
    signal.initialize( "over_time", signal_over_time, srcPort, &payload_over_time );
    return signal;
}

UMLRTOutSignal communication::Conj::send_data( char * data ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "send_data", signal_send_data, srcPort, &payload_send_data, &data );
    return signal;
}

UMLRTInSignal communication::Conj::ack_data() const
{
    UMLRTInSignal signal;
    signal.initialize( "ack_data", signal_ack_data, srcPort, &payload_ack_data );
    return signal;
}

UMLRTInSignal communication::Conj::connection_ok() const
{
    UMLRTInSignal signal;
    signal.initialize( "connection_ok", signal_connection_ok, srcPort, &payload_connection_ok );
    return signal;
}

UMLRTInSignal communication::Conj::disconnect_ok() const
{
    UMLRTInSignal signal;
    signal.initialize( "disconnect_ok", signal_disconnect_ok, srcPort, &payload_disconnect_ok );
    return signal;
}

UMLRTInSignal communication::Conj::reset() const
{
    UMLRTInSignal signal;
    signal.initialize( "reset", signal_reset, srcPort, &payload_reset );
    return signal;
}


