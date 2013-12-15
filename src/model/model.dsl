
/* This is Open Trading Framework Domain Model */

/* Model 分成三个大部分
 * 1.数据处理
 *    a)实时数据,又分为Quote和Trade及OrderBook
 *    b)历史数据处理
 * 2.订单处理及账务处理
 * 3.插件及接口管理
 * 其余如chart/IDE等UI方面不在这个模型中.
 */

/* 系统的总体结构如下:
 *+---------------------------------------------+
 *|Plugin-->PluginManager ---> DataManager      |
 *|                       ---> OrderManager     |
 *|                       ---> StrategyManager  +----> OutProcessStrategy
 *|      In one thread                          |      Strategy/PerProcess
 *+---------------------------------------------+
 */

/* Entities
 * Strategy         Each object of this class represents a running strategy within the system
 * Instrument       This is the base class of all securities in the system
 * Subscription     Market Data Subscriptions of a Strategy for particular Securities are represented by this class. For every Subscription the Strategy will receive Live Market Data for the corresponding Security
 * MarketDataEvent  Represents any type of market data related to a particular Security
 * Order            An Order for a particular security
 * Account          Represents an actual account / account group / allocation profile with an external Broker / Bank
 * Transaction      Each Fill is recorded as a transaction in the database using this entity. In addition the table transaction also stores transactions like intrest, debit, credit & fees
 * Position	    For each opening transaction a position is created which also carries exit values and maintenance margin
 */

/* Strategy Class
 * PortfolioValue           Every hour certain portfolio values (e.g. NetLiqValue, CashBalance, etc.) are saved to the database for every strategy. These will be displayed in the PortfolioChart for every strategy (in the client)
 * Measurement              Custom Measurements (e.g. current value of a custom indicator) related to a strategy can be saved using this class
 * CashBalance              A CashBalance represents the current cash amount of a particular strategy in a particular currency
 * OrderPreference          This class allows the definition of certain order default values for an order (e.g. quantity, orderType, delays, etc.). Except for the orderType, all values have to be defined through Properties. The method LookupService.getOrderByName() will lookup an orderPreference by its name, instantiate the corresponding OrderType and set all properties.
 * DefaultOrderPreference	This class allows the assignment of an OrderPreference and SecurityFamily for an individual strategy. This is useful for situations where the Base has to send an order regarding a position that belongs to a strategy (e.g. ClosePosition when the ExitValue is reached). The method LookupService.getOrderByStrategyAndSecurityFamily() will lookup a defaultOrderPreference by the specified strategyName and securityFamily, instantiate the corresponding OrderType and set all properties.
 * Allocation               If an OrderPreference is defined for an OrderType that sends orders to multiple sub accounts (e.g. DistributingOrder), the quantity allocated to each sub account will be according to the value of the Allocation.
 *                          Note: the total of all allocations needs to be 1.0
 */

/* UML
 * Account
 * Order        --0..* ---1--> Account
 *              --0..* ---1--> Instrument
 *              --0..* ---1--> Strategy         (????)
 * Transaction  --0..* ---1--> Strategy         (????)
 *              --0..* ---0..1--> Instrument
 *              --0..* ---0..1--> Account
 *              <--0..* ---0..1--> Position
 * Subscription <--0..* ---1--> Instrument
 *              --0..* ---1--> Strategy
 *
 * Quote/Trade/OrderBook  --0..*----1-> Instrument
 *
 */

/* 数据管理问题
 * Map:
 * Instrument ---> QuoteSeries
 * Instrument ---> TradeSeries
 * Instrument ---> OrderBook
 *
 * MultiIndex:
 * QuoteSeires<Quote, DateTime, Index>  //通过DateTime或者Index访问, Q:DateTime是Unique??
 * TradeSeries<Trade, DateTime, Index>
 * BarSeries<Bar, DateTime, Index>
 */

/* ProviderId是固定的,只要不重复就可以 */


/* User Case
 * Quote -->
 * Trade -->
 * OrderBook -->
 * HistoryData -->
 *
 * OrderFill -->
 * OrderPartialFill -->
 * OrderAccept -->
 */

//Value Object
class AltIDGroup
{
  properties:
    string AltExchange {get;set;}
    string AltSource {get;set;}
    string AltSymbol {get;set;}
  methods:
    bool Equals(Object obj)
    int GetHashCode()
    string ToString()
}

//Value Object
class AltIDGroupList: IEnumerable
{
methods:
    AltIDGroup Add( string altSource )
    bool Contains( string altSource )
    IEnumerator GetEnumerator()
    void Remove( string altSource )
properties:
    int Count {get;}
    AltIDGroup this[ string altSource ] { get; }

}

static class Appearance
{
properties:
    static Font OutputWindownFound {get;set;}
}

/* DateTime的问题
 * DateTime==BeginTime
 * 在OnBarOpen时，BeginTime==EndTime
 * 在OnBar时，EndTime正好为+BarSize
 */
//Value Object
class Bar
{
constructor:
    Bar(DateTime dateTime, double open, double high, double low, double close, long volume, long size)
    private Bar(Bar bar)
methods:
    override string ToString()
properties:
    double Average {get;}
    DateTime BeginTime {get;}
    double Close {get;}
    DateTime DateTime {get;}
    TimeSpan Duration {get;}
    virtual DateTime EndTime {get;}     //注意virtual
    double High {get;}
    bool IsComplete {get;}
    double this[ BarData barData ] { get; }
    double Low {get;}
    double Median {get;}
    double Open {get;}
    double OpenInt {get;}
    int Size {get;} /* Bar size meaning depends on the bar type
                     * - Time bars: size - number of seconds "inside" the bar, 86400 in the case of a Daily bar,
                     *                     60 * 60 = 3600 in the case of a bar from 10:00 to 11:00, etc
                     * - Tick bars: size - number of ticks "inside" the bar.
                     * - Volume bars: size - total volume of a bar.
                     * - Range bars: size - bar range (high - low) multiplied by 10000.
                     */

    BarType Type {get;}
    double Typical {get;}
    double Volume {get;}
    double Weighted {get;}
}

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

/* Sometimes MarketDataProviders sends "bad" data right before the trading session is opened.
 * In this case it makes sense to reset the BarFactory when the trading session starts.
 * When BarFactory is reset - all current "opened" bars are reset and new bars are collecting using incoming market data. */
enum BarFactoryInput
{
    Trade,
    Bid,
    Ask,
    BidAsk,
    Middle,
    Spread
}

class BarFactory
{
    methods:
      void Reset()
    properties:
      BarFactoryInput input;
}

//Value Object
class BarRequest
{
    constructor:
      BarRequest(BarType barType, long barSize, bool isBarFactoryRequest)
    properties:
      long BarSize {get;}
      BarType BarType {get;}
      bool isBarFactoryRequest {get;set;}
}

//Value Object
class BarRequestList: IEnumerable
{
constructor:
    BarRequestList()
metod:
    void Add( BarRequest barRequest )
    BarRequest Add( BarType barType, long barSize, bool isBarFacroryRequest )
    bool Contains( BarRequest barRequest )
    bool Contains( BarType barType, long barSize )
    bool Contains( BarType barType, long barSize, bool isBuiltFromTrades )
    IEnumerator GetEnumerator()
    void Remove( BarRequest barRequest )
    void Remove( BarType barType, long barSize )
proerty:
    int Count { get; }
    BarRequest this[ int index ] { get; }
}

class BarSeries: IEnumerable, ISeries
{
constructor:
    BarSeries();
    BarSeries( string name );
    BarSeries(string name, string title);
methods:
    void Add(Bar bar);
    void Add( DateTime datetime, double open, double high, double low, double close, long volume, long size );
    void Add( BarType barType, long size, DateTime beginTime, DateTime endTime, double open, double high, double low, double close, long volume, long openInt );
    Bar Ago( int n );
    void Clear();
    BarSeries Compress( long newBarSize );
    bool Contains( DateTime dateTime );
    bool Contains( Bar bar );
    Cross Crosses( BarSeries series, Bar bar );
    Cross Crosses( Indicator indicator, Bar bar );
    virtual Cross Crosses( TimeSeries series, DateTime dateTime );
    bool CrossesAbove( BarSeries series, Bar bar );
    bool CrossesAbove( Indicator indicator, Bar bar );
    virtual bool CrossesAbove( TimeSeries series, DateTime dateTime );
    bool CrossesBelow( BarSeries series, Bar bar );
    bool CrossesBelow( Indicator indicator, Bar bar );
    virtual bool CrossesBelow( TimeSeries series, DateTime dateTime );
    DateTime GetDateTime( int index );
    IEnumerator GetEnumerator();
    int GetIndex( DateTime dateTime );
    BarSeries GetRange( DateTime dateTime1, DateTime dateTime2 );
    double HighestHigh();
    double HighestHigh( int nBars );
    double HighestHigh( DateTime dateTime1, DateTime dateTime2 );
    double HighestHigh( int index1, int index2 );
    double LowestLow();
    double LowestLow( int nBars);
    double LowestLow( DateTime dateTime1, DateTime dateTime2);
    double LowestLow( int index1, int index2);
    void Remove( DateTime dateTime );
    void Remove( int index );
properties:
      int Count { get; }
      Bar First {get;}
      Bar Last {get;}
      Bar this[ DateTime dateTime ] { get; }
      Bar this[ int index ] { get; }
      Bar this[ DateTime dateTime, SearchOption searchOption ] { get; }
      double this[ DateTime dateTime, BarData barData ] { get; }
      double this[ int index, BarData barData ] { get; }
    string Name { get; }
}

