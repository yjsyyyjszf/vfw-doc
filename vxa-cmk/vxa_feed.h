#pragma once

//-----------------------------------------------------------------------------------------------------------=
namespace vxa_feed  {
//-----------------------------------------------------------------------------------------------------------=

//-----------------------------------------------------------------------------------------------------------	
#pragma push_macro("max")
#pragma push_macro("min")
#undef max
#undef min

static const int32_t  PRICE_NULL         = 2147483647;
static const int32_t  PRICE_NULL_32      = std::numeric_limits<int32_t>::max();
static const int64_t  PRICE_NULL_64      = std::numeric_limits<int64_t>::max();
static const int32_t  PRICE_CONSTANT     = 10000000;
static_assert( (PRICE_NULL_32 == PRICE_NULL), "PRICE_NULL is not a int32 max" );
static_assert( (2147483647    == std::numeric_limits<int32_t>::max()), "not a int32 max" );

#pragma pop_macro("max")
#pragma pop_macro("min")
//-----------------------------------------------------------------------------------------------------------	

//-----------------------------------------------------------------------------------------------------------	
#pragma push_macro("max")
#pragma push_macro("min")
#undef max
#undef min

static const uint32_t sNullInstrumentID = std::numeric_limits<int32_t>::max();
static const uint32_t sGroupSettleID    = (std::numeric_limits<uint32_t>::max() - 2);
	
#pragma pop_macro("max")
#pragma pop_macro("min")
//-----------------------------------------------------------------------------------------------------------	

enum class AggressorSide : uint8_t
{
    NoAggressor					= 0,
    Buy							= 1,
    Sell						= 2,
};

enum class Side : uint8_t
{
    NotSet						= 0,
    Buy							= 1,
    Sell						= 2,
};

enum class HaltReason : uint8_t
{
    NotSet						= 255,
    GroupSchedule				= 0,
    SurveillanceIntervention	= 1,
    MarketEvent					= 2,
    InstrumentActivation		= 3,
    InstrumentExpiration		= 4,
    Unknown						= 5,
    RecoveryInProcess			= 6,
};

enum class SecurityTradingStatus : uint8_t
{
    NotSet						= 0,
    TradingHalt					= 2,
    Close						= 4,
    NewPriceIndication			= 15,
    ReadyToTrade				= 17,
    NotAvailableForTrading		= 18,
    UnknownorInvalid			= 20,
    PreOpen						= 21,
    PreCross					= 24,
    Cross						= 25,
    PostClose					= 26,
    NoChange					= 103,
    //ICE
    PreClose					= 150,
    // Eurex
    Restricted					= 200,
    Freeze						= 201,
};

enum class SecurityTradingEvent : uint8_t
{
    NoEvent						= 0,
    NoCancel					= 1,
    ResetStatistics				= 4,
    ImpliedMatchingON			= 5,
    ImpliedMatchingOFF			= 6,
};

enum class BookType : char
{
    NotSet						= 'U',
    Bid							= 'B',
    Offer						= 'S',
    ImpliedBid					= 'b',
    ImpliedOffer				= 's',
    BookReset					= 'R',
};

enum class DailyStatisticsType : char
{
    SettlementPrice				= '6',
    ClearedVolume				= 'B',
    OpenInterest				= 'C',
    FixingPrice					= 'W',
};

enum class StatisticsType : char
{
    NotSet						= 127,
    OpenPrice					= 0,
    HighTrade					= 1,
    LowTrade					= 2,
    LastTrade					= 3,
    HighestBid					= 4,
    LowestOffer					= 5,
    ClosePrice					= 6,
};

enum class BookAction : uint8_t
{
    NotSet						= 255,
    New							= 0,
    Change						= 1,
    Delete						= 2,
    DeleteThru					= 3,
    DeleteFrom					= 4,
    Overlay						= 5,
    Replace						= 6,
};

enum class OpenCloseSettlFlag : uint8_t
{
    NotSet						= 255,
    DailyOpenPrice				= 0,
    IndicativeOpeningPrice		= 5,
    DailyClosePrice				= 10,
};

enum class PutOrCall : uint8_t
{
    NotSet						= 255,
    Put							= 0,
    Call						= 1,
};

enum class SettlPriceType : uint8_t
{
    Final						= 0x01,
    Actual						= 0x02,
    Rounded						= 0x04,
    Intraday					= 0x08,
    ReservedBits				= 0x10,
    NullValue					= 0x80,
};

enum class TransactionType :  uint8_t
{
    NotSet						= 255,
    TransactionStart			= 0,
    TransactionEnd				= 1,
};
enum class EventIndicator :  uint8_t
{
    NotSet						= 0x0,
    LastOfType					= 01,
    EndOfEvent					= 0x80,
};

enum class InvestigateStatus : uint8_t
{
    NotSet						= 0x0,
    UnderInvestigation			= 1,
    InvestigationCompleted		= 2,
};

template<typename EnumBitValueType>

inline bool IsEnumBitSet(EnumBitValueType bitValues, EnumBitValueType enumValue) 
{
    return ((uint64_t)bitValues &  (uint64_t)enumValue) == (uint64_t)enumValue;
}

// NOT TO BE USED FOR UTF FILE!
enum class UnionId : uint8_t
{
    NotSet						= 255,
    NotMapped					= 250,
    TradeSummary				= 0,
    TradeMatch					= 1,
    VolumeUpdate				= 2,
    BookLevel					= 3,
    DetailedOrderBook			= 4,
    SecurityStatus				= 5,
    DailyStatistics				= 6,
    SessionStatistics			= 7,
    LimitsBanding				= 8,
    ChannelReset				= 9,
    TransactionMarker			= 10,
    InvestigatedTrade			= 11,
    AuctionClearingPrice		= 12,
};

#pragma pack(push,1)

struct TransactionMarkerEntry
{
    TransactionType			type;
};

struct ChannelResetEntry
{
    BookType				type;
};

struct TradeSummaryEntry
{
    int64_t					price;
    int32_t					tradeQuantity;
    uint32_t				numberOfMatches;
    AggressorSide			aggressorSide;
    bool					isImplieds;
    bool					isSnapShot;
    uint32_t				marketVolume; // sometimes trades contain volume;
};

struct TradeMatchEntry
{
    bool					isAggressor;
    uint16_t				matchNumber;
    int64_t					matchPrice;
    uint64_t				orderId;
    uint64_t				origOrderId;
    int32_t					tradeQuantity;
    int32_t					flags;
};

struct VolumeUpdateEntry
{
    uint32_t				marketVolume;
    int64_t					vwap;
};

struct BookLevelEntry
{
    int64_t					price;
    int32_t					aggQty;
    int32_t					numberOfOrders;
    int32_t					impliedsAggQty;
    int32_t					impliedNumberOfOrders;
    uint8_t					priceLevel;
    BookAction				action;
    BookType				bookType;
    bool					bookEndEvent;
};

struct IncrementalOrderBookEntry
{
    uint64_t				orderID;
    uint64_t				origOrderId;
    uint64_t				priority;
    int64_t					price;
    uint64_t				prevOrderId;
    int32_t					displayQuantity;
    BookAction				action;
    BookType				bookType;
    bool					isSnapShot;
};

struct SecurityStatusEntry
{
    char					securityGroup[10];
    char					asset[10];
    uint16_t				tradeDate;
    SecurityTradingStatus	securityTradingStatus;
    HaltReason				haltReason;
    SecurityTradingEvent	securityTradingEvent;
};

struct DailyStatisticsEntry
{
    uint32_t				instrumentId; // TO
    int64_t					price;
    int32_t					size;
    uint16_t				tradingReferenceDate;
    SettlPriceType			settlPriceType;
    DailyStatisticsType		dailyStatsType;
};

struct LimitsBandingEntry
{
    int64_t					highLimitPrice;
    int64_t					lowLimitPrice;
    int64_t					maxPriceVariation;
};

struct SessionStatistics
{
    uint32_t				instrumentId; // TO
    int64_t                 price;
    OpenCloseSettlFlag		openCloseSettlFlag;
    BookAction				action;
    StatisticsType			statType;
    int32_t                 size;
};

struct InvestigatedTrade 
{
    uint64_t				OrderID; 
    int64_t					price;
    uint32_t				quantity;
    InvestigateStatus		status;
};

struct AuctionClearingPrice
{
    int64_t					price;
    uint32_t				quantity;
};

struct VxaEvent
{
 	uint32_t				instrumentId;
	uint32_t				sequence;

