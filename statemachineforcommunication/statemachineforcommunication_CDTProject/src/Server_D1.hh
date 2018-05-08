
#ifndef SERVER_D1_HH
#define SERVER_D1_HH

#include "communication.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerid.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_Server_D1 : public UMLRTCapsule
{
public:
    Capsule_Server_D1( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    UMLRTLogProtocol_baserole log;
    communication::Conj serverPort;
public:
    enum BorderPortId
    {
        borderport_serverPort
    };
protected:
    UMLRTTimerProtocol_baserole timer;
public:
    enum InternalPortId
    {
        internalport_timer,
        internalport_log
    };
    enum PartId
    {
    };
    enum PortId
    {
        port_log,
        port_serverPort,
        port_timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    UMLRTTimerId timerID;
    char * Data;
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        Connected,
        Data_send,
        Disconnected,
        Exit,
        time_out,
        SPECIAL_INTERNAL_STATE_TOP,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[7];
    State currentState;
    void update_state( State newState );
    void entryaction_____Connected( const UMLRTMessage * msg );
    void entryaction_____Data_send( const UMLRTMessage * msg );
    void entryaction_____Disconnected( const UMLRTMessage * msg );
    void entryaction_____Exit( const UMLRTMessage * msg );
    void entryaction_____time_out( const UMLRTMessage * msg );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    void transitionaction_____timeout( const UMLRTMessage * msg );
    void transitionaction_____transition1( const UMLRTMessage * msg );
    void transitionaction_____transition2( const UMLRTMessage * msg );
    void transitionaction_____transition3( const UMLRTMessage * msg );
    void transitionaction_____transition5( const UMLRTMessage * msg );
    void transitionaction_____transition6( const UMLRTMessage * msg );
    void transitionaction_____transition7( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____timeout( const UMLRTMessage * msg );
    void actionchain_____transition1( const UMLRTMessage * msg );
    void actionchain_____transition2( const UMLRTMessage * msg );
    void actionchain_____transition3( const UMLRTMessage * msg );
    void actionchain_____transition5( const UMLRTMessage * msg );
    void actionchain_____transition6( const UMLRTMessage * msg );
    void actionchain_____transition7( const UMLRTMessage * msg );
    State state_____Connected( const UMLRTMessage * msg );
    State state_____Data_send( const UMLRTMessage * msg );
    State state_____Disconnected( const UMLRTMessage * msg );
    State state_____Exit( const UMLRTMessage * msg );
    State state_____time_out( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Server_D1;

#endif