class BarSeriesInfo
{
properties:
      long BarSize { get; private set; }
      BarType BarType { get; private set; }
}

class BarSeriesList
{
constructor:
    BarSeriesList()
Properties:
    BarSeries this[ Instrument instrument ] { get; }
    BarSeries this[ Instrument instrument, BarType barType, long barSize ] { get; }
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

class BrokerAccount
{
methods:
      void AddField( string name, string currency, string value )
      void AddField( string name, string value)
      BrokerOrder AddOrder()
      BrokerPosition AddPosition()
properties:
      double BuyingPower { get; set; }
      string Name { get; }
      BrokerOrderList Orders { get; }
      BrokerPositionList Positions { get; }
      BrokerAccountFieldList Fields { get; }
}

class BrokerAccountField
{
methods:
      string ToString()
properties:
      string Currency { get; }
      string Name { get; }
      string Value { get; }
}

class BrokerAccountFieldList: ICollection, IEnumerable
{
methods:
    bool Contains( string name )
    bool Contains( string name, string currency )
    void CopyTo( Array array, int index )
    BrokerAccountField[] GetAllByName( string name )
    IEnumerator GetEnumerator()
properties:
    int Count { get; }
    bool IsSynchronized { get; }
    BrokerAccountField this[ string name ] { get; }
    BrokerAccountField this[ string name, string currency ] { get; }
    Object SyncRoot { get; }
}

class BrokerAccountList: ICollection, IEnumerable
{
methods:
    void CopyTo( Array array, int index )
    IEnumerator GetEnumerator()
properties:
    int Count { get; }
    bool IsSynchronized { get; }
    BrokerAccount this[ int index ] { get; }
    BrokerAccount this[ string name ] { get; }
    Object SyncRoot { get; }
}


class BrokerInfo
{
  constructor:
    BrokerInfo()
  methods:
    BrokerAccount addAccount(string name)
  properties:
    BrokerAccountList Accounts {get;}
}

class BrokerOrder
{
    methods:
      void AddCustomField( string name, string value )
    properties:
      string Currency { get; set; }
      string Exchange { get; set; }
      BrokerOrderFieldList Fields { get; }
      InstrumentType InstrumentType { get; set; }
      string OrderID { get; set; }
      double Price { get; set; }
      double Qty { get; set; }
      OrderSide Side { get; set; }
      OrderStatus Status { get; set; }
      double StopPrice { get; set; }
      string Symbol { get; set; }
      OrderType Type { get; set; }
}

class BrokerOrderField
{
    methods:
      string ToString()
    properties:
      string Name { get; }
      string Value {get;}
}

class BrokerOrderFieldList: ICollection, IEnumerable
{
methods:
     void CopyTo( Array array, int index )
    IEnumerator GetEnumerator()
properties:
    int Count { get; }
    bool IsSynchronized { get; }
    BrokerOrderField this[ string name ] { get; }
    Object SyncRoot { get; }
}

class BrokerOrderList: ICollection, IEnumerable
{
methods:
    void CopyTo( Array array, int index )
    IEnumerator GetEnumerator()
properties:
    int Count { get; }
    bool IsSynchronized { get; }
    BrokerOrder this[ int index ] { get; }
    Object SyncRoot { get; }
}

class BrokerPosition
{
    methods:
      void AddCustomField( string name, string value )
    properties:
      string Currency { get; set; }
      string Exchange { get; set; }
      BrokerPositionFieldList Fields { get; }
      InstrumentType InstrumentType { get; set; }
      double LongQty { get; set; }
      DateTime Maturity { get; set; }
      PutCall PutCall { get; set; }
      double Qty { get; set; }
      double ShortQty { get; set; }
      double Strike { get; set; }
      string Symbol { get; set; }
}

class BrokerPositionField
{
methods:
     override string ToString()
properties:
    string Name { get; }
    string Value { get; }
}

class BrokerPositionFieldList: ICollection, IEnumerable
{
methods:
    void CopyTo( Array array, int index )
    IEnumerator GetEnumerator()
properties:
    int Count { get; }
    bool IsSynchronized { get; }
    BrokerPositionField this[ string name ] { get; }
    Object SyncRoot { get; }
}

class BrokerPositionList: ICollection, IEnumerable
{
methods:
    void CopyTo( Array array, int index )
    IEnumerator GetEnumerator()
properties:
    int Count { get; }
    bool IsSynchronized { get; }
    BrokerPosition this[ int index ] { get; }
    Object SyncRoot { get; }
}

class Canvas
{
    constructor:
      Canvas( string name )
    methods:
      void Add( BarSeries series )
      void Add( Indicator indicator )
      void Add( Order order )
      void Add( QuoteSeries quoteSeries )
      void Add( TimeSeries series )
      void Add( TradeSeries tradeSeries )
      void Add( Transaction transaction )
      void Cd( int pad )
      void Clear()
      void Divide( int x, int y )
      void Run()
      void SetRangeX( DateTime dateTime1, DateTime dateTime2 )
      void SetRangeX( double minX, double maxX )
      void SetRangeY( double minY, double maxY )
      void Update()
}

class Chart
{
constructor:
    Chart()
properties:
    Color BackColor { get; set; }
    Color BorderColor { get; set; }
    Color BottomAxisGridColor { get; set; }
    Color BottomAxisTextColor { get; set; }
    Color CandleDownColor { get; set; }
    Color CandleUpColor { get; set; }
    Color CrossColor { get; set; }
    Color DateTipRectangleColor { get; set; }
    Color DateTipTextColor { get; set; }
    Color ForeColor { get; set; }
    Color RightAxisGridColor { get; set; }
    Color RightAxisMajorTicksColor { get; set; }
    Color RightAxisMinorTicksColor { get; set; }
    Color RightAxisTextColor { get; set; }
    Color SplitterColor { get; set; }
    Color ValueTipRectangleColor { get; set; }
    Color ValueTipTextColor { get; set; }
    Color VolumeColor { get; set; }
}

class Clock
{
    constructor:
      Clock()
    properties:
      static DateTime Now {get;}    /* 策略运行时间
                                     * 例如: 回测自带的那个简单移动平均策略。这个策略的数据时间是1999年到2004年
                                     * Clock.Now会从1999年渐渐输出至2004年
                                     */
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

class DataManager
{
    constructor:
      DataManager()
    methods:
      static void Add( Instrument instrument, Bar bar )
      static void Add( Instrument instrument, OrderBookUpdate update )
      static void Add( Instrument instrument, Quote quote )
      static void Add( Instrument instrument, Trade trade )
      static void Add( Instrument instrument, DateTime datetime, double price, int size )
      static void Add( Instrument instrument, DateTime datetime, double bid, int bidsize, double ask, int asksize )
      static void Add( Instrument instrument, DateTime datetime, BidAsk side, OrderBookAction action, int position, double price, int size )
      static void Add( Instrument instrument, DateTime datetime, double open, double high, double low, double close, long volume, long size )
      static BarSeries CompressBars( BarSeries bars, long barSize )
      static BarSeries CompressBars( TradeSeries trades, BarType barType, long barSize )
      static BarSeries CompressBars( QuoteSeries quotes, QuoteData input, BarType barType, long barSize )
      static void DeleteBar( Instrument instrument, DateTime datetime, BarType barType, long barSize )
      static void DeleteBarSeries( Instrument instrument, BarType barType, long barSize )
      static void DeleteDaily( Instrument instrument, DateTime date )
      static void DeleteDailySeries( Instrument instrument )
       static void DeleteQuote( Instrument instrument, DateTime datetime )
       static void DeleteQuoteSeries( Instrument instrument )
       static void DeleteTrade( Instrument instrument, DateTime datetime )
       static void DeleteTradeSeries( Instrument instrument )
       static void Flush()
       static BarSeriesInfo[] GetBarSeriesInfoList( Instrument instrument )

        static BrokerInfo GetBrokerInfo()
       static BrokerInfo GetBrokerInfo( string provider )
       static BrokerInfo GetBrokerInfo( string provider, byte route )

