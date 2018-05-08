
#ifndef COMMUNICATION_HH
#define COMMUNICATION_HH

#include "umlrtinsignal.hh"
#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace communication
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTInSignal connect_req() const;
        UMLRTInSignal disconnect_req() const;
        UMLRTInSignal over_time() const;
        UMLRTInSignal send_data() const;
        UMLRTOutSignal ack_data() const;
        UMLRTOutSignal connection_ok() const;
        UMLRTOutSignal disconnect_ok() const;
        UMLRTOutSignal reset() const;
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal connect_req() const;
        UMLRTOutSignal disconnect_req() const;
        UMLRTOutSignal over_time() const;
        UMLRTOutSignal send_data( char * data ) const;
        UMLRTInSignal ack_data() const;
        UMLRTInSignal connection_ok() const;
        UMLRTInSignal disconnect_ok() const;
        UMLRTInSignal reset() const;
    };
    enum SignalId
    {
        signal_connect_req = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID,
        signal_disconnect_req,
        signal_over_time,
        signal_send_data,
        signal_ack_data,
        signal_connection_ok,
        signal_disconnect_ok,
        signal_reset
    };
};

#endif

