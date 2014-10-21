enum BarData
{
    Close = 0
    Open = 1
    Hight = 2
    Low = 3
    Median = 4
    Typical = 5
    Weighted = 6
    Average = 7
    Volume = 8
    OpenInt = 9
}

enum BarFactoryInput
{
    Trade
    Bid
    Ask
    BidAsk
    Middle
    Spread
}

enum BarType
{
    Time = 0
    Tick = 1
    Volume = 2
    Range = 3
}

enum BidAsk
{
    Bid = 0
    Ask = 1
}

enum CommissionType
{
    PerShare = 0
    Percent = 1
    Absolute = 2
}

enum Cross
{
    Above = 0
    Below = 1
    None = 2
}

enum DataType
{
    Trade = 0
    Quote = 1
    Bar = 2
    Daily = 3
}

enum DrawStyle
{
    Line = 0
    Histogram = 1
    Circles = 2
}

enum IBFaMethod
{
    PctChange = 0
    AvailableEquity = 1
    NetLiq = 2
    EqualQuantity = 3
    Undefined = 4
}

enum InstrumentType
{
    Stock = 0
    Futures = 1
    Option = 2
    FutOpt = 3
    Bond = 4
    Index = 5
    ETF = 6
    FX = 7
    MultiLeg = 8
}

enum OrderBookAction
{
    Insert = 0
    Update = 1
    Delete = 2
    Reset = 3
    Undefined = 4
}

enum OrderSide
{
    Buy = 0
    Sell = 1
}

enum OrderStatus
{
    PendingNew = 0
    New = 1
    PartiallyFilled = 2
    Filled = 3
    PendingCancel = 4
    Cancelled = 5
    Expired = 6
    PendingReplace = 7
    Replaced = 8
    Rejected = 9
}

enum OrderType
{
    Market = 0
    Limit = 1
    Stop = 2
    StopLimit = 3
    Trail = 4
    TrailLimit = 5
    MarketOnClose = 6
}

enum PositionSide
{
    Long = 0
    Short = 1
}

enum PutCall
{
    Put = 0
    Call = 1
}

enum QuoteData
{
    Bid = 0
    Ask = 1
    BidAsk = 2
    Middle = 3
    Spread = 4
}

enum SearchOptions
{
    Next = 0
    Prev = 1
}

enum StopMode
{
    Absolute = 0
    Percent = 1
}

enum StopStatus
{
    Active = 0
    Executed = 1
    Canceled = 2
}

enum StopType
{
    Fixed = 0
    Trailing = 1
    Time = 2
}

enum StrategyMode
{
    Simulation = 0
    Paper = 1
    Live = 2
}

enum TimeInForce
{
    Day = 0
    GTC = 1
    OPG = 2
    IOC = 3
    FOK = 4
    GTX = 5
    GTD = 6
    ATC = 7
    GFS = 8
}

enum TransactionSide
{
    Buy = 0
    Sell = 1
}