       static BarSeries GetHistoricalBars( Instrument instrument )
       static BarSeries GetHistoricalBars( Instrument instrument, BarType barType, long barSize )
       static BarSeries GetHistoricalBars( string provider, Instrument instrument, DateTime begin, DateTime end, int size )
       static BarSeries GetHistoricalBars( Instrument instrument, DateTime begin, DateTime end, BarType barType, long barSize )
       static QuoteSeries GetHistoricalQuotes( Instrument instrument, DateTime begin, DateTime end )
       static QuoteSeries GetHistoricalQuotes( string provider, Instrument instrument, DateTime begin, DateTime end )
       static TradeSeries GetHistoricalTrades( Instrument instrument, DateTime begin, DateTime end )
       static TradeSeries GetHistoricalTrades( string provider, Instrument instrument, DateTime begin, DateTime end )
}

class DataRequests
{
    constructor:
      DataRequests()
    methods:
      BarRequest Add( BarType barType, long barSize, bool isBarFacroryRequest )
      void AddDaily()
      void AddQuote()
      void AddTrade()
      void Remove( BarType barType, long barSize )
      void RemoveDaily()
      void RemoveQuote()
      void RemoveTrade()
    properties:
      BarRequestList BarRequests { get; }
      bool HasBarRequests { get; set; }
      bool HasDailyRequest { get; set; }
      bool HasMarketDepthRequest { get; set; }
      bool HasQuoteRequest { get; set; }
      bool HasTradeRequest { get; set; }
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

class ExecutionProvider: Provider
{
    methods:
      void connect()
      void Disconnect()
    properties:
      byte Id {get;}
      bool IsConnected {get;}
      bool IsExecutionProvider { get; }
      bool IsHistoricalDataProvider { get; }
      bool IsInstrumentProvider { get; }
      bool IsMarketDataProvider { get; }
      string Name { get; }
      ProviderPropertyList Properties { get; private set; }
}

class HistoricalDataProvider: Provider
{
methods:
    void Connect()
    void Disconnect()
properties:
    byte Id { get; }
    bool IsConnected { get; }
    bool IsExecutionProvider { get; }
    bool IsHistoricalDataProvider { get; }
    bool IsInstrumentProvider { get; }
    bool IsMarketDataProvider { get; }
    string Name { get; }
    ProviderPropertyList Properties { get; private set; }
}

class HistoricalDataRequest
{
    properties:
      long BarSize { get; }
      DateTime BeginDate { get; }
      DataType DataType { get; }
      DateTime EndDate { get; }
      Instrument Instrument { get; }
}

class IBEx 
{
    properties:
      double DisplaySize { get; set; }
      string FaGroup { get; set; }
      IBFaMethod FaMethod { get; set; }
      double FaPercentage { get; set; }
      string FaProfile { get; set; }
      bool Hidden { get; set; }
}

enum IBFaMethod
{
    PctChange = 0
    AvailableEquity = 1
    NetLiq = 2
    EqualQuantity = 3
    Undefined = 4
}

class Indicator: ISeries
{
constructor:
    Indicator()
methods:
    virtual double Ago(int n)
    virtual bool Contains( DateTime dateTime )
    virtual bool Contains( Bar bar )
    virtual Cross Crosses( double level, Bar bar )
    virtual Cross Crosses( BarSeries series, Bar bar )
    virtual Cross Crosses( Indicator indicator, Bar bar )
    virtual Cross Crosses( TimeSeries series, DateTime dateTime )
    virtual Cross Crosses( BarSeries series, Bar bar, BarData barData )
    virtual bool CrossesAbove( double level, Bar bar )
    virtual bool CrossesAbove( BarSeries series, Bar bar )
    virtual bool CrossesAbove( Indicator indicator, Bar bar )
    virtual bool CrossesAbove( TimeSeries series, DateTime dateTime )
    virtual bool CrossesAbove( BarSeries series, Bar bar, BarData barData )
    virtual bool CrossesBelow( double level, Bar bar )
    virtual bool CrossesBelow( BarSeries series, Bar bar )
    virtual bool CrossesBelow( Indicator indicator, Bar bar )
    virtual bool CrossesBelow( TimeSeries series, DateTime dateTime )
    virtual bool CrossesBelow( BarSeries series, Bar bar, BarData barData )
    double GetAsymmetry( DateTime dateTime1, DateTime dateTime2 )
    double GetAsymmetry( int index1, int index2 )
    double GetAutoCorrelation( int lag )
    double GetAutoCovariance( int lag )
    double GetCorrelation( TimeSeries timeSeries )
    double GetCovariance( TimeSeries timeSeries )
    virtual DateTime GetDateTime( int index )
    double GetExcess( DateTime dateTime1, DateTime dateTime2 )
    double GetExcess( int index1, int index2 )
    int GetIndex( DateTime dateTime )
    double GetMax( DateTime dateTime1, DateTime dateTime2 )
    double GetMax( int index1, int index2 )
    double GetMedian( DateTime dateTime1, DateTime dateTime2 )
    double GetMedian( int index1, int index2 )
    double GetMean( DateTime dateTime1, DateTime dateTime2 )
    double GetMean( int index1, int index2 )
    double GetMin( DateTime dateTime1, DateTime dateTime2 )
    double GetMin( int index1, int index2 )
    double GetMoment( int k, DateTime dateTime1, DateTime dateTime2 )
    double GetMoment( int k, int index1, int index2 )
    double GetNegativeStdDev( DateTime dateTime1, DateTime dateTime2 )
    double GetNegativeStdDev( int index1, int index2 )
    double GetNegativeVariance( DateTime dateTime1, DateTime dateTime2 )
    double GetNegativeVariance( int index1, int index2 )
    double GetPositiveStdDev( DateTime dateTime1, DateTime dateTime2 )
    double GetPositiveStdDev( int index1, int index2 )
    double GetPositiveVariance( DateTime dateTime1, DateTime dateTime2 )
    double GetPositiveVariance( int index1, int index2 )
    double GetStdDev( DateTime dateTime1, DateTime dateTime2 )
    double GetStdDev( int index1, int index2 )
    double GetSum( DateTime dateTime1, DateTime dateTime2 )
    double GetSum( int index1, int index2 )
    double GetVariance( DateTime dateTime1, DateTime dateTime2 )
    double GetVariance( int index1, int index2 )
properties:
    Color Color { get; set; }
    virtual int Count { get; }
    string Description { get; set; }
    virtual DateTime FirstDateTime { get; }
    virtual double this[ DateTime dateTime ] { get; }
    virtual double this[ int index ] { get; }
    virtual double this[ Bar bar ] { get; }
    virtual double this[ DateTime dateTime, BarData barData ] { get; }
    virtual double this[ int index, BarData barData ] { get; }
    virtual double Last { get; }
    virtual DateTime LastDateTime { get; }
    string Name { get; set; }
    int Width { get; set; }
}

class Instrument
{
    constructor:
      Instrument( InstrumentType type, string symbol )
      Instrument( InstrumentType type, string symbol, string secutityExchange, string currency )
    methods:
      string GetExchange( string source )
      string GetSymbol( string source )
      override string ToString()
    properties:
      AltIDGroupList AltIDGroups { get; private set; }
      Bar Bar { get; }
      string Currency { get; set; }
      string Description { get; set; }
      string Exchange { get; set; }
      double Factor { get; set; }
      string Group { get; set; }
      double Margin { get; set; }
      DateTime Maturity { get; set; }
      OrderBook OrderBook { get; }
      string PriceFormat { get; set; }
      PutCall PutCall { get; set; }
      Quote Quote { get; }
      string Sector { get; set; }
      double Strike { get; set; }
      string Symbol { get; }
      double TickSize { get; set; }
      Trade Trade { get; }
      InstrumentType Type { get; }
}

class InstrumentList: IEnumerable
{
constructor:
    public InstrumentList()
methods:
    IEnumerator GetEnumerator()
properties:
    int Count { get; }
    Instrument this[ string symbol ] { get; }
}

class InstrumentManager
{
    methods:
      static void Remove( string symbol )
      static void Remove( Instrument instrument )
    properties:
      static InstrumentList Instruments { get; }
}

class InstrumentProvider: Provider
{
methods:
    void Connect()
    void Disconnect()
properties:
    byte Id { get; }
    bool IsConnected { get; }
    bool IsExecutionProvider { get; }
    bool IsHistoricalDataProvider { get; }
    bool IsInstrumentProvider { get; }
    bool IsMarketDataProvider { get; }
    string Name { get; }
    ProviderPropertyList Properties { get; private set; }
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

interface ISeries
{
    methods:
      double Ago( int n )
      bool Contains( DateTime dateTime )
      DateTime GetDateTime( int index )
      int GetIndex( DateTime dateTime )
    properties:
      int Count {get;}
      double this[ DateTime dateTime, BarData barData ] { get; }
      double this[ int index, BarData barData ] { get; }
      string Name {get;}
}

class MarketDataFilter
{
    constructor:
      MarketDataFilter()
    properties:
      virtual Bar FilterBar( Bar bar, string symbol )
      virtual Bar FilterBarOpen( Bar bar, string symbol )
      virtual Quote FilterQuote( Quote quote, string symbol )
      virtual Trade FilterTrade( Trade trade, string symbol )
}

class MarketDataProvider :Provider
{
methods:
    void Connect()
    void Disconnect()
properties:
    BarFactory BarFactory { get; private set; }
    MarketDataFilter Filter { set; }
}

class OpenQuant
{
    constructor:
      public OpenQuant()
    properties:
      static BarSeriesList Bars { get; }
      static bool EnablePartialTransactions { get; set; }
      static InstrumentList Instruments { get; }
      static OrderList Orders { get; }
}

class OptimizationParameterAttribute: Attribute
{
    constructor:
      OptimizationParameterAttribute( double start, double stop, double step )
    properties:
      double Start { get; }
      double Step { get; }
      double Stop { get; }
}

class Order
{
   methods:
     void Cancel()
     void Replace()
     void Send()
   properties:
     string Account { get; set; }
     double AvgPrice { get; }
     string ClientID { get; set; }
     double CumQty { get; }
     DateTime DateTime { get; }
     int ExpireSeconds { get; set; }
     DateTime ExpireTime { get; set; }
     IBEx IB { get; }
     Instrument Instrument { get; }
     bool IsCancelled { get; }
     bool IsDone { get; }       /* IsDone = IsFilled or IsCancelled or IsRejected. */
     bool IsExpired { get; }
     bool IsFilled { get; }
     bool IsNew { get; }
     bool IsPartiallyFilled { get; }
     bool IsPendingCancel { get; }
     bool IsPendingNew { get; }
     bool IsPendingReplace { get; }
     bool IsRejected { get; }
     double LastPrice { get; }
     double LastQty { get; }
     double LeavesQty { get; }
     string OCAGroup { get; set; }
     string OrderID { get; set; }
     double Price { get; set; }
     double Qty { get; set; }
     byte Route { get; set; }
     OrderSide Side { get; }
     OrderStatus Status { get; }
     double StopPrice { get; set; }
     bool StrategyFill { get; set; }
     double StrategyPrice { get; set; }
     string Text { get; set; }
     TimeInForce TimeInForce { get; set; }
     int TradeVolumeDelay { get; set; }
     double TrailingAmt { get; set; }
     OrderType Type { get; set; }
}

/* 存储深度行情 */
class OrderBook
{
methods:
    int GetAskVolume()
    ouble GetAvgAskPrice()
    double GetAvgBidPrice()
    int GetBidVolume()
    Quote GetQuote( int level )
properties:
    int Count { get; }
}

enum OrderBookAction
{
    Insert = 0
    Update = 1
    Delete = 2
    Reset  = 3
    Undefined = 4
}

class OrderBookUpdate
{
    methods:
      override string ToString()
    properties:
      OrderBookAction Action { get; }
      DateTime DateTime { get; }
      int Position { get; }
      double Price { get; }
      BidAsk Side { get; }
      int Size { get; }
}

class OrderList: IEnumerable
{
constructor:
    OrderList()
methods:
    IEnumerator GetEnumerator()
properties:
    int Count { get; }
    Order this[ int index ] { get; }
}

enum OrderSide
{
    Buy = 0
    Sell = 1
}

enum OrderStatus
{
    PendingNew = 0          /* Order Send之后, 转入该状态 */
    New = 1                 /* 如果交易所接受该订单,转入该状态,触发OnNewOrder */
    PartiallyFilled = 2     /* 如果交易所成交部分交易,转入该状态, 触发 OnOrderPartiallyFilled 然后触发 OnOrderStatusChanged */
    Filled = 3              /* 如果交易所全部成交, 转入该状态, 触发OnOrderStatusChanged, 然后再触发 OnOrderFilled */
    PendingCancel = 4       /* Order Cancel之后, 转入该状态 */
    Cancelled = 5           /* 如果交易所成功取消订单, 转入该状态, 触发OnOrderCancelled事件 */
    Expired = 6             /* 直到合约到期报单未成交，转入该状态, 触发OnOrderExpired事件 */
    PendingReplace = 7      /* Order Replace之后, 转入该状态 */
    Replaced = 8            /* 如果交易所成功修改订单, 转入该状态, 触发OnOrderReplaced事件 */
    Rejected = 9            /* 如果交易所拒绝PendingNew/PendingCancel/PendingReplace,转入该状态
                             * 如果前一个状态为:
                             * PendingNew: 触发OnOrderRejected事件
                             * PendingCancel: 触发OnOrderCancelRejected事件
                             * PendingReplace: OnOrderReplaceRejected事件
                             */
    /* 一次正常的交易触发的事件先后为OnNewOrder，OnOrderPartiallyFilled，OnOrderFilled，OnOrderDone。*/
    /* OnOrderStatusChanged只在状态变为PartiallyFilled，Filled，Cancelled，Expired，Replaced, Rejected时触发 */
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

class ParameterAttribute : Attribute
{
    constructor:
      ParameterAttribute()
      ParameterAttribute( string description )
      ParameterAttribute( string description, string category )
    properties:
      string Category { get; }
      string Description { get; }
}

class Performance
{
    properties:
      double CoreEquity { get; }
      TimeSeries CoreEquitySeries { get; }      /* Equity减去持仓资金（空仓为负）= Portfolio.GetCoreEquity()*/
      double Drawdown { get; }                  /* Equity-HighEquity */
      double DrawdownPercent { get; }           /* = Drawdown/Cash ?? or = Math.Abs(Drawdown /HighEquity) */
      TimeSeries DrawdownPercentSeries { get; }
      TimeSeries DrawdownSeries { get; }
      double Equity { get; }                    /* 动态权益 =Portfolio.GetTotalEquity() */
      TimeSeries EquitySeries { get; }
      double HighEquity { get; }                /* Equity中的最大值 */
      bool IsEnabled { get; set; }
      double LowEquity { get; }                 /* Equity中最小值 */
      double PnL { get; }                       /* bar数据段内的损益 = EquitySeries[lastIndex] - EquitySeries[lastIndex-1]*/
      TimeSeries PnLSeries { get; }
}

class Portfolio
{
      methods:
        void Add( DateTime datetime, TransactionSide side, double qty, Instrument instrument, double price )
        void Add( DateTime datetime, TransactionSide side, double qty, Instrument instrument, double price, string text )
        double GetAccountValue()        /* = account.GetValue */
        double GetCashFlow()            /* 多个position.GetCashFlow累加 */
        double GetCoreEquity()          /* = GetAccountValue */
        double GetDebtEquityRatio()
        double GetDebtValue()           /* 多个position.GetDebtValue累加 */
        double GetLeverage()
        double GetMarginValue()         /* 多个position.GetMarginValue累加 */
        double GetNetCashFlow()         /* 多个position.GetNetCashFlow累加 */
        double GetPositionValue()       /* 多个position.GetValue累加 */
        double GetTotalEquity()         /* = GetValue - GetDebtValue */
        double GetValue()               /* = GetAccountValue + GetPositionValue */
        bool HasPosition( Instrument instrument )
    properties:
        PortfolioAccount Account { get; }
        PositionList Positions { get; }         /* 现有持仓 */
        TransactionList Transactions { get; }  /* 每次交易的时间和具体细节 */
}

/* 		private Currency ;
        private AccountTransactionList ;
*/
class PortfolioAccount
{
    methods:
       void Clear()
       void Deposit( DateTime datetime, double value )
       void Deposit( string currencyCode, double value )
       void Deposit( DateTime datetime, double value, string text )
       void Deposit( string currencyCode, double value, DateTime dateTime )
       void Deposit( string currencyCode, double value, DateTime dateTime, string text )
       void Withdraw( DateTime datetime, double value )
       void Withdraw( string currencyCode, double value )
       void Withdraw( DateTime datetime, double value, string text )
       void Withdraw( string currencyCode, double value, DateTime dateTime )
       void Withdraw( string currencyCode, double value, DateTime dateTime, string text )
}

class PortfolioPricer
{
    contructor:
      PortfolioPricer()
    methods:
      virtual double Price( Position position )
    properties:
      static PortfolioPricer Default { get; }
}

class Position
{
    methods:
      double GetCashFlow()          /* 并不叠加，而是计算总资金流  =NetCashFlow - Cost 如果持有多仓，现金流为负*/
      double GetDebtValue()
      TimeSpan GetDuration()        /* Clock.Now -  Transactions[0].DateTime */
      double GetLeverage()          /* 杠杆 =GetValue/GetMarginValue */
      double GetMarginValue()
      double GetNetCashFlow()       /* 多个transaction.NetCashFlow累加 */
      double GetNetPnL()            /* GetValue + GetNetCashFlow */
      double GetNetPnLPercent()     /* GetNetPnL/Transactions[0].Value */
      double GetPnL()               /* GetValue + GetCashFlow 即在现金流的基础上加上当前持仓的价值 */
      double GetPnLPercent()        /* GetPnL/fTransactions[0].Value */
      double GetPrice()             /* 每个Bar的Close价格 */
      double GetUnrealizedPnL()
      double GetValue()             /* 当前交易花费资金获得的仓位价值 = Price*Amount*Instrument.Factor*/
    properties:
      double Amount { get; }        /* 有正负，做空时为负。数值等于现有持仓数 */
      double Debt { get; }          /* 债务, =Value - Instrument.Margin * Qty 债务就是交了保证金后，欠下还没交的部分*/
      DateTime EntryDate { get; }   /* Transactions[0].DateTime */
      double EntryPrice { get; }    /* Transactions[0].Price */
      double EntryQty { get; }      /* Transactions[0].Qty */
      Instrument Instrument { get; }
      double Margin { get; }        /* Instrument.Margin * Qty. 不一定吧???*/
      double Qty { get; }           /* 现有仓位量 */
      /* QtyBought and QtySoldShort indicate how much you bought, sold and sold short building up your position.
       * For example if you execute market orders to buy 100 and sell 200, then you are short 100 (your position), y
       * ou bought 100, sold 100 and sold short 100.*/
      double QtyBought { get; }     /* 买入量,一直累计 */
      double QtySold { get; }       /* 卖出量，一直累计 */
      double QtySoldShort { get; }  /* 做空仓位量，做空时记录，为交易中最大做空仓位，只加不减 */
      PositionSide Side { get; }
      TransactionList Transactions { get; }

