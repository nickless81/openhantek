#ifndef TYPES_H
#define TYPES_H


#define HANTEK_VENDOR_ID         0x04b5 ///< VID for Hantek DSOs with loaded fw
#define HANTEK_EP_OUT              0x02 ///< OUT Endpoint for bulk transfers
#define HANTEK_EP_IN               0x86 ///< IN Endpoint for bulk transfers
#define HANTEK_TIMEOUT              500 ///< Timeout for USB transfers in ms
#define HANTEK_TIMEOUT_MULTI         10 ///< Timeout for multi packet USB transfers in ms
#define HANTEK_ATTEMPTS               3 ///< The number of transfer attempts
#define HANTEK_ATTEMPTS_MULTI         1 ///< The number of multi packet transfer attempts

#define HANTEK_CHANNELS               2 ///< Number of physical channels
#define HANTEK_SPECIAL_CHANNELS       2 ///< Number of special channels

class types
{
public:
    types();
};

#endif // TYPES_H