    uint64_t				time           = 0;
    uint32_t				gseq           = 0U;
    uint32_t				seq            = 0U;
    UnionId					unionId        = UnionId::NotSet;
    EventIndicator			eventIndicator = EventIndicator::NotSet;
    bool					realEvent      = true;
    uint8_t					baseExponent   = 0U;

    union
    {
        TradeSummaryEntry			tradeSummary;
        TradeMatchEntry				matchEntry;
        VolumeUpdateEntry			volumeEntry;
        BookLevelEntry				bookEntry;
        IncrementalOrderBookEntry	orderBookEntry;
        SecurityStatusEntry			securityStatus;
        DailyStatisticsEntry		dailyStatsEntry;
        LimitsBandingEntry			bandingEntry;
        SessionStatistics			sessionStatsEntry;
        ChannelResetEntry			channelReset;
        TransactionMarkerEntry		transactionMarker;
        InvestigatedTrade			investigatedTrade;
        AuctionClearingPrice		clearingPrice;
	};

    bool IsTrade()  const { return (unionId == UnionId::TradeSummary || unionId == UnionId::TradeMatch || unionId == UnionId::VolumeUpdate); }

    bool IsEndOfEvent() const
    {
        if( unionId == UnionId::BookLevel )
            return bookEntry.bookEndEvent;
        return ( (((uint8_t)eventIndicator) & ((uint8_t)EventIndicator::EndOfEvent))) == ((uint8_t)EventIndicator::EndOfEvent);
    }
        
	bool IsLastofType() const
    {
        return ( (((uint8_t)eventIndicator) & ((uint8_t)EventIndicator::LastOfType))) == ((uint8_t)EventIndicator::LastOfType);
    }

    void Reset()
    {
        time           = 0;
        gseq           = 0U;
        seq            = 0U;
        unionId        = UnionId::NotSet;
        eventIndicator = EventIndicator::NotSet;
    }

};
#pragma pack(pop)

#pragma pack(push,1)
struct VxaHeader
{
	uint32_t	symbolId;		// Unique ID for this symbol  
	uint32_t	size;			// Total size in bytes of this packet  
	uint32_t	records;		// Number of VxaEvent records in this packet
	uint32_t	zero[8-3];		// Future
};
#pragma pack(pop)


//-----------------------------------------------------------------------------------------------------------=
}	//namespace vxa_event  {
//-----------------------------------------------------------------------------------------------------------=