    /* 所有属性平仓后重置 */
    /* 如果仓位直接从做多到做空，QtyBought并没有变化，而QtySold也只变化到与QtyBought相等。说明QtyBought与QtySold的最大值只与做多相关，与做空无关。
     * EntryDate，EntryPrice，EntryQty都没有变化，说明由做多直接变为做空时，OpenQuant不会识别为先平仓再开仓。也就不会触发OnPositionOpen事件。
     **/
}

class PositionList: IEnumerable
{
methods:
    IEnumerator GetEnumerator()
properties:
    int Count { get; }
    Position this[ string symbol ] { get; }
    Position this[ Instrument instrument ] { get; }
}

enum PositionSide
{
    Long = 0
    Short = 1
}

class Provider
{
methods:
    void Connect()
    void Disconnect()
properties:
    byte Id { get; }
    bool IsConnected { get; }
    bool IsExecutionProvider { get; }
    bool IsHistoricalDataProvider { get; }
    bool IsInstrumentProvider { get; }
    bool IsMarketDataProvider { get; }
    string Name { get; }
    ProviderPropertyList Properties { get; private set; }
}

class ProviderError
{
    properties:
      int Code { get; }
      DateTime DateTime { get; }
      int Id { get; }
      string Message { get; }
      string Provider { get; }
}

class ProviderList: IEnumerable<Provider>, IEnumerable
{
methods:
    IEnumerator<Provider> GetEnumerator()
properties:
    int Count { get; }
    Provider this[ byte id ] { get; }
    Provider this[ string name ] { get; }
}

class ProviderManager
{
    Property:
      static ProviderList Providers { get; private set;}
}

class ProviderProperty
{
    properties:
      string Name { get; }
      Type Type { get; }
      Object Value { get; set; }
}

class ProviderPropertyList: IEnumerable<ProviderProperty>, IEnumerable
{
methods:
    IEnumerator<ProviderProperty> GetEnumerator()
properties:
    int Count { get; }
    ProviderProperty this[ string name ] { get; }
}

enum PutCall
{
    Put = 0
    Call = 1
}

/* Quote(报价数据)数据包含多对人们愿意去买或卖一个合约的买价、卖价。这个买卖价对的存在不意味着这个交易一定会发生——如果价差太大，直到做市商干预才会产生交易
 * 注意不是Market Depth, Market Depth数据是用OrderBook存储的.
 */
class Quote
{
    constructor:
      Quote( DateTime dateTime, double bid, int bidSize, double ask, int askSize )
    methods:
      string ToString()
    properties:
      double Ask { get; }
      int AskSize { get; }
      double Bid { get; }
      int BidSize { get; }
      DateTime DateTime { get; }
      byte ProviderId { get; }
}

enum QuoteData
{
    Bid = 0
    Ask = 1
    BidAsk = 2
    Middle = 3
    Spread = 4
}

class QuoteSeries
{
    construct:
      QuoteSeries()
    methods:
      void Add( Quote quote )
      BarSeries CompressBars( QuoteData input, BarType barType, long barSize )
      IEnumerator GetEnumerator()
    properties:
      int Count { get; }
      Quote this[ int index ] { get; }
      Quote Last { get; }
}

class Route
{
const byte AlfaDirect
const byte Currenex
const byte Finam
const byte Genesis
const byte Hotspot
    
}

abstract class Script
{
constructor:
    Script()
methods:
    void AddTimer( DateTime dateTime, Object data )
    void Invoke( Action action )
    virtual void OnScriptStopped( string path )
    virtual void OnSolutionOpened( string name )
    virtual void OnSolutionStarted()
    virtual void OnSolutionStarting()
    virtual void OnSolutionStopped()
    virtual void OnSolutionStopping()
    virtual void OnStop()
    virtual void OnTimer( DateTime dateTime, Object data )
    void RemoveTimer( DateTime dateTime )
    void RemoveTimers()
    abstract void Run() 
}
class ScriptInfo
{
constructor:
    ScriptInfo( string path )
methods:
    string Path { get; set; }
    ScriptSettings Settings { get; private set; }
}
    
class ScriptSettings
{
methods:
    void Add( string name, Object data )
    IEnumerator<KeyValuePair<string, Object>> GetEnumerator()
    void Remove( string name )
properties:
    int Count { get; }
    Object this[ string name ] { get; set; }
}

enum SearchOptions
{
    Next = 0
    Prev = 1
}

class Stop
{
    methods:
      void Cancel()
      void Disconnect()
      void SetBarFilter( long barSize )
      void SetBarFilter( long barSize, BarType barType )
    properties:
      DateTime CompletionTime { get; }
      DateTime CreationTime { get; }
      double FillPrice { get; }
      Instrument Instrument { get; }
      double Level { get; }
      StopMode Mode { get; }
      StopStatus Status { get; }
      bool TraceOnBar { get; set; }
      bool TraceOnQuote { get; set; }
      bool TraceOnTrade { get; set; }
      StopType Type { get; }
}

enum StopMode
{
    Absolute = 0    /* 在跟随价的基础上向不利方向变动一定价格 */
    Percent = 1     /* 在跟随价的基础上向不利方向变动一定价格百分比 */
}

enum StopStatus
{
    Active = 0
    Executed = 1
    Canceled = 2
}

enum StopType
{
    Fixed = 0           /* 定价止损，当价格到时自动触发止损。虚线显示成从开始时间到止损价的一条水平线 */
    Trailing = 1        /* 跟随止损，当向不利方向回撤指定数量时触发，比如从最高价向下回撤1%时触发。虚线显示会动态的将每次的止损价显示，所以是一条曲线 */
    Time = 2            /* 定时止损，会自动设置一个定时器，时间到时触发止损。虚线会显示成从开始时间到现在时间的价格的一条水平线 */
}

class Strategy
{
    constructor:
      Strategy()
    methods:
      void AddTimer( DateTime datetime )
      void AddTimer( DateTime datetime, Object data )

    /* Buy和Sell相当于MarketOrder */
      void Buy( double qty )
      void Buy( double qty, string text )   /* text 可以用来强制制定开平仓,用法使用特殊的开始字符
                                             * O| 表示开仓
                                             * C| 表示平仓
                                             */
      void Buy( Instrument instrument, double qty, string text )
      void BuyLimit( double qty, double limitPrice )
      void BuyLimit( double qty, double limitPrice, string text )
      void BuyLimit( Instrument instrument, double qty, double limitPrice )
      void BuyLimit( Instrument instrument, double qty, double limitPrice, string text )
      Order BuyLimitOrder( double qty, double limitPrice )
      Order BuyLimitOrder( double qty, double limitPrice, string text )
      Order BuyLimitOrder( Instrument instrument, double qty, double limitPrice )
      Order BuyLimitOrder( Instrument instrument, double qty, double limitPrice, string text )
      Order BuyOrder( double qty )
      Order BuyOrder( double qty, string text )
      Order BuyOrder( Instrument instrument, double qty )
      Order BuyOrder( Instrument instrument, double qty, string text )
      void BuyStop( double qty, double stopPrice )
      void BuyStop( double qty, double stopPrice, string text )
      void BuyStop( Instrument instrument, double qty, double stopPrice )
      void BuyStop( Instrument instrument, double qty, double stopPrice, string text )
      void BuyStopLimit( double qty, double limitPrice, double stopPrice )
      void BuyStopLimit( double qty, double limitPrice, double stopPrice, string text )
      void BuyStopLimit( Instrument instrument, double qty, double limitPrice, double stopPrice )
      void BuyStopLimit( Instrument instrument, double qty, double limitPrice, double stopPrice, string text )
      Order BuyStopLimitOrder( double qty, double limitPrice, double stopPrice )
      Order BuyStopLimitOrder( double qty, double limitPrice, double stopPrice, string text )
      Order BuyStopLimitOrder( Instrument instrument, double qty, double limitPrice, double stopPrice )
      Order BuyStopLimitOrder( Instrument instrument, double qty, double limitPrice, double stopPrice, string text )
      Order BuyStopOrder( double qty, double stopPrice )
      Order BuyStopOrder( double qty, double stopPrice, string text )
      Order BuyStopOrder( Instrument instrument, double qty, double stopPrice )
      Order BuyStopOrder( Instrument instrument, double qty, double stopPrice, string text )
      void CancelAllOrders()
      void CancelOrders()
      void CloseAllPositions()
      void CloseAllPositions( string text )
      void ClosePosition()
      void ClosePosition( string text )
      void Draw( Indicator indicator )
      void Draw( TimeSeries series )
      void Draw( Indicator indicator, DrawStyle style )
      void Draw( Indicator indicator, int padNumber )
      void Draw( TimeSeries series, DrawStyle style )
      void Draw( TimeSeries series, int padNumber )
      void Draw( Indicator indicator, int padNumber, DrawStyle style )
      void Draw( TimeSeries series, int padNumber, DrawStyle style )
      BarSeries GetBars( long barSize )
      BarSeries GetBars( Instrument instrument )
      BarSeries GetBars( BarType barType, long barSize )
      BarSeries GetBars( Instrument instrument, long barSize )
      BarSeries GetBars( Instrument instrument, BarType barType, long barSize )
      BarSeries GetHistoricalBars()
      BarSeries GetHistoricalBars( DateTime begin, DateTime end )
      BarSeries GetHistoricalBars( BarType barType, long barSize )
      BarSeries GetHistoricalBars( DateTime begin, DateTime end, BarType barType, long barSize )
      BarSeries GetHistoricalBars( string provider, DateTime begin, DateTime end, int size )
      BarSeries GetHistoricalBars( string provider, Instrument instrument, DateTime begin, DateTime end, int size )
      QuoteSeries GetHistoricalQuotes( DateTime begin, DateTime end )
      QuoteSeries GetHistoricalQuotes( string provider, DateTime begin, DateTime end )
      QuoteSeries GetHistoricalQuotes( string provider, Instrument instrument, DateTime begin, DateTime end )
      TradeSeries GetHistoricalTrades( DateTime begin, DateTime end )
      TradeSeries GetHistoricalTrades( string provider, DateTime begin, DateTime end )
      TradeSeries GetHistoricalTrades( string provider, Instrument instrument, DateTime begin, DateTime end )
      QuoteSeries GetQuotes( Instrument instrument )
      TradeSeries GetTrades( Instrument instrument )
      bool HasPositionAmount( double amount )
      bool HasPositionQty( double qty )
      Order LimitOrder( OrderSide side, double qty, double limitPrice )
      Order LimitOrder( Instrument instrument, OrderSide side, double qty, double limitPrice )
      Order LimitOrder( OrderSide side, double qty, double limitPrice, string text )
      Order LimitOrder( Instrument instrument, OrderSide side, double qty, double limitPrice, string text )
      Order MarketOrder( OrderSide side, double qty )
      Order MarketOrder( Instrument instrument, OrderSide side, double qty )
      Order MarketOrder( OrderSide side, double qty, string text )
      Order MarketOrder( Instrument instrument, OrderSide side, double qty, string text )
      virtual void OnActiveChanged()        // Called when Active property gets changed

    /* 数据处理 */
      virtual void OnQuote( Quote quote )
      virtual void OnTrade( Trade trade )
      virtual void OnBar( Bar bar )
      virtual void OnBarOpen( Bar bar )
      virtual void OnBarSlice( long size )
      virtual void OnOrderBookChanged( OrderBookUpdate update )
/* 连接管理 */
      virtual void OnConnected( string provider )
      virtual void OnDisconnected( string provider )
      virtual void OnError( ProviderError error )
/* 订单处理 */
      virtual void OnNewOrder( Order order )                // Called when new order event occurs
      virtual void OnOrderCancelled( Order order )          //
      virtual void OnOrderCancelReject( Order order )
      virtual void OnOrderDone( Order order )
      virtual void OnOrderExpired( Order order )
      virtual void OnOrderFilled( Order order )
      virtual void OnOrderPartiallyFilled( Order order )
      virtual void OnOrderRejected( Order order )
      virtual void OnOrderReplaced( Order order )
      virtual void OnOrderReplaceReject( Order order )
      virtual void OnOrderStatusChanged( Order order )
/* 仓位变化 */
      virtual void OnPositionChanged()
      virtual void OnPositionClosed()
      virtual void OnPositionOpened()
      virtual void OnPositionValueChanged()
/* 策略本身变化 */
      virtual void OnStopExecuted( Stop stop )
      virtual void OnStrategyStart()
      virtual void OnStrategyStop()
    /* 定时处理 */
      virtual void OnTimer( DateTime datetime, Object data )
/* 命令处理 */
      virtual void OnUserCommand( UserCommand command )     /* 用户在IDE里发送的命令 */
      virtual void OnCustomCommand( Object[] parameters )       /* 接收另外一个策略发来的命令 */

      void RemoveTimer( DateTime datetime )
      void RemoveTimer( DateTime datetime, Object data )
      void RemoveTimers()
      void RemoveTimers( DateTime datetime )
      void Scan( BarData barData )
      void Scan( ISeries series )
      void Sell( double qty )
      void Sell( double qty, string text )
      void Sell( Instrument instrument, double qty )
      void Sell( Instrument instrument, double qty, string text )
      void SellLimit( double qty, double limitPrice )
      void SellLimit( double qty, double limitPrice, string text )
      void SellLimit( Instrument instrument, double qty, double limitPrice )
      void SellLimit( Instrument instrument, double qty, double limitPrice, string text )
      Order SellLimitOrder( double qty, double limitPrice )
      Order SellLimitOrder( double qty, double limitPrice, string text )
      Order SellLimitOrder( Instrument instrument, double qty, double limitPrice )
      Order SellLimitOrder( Instrument instrument, double qty, double limitPrice, string text )
      Order SellOrder( double qty )
      Order SellOrder( double qty, string text )
      Order SellOrder( Instrument instrument, double qty )
      Order SellOrder( Instrument instrument, double qty, string text )
      void SellStop( double qty, double stopPrice )
      void SellStop( double qty, double stopPrice, string text )
      void SellStop( Instrument instrument, double qty, double stopPrice )
      void SellStop( Instrument instrument, double qty, double stopPrice, string text )
      void SellStopLimit( double qty, double limitPrice, double stopPrice )
      void SellStopLimit( double qty, double limitPrice, double stopPrice, string text )
      void SellStopLimit( Instrument instrument, double qty, double limitPrice, double stopPrice )
      void SellStopLimit( Instrument instrument, double qty, double limitPrice, double stopPrice, string text )
      Order SellStopLimitOrder( double qty, double limitPrice, double stopPrice )
      Order SellStopLimitOrder( double qty, double limitPrice, double stopPrice, string text )
      Order SellStopLimitOrder( Instrument instrument, double qty, double limitPrice, double stopPrice )
      Order SellStopLimitOrder( Instrument instrument, double qty, double limitPrice, double stopPrice, string text )
      Order SellStopOrder( double qty, double stopPrice )
      Order SellStopOrder( double qty, double stopPrice, string text )
      Order SellStopOrder( Instrument instrument, double qty, double stopPrice )
      Order SellStopOrder( Instrument instrument, double qty, double stopPrice, string text )
      void SendCustomCommand( params Object[] parameters )
      void SendCustomCommand( string projectName, params Object[] parameters )
      void SendCustomCommand( string projectName, string symbol, params Object[] parameters )
      void SendLimitOrder( OrderSide side, double qty, double limitPrice )
      void SendLimitOrder( Instrument instrument, OrderSide side, double qty, double limitPrice )
      void SendLimitOrder( OrderSide side, double qty, double limitPrice, string text )
      void SendLimitOrder( Instrument instrument, OrderSide side, double qty, double limitPrice, string text )
      void SendMarketOrder( OrderSide side, double qty )
      void SendMarketOrder( Instrument instrument, OrderSide side, double qty )
      void SendMarketOrder( OrderSide side, double qty, string text )
      void SendMarketOrder( Instrument instrument, OrderSide side, double qty, string text )
      void SendStopLimitOrder( OrderSide side, double qty, double limitPrice, double stopPrice )
      void SendStopLimitOrder( Instrument instrument, OrderSide side, double qty, double limitPrice, double stopPrice )
      void SendStopLimitOrder( OrderSide side, double qty, double limitPrice, double stopPrice, string text )
      void SendStopLimitOrder( Instrument instrument, OrderSide side, double qty, double limitPrice, double stopPrice, string text )
      void SendStopOrder( OrderSide side, double qty, double stopPrice )
      void SendStopOrder( Instrument instrument, OrderSide side, double qty, double stopPrice )
      void SendStopOrder( OrderSide side, double qty, double stopPrice, string text )
      void SendStopOrder( Instrument instrument, OrderSide side, double qty, double stopPrice, string text )

    /* 止损指标SetStop，是由OpenQuant维护的止损功能，与发送到交易所的止损单BuyStop是有区别的。
     *止损指标的用法是在有持仓时SetStop，当条件满足时就会触发OnStopExecuted，得自行在OnStopExecuted进行报单处理
     */
      Stop SetStop( DateTime dateTime )
      Stop SetStop( Position position, DateTime dateTime )
      Stop SetStop( double level, StopType type, StopMode mode )
      Stop SetStop( Position position, double level, StopType type, StopMode mode )

      Order StopLimitOrder( OrderSide side, double qty, double limitPrice, double stopPrice )
      Order StopLimitOrder( Instrument instrument, OrderSide side, double qty, double limitPrice, double stopPrice )
      Order StopLimitOrder( OrderSide side, double qty, double limitPrice, double stopPrice, string text )
      Order StopLimitOrder( Instrument instrument, OrderSide side, double qty, double limitPrice, double stopPrice, string text )
      Order StopOrder( OrderSide side, double qty, double stopPrice )
      Order StopOrder( Instrument instrument, OrderSide side, double qty, double stopPrice )
      Order StopOrder( OrderSide side, double qty, double stopPrice, string text )
      Order StopOrder( Instrument instrument, OrderSide side, double qty, double stopPrice, string text )
      void StopStrategy()

    properties:
      bool Active { get; }
      Bar Bar { get; }
      BarSeries Bars { get; }
      double Cash { get; }
      Chart Chart { get; }
      DataRequests DataRequests { get; }
      ExecutionProvider ExecutionProvider { get; }
      static Hashtable Global { get; }
      bool HasPosition { get; }
      Instrument Instrument { get; }
      IStrategyLogList InstrumentLogs { get; }
      InstrumentList Instruments { get; }
      MarketDataProvider MarketDataProvider { get; }
      Performance MetaPerformance { get; }
      Portfolio MetaPortfolio { get; }
      StrategyMode Mode { get; }
      string Name { get; }
      OrderBook OrderBook { get; }
      OrderList Orders { get; }
      Performance Performance { get; }
      Portfolio Portfolio { get; }
      Position Position { get; }
      Quote Quote { get; }
      QuoteSeries Quotes { get; }
      IStrategyLogList SolutionLogs { get; }
      DateTime StartDate { get; }
      DateTime StopDate { get; }
      IStrategyLogList StrategyLogs { get; }
      bool TraceOnBar { get; set; }
      bool TraceOnQuote { get; set; }
      bool TraceOnTrade { get; set; }
      Trade Trade { get; }
      TradeSeries Trades { get; }
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

class TimeSeries: ISeries
{
constructor:
    TimeSeries()
    TimeSeries( string name )
    TimeSeries( string name, Color color )
    [TimeSeries( string name, string title )
    TimeSeries( string name, string title, Color color )
methods:
    void Add( DateTime dateTime, double data )
    double Ago( int length )
    bool Contains( DateTime dateTime )
    virtual Cross Crosses( double level, Bar bar )
    virtual Cross Crosses( BarSeries series, Bar bar )
    virtual Cross Crosses( Indicator indicator, DateTime dateTime )
    virtual Cross Crosses( TimeSeries series, DateTime dateTime )
    virtual Cross Crosses( BarSeries series, Bar bar, BarData barData )
    virtual bool CrossesAbove( double level, Bar bar )
    virtual bool CrossesAbove( Indicator indicator, DateTime dateTime )
    virtual bool CrossesAbove( TimeSeries series, DateTime dateTime )
    virtual bool CrossesAbove( BarSeries series, Bar bar, BarData barData )
    virtual bool CrossesBelow( double level, Bar bar )
    virtual bool CrossesBelow( Indicator indicator, DateTime dateTime )
    virtual bool CrossesBelow( TimeSeries series, DateTime dateTime )
    virtual bool CrossesBelow( BarSeries series, Bar bar, BarData barData )
    double GetAsymmetry( DateTime dateTime1, DateTime dateTime2 )
    double GetAsymmetry( int index1, int index2 )
    double GetAutoCorrelation( int lag )
    double GetAutoCovariance( int lag )
    double GetCorrelation( TimeSeries timeSeries )
    double GetCovariance( TimeSeries timeSeries )
    DateTime GetDateTime( int index )
    double GetExcess( DateTime dateTime1, DateTime dateTime2 )
    double GetExcess( int index1, int index2 )
    int GetIndex( DateTime dateTime )
    double GetMax( DateTime dateTime1, DateTime dateTime2 )
    double GetMax( int index1, int index2 )
    double GetMean( DateTime dateTime1, DateTime dateTime2 )
    double GetMean( int index1, int index2 )
    double GetMedian( DateTime dateTime1, DateTime dateTime2 )
    double GetMedian( int index1, int index2 )
    double GetMin( DateTime dateTime1, DateTime dateTime2 )
    double GetMin( int index1, int index2 )
    double GetMoment( int k, DateTime dateTime1, DateTime dateTime2 )
    double GetMoment( int k, int index1, int index2 )
    double GetNegativeStdDev( DateTime dateTime1, DateTime dateTime2 )
    double GetNegativeStdDev( int index1, int index2 )
    double GetNegativeVariance( DateTime dateTime1, DateTime dateTime2 )
    double GetNegativeVariance( int index1, int index2 )
    double GetPositiveStdDev( DateTime dateTime1, DateTime dateTime2 )
    double GetPositiveStdDev( int index1, int index2 )
    double GetPositiveVariance( DateTime dateTime1, DateTime dateTime2 )
    double GetPositiveVariance( int index1, int index2 )
    double GetStdDev( DateTime dateTime1, DateTime dateTime2 )
    double GetStdDev( int index1, int index2 )
    double GetSum( DateTime dateTime1, DateTime dateTime2 )
    double GetSum( int index1, int index2 )
    double GetVariance( DateTime dateTime1, DateTime dateTime2 )
    double GetVariance( int index1, int index2 )
    void Remove( DateTime dateTime )
    void Remove( int index )
properties:
    Color Color { get; set; }
    int Count { get; }
     double this[ DateTime dateTime ] { get; }
     double this[ int index ] { get; }
     double this[ DateTime dateTime, BarData barData ] { get; }
     double this[ int index, BarData barData ] { get; }
     double Last { get; }
     string Name { get; }
     int Width { get; set; }
}

/* Trade数据包含了单一的成交价（和成交量）。这些价格会用来生成OHLCV(开高低收量)Bar */
class Trade
{
    constructor:
      Trade(DateTime dateTime, double price, int size)
    methods:
      string ToString()
    properties:
      DateTime DateTime { get; }
      double Price { get; }
      byte ProviderId { get; }
      int Size { get; }
}

class TradeSeries: IEnumerable
{
    constructor:
      TradeSeries()
    methods:
      void Add( Trade trade )
      BarSeries CompressBars( BarType barType, long barSize )

    properties:
      int Count { get; }
      Trade this[ int index ] { get; }
      Trade Last { get; }
}

class Transaction
{
    methods:
      string ToString()
    properties:
      double Cost { get; }
      DateTime DateTime { get; }
      Instrument Instrument { get; }
      double PnL { get; }
      double Price { get; }
      double Qty { get; }           //Math.Abs(Amount), Qty只表示数量，不含方向???
      TransactionSide Side { get; }
      string Text { get; }
}

class TransactionList: IEnumerable
{
methods:
    IEnumerator GetEnumerator()
properties:
    int Count { get; }
    Transaction this[ int index ] { get; }
}

enum TransactionSide
{
    Buy = 0
    Sell = 1
}

class UserCommand
{
    constructor:
      UserCommand( DateTime datetime, string text )
    properties:
      DateTime DateTime { get; private set;}
      string Text { get; private set; }
}

class IDE
{
methods:
	static void BuildSolution()
	static void CloseSolution()
	static bool OpenSolution( string name )
	static void StartScript( ScriptInfo scriptInfo )
	static void StartSolution()
	static void StopScript( ScriptInfo scriptInfo )
	static void StopSolution()
properties:
	static StrategyMode Mode { get; set; }
	static DirectoryInfo ProjectsDirectory { get; private set; }
	static Scenario Scenario { get; }
	static DirectoryInfo ScriptsDirectory { get; private set; }
	static Solution Solution { get; set; }
	static SolutionInfo SolutionInfo { get; }
	static DirectoryInfo SolutionsDirectory { get; private set; }
}

class Engine_InstrumentList: IEnumerable
{
methods:
	void Add( string symbol )
	void Add( Instrument instrument )
	void Clear()
	bool Contains( string name )
	IEnumerator GetEnumerator()
	void Remove( string symbol )
	void Remove( Instrument instrument )
	bool TryGetValue( string name, out Instrument instrument )
properties:
	int Count { get; }
	Instrument this[ string symbol ] { get; }
}

class Engine_Parameter
{
methods:
	Parameter( string name, Object value, Type type )
properties:
	string Name { get; set; }
	Type Type { get; private set; }
	Object Value { get; set; }
}

class class ParameterSet : IEnumerable
{
methods:
	bool Contains( string name )
	IEnumerator GetEnumerator()
	bool TryGetValue( string name, out Engine_Parameter parameter )
properties:
	int Count { get; }
	Engine_Parameter this[ string name ] { get; }
}

class Project
{
methods:
	void AddInstrument( string symbol )
	void AddInstrument( Instrument instrument )
	void ClearInstruments()
	void RemoveInstrument( string symbol )
	void RemoveInstrument( Instrument instrument )
properties:
	bool Enabled { get; set; }
	Engine_InstrumentList Instruments { get; private set; }
	string Name { get; private set; }
	ParameterSet Parameters { get; private set; }
	Performance Performance { get; private set; }
	Portfolio Portfolio { get; private set; }
	bool ReportEnabled { get; set; }
	Statistics Statistics { get; }
}

class ProjectInfo
{
properties:
	FileInfo CodeFile { get; private set; }
	string Name { get; private set; }
	FileInfo ProjectFile { get; private set; }
}

class ProjectInfoList : IEnumerable
{
methods:
    bool Contains( string name )
    IEnumerator GetEnumerator()
    bool TryGetValue( string name, out ProjectInfo project )
properties:
    int Count { get; }
    ProjectInfo this[ int index ] { get; }
    ProjectInfo this[ string name ] { get; }
}


class ProjectList : IEnumerable
{
methods:
    bool Contains( string name )
    IEnumerator GetEnumerator()
    bool TryGetValue( string name, out Project project )
properties:
    int Count { get; }
    Project this[ int index ] { get; }
    Project this[ string name ] { get; }
}

class Scenario
{
constructor:
    protected Scenario()
methods:
    virtual void Run()
    protected void Start()
    protected void Start( StrategyMode mode )
    protected void Stop()
properties:
    ExecutionProvider ExecutionProvider { get; }
    MarketDataProvider MarketDataProvider { get; }
    StrategyMode Mode { get; private set; }
    PortfolioPricer PortfolioPricer { set; }
    bool ResetOnStart { get; set; }
    Solution Solution { get; }
    bool StartOver { get; set; }
event:
    EventHandler StartRequested
    EventHandler StopRequested
}

class Solution
{
properties:
    double Cash { get; set; }
    string Name { get; private set; }
    Performance Performance { get; private set; }
    Portfolio Portfolio { get; private set; }
    ProjectList Projects { get; private set; }
    bool ReportEnabled { get; set; }
    DataRequests Requests { get; set; }
    DateTime StartDate { get; set; }
    Statistics Statistics { get; }
    DateTime StopDate { get; set; }
}

class SolutionInfo
{
properties:
    string Name { get; private set; }
    ProjectInfoList Projects { get; }
    FileInfo ScenarioFile { get; private set; }
    FileInfo SolutionFile { get; private set; }
}

class Statistics
{
properties:
    double AnnualReturn { get; }
    TimeSpan Duration { get; }
    double FinalWealth { get; }
    double InitialWealth { get; }
    int LongTrades { get; }
    double LongTradesPnL { get; }
    int LosingLongTrades { get; }
    int LosingShortTrades { get; }
    int LosingTrades { get; }
    double PnLPerLongTrade { get; }
    double PnLPerShortTrade { get; }
    double PnLPerTrade { get; }
    int ShortTrades { get; }
    double ShortTradesPnL { get; }
    double TotalPnL { get; }
    double TotalReturn { get; }
    int TotalTrades { get; }
    TimeSpan TransactionsFrequency { get; }
    int WinningLongTrades { get; }
    int WinningShortTrades { get; }
    int WinningTrades { get; }
}



// Plugin

class UserProvider
{
constructor:
    protected UserProvider()
fields:
    protected string description
    protected byte id
    protected bool isConnected
    protected string name
    protected string url
methods:
    protected virtual BrokerInfo GetBrokerInfo()

    protected virtual void Connect()
    protected virtual void Disconnect()
    protected virtual void Shutdown()

    protected void EmitConnected()
    protected void EmitDisconnected()
    protected void EmitError( string message )
    protected void EmitError( int id, int code, string message )


    /* 市场数据 */
    protected virtual void Subscribe( Instrument instrument )
    protected virtual void Unsubscribe( Instrument instrument )

    protected void EmitNewBar( Instrument instrument, BarType barType, long barSize, DateTime beginDateTime, DateTime endDateTime, double open, double high, double low, double close, long volume )
    protected void EmitNewBarOpen( Instrument instrument, BarType barType, long barSize, DateTime beginDateTime, DateTime endDateTime, double open, double high, double low, double close, long volume )
    protected void EmitNewBarSlice( long barSize )
    protected void EmitNewQuote( Instrument instrument, DateTime time, double bid, int bidSize, double ask, int askSize )
    protected void EmitNewQuote( Instrument instrument, DateTime time, byte providerId, double bid, int bidSize, double ask, int askSize )
    protected void EmitNewTrade( Instrument instrument, DateTime time, double price, int size )
    protected void EmitNewTrade( Instrument instrument, DateTime time, byte providerId, double price, int size )

    protected void EmitNewOrderBookUpdate( Instrument instrument, DateTime time, BidAsk side, OrderBookAction action, double price, int size, int position )

    /* 历史数据 */
    protected virtual void RequestHistoricalData( HistoricalDataRequest request )
    protected virtual void CancelHistoricalData( HistoricalDataRequest request )

    protected void EmitHistoricalDataCancelled( HistoricalDataRequest request )
    protected void EmitHistoricalDataCompleted( HistoricalDataRequest request )
    protected void EmitHistoricalDataError( HistoricalDataRequest request, string message )


    protected void EmitNewHistoricalBar( HistoricalDataRequest request, DateTime datetime, double open, double high, double low, double close, long volume )
    protected void EmitNewHistoricalQuote( HistoricalDataRequest request, DateTime datetime, double bid, int bidSize, double ask, int askSize )
    protected void EmitNewHistoricalTrade( HistoricalDataRequest request, DateTime datetime, double price, int size )

    /* 订单处理 */
    protected virtual void Send( Order order )
    protected virtual void Cancel( Order order )
    /* only change Qty Price  StopPrice  TrailingAmt */
    protected virtual void Replace( Order order, double newQty, double newPrice, double newStopPrice )

    /* 从数据结构的角度需要维护一个Order<----->Strategy的关系
    /*
     * Accepted ---> update Order Status ---> Stragecy_OnNewOrder
     *                                  ----> save order status change event
     *
     * Cancelled --> update Order Status ---> save order status change event ---> Strategy_OnOrderCanceled
     *
     * Filled --> update Order Status --> save order status change evnet --> new Transaction --> process account value ---> process Postion --> Strategy_OnPositionXXX
     *
     *
     */
    /* EmitAccepted When Order accepted by exchange */
    protected void EmitAccepted( Order order )
    protected void EmitCancelled( Order order )
    protected void EmitRejected( Order order, string message )
    protected void EmitReplaced( Order order )
    protected void EmitPendingCancel( Order order )
    protected void EmitCancelReject( Order order, OrderStatus status, string message )
    protected void EmitPendingReplace( Order order )
    protected void EmitReplaceReject( Order order, OrderStatus status, string message )
    protected void EmitFilled( Order order, double price, int quantity )
    protected void EmitFilled( Order order, double price, int quantity, CommissionType commissionType, double commission )

properties:
    protected virtual bool IsConnected { get; }
}

class UserIndicator : Indicator
{
constructor:
    UserIndicator( ISeries input )
methods:
    override double Ago( int n )
    virtual double Calculate( int index )

    override bool Contains( DateTime dateTime )
    override bool Contains( Bar bar )

    override Cross Crosses( BarSeries series, Bar bar )
    override Cross Crosses( Indicator indicator, Bar bar )

    override bool CrossesAbove( BarSeries series, Bar bar )
    override bool CrossesAbove( Indicator indicator, Bar bar )

    override bool CrossesBelow( BarSeries series, Bar bar )
    override bool CrossesBelow( Indicator indicator, Bar bar )

    override DateTime GetDateTime( int index )
    void Init()

properties:
    override int Count { get; }
    override DateTime FirstDateTime { get; }
    ISeries Input { get; }
    override double this[ DateTime dateTime ] { get; }
    override double this[ int index ] { get; }
    override double this[ Bar bar ] { get; }
    override double this[ DateTime dateTime, BarData barData ] { get; }
    override double this[ int index, BarData barData ] { get; }
    override double Last { get; }
    override DateTime LastDateTime { get; }
    string Name { get; set; }
}
